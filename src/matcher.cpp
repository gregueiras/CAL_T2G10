/*
 * matcher.cpp
 */
#include "matcher.h"


vector<int> computePrefixFunction(string pattern)
{
	int m = pattern.length();
	vector<int> pi(m);
	pi.at(0) = 0;
	int k = 0;
	for (int q = 1; q < m; q++)
	{
		while(k > 0 && pattern[k] != pattern[q]){
			k = pi.at(k-1);
		}
		if (pattern[k+1] == pattern[q])
			k++;
		pi.at(q) = k;
	}
	return pi;

}



int kmpMatcher(string text, string pattern) {
	int n = text.length();
	int m = pattern.length();
	vector<int> pi =  computePrefixFunction(pattern);
	int q = 0;
	int count = 0;

	//caso text seja menor que pattern
	if (n < m)
		return 0;
	//caso text e pattern tenham o mesmo tamanho
	if (m == n)
		return (text == pattern);

	for (int i = 0; i < n; i++)
	{
		while(q>0 && pattern[q] != text[i])
		{
			q = pi.at(q-1);
		}
		if (pattern[q] == text[i])
			q++;
		if (q == m-1)
		{
			q =pi.at(q);
			count++;
		}
	}
	return count;
}


int numStringMatching(string filename,string toSearch) {
	int num = 0;
	string line;
	ifstream input;
	input.open(filename);
	while (getline(input, line))
	{
		num += kmpMatcher(line, toSearch);
	}

	input.close();
	return num;
}


//ha um mais eficaz mas ainda nao o implementei


/*A distância de edição entre P (pattern string) e T (text string)
é o menor número de alterações necessárias para transformar
T em P, em que as alterações podem ser:
• substituir um carácter por outro
• inserir um carácter
• eliminar um carácter */

//Tempo e espaco: O(|P|.|T|)
int editDistance1(string pattern, string text) {
/*	int t = text.length() + 1;
	int p = pattern.length()+ 1;

	int D[t][p];

	for (int i = 0; i < t ; i++)
	{
			D[i][0] = i;
	}
	for (int i = 0; i < p; i++)
	{
		D[0][i] = i;
	}

	for (int i = 1; i < t; i++)
	{
		for (int j = 1; j < p; j++)
		{
			if (pattern[j - 1] == text[i - 1])
				D[i][j] = D[i - 1][j - 1];
			else
				D[i][j] = 1 + min(min(D[i - 1][j - 1], D[i - 1][j]), D[i][j - 1]);
		}
	}
	return D[t-1][p-1];
	*/
	return 0;
}

//Espaco: O(|T|)
int editDistance(string pattern, string text)
{
	int t = text.length()+1;
	int p = pattern.length()+1;
	vector<int> D;
	int old, nw;
	for (int j = 0; j < t; j++)
	{
		D.push_back(j);
	}

	for (int i = 1; i < p ; i++)
	{
		old = D.at(0);
		D.at(0) = i;
		for (int j = 1; j < t; j++)
		{
			if (pattern[i-1] == text[j-1])
				nw = old;
			else
				nw = 1 + min(min(old,D.at(j)), D.at(j-1));

			old = D.at(j);
			D.at(j)= nw;
		}
	}

	return D.at(t-1);
}


float numApproximateStringMatching(string filename,string toSearch) {
	int num = 0;
	int count = 0;
	string line;
	ifstream input;
	input.open(filename);

	while (getline(input, line))
	{
	  istringstream iss(line);
	  string s;
	  while ( getline( iss, s, ' ' ) )
	  {
		num += editDistance(s, toSearch);
		count ++;
	  }
	}

	input.close();
	float avg = num/(count*1.0);
	return avg;
}
