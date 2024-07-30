#include <iostream>
#include <cstring>

#include "JsonArray.h"


int main() {

    char *sourceJson = (char *) R"({"obsessions":["parser creation", "karate"], "idol":{"name": "Marcell D'Avis", "age": 42}, "foo":[{"bar":{"buzz":16}}]}})";
    JsonObject obj(sourceJson);

    // Now, you can query get data from the JSON in fluent syntax:
    char *idolName = obj
            .getJsonObject("idol")
            .getValue("name")
            .asString();
    int idolAge = obj
            .getJsonObject("idol")
            .getValue("age")
            .asInt();
    char* mainObsession = obj
            .getJsonArray("obsessions")
            .getValue(0)
            .asString();

    int num = obj
            .getJsonArray("foo")
            .getJsonObject(0)
            .getJsonObject("bar")
            .getValue("buzz")
            .asInt();

    std::cout << idolName << '\n';
    std::cout << idolAge << '\n';
    std::cout << mainObsession << '\n';
    std::cout << num << '\n';
    /*
    char *rawJson = (char *) R"(["yeet",{"karsten":16}, [16,1,2]])";
    JsonArray element(rawJson);
    std::cout << element.count() << '\n';
    std::cout << element.getJsonObject(1).has("karste") << '\n';
    std::cout << element.getJsonObject(1).getValue("karsten").asInt() << '\n';
    std::cout << element.getValue(0).asString() << '\n';
    std::cout << element.getJsonArray(2).getValue(1).asInt() << '\n';
    return 0;*/
}
