#pragma once
#include <stdlib.h>

int autoTestCreateAndGet(int n_tests, size_t max_size, unsigned int seed);
int autoTestSetAndGet(int n_tests, size_t size, unsigned int seed);
int autoTestCopy(int n_tests, size_t max_size, unsigned int seed);
int autoTestEquals(int n_tests, size_t max_size, unsigned int seed);
int autoTestFill(int n_tests, size_t max_size, unsigned int seed);
int autoTestSwap(int n_tests, size_t max_size, unsigned int seed);
int autoTestReverse(int n_tests, size_t max_size, unsigned int seed);
int autoTestConcatenate(int n_tests, size_t max_size, unsigned int seed);
int autoTestSubString(int n_tests, size_t max_size, unsigned int seed);
int autoTestEncode(int n_tests, size_t max_size, unsigned int seed);
int simpleCharAutoTest();

int autoTestAll(int n_tests, size_t max_size, unsigned int seed);