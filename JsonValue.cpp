//
// Created by zeno on 29.07.2024.
//

#include <stdexcept>
#include "JsonValue.h"
#include <cmath>


char* JsonValue::asString() const {
    if (rawJson[startIndex] != '"') throw std::invalid_argument("Json value is not of type string.");
    char *str = static_cast<char *>(malloc(
            endIndex - startIndex)); // please don't ask why this works, I am too lazy to explain
    memcpy(str, rawJson + startIndex + 1, endIndex - startIndex);
    str[endIndex - startIndex - 1] = 0;
    return str;
}

double JsonValue::asDouble() const {
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

int JsonValue::asInt() const{
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

bool JsonValue::asBool() const{
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