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



int kmpMatcher(string text, string pattern, vector<int> pi) {
	int n = text.length();
	int m = pattern.length();
	//vector<int> pi =  computePrefixFunction(pattern);
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





/*A distância de edição entre P (pattern string) e T (text string)
é o menor número de alterações necessárias para transformar
T em P, em que as alterações podem ser:
• substituir um carácter por outro
• inserir um carácter
• eliminar um carácter */


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

