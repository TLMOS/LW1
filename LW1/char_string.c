#include <stdlib.h>
#include <stdint.h>
#include "string.h"
#include "char_string.h"

void* zero = NULL;

struct String* createZerosChar(size_t size) {
	if (!zero)
	{
		zero = malloc(sizeof(char));
		*(char*)zero = ' ';
	}
	return createZeros(size, sizeof(char), zero);
}

struct String* createFromValuesChar(size_t size, char* values) {
	if (!zero)
	{
		zero = malloc(sizeof(char));
		*(char*)zero = ' ';
	}
	return createFromValues(size, sizeof(char), zero, (void*)values);
}

char getChar(struct String* s, size_t i) {
	return *(char*)getPointer(s, i);
}

char* getChars(struct String* s) {
	char* values = malloc(getSize(s) * sizeof(char));
	for (int i = 0; i < getSize(s); i++)
		values[i] = getChar(s, i);
	return values;
}

void setChar(struct String* s, size_t i, char c) {
	set(s, i, (void*)&c);
}

void fillChar(struct String* s, char c) {
	fill(s, &c);
}