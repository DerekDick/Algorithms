#include "PatternMatching.h"
#include <cstring>

/*Brute-force algorithm for pattern matching.
Return value: The index of the first character of the first matching string
(If there is no matching pattern, return -1)*/
int PatternMatching::BruteForce(char target[], char pattern[]) {
	int length_target = strlen(target), length_pattern = strlen(pattern);
	for (int i = 0; i <= length_target - length_pattern; i++) {
		for (int j = 0; j < length_pattern; j++) {
			if (target[i + j] != pattern[j]) {
				break;
			}
			else if (j == length_pattern - 1) {
				return i;
			}
		}
	}
	return -1;
}
