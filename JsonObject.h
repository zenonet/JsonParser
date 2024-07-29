//
// Created by zeno on 29.07.2024.
//

#ifndef JSONPARSER_JSONOBJECT_H
#define JSONPARSER_JSONOBJECT_H


#include "JsonArray.h"
#include "JsonValue.h"

struct JsonObject {
    JsonObject(char *rawJson);

    JsonObject(char *rawJson, int start, int end);

    char *rawJson;
    int startIndex;
    int endIndex;

    JsonArray getJsonArray(char *name);
    JsonObject getJsonObject(char *name);

    JsonValue getValue(char *name);
};


#endif //JSONPARSER_JSONOBJECT_H
