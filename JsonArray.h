//
// Created by zeno on 29.07.2024.
//

#ifndef JSONPARSER_JSONARRAY_H
#define JSONPARSER_JSONARRAY_H

#include "JsonObject.h"
#include "JsonValue.h"

struct JsonArray {
    JsonArray(char *rawJson, int start, int end);
    JsonArray(char *rawJson);

    char *rawJson;
    int startIndex;
    int endIndex;

    JsonValue getValue(int index);

    JsonArray getJsonArray(int index);

    JsonObject getJsonObject(int index);

};

#endif //JSONPARSER_JSONARRAY_H
