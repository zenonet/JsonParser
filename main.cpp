#include <iostream>
#include <cstring>
#include "cmath"

struct JsonValue {
    char *rawJson;
    int startIndex;
    int endIndex;

    char *asString() const {
        if (rawJson[startIndex] != '"') throw std::invalid_argument("Json value is not of type string.");
        char *str = static_cast<char *>(malloc(
                endIndex - startIndex)); // please don't ask why this works, I am too lazy to explain
        memcpy(str, rawJson + startIndex + 1, endIndex - startIndex);
        str[endIndex - startIndex - 1] = 0;
        return str;
    }

    double asDouble() const {
        int i = startIndex;
        if (rawJson[i] >= 48 && rawJson[i] <= 57 || rawJson[i] == '-')
        {
            double number = 1;
            // Find the sign of the number and increment i if there's a negative sign in front
            signed char sign = rawJson[i] == '-' ? -1 + (0 * i++) : 1;

            number *= rawJson[i] - 48;
            int pointIndex = -1;
            for (i++; i <= endIndex && (isdigit(rawJson[i]) || rawJson[i] == '.'); i++)
            {
                if (rawJson[i] == '.')
                {
                    if (pointIndex != -1) throw std::invalid_argument("Second decimal point in number in JSON");
                    pointIndex = i;
                    continue;
                }

                if (pointIndex != -1)
                    number += (rawJson[i] - '0') / pow(10, i - pointIndex);
                else
                    number = number * 10 + rawJson[i] - '0';
            }
            if(i-1 != endIndex) throw std::invalid_argument("JSON value is not a double");

            return number * sign;
        }

        throw std::invalid_argument("JSON value is not a number");
    }

    int asInt() const{
        int i = startIndex;
        if (rawJson[i] >= 48 && rawJson[i] <= 57 || rawJson[i] == '-')
        {
            double number = 1;
            // Find the sign of the number and increment i if there's a negative sign in front
            signed char sign = rawJson[i] == '-' ? -1 + (0 * i++) : 1;

            number *= rawJson[i] - 48;
            for (i++; i <= endIndex && (isdigit(rawJson[i])); i++)
            {
                number = number * 10 + rawJson[i] - '0';
            }

            if(i-1 != endIndex) throw std::invalid_argument("JSON value is not an integer");
            return number * sign;
        }

        throw std::invalid_argument("JSON value is not an int");
    }

    bool asBool() const{
        const char t[] = "true";
        for (int i = 0;i <= endIndex-startIndex; i++){
            if(t[i] != rawJson[startIndex+i] || endIndex-startIndex+2 != sizeof t) goto falseCheck;
        }
        return true;

        falseCheck:
        const char f[] = "false";
        for (int i = 0;i <= endIndex-startIndex; i++){
            if(f[i] != rawJson[startIndex+i] || endIndex-startIndex+2 != sizeof f) throw std::invalid_argument("JSON value is not a bool");
        }
        return false;
    }

};

struct JsonElement {
    char *rawJson;
    int startIndex;
    int endIndex;

    JsonElement getJsonObject(char *name) {
        std::cout << startIndex;
    }

    JsonValue getValue(char *name) {
        for (int i = startIndex; i <= endIndex; i++) {
            skipWhitespace(rawJson, i, endIndex);

            int nameStartIndex = i + 1;
            int nameLength = getStringLiteralLengthAndSkip(rawJson, i, endIndex);

            skipWhitespace(rawJson, i, endIndex);
            if (rawJson[i++] != ':') throw std::invalid_argument("Expected colon after property name in JSON");
            skipWhitespace(rawJson, i, endIndex);

            if (strcmp(rawJson + nameStartIndex, name, nameLength)) {
                JsonValue val{};
                val.rawJson = rawJson;
                val.startIndex = i;
                skipJsonValue(rawJson, i, endIndex);
                val.endIndex = i - 1;
                return val;
            }

            skipJsonValue(rawJson, i, endIndex);

            if (rawJson[i] != ',' && rawJson[i] != '}')
                throw std::invalid_argument("Expecting comma after property in JSON");
        }
        return JsonValue();
    }

    JsonElement(char *rawJson) {
        this->rawJson = rawJson;
        startIndex = 0;
        endIndex = strlen(rawJson) - 1;

        // Cut out the outer curly braces
        if (rawJson[startIndex++] != '{')
            throw std::invalid_argument("JSON source does not start with '{'");
        if (rawJson[endIndex--] != '}')
            throw std::invalid_argument("JSON source does not end with '}'");
    }

private:
    JsonElement(char *rawJson, int start, int end) {
        this->rawJson = rawJson;
        startIndex = start;
        endIndex = end;
    }

    void skipWhitespace(char *source, int &i, int endIndex) {
        for (; i <= endIndex && iswspace(source[i]); i++) {}
    }

    int getStringLiteralLengthAndSkip(char *source, int &i, int endIndex) {
        if (source[i++] != '"') throw std::invalid_argument("String literal does not start with quotation marks.");
        int len = 0;
        for (; i <= endIndex && source[i] != '\"'; i++, len++) {
            // Allow escaping quotation marks
            if (source[i] == '\\' && i < endIndex) i++;
        }
        if (source[i++] != '\"') throw std::invalid_argument("String literal does not end with quotation marks.");
        return len;
    }

    void skipJsonValue(char *source, int &i, int endIndex) {
        if (source[i] == '{' || source[i] == '[') {
            // Analyze brace pattern

        } else {
            // Skip to the next comma
            for (; i <= endIndex && source[i] != ','; i++) {}
        }

    }

    static bool strcmp(char *a, char *b, int length) {
        for (int i = 0; i < length; i++) {
            if (a[i] != b[i]) return false;
        }
        return true;
    }
};


int main() {
    char *rawJson = (char *) R"({"yeet":16, "yote":-25.2, "huh":truee})";
    JsonElement element(rawJson);
    JsonValue val = element.getValue("huh");
    std::cout << val.asBool() << '\n';
    return 0;
}
