#include "stem.h"
#include "parse.h"
#include "except.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

std::vector<string> readfile(string filename){
        //Raw words from file
        std::vector<string> words1;

        ifstream infile(filename); //open the file

        //Read the file into the words vector
        if (infile.is_open() && infile.good()) {
                //      cout << "File is now open!\n";
                string in;
                if (infile >> in){
                        words1.push_back(in);
                        while (infile >> in) {
                //        cout << in << "\n";
                                words1.push_back(in);
                        }
                }
                else{
                        cerr << "Cannot read file: " << filename << " Exiting program." << "\n";

                }
        }
        else{
                cerr << "Invalid file: " << filename << " Exiting program." << "\n";
        }
        return words1;
}



std::vector<string> punct(std::vector<string> words1){
        //Remove punctuation
        std::vector<string> words2;
        for (int a = 0; a < int(words1.size()); a++){
                //examine one string from words vector
                string punct = "";
                string one = "";
                string curr = words1[a];
                for (int b = 0; b < int(curr.length()); b++){
                        //examine individual characters of string
                        char c = curr[b];

                        //If part of a string of puntuation, add to punct string
                        if ((b!=0) && (c != '\'') && (ispunct(curr[b])) && (ispunct(curr[b - 1])) && (curr[b-1] != '\'')){

                                punct+=c;

                                //If end of punctuation string, add to vector
                                if (!ispunct(curr[b + 1]) || (curr[b+1] == '\'')){

                                         words2.push_back(punct);
                                         punct = "";
                                }

                                if ((b == int(curr.length() - 1)) && (one.length() != 0)){
                                        words2.push_back(one);
                                        one = "";
                                }
                        }

                        else if (c == '.'){

                                //If period is part of a number, leave it
                                if ((isdigit(curr[b+1])) && ((b == 0)
                                        || isdigit(curr[b-1]))){
                                        one += c;
                                }

                                //if not part of a number, period is a string
                                else{
                                //break string into period, first part of string
                                //and second part of string
                                        punct += c;
                                        if (one.length() != 0){
                                                words2.push_back(one);
                                                one = "";
                                        }
                                        //If next character is not punctuation,
                                        //punct is a string
                                        if (!ispunct(curr[b + 1]) || (curr[b+1] == '\'')){

                                                words2.push_back(punct);
                                                punct = "";
                                        }
                                }
                                if ((b == int(curr.length() - 1)) && (one.length() != 0)){
                                        words2.push_back(one);
                                        one = "";
                                }

                        }



                        else if (c == ','){
                                //If comma is part of a number, leave it
                                if (isdigit(curr[b+1]) && isdigit(curr[b-1])){
                                        one += c;
                                }

                                //if not part of a number, comma is a string
                                else{
                                //break string into comma and first part of string
                                //add first part of string to vector
                                        punct += c;
                                        if (one.length() != 0){
                                                words2.push_back(one);
                                                one = "";
                                        }
                                        //If next character is not punctuation,
                                        //punct is a string
                                        if (!ispunct(curr[b + 1]) || (curr[b+1] == '\'')){

                                                words2.push_back(punct);
                                                punct = "";
                                        }
                                }

                                if ((b == int(curr.length() - 1)) && (one.length() != 0)){
                                        words2.push_back(one);
                                        one = "";
                                }


                        }

                        //if apostrophe, ignore
                        else if (c == '\'') {
                                one += c;
                                if ((b == int(curr.length() - 1)) && (one.length() != 0)){
                                        words2.push_back(one);
                                        one = "";
                                }
                        }



                        //If ? or !, no applicable rules.
                        //add to punct string, if only punctuation in string,
                        //add to vector
                        else if (ispunct(c)){
                                punct += c;
                                if (one.length() != 0){
                                        words2.push_back(one);
                                        one = "";
                                }

                                if (!ispunct(curr[b + 1]) || (curr[b+1] == '\'')){

                                        words2.push_back(punct);
                                        punct = "";
                                }

                                if ((b == int(curr.length() - 1)) && (one.length() != 0)){
                                        words2.push_back(punct);
                                        punct = "";
                                        words2.push_back(one);
                                        one = "";
                                }

                        }

                        //Alpanumeric character
                        else{
                                one += c;
                                if ((b == int(curr.length() - 1)) && (one.length() != 0)){
                                        words2.push_back(one);
                                        one = "";
                                }
                        }
                }
        }
        return words2;
}




std::vector<string> cap(std::vector<string> words2){
        //Deal with capitalization rules
        std::vector<string> words3;
        for (int a = 0; a < int(words2.size()); a++){
                string curr = words2[a];

                //if 1st character is capitalized,
                if (isupper(curr[0])){
                        //if it is the 1st word or the first word of a sentence
                        if ((a == 0) || (words2[a-1].find('.') != std::string::npos) ||
                                (words2[a-1].find('!') != std::string::npos) ||
                                (words2[a-1].find('?') != std::string::npos)){

                                //cout << "Upper: " << curr << "\n";
                                string s = curr.substr(1, curr.length() - 1);

                                //Check if word contains digit
                                if(std::any_of(curr.begin(), curr.end(), ::isdigit)){
                                        words3.push_back(curr);
                                        //cout << "Has dig: " << curr << "\n";
                                }

                                //Check if word has another capital letter
                                //string s = curr.substr(1, curr.length() - 1);
                                else if ((std::any_of(s.begin(), s.end(), ::isupper))){
                                        words3.push_back(curr);
                                        //cout << "Acronym: " << curr << "\n";
                                }

                                //Don't know if it should be capitalized, add + to word
                                else{
                                        //cout << "Ambiguous: " << curr << "\n";
                                        int n = 0;
					//cout << "+ word: " << curr << " Without +: " << curr.substr(1) << "\n";
                        		for(int j = 0; j < int(words2.size()); j++){
                                		if(curr == words2[j]){
                                        		//cout << "Words: " << words[j] << "\n";
                                        		if(j != 0 && (((words2[j-1].find('.') 
								== std::string::npos) || 
								std::any_of(words2[j-1].begin(), 
								words2[j-1].end(), ::isdigit)) &&
                                				(words2[j-1].find('!') 
								== std::string::npos) &&
                                				(words2[j-1].find('?') 
								== std::string::npos))){
                                        				n++;
							}
                                		}
                        		}

					//cout << curr << ": " << n << "\n";

                        		if(n == 0){
                                		//words.erase(words.begin()+i);
                                		//cout << curr << "\n";
                                		char c = char(tolower(curr[0]));
                                		stringstream ss;
                                		string ch;
                                		ss << c;
                                		ss >> ch;
                                		ch += s;
                                		//cout << "Lower case: " << curr << "\n";
                                		words3.push_back(ch);
                        		}

                        		else{
                                		//words.erase(words.begin()+i);
		                                //cout << "Matched: " << curr << "\n";
                		                words3.push_back(curr);
                        		}
                		
                                       	//string str = "";
                                        //str += '+';
                                        //str += curr;
                                        //words3.push_back(str);
                                }
                        }

                        else {
                                words3.push_back(curr);
                        }

                }

                //else add word to new vector
                else{
                        words3.push_back(curr);

                }

        }
        return words3;
}




std::vector<int> cnt(std::vector<string> words3){
        std::vector<int> count;

        sort(words3.begin(), words3.end());

        for (int i = 0; i <= int(words3.size()); i++){
                count.push_back(1);
                while (i + 1 < int(words3.size())) {
                        if (words3[i + 1] == words3[i]) {
                           // Next word is a duplicate, count it and delete it
                                count[i]++;
                                words3.erase(words3.begin() + i + 1);
                        }
                        else {
                           // New word found
                                break;
                        }
                }
        }

        //count.push_back(0);
        /*for (int j = 0; j < int(words3.size()); j++){
                cout << words3[j] << " " << count[j] << "\n";
        }*/

	return count;

}






std::vector<string> Wordscnt(std::vector<string> words3){
        std::vector<int> count;

        sort(words3.begin(), words3.end());

        for (int i = 0; i <= int(words3.size()); i++){
                count.push_back(1);
                while (i + 1 < int(words3.size())) {
                        if (words3[i + 1] == words3[i]) {
                           // Next word is a duplicate, count it and delete it
                                count[i]++;
                                words3.erase(words3.begin() + i + 1);
                        }
                        else {
                           // New word found
                                break;
                        }
                }
        }
        return words3;
}

