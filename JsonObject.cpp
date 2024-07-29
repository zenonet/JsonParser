//
// Created by zeno on 29.07.2024.
//

#include <stdexcept>
#include <cstring>
#include "JsonObject.h"
#include "JsonValue.h"
#include "JsonArray.h"
#include "ParsingUtils.cpp"


JsonValue JsonObject::getValue(char *name) {
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
    throw std::invalid_argument(
            "JSON Element does not contain a property with that name"); // I am too lazy to interpolate the name of the property in there, sorry
}

JsonObject JsonObject::getJsonObject(char *name) {
    for (int i = startIndex; i <= endIndex; i++) {
        skipWhitespace(rawJson, i, endIndex);

        int nameStartIndex = i + 1;
        int nameLength = getStringLiteralLengthAndSkip(rawJson, i, endIndex);

        skipWhitespace(rawJson, i, endIndex);
        if (rawJson[i++] != ':') throw std::invalid_argument("Expected colon after property name in JSON");
        skipWhitespace(rawJson, i, endIndex);

        if (strcmp(rawJson + nameStartIndex, name, nameLength)) {
            JsonObject element(rawJson, i + 1, 0);
            skipJsonValue(rawJson, i, endIndex);
            element.endIndex = i - 2;
            return element;
        }

        skipJsonValue(rawJson, i, endIndex);

        if (rawJson[i] != ',' && rawJson[i] != '}')
            throw std::invalid_argument("Expecting comma after property in JSON");
    }
    throw std::invalid_argument("JSON Element does not contain a property with that name");
}

JsonArray JsonObject::getJsonArray(char *name) {
    for (int i = startIndex; i <= endIndex; i++) {
        skipWhitespace(rawJson, i, endIndex);

        int nameStartIndex = i + 1;
        int nameLength = getStringLiteralLengthAndSkip(rawJson, i, endIndex);

        skipWhitespace(rawJson, i, endIndex);
        if (rawJson[i++] != ':') throw std::invalid_argument("Expected colon after property name in JSON");
        skipWhitespace(rawJson, i, endIndex);

        if (strcmp(rawJson + nameStartIndex, name, nameLength)) {
            JsonArray array(rawJson, i + 1, 0);
            skipJsonValue(rawJson, i, endIndex);
            array.endIndex = i - 2;
            return array;
        }

        skipJsonValue(rawJson, i, endIndex);

        if (rawJson[i] != ',' && rawJson[i] != '}')
            throw std::invalid_argument("Expecting comma after property in JSON");
    }
    throw std::invalid_argument("JSON Element does not contain a property with that name");
}

JsonObject::JsonObject(char *rawJson) {
    this->rawJson = rawJson;
    startIndex = 0;
    endIndex = strlen(rawJson) - 1;

    // Cut out the outer curly braces
    if (rawJson[startIndex++] != '{')
        throw std::invalid_argument("JSON object source does not start with '{'");
    if (rawJson[endIndex--] != '}')
        throw std::invalid_argument("JSON object source does not end with '}'");
}

JsonObject::JsonObject(char *rawJson, int start, int end) {
    this->rawJson = rawJson;
    startIndex = start;
    endIndex = end;
}

