#pragma once
#include <stdlib.h>

struct String* createZerosChar(size_t size);
struct String* createFromValuesChar(size_t size, char* values);

char getChar(struct String* s, size_t i);
char* getChars(struct String* s);
void setChar(struct String* s, size_t i, char c);

void fillChar(struct String* s, char c);