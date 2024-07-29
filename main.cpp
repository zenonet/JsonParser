#include <iostream>
#include <cstring>


struct JsonElement{
    char* rawJson;
    int startIndex;
    int endIndex;

    JsonElement getJsonObject(char* name){
        std::cout << startIndex;
    }

    char* getString(char* name){
        for(int i=0; i<=endIndex;i++){
            skipWhitespace(rawJson, i, endIndex);
        }
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
        while(i<endIndex && iswspace(source[i])){
            i++;
        }
    }
};

int main() {
    char* rawJson = (char*)"{\"yeet\":16}";
    JsonElement element(rawJson);
    return 0;
}
