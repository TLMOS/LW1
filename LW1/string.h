#pragma once
#include <stdlib.h>

struct String;

struct String* createZeros(size_t size, size_t element_size, void* zero);
struct String* createFromValues(size_t size, size_t element_size, void* zero, void* values);

size_t getSize(struct String* s);
void* get(struct String* s, size_t i);
void* getPointer(struct String* s, size_t i);
void set(struct String* s, size_t i, void* value);

struct String* copy(struct String* s);
void freeString(struct String* s);

int equals(struct String* s1, struct String* s2);

void fill(struct String* s, void* value);

void swap(struct String* s, size_t i, size_t j);
void reverse(struct String* s);
struct String* reversed(struct String* s);

struct String* concatenate(struct String* s1, struct String* s2);
struct String* subString(struct String* s, size_t i, size_t j);

void encode(struct String* s, void* (*f)(void* x));