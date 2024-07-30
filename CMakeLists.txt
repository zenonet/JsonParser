cmake_minimum_required(VERSION 3.28)
project(JsonParser)

set(CMAKE_CXX_STANDARD 17)

add_library(JsonParserLib STATIC
        JsonObject.cpp
        JsonObject.h

        JsonArray.cpp
        JsonArray.h

        JsonValue.cpp
        JsonValue.h)

add_executable(Example main.cpp)
target_link_libraries(Example JsonParserLib)  # Important to place before add_custom_target
