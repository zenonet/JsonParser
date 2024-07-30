//
// Created by zeno on 29.07.2024.
//

#include <stdexcept>
#include <cstring>
#include "../JsonParserConsumer/libs/JsonArray.h"
#include "../JsonParserConsumer/libs/JsonObject.h"
#include "../JsonParserConsumer/libs/JsonValue.h"
#include "ParsingUtils.cpp"

JsonValue JsonArray::getValue(int index) {
    int currentIndex = 0;

    for (int i = startIndex; i <= endIndex; i++) {
        skipWhitespace(rawJson, i, endIndex);

        if (index == currentIndex) {
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
        currentIndex++;
    }
    throw std::invalid_argument("JSON Element does not contain a property with that name"); // I am too lazy to interpolate the name of the property in there, sorry
}

JsonObject JsonArray::getJsonObject(int index) {
    int currentIndex = 0;
    for (int i = startIndex; i <= endIndex; i++) {
        skipWhitespace(rawJson, i, endIndex);

        if (currentIndex == index) {
            JsonObject object(rawJson, i + 1, 0);
            skipJsonValue(rawJson, i, endIndex);
            object.endIndex = i - 2;
            return object;
        }

        skipJsonValue(rawJson, i, endIndex);
        currentIndex++;
        if (rawJson[i] != ',' && rawJson[i] != ']')
            throw std::invalid_argument("Expecting comma after array element in JSON.");
    }
    throw std::invalid_argument("Index out of bounds in JSON array.");
}

JsonArray JsonArray::getJsonArray(int index) {
    int currentIndex = 0;
    for (int i = startIndex; i <= endIndex; i++) {
        skipWhitespace(rawJson, i, endIndex);

        if (currentIndex == index) {
            JsonArray array(rawJson, i + 1, 0);
            skipJsonValue(rawJson, i, endIndex);
            array.endIndex = i - 2;
            return array;
        }

        skipJsonValue(rawJson, i, endIndex);
        currentIndex++;
        if (rawJson[i] != ',' && rawJson[i] != ']')
            throw std::invalid_argument("Expecting comma after array element in JSON.");
    }
    throw std::invalid_argument("Index out of bounds in JSON array.");
}

JsonArray::JsonArray(char *rawJson) {
    this->rawJson = rawJson;
    startIndex = 0;
    endIndex = strlen(rawJson) - 1;

    // Cut out the outer curly braces
    if (rawJson[startIndex++] != '[')
        throw std::invalid_argument("JSON array source does not start with '['");
    if (rawJson[endIndex--] != ']')
        throw std::invalid_argument("JSON array source does not end with ']'");
}

JsonArray::JsonArray(char *rawJson, int start, int end) {
    this->rawJson = rawJson;
    startIndex = start;
    endIndex = end;
}