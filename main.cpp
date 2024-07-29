#include <iostream>
#include <cstring>

struct JsonValue{
    char* rawJson;
    int startIndex;
    int endIndex;

    char* asString() const{
        char* str = static_cast<char *>(malloc(endIndex - startIndex));
        memcpy(str, rawJson+startIndex, endIndex-startIndex);
        return str;
    }
};

struct JsonElement{
    char* rawJson;
    int startIndex;
    int endIndex;

    JsonElement getJsonObject(char* name){
        std::cout << startIndex;
    }

    JsonValue getValue(char* name){
        for(int i=startIndex; i<=endIndex;i++){
            skipWhitespace(rawJson, i, endIndex);

            int nameStartIndex = i+1;
            int nameLength = getStringLiteralLengthAndSkip(rawJson, i, endIndex);
            if(strcmp(rawJson+nameStartIndex, name, nameLength)){
                std::cout << "Found property: " << name << "\n";
                break;
            }
            skipWhitespace(rawJson, i, endIndex);
            if(rawJson[i++] != ':') throw std::invalid_argument("Expected colon after property name in JSON");
            skipWhitespace(rawJson, i, endIndex);

            skipJsonValue(rawJson, i, endIndex);

            if(rawJson[i] != ',' && rawJson[i] != '}') throw std::invalid_argument("Expecting comma after property in JSON");
        }
        return JsonValue();
    }

    JsonElement(char* rawJson){
        this->rawJson = rawJson;
        startIndex = 0;
        endIndex = strlen(rawJson)-1;

        // Cut out the outer curly braces
        if(rawJson[startIndex++] != '{')
            throw std::invalid_argument("JSON source does not start with '{'");
        if(rawJson[endIndex--] != '}')
            throw std::invalid_argument("JSON source does not end with '}'");
    }
private:
    JsonElement(char* rawJson, int start, int end){
        this->rawJson = rawJson;
        startIndex = start;
        endIndex = end;
    }
    void skipWhitespace(char* source, int& i, int endIndex){
        for(;i<=endIndex && iswspace(source[i]);i++){}
    }

    int getStringLiteralLengthAndSkip(char* source, int& i, int endIndex){
        if(source[i++] != '\"') throw std::invalid_argument("String literal does not start with quotation marks.");
        int len = 0;
        for(;i<=endIndex && source[i] != '\"';i++,len++){
            // Allow escaping quotation marks
            if(source[i] == '\\' && i < endIndex) i++;
        }
        if(source[i++] != '\"') throw std::invalid_argument("String literal does not end with quotation marks.");
        return len;
    }

    void skipJsonValue(char* source, int& i, int endIndex){
        if(source[i] == '{' || source[i] == '['){
            // Analyze brace pattern

        }else{
            // Skip to the next comma
            for(;i<=endIndex && source[i] != ',';i++){}
        }

    }

    static bool strcmp(char* a, char* b, int length){
        for(int i=0; i<length; i++){
            if(a[i] != b[i]) return false;
        }
        return true;
    }
};


int main() {
    char* rawJson = (char*)"{\"yeet\":16, \"yote\":25}";
    JsonElement element(rawJson);
    JsonValue val = element.getValue("yote");
    return 0;
}
