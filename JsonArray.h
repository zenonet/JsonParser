//
// Created by zeno on 29.07.2024.
//

#ifndef JSONPARSER_JSONARRAY_H
#define JSONPARSER_JSONARRAY_H

#include "JsonObject.h"
#include "JsonValue.h"

struct JsonObject;
struct JsonArray {
    JsonArray(char *rawJson, int start, int end);
    JsonArray(char *rawJson);

    char *rawJson;
    int startIndex;
    int endIndex;

    JsonObject *getJsonObject(int index);

    JsonArray *getJsonArray(int index);

    JsonValue getValue(int index);
};

#endif //JSONPARSER_JSONARRAY_H
