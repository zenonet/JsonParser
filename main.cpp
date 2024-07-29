#include <iostream>
#include <cstring>
#include "cmath"
#include "main.h"
#include "JsonArray.h"
#include "JsonObject.h"


int main() {
    char *rawJson = (char *) R"(["yeet",{"karsten":16}, [16,1,2]])";
    JsonArray element(rawJson);
    std::cout << element.getJsonObject(1).getValue("karsten").asInt() << '\n';
    std::cout << element.getValue(0).asString() << '\n';
    std::cout << element.getJsonArray(2).getValue(1).asInt() << '\n';
    return 0;
}
