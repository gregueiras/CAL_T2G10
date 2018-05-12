/*
 * matcher.cpp
 */
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;



vector<int> computePrefixFunction(string pattern);


int kmpMatcher(string text, string pattern);


int numStringMatching(string filename,string toSearch);


int editDistance(string pattern, string text);


float numApproximateStringMatching(string filename,string toSearch) ;
