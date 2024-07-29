cmake_minimum_required(VERSION 3.28)
project(JsonParser)

set(CMAKE_CXX_STANDARD 17)

add_executable(JsonParser main.cpp
        main.h
        JsonObject.cpp
        JsonObject.h
        JsonArray.cpp
        JsonArray.h
        JsonValue.cpp
        JsonValue.h
        ParsingUtils.cpp)
