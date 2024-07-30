//
// Created by zeno on 29.07.2024.
//

#ifndef JSONPARSER_JSONOBJECT_H
#define JSONPARSER_JSONOBJECT_H


#include "JsonArray.h"
#include "JsonValue.h"

struct JsonArray;
/// Represents an object/dictionary in JSON encoded data.
struct JsonObject {
    JsonObject(char *rawJson);

    JsonObject(char *rawJson, int start, int end);

    char *rawJson;
    int startIndex;
    int endIndex;

    /// Gets a value from a property of this Json object by it's property name
    JsonValue getValue(char *name);

    /// Gets a json object from a property of this Json object by it's property name
    JsonObject getJsonObject(char *name);

    /// Gets a json array from a property of this Json object by it's property name
    JsonArray getJsonArray(char *name);

    /// Checks if the JsonObject contains a property of a certain name
    bool has(char* propertyName);
};

#endif //JSONPARSER_JSONOBJECT_H
