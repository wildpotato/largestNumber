/*
*  Author: Johnny Chan
*  Date:   11/15/2017
*  Largest Number (LeetCode No. 179):
*  Given a list of non-negative integers, arrange them such that they form the 
*  largest number.

*  For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.

*   Note: The result may be very large, so you need to return a string instead 
*   of an integer.
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	
#include "assert.h"
#define true 1
#define false 0 

/*
*  Returns true (1) if ab is not less than ba, returns false (0) otherwise
*/
int isLarger(int a, int b) {
	char string_a[10], string_b[10];
	char* a_ptr = string_a;
	char* b_ptr = string_b;
	sprintf(string_a, "%d", a);
	sprintf(string_b, "%d", b);
	while (*a_ptr != '\0' && *b_ptr != '\0') {
		if (*a_ptr - *b_ptr > 0) return true;
		else if (*a_ptr - *b_ptr < 0) return false;
		else {
			++a_ptr;
			++b_ptr;
		} 
	}
	if (*a_ptr == '\0' && *b_ptr != '\0') { // a reach end
		--a_ptr;
		while (*b_ptr != '\0') {
			if (*a_ptr > *b_ptr) return true;
			else if (*a_ptr < *b_ptr) return false;
			else ++b_ptr;
		}
		return true;
	}
	if (*a_ptr != '\0' && *b_ptr == '\0') { // b reach end
		--b_ptr;
		while (*a_ptr != '\0') {
			if (*a_ptr > *b_ptr) return true;
			else if (*a_ptr < *b_ptr) return false;
			else ++a_ptr;
		}
		return true;
	}
	return true; // a and b both reach end simultaneously 
}

void swap(int* arr, int a, int b) {
	int temp = *(arr + a);
	*(arr + a) = *(arr + b);
	*(arr + b) = temp;
} 

/*
*  Partition the subarray arr[lo...hi] so that arr[lo...j-1] <= arr[j] <= 
*  arr[j+1...hi] and return the index j
*/
int partition(int arr[], int lo, int hi) {
	int i = lo;
	int j = hi + 1;
	int cmp = arr[lo];
	while (true) {
		// find item on lo to swap
		while (isLarger(arr[++i], cmp))
			if (i == hi) break;
		// find item on hi to swap
		while (isLarger(cmp, arr[--j]))
			if (j == lo)  break;
		// check if pointers cross
		if (i >= j) break;
		swap(arr, i, j);
	}
	// put partioning item cmp at a[j]
	swap(arr, lo, j);
	return j;
}

/*
*  Sorts the array in descending order using isLarger() as comparable
*/
void quickSort(int arr[], int lo, int hi)
{
   if (lo < hi) 
   {
   	// divide and conquer
 	   int j = partition(arr, lo, hi);
       quickSort(arr, lo, j-1);
       quickSort(arr, j+1, hi);
   }
}

void test_isLarger() {
	assert(!isLarger(1, 5));
	assert(isLarger(4, 3));
	assert(isLarger(33, 31));
	assert(isLarger(3, 3));
	assert(!isLarger(759, 8));
	assert(isLarger(1, 1111));
	assert(isLarger(1111, 1));
	assert(isLarger(1112, 1));
	assert(!isLarger(1, 1112));
	assert(isLarger(34, 3));
	assert(!isLarger(3, 34));
	assert(isLarger(34, 30));
	assert(!isLarger(30, 34));
	assert(isLarger(3, 30));
	assert(!isLarger(30, 3));
}

void printArray(int arr[], int size) {
	for (int i = 0; i < size; ++i) 
		printf("%d ", arr[i]);
	printf("\n");
}

void printCharArr(char* arr, int size) {
	for (int i = 0; i < size; ++i) {
		printf("%c ", *(arr + i));
	}
	printf("\n");
}

int isSorted(int arr[], int size) {
	for (int i = 0; i < size - 1; ++i) 
		if (arr[i] < arr[i+1]) return false;
	return true;
}

void test_quickSort() {
	int arr1[] = {7, 0, 8, 1, 2, 9, 3, 5, 6, 4};
	printf("--------------------------\n");
	printf("before: ");
	printArray(arr1, 10);
	quickSort(arr1, 0, 9);
	printf("after: ");
	printArray(arr1, 10);

	int arr2[] = {3, 30, 34, 5, 9};
	printf("--------------------------\n");
	printf("before: ");
	printArray(arr2, 5);
	quickSort(arr2, 0, 4);
	printf("after: ");
	printArray(arr2, 5);
	//assert(isSorted(arr1, 10));
}

// return the number of digits for the given integer
int countDigit(int num) {
	if (!num) return 1;
	int count = 0;
	while (num) {
		num /= 10;
		count++;
	}
	return count;
}

char* largestNumber(int* nums, int numsSize) {
	quickSort(nums, 0, numsSize-1);
	
	int numsTotalDigit = 0;
	for (int i = 0; i < numsSize; ++i) {
		numsTotalDigit += countDigit(*nums + i);
	}

	char *result = malloc(numsTotalDigit);
	for (int i = 0; i < numsSize; ++i) {
		char* buff = malloc(countDigit(*nums + i));
		sprintf(buff, "%d", *nums++);
		strcat(result, buff); 
		free(buff);
	}
	printCharArr(result, numsTotalDigit);
	printf("%s\n", result);
	return result;
}

void test_largestNumber() {
	int arr[] = {3, 30, 34, 5, 9};
	largestNumber(arr, 5);
	// printArray(arr, 5);
}

int main() {
	
	test_isLarger();
	printf("isLarge is good!\n");
	
	test_quickSort();
	printf("quickSort is good!\n");
	
	test_largestNumber();
	printf("largestNumber is good!\n");
	
	return 0;
}
