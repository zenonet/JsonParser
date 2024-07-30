//
// Created by zeno on 29.07.2024.
//

#ifndef JSONPARSER_JSONOBJECT_H
#define JSONPARSER_JSONOBJECT_H


#include "JsonArray.h"
#include "JsonValue.h"

struct JsonArray;
struct JsonObject {
    JsonObject(char *rawJson);

    JsonObject(char *rawJson, int start, int end);

    char *rawJson;
    int startIndex;
    int endIndex;

    JsonValue getValue(char *name);

    JsonObject getJsonObject(char *name);

    JsonArray getJsonArray(char *name);
};

#endif //JSONPARSER_JSONOBJECT_H
