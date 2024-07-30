//
// Created by zeno on 29.07.2024.
//

#ifndef JSONPARSER_JSONARRAY_H
#define JSONPARSER_JSONARRAY_H

#include "JsonObject.h"
#include "JsonValue.h"

struct JsonObject;
/// Represents an array in json encoded data
struct JsonArray {
    JsonArray(char *rawJson, int start, int end);
    JsonArray(char *rawJson);

    char *rawJson;
    int startIndex;
    int endIndex;

    /// Gets a json object from an index in this json array
    JsonObject getJsonObject(int index);

    /// Gets a json array from an index in this json array
    JsonArray getJsonArray(int index);

    /// Gets a value from an index in this json array
    JsonValue getValue(int index);

    /// Counts the elements of this array and returns the count
    int count();
};

#endif //JSONPARSER_JSONARRAY_H
