/*
 * matcher.h
 */
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;



vector<int> computePrefixFunction(string pattern);

int kmpMatcher(string text, string pattern, vector<int> pi);

int editDistance(string pattern, string text);


