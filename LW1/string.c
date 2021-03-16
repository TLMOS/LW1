#include "string.h"
#include <stdlib.h>
#include <stdint.h>

struct String {
	size_t size;
	size_t element_size;
	void* values;
	void* zero;
};

struct String* createZeros(size_t size, size_t element_size, void* zero) {
	struct String* s = malloc(sizeof(struct  String));
	s->size = size;
	s->element_size = element_size;
	s->zero = zero;
	s->values = malloc(element_size * size);
	for (int i = 0; i < size; i++) {
		int8_t* dest = (int8_t*)s->values + i * element_size;
		memcpy((void*)dest, zero, element_size);
	}
	return s;
}

struct String* createFromValues(size_t size, size_t element_size, void* zero, void* values) {
	struct String* s = malloc(sizeof(struct  String));
	s->size = size;
	s->element_size = element_size;
	s->zero = zero;
	s->values = malloc(element_size * size);
	memcpy(s->values, values, size * element_size);
	return s;
}

size_t getSize(struct String* s) {
	return s->size;
}

void* get(struct String* s, size_t i) {
	void* x = malloc(s->element_size);
	int8_t* src = (int8_t*)s->values + i * s->element_size;
	memcpy(x, (void*)src, s->element_size);
	return x;
}

void* getPointer(struct String* s, size_t i) {
	int8_t* p = (int8_t*)s->values + i * s->element_size;
	return p;
}

void set(struct String* s, size_t i, void* value) {
	int8_t* dest = (int8_t*)s->values + i * s->element_size;
	memcpy((void*)dest, value, s->element_size);
}

struct String* copy(struct String* s) {
	return createFromValues(s->size, s->element_size, s->zero, s->values);
}

void freeString(struct String* s) {
	free(s->values);
	free(s);
}

int equals(struct String* s1, struct String* s2) {
	if (s1->size == s2->size
		&& s1->element_size == s2->element_size
		&& s1->zero == s2->zero) {
		int result = 1;
		for (int i = 0; i < s1->size; i++) {
			int8_t* a = (int8_t*)s1->values + i;
			int8_t* b = (int8_t*)s2->values + i;
			if (*a != *b) {
				result = 0;
				break;
			}
		}
		return result;
	}
	else
		return 0;
}

void fill(struct String* s, void* value) {
	for (int i = 0; i < s->size; i++) {
		int8_t* dest = (int8_t*)s->values + i * s->element_size;
		memcpy((void*)dest, value, s->element_size);
	}
}

void swap(struct String* s, size_t i, size_t j) {
	void* tmp = malloc(s->element_size);
	int8_t* a = (int8_t*)s->values + i * s->element_size;
	int8_t* b = (int8_t*)s->values + j * s->element_size;
	memcpy((void*)tmp, (void*)a, s->element_size);
	memcpy((void*)a, (void*)b, s->element_size);
	memcpy((void*)b, (void*)tmp, s->element_size);
	free(tmp);
}

void reverse(struct String* s) {
	void* tmp = malloc(s->element_size);
	for (int i = 0; i < s->size / 2; i++) {
		int8_t* a = (int8_t*)s->values + i * s->element_size;
		int8_t* b = (int8_t*)s->values + (s->size - i - 1) * s->element_size;
		memcpy((void*)tmp, (void*)a, s->element_size);
		memcpy((void*)a, (void*)b, s->element_size);
		memcpy((void*)b, (void*)tmp, s->element_size);
	}
	free(tmp);
}

struct String* reversed(struct String* s) {
	struct String* rev = copy(s);
	reverse(rev);
	return rev;
}

struct String* concatenate(struct String* s1, struct String* s2) {
	size_t size = s1->size + s2->size;
	size_t element_size = s1->element_size;
	void* zero = s1->zero;

	if (s1->element_size == s2->element_size){
		void* values = malloc(size * element_size);
		memcpy(values, s1->values, s1->size * element_size);
		int8_t* p = (int8_t*)values + s1->size * element_size;
		memcpy((void*)p, s2->values, s2->size * element_size);
		struct String* s3 = createFromValues(size, element_size, zero, values);
		return s3;
	}
	else {
		// do smth about error
	}
}

struct String* subString(struct String* s, size_t i, size_t j) {
	size_t size = j - i + 1;
	void* values = malloc(size * s->element_size);
	int8_t* p = (int8_t*)s->values + i * s->element_size;
	memcpy(values, (void*)p, size * s->element_size);
	struct String* s_sub = createFromValues(size, s->element_size, s->zero, values);
	return s_sub;
}

void encode(struct String* s, void* (*f)(void* x)) {
	for (int i = 0; i < s->size; i++) {
		set(s, i, f(get(s, i)));
	}
}