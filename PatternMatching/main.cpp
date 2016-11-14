#include <iostream>
#include "PatternMatching.h"

int main(int argc, char* argv[]) {
	char target[100] = "derekdick";
	char pattern[20] = "dick";
	std::cout << PatternMatching::BruteForce(target, pattern) << std::endl;

	return 0;
}
