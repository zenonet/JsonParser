//
// Created by zeno on 29.07.2024.
//

#ifndef JSONPARSER_JSONVALUE_H
#define JSONPARSER_JSONVALUE_H


struct JsonValue {
    char *rawJson;
    int startIndex;
    int endIndex;

    char *asString() const;
    double asDouble() const;
    bool asBool() const;
    int asInt() const;
};


#endif //JSONPARSER_JSONVALUE_H
