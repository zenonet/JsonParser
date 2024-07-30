//
// Created by zeno on 29.07.2024.
//

#ifndef JSONPARSER_JSONVALUE_H
#define JSONPARSER_JSONVALUE_H

/// Represents a value of any primitive type in json encoded data
struct JsonValue {
    char *rawJson;
    int startIndex;
    int endIndex;

    /// Decodes the value to a C-style string (null terminated char*). If the value is not a string, throws an invalid argument exception.
    char *asString() const;

    /// Decodes the value to a double. If the value is not a double, throws an invalid argument exception.
    double asDouble() const;

    /// Decodes the value to a bool value. If the value is not a bool, throws an invalid argument exception.
    bool asBool() const;

    /// Decodes the value to an integer value. If the value is not an integer, throws an invalid argument exception.
    int asInt() const;
};


#endif //JSONPARSER_JSONVALUE_H
