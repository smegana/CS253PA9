#include "tfidf.h"
#include "stem.h"
#include "parse.h"
#include "except.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

std::vector<double> wordletters(std::vector<string> words){
	string curr;
	double wordcount;
	double lettercount;
	for(int i = 0; i < int (words.size()); i++){
		curr = words[i];
		if(!ispunct(curr[0]) || (curr[0] == '\'') || 
				((curr[0] == '.') && isdigit(curr[1]))){
			wordcount++;
			lettercount += curr.length();
		}
	}

	//cout << "Letters = " << lettercount << "\n";
	//cout << "Words = " << wordcount << "\n";

	std::vector<double> count;
	count.push_back(lettercount);
	count.push_back(wordcount);
	return count;
}



double L(std::vector<string> words){
	std::vector<double> count = wordletters(words);
	if(count[1] < 1){
		return -1;
	}
	return ((count[0] / count[1]) * 100);
}



int countsentences(std::vector<string> words){
	string curr;
	int sentences;
	for(int i = 0; i < int (words.size()); i++){
		curr = words[i];
		if(ispunct(curr[0]) && !isdigit(curr[1]) &&
				((curr.find('.') != std::string::npos) || 
				(curr.find('?') != std::string::npos) ||
				(curr.find('!') != std::string::npos))){
			sentences++;
		}
	}
	
	//cout << "Sentences = " << sentences << "\n";

	return sentences;
}



double S(std::vector<string> words){
	std::vector<double> count = wordletters(words);
	double cnt = double (countsentences(words));
	return ((cnt / count[1]) * 100);
}



int CL(std::vector<string> words){
	double s = S(words);
	//cout << "S(doc) = " << s << "\n";
	double l = L(words);
	if(l == -1){
		return -1;
	}
	//cout << "L(doc) = " << l << "\n";
	double CL = (0.0588*l) - (0.296*s) - 15.8;
	//cout << "CL(doc) = " << CL << "\n";
	return CL;
}
