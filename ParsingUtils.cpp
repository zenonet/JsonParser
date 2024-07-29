//
// Created by zeno on 29.07.2024.
//

#include <cctype>
#include <stdexcept>

static void skipWhitespace(char *source, int &i, int endIndex) {
    for (; i <= endIndex && iswspace(source[i]); i++) {}
}

static int getStringLiteralLengthAndSkip(char *source, int &i, int endIndex) {
    if (source[i++] != '"') throw std::invalid_argument("String literal does not start with quotation marks.");
    int len = 0;
    for (; i <= endIndex && source[i] != '\"'; i++, len++) {
        // Allow escaping quotation marks
        if (source[i] == '\\' && i < endIndex) i++;
    }
    if (source[i++] != '\"') throw std::invalid_argument("String literal does not end with quotation marks.");
    return len;
}

static void skipJsonValue(char *source, int &i, int endIndex) {
    if (source[i] == '{' || source[i] == '[') {
        // Analyze brace pattern
        char openingBracket = source[i];
        char closingBracket = openingBracket == '{' ? '}' : ']';
        i++;
        int bracketsOpened = 1;

        for(;i <= endIndex && bracketsOpened > 0;i++){
            if(source[i] == openingBracket) bracketsOpened++;
            if(source[i] == closingBracket) bracketsOpened--;
        }
        skipWhitespace(source, i, endIndex);

    } else {
        // Skip to the next comma
        for (; i <= endIndex && source[i] != ','; i++) {}
    }

}

static bool strcmp(char *a, char *b, int length) {
    for (int i = 0; i < length; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}