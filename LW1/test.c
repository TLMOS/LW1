#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <conio.h>
#include "string.h"
#include "char_string.h"

int autoTestCreate(int n_tests, size_t max_size, unsigned int seed) {
	//Assuming getPointer and getSize work correctly
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("\nCreateAndGet autotest:\n");
	printf("Info: Starting CreateAndGet autotest on seed %d.\n", seed);
	int result = 1;

	size_t size;
	int zero_int = 0;
	char zero_char = ' ';
	struct String* s;

	//Random tests, int, createZeros
	for (int test_i = 0; test_i < n_tests; test_i++) {
		size = rand(max_size);
		s = createZeros(size, sizeof(int), (void*)&zero_int);
		//Size mismatch check
		if (getSize(s) != size) {
			printf("Error: (Random) Wrong size in createZeros. ");
			printf("Expected %d, got %d.\n", size, getSize(s));
			result = 0;
		}
		//Value mismatch check
		for (int i = 0; i < size; i++) {
			int* x = (int*)getPointer(s, i);
			if (*x != zero_int) {
				printf("Error: (Random) Value mismatch in createZeros. ");
				printf("Expected %d, got %d.\n", zero_int, *x);
				result = 0;
				break;
			}
		}
		freeString(s);
		if (!result)
			break;
	}

	//Random tests, int, createFromValues
	for (int test_i = 0; test_i < n_tests; test_i++) {
		size = rand(max_size);
		int* values = malloc(size * sizeof(int));
		for (int i = 0; i < size; i++)
			values[i] = rand();
		s = createFromValues(size, sizeof(int), (void*)&zero_int, (void*)values);
		//Size mismatch check
		if (getSize(s) != size) {
			printf("Error: (Random) Wrong size in createFromValues. ");
			printf("Expected %d, got %d.\n", size, getSize(s));
			result = 0;
		}
		//Value mismatch check
		for (int i = 0; i < size; i++){
			int* x = (int*)getPointer(s, i);
			if (*x != values[i]) {
				printf("Error: (Random) Value mismatch in createFromValues. ");
				printf("Expected %d, got %d.\n", values[i], *x);
				result = 0;
				break;
			}
		}
		free(values);
		freeString(s);
		if (!result)
			break;
	}

	//Other tests
	struct String* s1;
	struct String* s2;
	struct String* s3;

	//Test 1
	freeString(createZeros(0, sizeof(int), (void*)&zero_int));
	freeString(createZeros(0, sizeof(char), (void*)&zero_char));
	freeString(createZerosChar(0));

	//Test 2
	int x_int = 2;
	char x_char = 'a';
	s1 = createFromValues(1, sizeof(int), (void*)&zero_int, &x_int);
	s2 = createFromValues(1, sizeof(char), (void*)&zero_char, &x_char);
	s3 = createFromValuesChar(1, &x_char);
	if (getSize(s1) != 1 || getSize(s2) != 1 || getSize(s3) != 1) {
		printf("Error: (Test 2) Wrong size.\n");
		result = 0;
	}
	else if (*(int*)getPointer(s1, 0) != x_int ||
		*(char*)getPointer(s2, 0) != x_char ||
		*(char*)getPointer(s3, 0) != x_char) {
		printf("Error: (Test 2) Value mismatch.\n");
		result = 0;
	}
	freeString(s1);
	freeString(s2);
	freeString(s3);

	//Test 3
	size = 3;
	s1 = createZeros(size, sizeof(int), (void*)&zero_int);
	s2 = createZeros(size, sizeof(char), (void*)&zero_char);
	s3 = createZerosChar(size);
	if (getSize(s1) != size || getSize(s2) != size || getSize(s3) != size) {
		printf("Error: (Test 3) Wrong size.\n");
		result = 0;
	}
	for (int i = 0; i < size; i++) {
		if (*(int*)getPointer(s1, i) != zero_int ||
			*(char*)getPointer(s2, i) != zero_char ||
			*(char*)getPointer(s3, i) != zero_char) {
			printf("Error: (Test 3) Value mismatch.\n");
			result = 0;
		}
	}
	freeString(s1);
	freeString(s2);
	freeString(s3);

	//Test 4
	size = 3;
	int v_int[] = {1, 2, 3};
	char v_char[] = "abc";
	s1 = createFromValues(size, sizeof(int), (void*)&zero_int, (void*)v_int);
	s2 = createFromValues(size, sizeof(char), (void*)&zero_char, (void*)v_char);
	s3 = createFromValuesChar(size, v_char);
	if (getSize(s1) != size || getSize(s2) != size || getSize(s3) != size) {
		printf("Error: (Test 4) Wrong size.\n");
		result = 0;
	}
	for (int i = 0; i < size; i++) {
		if (*(int*)getPointer(s1, i) != v_int[i] ||
			*(char*)getPointer(s2, i) != v_char[i] ||
			*(char*)getPointer(s3, i) != v_char[i]) {
			printf("Error: (Test 4) Value mismatch.\n");
			result = 0;
		}
	}
	freeString(s1);
	freeString(s2);
	freeString(s3);


	if (result)
		printf("Info: All tests passed successfully.\n");
	else
		printf("Info: At least one error occured during the tests.\n");
	return result;
}

int autoTestSetAndGet(int n_tests, size_t size, unsigned int seed) {
	//Assuming getPointer and createZeros work correctly
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("\nSetAndGet autotest:\n");
	printf("Info: Starting SetAndGet autotest on seed %d.\n", seed);
	int result = 1;

	int zero_int = 0;
	char zero_char = ' ';
	struct String* s;

	//Random tests, int
	s = createZeros(size, sizeof(int), (void*)&zero_int);
	for (int test_i = 0; test_i < n_tests; test_i++) {
		int x = rand();
		size_t idx = rand() % size;
		set(s, idx, (void*)&x);
		//Value mismatch check
		int* a = (int*)get(s, idx);
		if (*a != x) {
			printf("Error: (Random) Wrong value. ");
			printf("Expected %d, got %d.\n", x, *a);
			result = 0;
			break;
		}
		free(a);
	}
	freeString(s);

	//Other tests
	//Test 1
	char x_char = 'a';
	s = createZeros(1, sizeof(char), (void*)&zero_char);
	set(s, 0, (void*)&x_char);
	char* p = (char*)get(s, 0);
	if (*(char*)getPointer(s, 0) != x_char ||
		*p != x_char ||
		getChar(s, 0) != x_char) {
		printf("Error: (Test 1) Wrong value.\n");
		result = 0;
	}
	free(p);
	freeString(s);

	//Test 2
	size = 3;
	char v_char[] = "abc";
	s = createZeros(size, sizeof(char), (void*)&zero_char);
	for (int i = 0; i < size; i++) {
		set(s, i, &v_char[i]);
		char* p = (char*)get(s, i);
		if (*(char*)getPointer(s, i) != v_char[i] ||
			*p != v_char[i] ||
			getChar(s, i) != v_char[i]) {
			printf("Error: (Test 2) Wrong value.\n");
			result = 0;
		}
		free(p);
	}
	freeString(s);

	if (result)
		printf("Info: All tests passed successfully.\n");
	else
		printf("Info: At least one error occured during the tests.\n");
	return result;
}

int autoTestEquals(int n_tests, size_t max_size, unsigned int seed) {
	//Assuming createZeros and createFromValues work correctly 
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("\nEquals autotest:\n");
	printf("Info: Starting Equals autotest on seed %d.\n", seed);
	int result = 1;

	size_t size;
	int zero_int = 0;
	char zero_char = ' ';
	struct String* s;
	struct String* s_equal;
	struct String* s_not_equal;

	//Random tests, int
	for (int test_i = 0; test_i < n_tests; test_i++) {
		size = rand() % (max_size - 1) + 1;
		int* values = malloc(size * sizeof(int));
		for (int i = 0; i < size; i++)
			values[i] = rand();
		s = createFromValues(size, sizeof(int), (void*)&zero_int, (void*)values);
		s_equal = createFromValues(size, sizeof(int), (void*)&zero_int, (void*)values);
		values[0] += 1;
		s_not_equal = createFromValues(size, sizeof(int), (void*)&zero_int, (void*)values);
		free(values);
		if (!equals(s, s_equal)) {
			printf("Error: (Random) Equal strings aren't equal.\n");
			result = 0;
		}
		if (equals(s, s_not_equal)) {
			printf("Error: (Random) Not equal strings are equal.\n");
			result = 0;
		}
		freeString(s);
		freeString(s_equal);
		freeString(s_not_equal);
		if (!result)
			break;
	}

	//Other tests
	//Test 1
	s = createZeros(0, sizeof(char), (void*)&zero_char);
	s_equal = createZeros(0, sizeof(char), (void*)&zero_char);
	if (!equals(s, s_equal)) {
		printf("Error: (Test 1) Empty strings aren't equal.\n");
		result = 0;
	}
	freeString(s);
	freeString(s_equal);

	//Test 2
	size = 3;
	char v_char[] = "abc";
	s = createFromValues(size, sizeof(char), (void*)&zero_char, (void*)v_char);
	s_equal = createFromValues(size, sizeof(char), (void*)&zero_char, (void*)v_char);
	v_char[0] = 'd';
	s_not_equal = createFromValues(size, sizeof(char), (void*)&zero_char, (void*)v_char);
	if (!equals(s, s_equal)) {
		printf("Error: (Test 2) Equal strings aren't equal.\n");
		result = 0;
	}
	if (equals(s, s_not_equal)) {
		printf("Error: (Test 2) Not equal strings are equal.\n");
		result = 0;
	}
	freeString(s);
	freeString(s_equal);

	//Test 3
	size = 3;
	int v_int[] = {1, 2, 3};
	s = createFromValues(size, sizeof(char), (void*)&zero_int, (void*)v_int);
	s_equal = createFromValues(size, sizeof(char), (void*)&zero_int, (void*)v_int);
	v_int[0] = 4;
	s_not_equal = createFromValues(size, sizeof(char), (void*)&zero_int, (void*)v_int);
	if (!equals(s, s_equal)) {
		printf("Error: (Test 3) Equal strings aren't equal.\n");
		result = 0;
	}
	if (equals(s, s_not_equal)) {
		printf("Error: (Test 3) Not equal strings are equal.\n");
		result = 0;
	}
	freeString(s);
	freeString(s_equal);

	if (result)
		printf("Info: All tests passed successfully.\n");
	else
		printf("Info: At least one error occured during the tests.\n");
	return result;
}

int autoTestCopy(int n_tests, size_t max_size, unsigned int seed) {
	//Assuming createZeros, createFromValues and copy work correctly 
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("\nCopy autotest:\n");
	printf("Info: Starting Copy autotest on seed %d.\n", seed);
	int result = 1;

	size_t size;
	int zero_int = 0;
	char zero_char = ' ';
	struct String* s;
	struct String* s_copy;

	//Random test, int
	for (int test_i = 0; test_i < n_tests; test_i++) {
		size = rand() % max_size;
		int* values = malloc(size * sizeof(int));
		for (int i = 0; i < size; i++)
			values[i] = rand();
		s = createFromValues(size, sizeof(int), (void*)&zero_int, (void*)values);
		s_copy = copy(s);
		if (!equals(s, s_copy)) {
			printf("Error: (Random) Copy of a string isn't equal to original string.\n");
			result = 0;
		}
		free(values);
		freeString(s);
		freeString(s_copy);
		if (!result)
			break;
	}

	//Other tests
	//Test 1
	s = createZeros(0, sizeof(char), (void*)&zero_char);
	freeString(copy(s));

	//Test 2
	s = createZeros(0, sizeof(char), (void*)&zero_char);
	s_copy = copy(s);
	if (!equals(s, s_copy)) {
		printf("Error: (Test 2) Copy of an empty string isn't equal to original string.\n");
		result = 0;
	}
	freeString(s);
	freeString(s_copy);

	//Test 3
	size = 3;
	char v_char[] = "abc";
	s = createFromValues(size, sizeof(char), (void*)&zero_char, (void*)v_char);
	s_copy = copy(s);
	if (!equals(s, s_copy)) {
		printf("Error: (Test 3) Copy of a string isn't equal to original string.\n");
		result = 0;
	}
	freeString(s);
	freeString(s_copy);

	if (result)
		printf("Info: All tests passed successfully.\n");
	else
		printf("Info: At least one error occured during the tests.\n");
	return result;
}

int autoTestFill(int n_tests, size_t max_size, unsigned int seed) {
	//Assuming getPointer createZeros, createFromValues and equals work correctly
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("\nFill autotest:\n");
	printf("Info: Starting Fill autotest on seed %d.\n", seed);
	int result = 1;

	size_t size;
	int zero_int = 0;
	char zero_char = ' ';
	struct String* s;
	int fill_value_int;
	char fill_value_char;

	//Random test, int
	for (int test_i = 0; test_i < n_tests; test_i++) {
		size = rand() % max_size;
		s = createZeros(size, sizeof(int), (void*)&zero_int);
		fill_value_int = rand();
		fill(s, (void*)&fill_value_int);
		//Value mismatch check
		for (int i = 0; i < size; i++) {
			int* x = (int*)getPointer(s, i);
			if (*x != fill_value_int) {
				printf("Error: (Random) Wrong value. ");
				printf("Expected %d, got %d.\n", fill_value_int, *x);
				result = 0;
				break;
			}
		}
		freeString(s);
		if (!result)
			break;
	}
	
	//Other tests
	struct  String* s_target;

	//Test 1
	fill_value_char = 'a';
	s = createZeros(0, sizeof(char), (void*)&zero_char);
	fill(s, (void*)&fill_value_char);
	freeString(s);

	//Test 2
	size = 3;
	char v_char[] = "abc";
	char v_char_target[] = "aaa";
	fill_value_char = 'a';
	s = createFromValues(size, sizeof(char),
		(void*)&zero_char, (void*)v_char);
	s_target = createFromValues(size, sizeof(char),
		(void*)&zero_char, (void*)v_char_target);
	fill(s, (void*)&fill_value_char);
	if (!equals(s, s_target)) {
		printf("Error: (Test 2) Result isn;t equal to a target.\n");
		result = 0;
	}
	freeString(s);
	freeString(s_target);

	//Test 3
	size = 3;
	int v_int[] = {1, 2, 3};
	int v_int_target[] = {1, 1, 1};
	fill_value_int = 1;
	s = createFromValues(size, sizeof(int),
		(void*)&zero_int, (void*)v_int);
	s_target = createFromValues(size, sizeof(int),
		(void*)&zero_int, (void*)v_int_target);
	fill(s, (void*)&fill_value_int);
	if (!equals(s, s_target)) {
		printf("Error: (Test 3) Result isn;t equal to a target.\n");
		result = 0;
	}
	freeString(s);
	freeString(s_target);
	
	if (result)
		printf("Info: All tests passed successfully.\n");
	else
		printf("Info: At least one error occured during the tests.\n");
	return result;
}

int autoTestSwap(int n_tests, size_t max_size, unsigned int seed) {
	//Assuming getPointer createZeros, createFromValues and equals work correctly
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("\nSwap autotest:\n");
	printf("Info: Starting Swap autotest on seed %d.\n", seed);
	int result = 1;

	size_t size;
	int zero_int = 0;
	char zero_char = ' ';
	struct String* s;

	//Random test, int
	for (int test_i = 0; test_i < n_tests; test_i++) {
		size = rand() % (max_size - 1) + 1;
		int* values = malloc(size * sizeof(int));
		for (int i = 0; i < size; i++)
			values[i] = rand();
		s = createFromValues(size, sizeof(int), (void*)&zero_int, (void*)values);
		free(values);
		int a_id = rand() % size;
		int b_id = rand() % size;
		struct String* s_old = copy(s);
		int* a = (int*)getPointer(s, a_id);
		int* b = (int*)getPointer(s, b_id);
		int a_old = *a;
		int b_old = *b;
		swap(s, a_id, b_id);
		
		//Target elements check
		if (*a != b_old || *b != a_old) {
			printf("Error: (Random) Target elements weren't swapped correctly.\n");
			result = 0;
		}
		//Rest elements check
		set(s, a_id, &a_old);
		set(s, b_id, &b_old);
		if (!equals(s, s_old)) {
			printf("Error: (Random) More then two elements were swapped.\n");
			result = 0;
		}
		freeString(s);
		freeString(s_old);
		if (!result)
			break;
	}

	//Other tests
	struct  String* s_target;

	//Test 1
	size = 1;
	char v_char[] = "a";
	char v_char_target[] = "a";
	s = createFromValues(size, sizeof(char),
		(void*)&zero_char, (void*)v_char);
	s_target = createFromValues(size, sizeof(char),
		(void*)&zero_char, (void*)v_char_target);
	swap(s, 0, 0);
	if (!equals(s, s_target)) {
		printf("Error: (Test 1) Result isn;t equal to a target.\n");
		result = 0;
	}
	freeString(s);
	freeString(s_target);

	//Test 2
	size = 3;
	char v_char_2[] = "abc";
	char v_char_target_2[] = "acb";
	s = createFromValues(size, sizeof(char),
		(void*)&zero_char, (void*)v_char_2);
	s_target = createFromValues(size, sizeof(char),
		(void*)&zero_char, (void*)v_char_target_2);
	swap(s, 1, 2);
	if (!equals(s, s_target)) {
		printf("Error: (Test 2) Result isn;t equal to a target.\n");
		result = 0;
	}
	freeString(s);
	freeString(s_target);

	//Test 3
	size = 3;
	int v_int[] = {1, 2, 3};
	int v_int_target[] = {1, 3, 2};
	s = createFromValues(size, sizeof(int),
		(void*)&zero_int, (void*)v_int);
	s_target = createFromValues(size, sizeof(int),
		(void*)&zero_int, (void*)v_int_target);
	swap(s, 1, 2);
	if (!equals(s, s_target)) {
		printf("Error: (Test 3) Result isn;t equal to a target.\n");
		result = 0;
	}
	freeString(s);
	freeString(s_target);

	if (result)
		printf("Info: All tests passed successfully.\n");
	else
		printf("Info: At least one error occured during the tests.\n");
	return result;
}

int autoTestReverse(int n_tests, size_t max_size, unsigned int seed) {
	//Assuming createZeros, createFromValues and equals work correctly
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("\nReverse autotest:\n");
	printf("Info: Starting Reverse autotest on seed %d.\n", seed);
	int result = 1;

	size_t size;
	int zero_int = 0;
	char zero_char = ' ';
	struct String* s;
	struct String* rev;

	//Random test, int
	for (int test_i = 0; test_i < n_tests; test_i++) {
		size = rand() % max_size;
		int* values = malloc(size * sizeof(int));
		int* values_rev = malloc(size * sizeof(int));
		for (int i = 0; i < size; i++) {
			values[i] = rand();
			values_rev[size - 1 - i] = values[i];
		}
		s = createFromValues(size, sizeof(int),
			(void*)&zero_int, (void*)values);
		rev = createFromValues(size, sizeof(int),
			(void*)&zero_int, (void*)values_rev);
		free(values);
		free(values_rev);
		reverse(s);
		if (!equals(s, rev)) {
			printf("Error: (Random) Result isn't equal to a target.\n");
			result = 0;
		}
		freeString(s);
		freeString(rev);
		if (!result)
			break;
	}

	//Other tests
	struct  String* s_target;

	//Test 1
	size = 1;
	char v_char[] = "a";
	char v_char_target[] = "a";
	s = createFromValues(size, sizeof(char),
		(void*)&zero_char, (void*)v_char);
	s_target = createFromValues(size, sizeof(char),
		(void*)&zero_char, (void*)v_char_target);
	reverse(s);
	if (!equals(s, s_target)) {
		printf("Error: (Test 1) Result isn't equal to a target.\n");
		result = 0;
	}
	freeString(s);
	freeString(s_target);

	//Test 2
	size = 3;
	char v_char_2[] = "abc";
	char v_char_target_2[] = "cba";
	s = createFromValues(size, sizeof(char),
		(void*)&zero_char, (void*)v_char_2);
	s_target = createFromValues(size, sizeof(char),
		(void*)&zero_char, (void*)v_char_target_2);
	reverse(s);
	if (!equals(s, s_target)) {
		printf("Error: (Test 2) Result isn't equal to a target.\n");
		result = 0;
	}
	freeString(s);
	freeString(s_target);

	//Test 3
	size = 3;
	int v_int[] = { 1, 2, 3 };
	int v_int_target[] = { 3, 2, 1 };
	s = createFromValues(size, sizeof(int),
		(void*)&zero_int, (void*)v_int);
	s_target = createFromValues(size, sizeof(int),
		(void*)&zero_int, (void*)v_int_target);
	reverse(s);
	if (!equals(s, s_target)) {
		printf("Error: (Test 3) Result isn't equal to a target.\n");
		result = 0;
	}
	freeString(s);
	freeString(s_target);

	if (result)
		printf("Info: All tests passed successfully.\n");
	else
		printf("Info: At least one error occured during the tests.\n");
	return result;
}

int autoTestConcatenate(int n_tests, size_t max_size, unsigned int seed) {
	//Assuming createZeros, createFromValues and equals work correctly
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("\nConcatenate autotest:\n");
	printf("Info: Starting Concatenate autotest on seed %d.\n", seed);
	int result = 1;

	size_t size_1;
	size_t size_2;
	int zero_int = 0;
	char zero_char = ' ';
	struct String* s1;
	struct String* s2;
	struct String* s_concat;
	struct String* s3;

	//Random test, int
	for (int test_i = 0; test_i < n_tests; test_i++) {
		size_1 = rand() % max_size;
		size_2 = rand() % max_size;
		int* values_1 = malloc(size_1 * sizeof(int));
		int* values_2 = malloc(size_2 * sizeof(int));
		int* values_concat = malloc((size_1 + size_2) * sizeof(int));
		for (int i = 0; i < size_1; i++) {
			values_1[i] = rand();
			values_concat[i] = values_1[i];
		}
		for (int i = 0; i < size_2; i++) {
			values_2[i] = rand();
			values_concat[size_1 + i] = values_2[i];
		}
		s1 = createFromValues(size_1, sizeof(int),
			(void*)&zero_int, (void*)values_1);
		s2 = createFromValues(size_2, sizeof(int),
			(void*)&zero_int, (void*)values_2);
		s_concat = createFromValues(size_1 + size_2, sizeof(int),
			(void*)&zero_int, (void*)values_concat);
		free(values_1);
		free(values_2);
		free(values_concat);
		s3 = concatenate(s1, s2);
		if (!equals(s3, s_concat)) {
			printf("Error: (Random) Result isn't equal to a target.\n");
			result = 0;
		}
		freeString(s1);
		freeString(s2);
		freeString(s3);
		freeString(s_concat);
		if (!result)
			break;
	}

	//Other tests
	struct String* s_target;

	//Test 1
	char v_char[] = "a";
	s1 = createZeros(0, sizeof(char),
		(void*)&zero_char);
	s2 = createFromValues(1, sizeof(char),
		(void*)&zero_char, (void*)v_char);
	s3 = concatenate(s1, s2);
	if (!equals(s3, s2)) {
		printf("Error: (Test 1) Result isn't equal to a target.\n");
		result = 0;
	}
	freeString(s3);
	s3 = concatenate(s2, s1);
	if (!equals(s3, s2)) {
		printf("Error: (Test 1) Result isn't equal to a target.\n");
		result = 0;
	}
	freeString(s1);
	freeString(s2);
	freeString(s3);

	//Test 2
	size_1 = 3;
	size_2 = 5;
	char v_char_1[] = "abc";
	char v_char_2[] = "defgh";
	char v_char_target[] = "abcdefgh";
	s1 = createFromValues(size_1, sizeof(char),
		(void*)&zero_char, (void*)v_char_1);
	s2 = createFromValues(size_2, sizeof(char),
		(void*)&zero_char, (void*)v_char_2);
	s_target = createFromValues(size_1 + size_2, sizeof(char),
		(void*)&zero_char, (void*)v_char_target);
	s3 = concatenate(s1, s2);
	if (!equals(s3, s_target)) {
		printf("Error: (Test 2) Result isn't equal to a target.\n");
		result = 0;
	}
	freeString(s1);
	freeString(s2);
	freeString(s3);
	freeString(s_target);

	if (result)
		printf("Info: All tests passed successfully.\n");
	else
		printf("Info: At least one error occured during the tests.\n");
	return result;
}

int autoTestSubString(int n_tests, size_t max_size, unsigned int seed) {
	//Assuming createZeros, createFromValues and equals work correctly
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("\nSubString autotest:\n");
	printf("Info: Starting SubString autotest on seed %d.\n", seed);
	int result = 1;

	size_t size;
	int zero_int = 0;
	char zero_char = ' ';
	struct String* s;
	struct String* s_sub;
	struct String* s_target;

	//Random test, int
	for (int test_i = 0; test_i < n_tests; test_i++) {
		size = rand() % (max_size - 1) + 1;
		int start = rand() % size;
		int end = rand() % (size - start) + start;
		int* values = malloc(size * sizeof(int));
		int* values_sub = malloc((end - start + 1) * sizeof(int));
		for (int i = 0; i < size; i++)
			values[i] = rand();
		for (int i = 0; i < end - start + 1; i++)
			values_sub[i] = values[start + i];
		s = createFromValues(size, sizeof(int),
			(void*)&zero_int, (void*)values);
		s_target = createFromValues(end - start + 1, sizeof(int),
			(void*)&zero_int, (void*)values_sub);
		free(values);
		free(values_sub);
		
		s_sub = subString(s, start, end);
		if (!equals(s_sub, s_target)) {
			printf("Error: (Random) Result isn't equal to a target.\n");
			result = 0;
		}
		freeString(s);
		freeString(s_sub);
		freeString(s_target);
		if (!result)
			break;
	}

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
	//Assuming createZeros, createFromValues and equals work correctly
	if (!seed)
		seed = time(NULL);
	srand(seed);

	printf("\nEncode autotest:\n");
	printf("Info: Starting Encode autotest on seed %d.\n", seed);
	int result = 1;

	size_t size;
	int zero_int = 0;
	char zero_char = ' ';
	struct String* s;
	struct String* s_encoded;

	//Random test, int
	for (int test_i = 0; test_i < n_tests; test_i++) {
		size = rand() % max_size;
		int* values = malloc(size * sizeof(int));
		int* values_encoded = malloc(size * sizeof(int));
		for (int i = 0; i < size; i++){
			values[i] = rand();
			int* p = (int*)exampleIntEncodingFunc((void*)&values[i]);
			values_encoded[i] = *p;
			free(p);
		}
		s = createFromValues(size, sizeof(int),
			(void*)&zero_int, (void*)values);
		s_encoded = createFromValues(size, sizeof(int),
			(void*)&zero_int, (void*)values_encoded);
		free(values);
		free(values_encoded);
		encode(s, exampleIntEncodingFunc);
		if (!equals(s, s_encoded)) {
			printf("Error: (Random) Result isn't equal to a target.\n");
			result = 0;
		}
		freeString(s);
		freeString(s_encoded);
		if (!result)
			break;
	}

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
	result *= autoTestCreate(n_tests, max_size, seed);
	result *= autoTestSetAndGet(n_tests, max_size, seed);
	result *= autoTestEquals(n_tests, max_size, seed);
	result *= autoTestCopy(n_tests, max_size, seed);
	result *= autoTestFill(n_tests, max_size, seed);
	result *= autoTestSwap(n_tests, max_size, seed);
	result *= autoTestReverse(n_tests, max_size, seed);
	result *= autoTestConcatenate(n_tests, max_size, seed);
	result *= autoTestSubString(n_tests, max_size, seed);
	result *= autoTestEncode(n_tests, max_size, seed);


	if (result)
		printf("\nAll string autotests passed successfully.\n");
	else
		printf("\nAt least one error occured during the string autotests.\n");
	return result;
}