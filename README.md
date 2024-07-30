# JSON Parser

This is a JSON Parser I built from scratch in C++ to familiarize with the language. It exclusively uses C style strings (`char*`).<br>
The library contains three main header files:

 - `JsonObject.h`
 - `JsonArray.h`
 - `JsonValue.h`

and their respective .cpp source files.
Additionally, the source files need to access shared functions in `ParsingUtils.cpp`.

## Example

You can load a json string by creating a new instance of `JsonObject` like this:
```cpp
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
```

