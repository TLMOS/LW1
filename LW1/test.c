#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <conio.h>
#include "string.h"
#include "char_string.h"

int autoTestCreateAndGet(int n_tests, size_t max_size, unsigned int seed) {
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("\nCreateAndGet autotest:\n");
	printf("Info: Starting CreateAndGet autotest on seed %d.\n", seed);
	int result = 1;

	size_t size;
	size_t element_size = sizeof(int);
	int zero = 0;
	struct String* s;

	//Randomly Test createZeros
	for (int test_i = 0; test_i < n_tests; test_i++) {
		size = rand(max_size);
		s = createZeros(size, element_size, (void*)&zero);
		//Size mismatch check
		if (getSize(s) != size) {
			printf("Error: Size mismatch in createZeros on random values. ");
			printf("Expected %d, got %d.\n", size, getSize(s));
			result = 0;
		}
		//Value mismatch check
		for (int i = 0; i < size; i++) {
			int* x = (int*)get(s, i);
			if (*x != zero) {
				printf("Error: Value mismatch in createZeros on random values. ");
				printf("Expected %d, got %d.\n", zero, *x);
				result = 0;
				free(x);
				break;
			}
			free(x);
		}
		freeString(s);
		if (!result)
			break;
	}

	//Randomly test createFromValues
	for (int test_i = 0; test_i < n_tests; test_i++) {
		size = rand(max_size);
		int* values = malloc(size * sizeof(int));
		for (int i = 0; i < size; i++)
			values[i] = rand();
		s = createFromValues(size, element_size, (void*)&zero, (void*)values);
		//Size mismatch check
		if (getSize(s) != size) {
			printf("Error: Size mismatch in createFromValues on random values. ");
			printf("Expected %d, got %d.\n", size, getSize(s));
			result = 0;
		}
		//Value mismatch check
		for (int i = 0; i < size; i++){
			int* x = (int*)get(s, i);
			if (*x != values[i]) {
				printf("Error: Value mismatch in createFromValues on random values. ");
				printf("Expected %d, got %d.\n", values[i], *x);
				result = 0;
				free(x);
				break;
			}
			free(x);
		}
		free(values);
		freeString(s);
		if (!result)
			break;
	}

	//Boundary values (Sizes of 0 and 1)
	s = createZeros(0, element_size, (void*)&zero);
	freeString(s);
	s = createFromValues(0, element_size, (void*)&zero, NULL);
	freeString(s);
	s = createZeros(1, element_size, (void*)&zero);
	freeString(s);
	int x = 1;
	s = createFromValues(1, element_size, (void*)&zero, (void*)&x);
	freeString(s);

	if (result)
		printf("Info: All tests passed successfully.\n");
	else
		printf("Info: At least one error occured during the tests.\n");
	return result;
}

int autoTestSetAndGet(int n_tests, size_t size, unsigned int seed) {
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("\nSetAndGet autotest:\n");
	printf("Info: Starting SetAndGet autotest on seed %d.\n", seed);
	int result = 1;

	size_t element_size = sizeof(int);
	int zero = 0;
	struct String* s;

	//Random
	s = createZeros(size, element_size, (void*)&zero);
	for (int test_i = 0; test_i < n_tests; test_i++) {
		int x = rand();
		size_t idx = rand() % size;
		set(s, idx, (void*)&x);
		//Value mismatch check
		int* a = (int*)get(s, idx);
		if (*a != x) {
			printf("Error: Value mismatch on random values. ");
			printf("Expected %d, got %d.\n", x, *a);
			result = 0;
			break;
		}
		free(a);
	}
	freeString(s);

	//Boundary values (Indexes of 0 and 1)
	s = createZeros(1, element_size, (void*)&zero);
	free(get(s, 0));
	set(s, 0, (void*)&zero);
	freeString(s);

	if (result)
		printf("Info: All tests passed successfully.\n");
	else
		printf("Info: At least one error occured during the tests.\n");
	return result;
}

int autoTestCopy(int n_tests, size_t max_size, unsigned int seed) {
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("\nCopy autotest:\n");
	printf("Info: Starting Copy autotest on seed %d.\n", seed);
	int result = 1;

	size_t size;
	size_t element_size = sizeof(int);
	int zero = 0;
	struct String* s;
	struct String* s_copy;

	//Random
	for (int test_i = 0; test_i < n_tests; test_i++) {
		size = rand() % max_size;
		int* values = malloc(size * sizeof(int));
		for (int i = 0; i < size; i++)
			values[i] = rand();
		s = createFromValues(size, element_size, (void*)&zero, (void*)values);
		s_copy = copy(s);
		//Size mismatch chek
		if (getSize(s_copy) != size) {
			printf("Error: Size mismatch on random values. ");
			printf("Expected %d, got %d.\n", size, getSize(s_copy));
			result = 0;
		}
		//Value mismatch check
		for (int i = 0; i < size; i++) {
			int* x = (int*)get(s_copy, i);
			if (*x != values[i]) {
				printf("Error: Value mismatch on random values. ");
				printf("Expected %d, got %d.\n", values[i], *x);
				result = 0;
				free(x);
				break;
			}
			free(x);
		}
		free(values);
		freeString(s);
		freeString(s_copy);
		if (!result)
			break;
	}

	//Boundary values (Sizes of 0 and 1)
	s = createZeros(0, element_size, (void*)&zero);
	freeString(copy(s));
	freeString(s);
	s = createZeros(1, element_size, (void*)&zero);
	freeString(copy(s));
	freeString(s);

	if (result)
		printf("Info: All tests passed successfully.\n");
	else
		printf("Info: At least one error occured during the tests.\n");
	return result;
}

int autoTestEquals(int n_tests, size_t max_size, unsigned int seed) {
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("\nEquals autotest:\n");
	printf("Info: Starting Equals autotest on seed %d.\n", seed);
	int result = 1;

	size_t size;
	size_t element_size = sizeof(int);
	int zero = 0;
	struct String* s;
	struct String* s_equal;
	struct String* s_not_equal;

	//Random
	for (int test_i = 0; test_i < n_tests; test_i++) {
		size = rand() % (max_size - 1) + 1;
		int* values = malloc(size * sizeof(int));
		for (int i = 0; i < size; i++)
			values[i] = rand();
		s = createFromValues(size, element_size, (void*)&zero, (void*)values);
		free(values);
		s_equal = copy(s);
		s_not_equal = copy(s);
		int* x = (int*)get(s_not_equal, 0);
		*x += 1;
		set(s_not_equal, 0, (void*)x);
		free(x);
		if (!equals(s, s_equal)) {
			printf("Error: Equal strings aren't equal.\n");
			result = 0;
		}
		if (equals(s, s_not_equal)) {
			printf("Error: Not equal strings are equal.\n");
			result = 0;
		}
		freeString(s);
		freeString(s_equal);
		freeString(s_not_equal);
		if (!result)
			break;
	}

	//Boundary values (Sizes of 0 and 1)
	s = createZeros(0, element_size, (void*)&zero);
	if (!equals(s, s)) {
		printf("Error: Empty string isn't equal to itself.\n");
		result = 0;
	}
	freeString(s);
	s = createZeros(1, element_size, (void*)&zero);
	if (!equals(s, s)) {
		printf("Error: One symbol string isn't equal to itself.\n");
		result = 0;
	}
	freeString(s);

	if (result)
		printf("Info: All tests passed successfully.\n");
	else
		printf("Info: At least one error occured during the tests.\n");
	return result;
}

int autoTestFill(int n_tests, size_t max_size, unsigned int seed) {
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("\nFill autotest:\n");
	printf("Info: Starting Fill autotest on seed %d.\n", seed);
	int result = 1;

	size_t size;
	size_t element_size = sizeof(int);
	int zero = 0;
	struct String* s;
	int fill_value;

	//Random
	for (int test_i = 0; test_i < n_tests; test_i++) {
		size = rand() % max_size;
		s = createZeros(size, element_size, (void*)&zero);
		fill_value = rand();
		fill(s, (void*)&fill_value);
		//Value mismatch check
		for (int i = 0; i < size; i++) {
			int* x = (int*)get(s, i);
			if (*x != fill_value) {
				printf("Error: Value mismatch on random values. ");
				printf("Expected %d, got %d.\n", fill_value, *x);
				result = 0;
				free(x);
				break;
			}
			free(x);
		}
		freeString(s);
		if (!result)
			break;
	}
	
	//Boundary values (Indexes of 0 and 1)
	fill_value = 1;
	s = createZeros(0, element_size, (void*)&zero);
	fill(s, (void*)&fill_value);
	freeString(s);
	s = createZeros(1, element_size, (void*)&zero);
	fill(s, (void*)&fill_value);
	freeString(s);	

	if (result)
		printf("Info: All tests passed successfully.\n");
	else
		printf("Info: At least one error occured during the tests.\n");
	return result;
}

int autoTestSwap(int n_tests, size_t max_size, unsigned int seed) {
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("\nSwap autotest:\n");
	printf("Info: Starting Swap autotest on seed %d.\n", seed);
	int result = 1;

	size_t size;
	size_t element_size = sizeof(int);
	int zero = 7;
	struct String* s;

	//Random
	for (int test_i = 0; test_i < n_tests; test_i++) {
		size = rand() % (max_size - 1) + 1;
		int* values = malloc(size * sizeof(int));
		for (int i = 0; i < size; i++)
			values[i] = rand();
		s = createFromValues(size, element_size, (void*)&zero, (void*)values);
		free(values);
		int a_id = rand() % size;
		int b_id = rand() % size;
		struct String* s_old = copy(s);
		int* a_old = (int*)get(s, a_id);
		int* b_old = (int*)get(s, b_id);
		swap(s, a_id, b_id);
		int* a = (int*)get(s, a_id);
		int* b = (int*)get(s, b_id);
		//Target elements check
		if (*a != *b_old || *b != *a_old) {
			printf("Error: Target elements weren't swapped correctly on random values.\n");
			result = 0;
		}
		//Rest elements check
		set(s, a_id, a_old);
		set(s, b_id, b_old);
		if (!equals(s, s_old)) {
			printf("Error: More then two elements were swapped.\n");
			result = 0;
		}
		free(a_old);
		free(b_old);
		free(a);
		free(b);
		freeString(s);
		freeString(s_old);
		if (!result)
			break;
	}

	//Boundary values
	s = createZeros(2, element_size, (void*)&zero);
	swap(s, 0, 1);
	freeString(s);
	s = createZeros(1, element_size, (void*)&zero);
	swap(s, 0, 0);
	if (!equals(s, s)) {
		printf("Error: Swaping elements with same indexes changes string.\n");
		result = 0;
	}
	freeString(s);

	if (result)
		printf("Info: All tests passed successfully.\n");
	else
		printf("Info: At least one error occured during the tests.\n");
	return result;
}

int autoTestReverse(int n_tests, size_t max_size, unsigned int seed) {
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("\nReverse autotest:\n");
	printf("Info: Starting Reverse autotest on seed %d.\n", seed);
	int result = 1;

	size_t size;
	size_t element_size = sizeof(int);
	int zero = 0;
	struct String* s;
	struct String* rev;

	//Random
	for (int test_i = 0; test_i < n_tests; test_i++) {
		size = rand() % max_size;
		int* values = malloc(size * sizeof(int));
		for (int i = 0; i < size; i++)
			values[i] = rand();
		s = createFromValues(size, element_size, (void*)&zero, (void*)values);
		free(values);
		rev = copy(s);
		reverse(rev);

		//Value mismatch check
		for (int i = 0; i < size; i++) {
			int* a = (int*)get(s, i);
			int* b = (int*)get(rev, size - i - 1);
			if (*a != *b) {
				printf("Error: Value mismatch on random values. ");
				printf("Expected %d, got %d.\n", *a, *b);
				result = 0;
				free(a);
				free(b);
				break;
			}
			free(a);
			free(b);
		}
		//Double reverse check
		reverse(rev);
		if (!equals(rev, s)) {
			printf("Error: Double-reversed string isn't equal to original string.\n");
			result = 0;
		}
		freeString(s);
		freeString(rev);
		if (!result)
			break;
	}

	//Boundary values
	s = createZeros(0, element_size, (void*)&zero);
	reverse(s);
	if (!equals(s, s)) {
		printf("Error: Reversed empty string isn't empty.\n");
		result = 0;
	}
	freeString(s);
	s = createZeros(1, element_size, (void*)&zero);
	if (!equals(s, s)) {
		printf("Error: Reversion of an one symbol string changes it.\n");
		result = 0;
	}
	reverse(s);
	freeString(s);

	if (result)
		printf("Info: All tests passed successfully.\n");
	else
		printf("Info: At least one error occured during the tests.\n");
	return result;
}

int autoTestConcatenate(int n_tests, size_t max_size, unsigned int seed) {
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("\nConcatenate autotest:\n");
	printf("Info: Starting Concatenate autotest on seed %d.\n", seed);
	int result = 1;

	size_t size_1;
	size_t size_2;
	size_t element_size = sizeof(int);
	int zero = 0;
	struct String* s1;
	struct String* s2;
	struct String* s3;

	//Random
	for (int test_i = 0; test_i < n_tests; test_i++) {
		size_1 = rand() % max_size;
		size_2 = rand() % max_size;
		int* values_1 = malloc(size_1 * sizeof(int));
		int* values_2 = malloc(size_2 * sizeof(int));
		for (int i = 0; i < size_1; i++)
			values_1[i] = rand();
		for (int i = 0; i < size_2; i++)
			values_2[i] = rand();
		s1 = createFromValues(size_1, element_size, (void*)&zero, (void*)values_1);
		s2 = createFromValues(size_2, element_size, (void*)&zero, (void*)values_2);
		free(values_1);
		free(values_2);
		s3 = concatenate(s1, s2);
		//Size check
		if (size_1 + size_2 != getSize(s3)) {
			printf("Error: Size mismatch on random values. ");
			printf("Expected %d, got %d.\n", size_1 + size_2, getSize(s3));
			result = 0;
		}
		//Value mismatch check
		for (int i = 0; i < size_1; i++) {
			int* a = (int*)get(s1, i);
			int* b = (int*)get(s3, i);
			if (*a != *b) {
				printf("Error: Value mismatch on random values. ");
				printf("Expected %d, got %d.\n", *a, *b);
				result = 0;
				free(a);
				free(b);
				break;
			}
			free(a);
			free(b);
		}
		for (int i = 0; i < size_2; i++) {
			int* a = (int*)get(s2, i);
			int* b = (int*)get(s3, size_1 + i);
			if (*a != *b) {
				printf("Error: Value mismatch on random values. ");
				printf("Expected %d, got %d.\n", *a, *b);
				result = 0;
				free(a);
				free(b);
				break;
			}
			free(a);
			free(b);
		}
		freeString(s1);
		freeString(s2);
		freeString(s3);
		if (!result)
			break;
	}
	//Boundary values
	s1 = createZeros(0, element_size, (void*)&zero);
	s2 = createZeros(1, element_size, (void*)&zero);

	s3 = concatenate(s1, s1);
	if (!equals(s3, s1)) {
		printf("Error: Concatination product of two empty strings isn't an empty string.\n");
		result = 0;
	}
	freeString(s3);

	s3 = concatenate(s2, s1);
	if (!equals(s3, s2)) {
		printf("Error: Concatination of an empty string to other string changes that string.\n");
		result = 0;
	}
	freeString(s3);

	s3 = concatenate(s1, s2);
	if (!equals(s3, s2)) {
		printf("Error: Concatination of an empty string to other string changes that string.\n");
		result = 0;
	}
	freeString(s3);

	freeString(s1);
	freeString(s2);

	if (result)
		printf("Info: All tests passed successfully.\n");
	else
		printf("Info: At least one error occured during the tests.\n");
	return result;
}

int autoTestSubString(int n_tests, size_t max_size, unsigned int seed) {
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("\nSubString autotest:\n");
	printf("Info: Starting SubString autotest on seed %d.\n", seed);
	int result = 1;

	size_t size;
	size_t element_size = sizeof(int);
	int zero = 7;
	struct String* s;
	struct String* s_sub;

	//Random
	for (int test_i = 0; test_i < n_tests; test_i++) {
		size = rand() % (max_size - 1) + 1;
		int* values = malloc(size * sizeof(int));
		for (int i = 0; i < size; i++)
			values[i] = rand();
		s = createFromValues(size, element_size, (void*)&zero, (void*)values);
		free(values);
		int start = rand() % size;
		int end = rand() % (size - start) + start;
		s_sub = subString(s, start, end);
		//Size mismatch cehk
		if (getSize(s_sub) != end - start + 1) {
			printf("Error: Size mismatch on random values. ");
			printf("Expected %d, got %d.\n", end - start + 1, getSize(s_sub));
			result = 0;
		}
		//Value mismatch check
		for (int i = 0; i < start - end + 1; i++) {
			int* a = (int*)get(s, start + i);
			int* b = (int*)get(s_sub, i);
			if (*a != *b) {
				printf("Error: Value mismatch on random values. ");
				printf("Expected %d, got %d.\n", *a, *b);
				result = 0;
				free(a);
				free(b);
				break;
			}
			free(a);
			free(b);
		}
		freeString(s);
		freeString(s_sub);
		if (!result)
			break;
	}

	//Boundary values
	s = createZeros(1, element_size, (void*)&zero);
	s_sub = subString(s, 0, 0);
	if (!equals(s, s_sub)) {
		printf("Error: Substring taken from start to end of a string isn't equal to that string.\n");
		result = 0;
	}
	freeString(s);
	freeString(s_sub);

	if (result)
		printf("Info: All tests passed successfully.\n");
	else
		printf("Info: At least one error occured during the tests.\n");
	return result;
}

void* exampleIntEncodingFunc(void* x) {
	int* y = malloc(sizeof(int));
	*y = *(int*)x % 2;
	return (void*)y;
}

int autoTestEncode(int n_tests, size_t max_size, unsigned int seed) {
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("\nEncode autotest:\n");
	printf("Info: Starting Encode autotest on seed %d.\n", seed);
	int result = 1;

	size_t size;
	size_t element_size = sizeof(int);
	int zero = 7;
	struct String* s;
	struct String* s_encoded;

	//Random
	for (int test_i = 0; test_i < n_tests; test_i++) {
		size = rand() % max_size;
		int* values = malloc(size * sizeof(int));
		for (int i = 0; i < size; i++)
			values[i] = rand();
		s = createFromValues(size, element_size, (void*)&zero, (void*)values);
		free(values);
		s_encoded = copy(s);
		encode(s_encoded, exampleIntEncodingFunc);
		//Size mismatch cehk
		if (getSize(s_encoded) != getSize(s)) {
			printf("Error: Size mismatch on random values. ");
			printf("Expected %d, got %d.\n", getSize(s), getSize(s_encoded));
			result = 0;
		}
		//Value mismatch check
		for (int i = 0; i < size; i++) {
			int* a = (int*)get(s, i);
			int* b = (int*)get(s_encoded, i);
			int* c = (int*)exampleIntEncodingFunc((void*)a);
			if (*c != *b) {
				printf("Error: Value mismatch on random values. ");
				printf("Expected %d, got %d.\n", *b, *c);
				result = 0;
				free(a);
				free(b);
				free(c);
				break;
			}
			free(a);
			free(b);
			free(c);
		}
		freeString(s);
		freeString(s_encoded);
		if (!result)
			break;
	}

	//Boundary values
	s = createZeros(0, element_size, (void*)&zero);
	s_encoded = copy(s);
	encode(s_encoded, exampleIntEncodingFunc);
	if (!equals(s, s_encoded)) {
		printf("Error: Encoded empty string isn't empty.\n");
		result = 0;
	}
	freeString(s);
	freeString(s_encoded);

	if (result)
		printf("Info: All tests passed successfully.\n");
	else
		printf("Info: At least one error occured during the tests.\n");
	return result;
}

int simpleCharAutoTest() {
	printf("\nSimple char string autotest:\n");
	printf("Info: Starting simple char string autotest.\n");
	int result = 1;

	struct String* s;
	char* p;
	char c;

	s = createZerosChar(1);
	if (*(char*)get(s, 0) != ' ' || getSize(s) != 1) {
		result = 0;
		printf("Error: Error in createZerosChar.\n");
	}
	freeString(s);

	s = createFromValuesChar(11, "Lorem ipsum");
	char* values = "Lorem ipsum";
	for (int i = 0; i < getSize(s); i++) {
		if (*(char*)get(s, i) != values[i]) {
			result = 0;
			printf("Error: Error in createFromValuesChar.\n");
			break;
		}
	}
	if (getSize(s) != 11) {
		result = 0;
		printf("Error: Error in createFromValuesChar.\n");
	}

	for (int i = 0; i < getSize(s); i++) {
		if (getChar(s, i) != values[i]) {
			result = 0;
			printf("Error: Error in getChar.\n");
			break;
		}
	}

	setChar(s, 0, 'M');
	if (*(char*)get(s, 0) != 'M') {
		result = 0;
		printf("Error: Error in setChar.\n");
	}

	fillChar(s, 'O');
	for (int i = 0; i < getSize(s); i++) {
		if (*(char*)get(s, i) != 'O') {
			result = 0;
			printf("Error: Error in setChar.\n");
			break;
		}
	}
	freeString(s);

	if (result)
		printf("Info: All tests passed successfully.\n");
	else
		printf("Info: At least one error occured during the tests.\n");
	return result;
}

int autoTestAll(int n_tests, size_t max_size, unsigned int seed) {
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("String autotests:\n");
	
	int result = 1;
	result *= autoTestCreateAndGet(n_tests, max_size, seed);
	result *= autoTestSetAndGet(n_tests, max_size, seed);
	result *= autoTestCopy(n_tests, max_size, seed);
	result *= autoTestEquals(n_tests, max_size, seed);
	result *= autoTestFill(n_tests, max_size, seed);
	result *= autoTestSwap(n_tests, max_size, seed);
	result *= autoTestReverse(n_tests, max_size, seed);
	result *= autoTestConcatenate(n_tests, max_size, seed);
	result *= autoTestSubString(n_tests, max_size, seed);
	result *= autoTestEncode(n_tests, max_size, seed);
	result *= simpleCharAutoTest();


	if (result)
		printf("\nAll string autotests passed successfully.\n");
	else
		printf("\nAt least one error occured during the string autotests.\n");
	return result;
}