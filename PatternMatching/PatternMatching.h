#ifndef _PATTERN_MATCHING_H_
#define _PATTERN_MATCHING_H_

class PatternMatching {
public:
	static int BruteForce(char target[], char pattern[]);
	static int KMP(char target[], char pattern[]);
};

#endif // _PATTERN_MATCHING_H_
