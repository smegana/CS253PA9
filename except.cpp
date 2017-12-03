#include "tfidf.h"
#include "stem.h"
#include "parse.h"
#include "except.h"
#include <string>
#include <vector>

string except(string curr, std::vector<string> ex1, std::vector<string> ex2){
	for(int i = 0; i < int(ex1.size()); i++){
		if(ex1[i] == curr){
			curr = ex2[i];
		}
	}
	return curr;
}

bool ifExcept(string curr, std::vector<string> ex1, std::vector<string> ex2){
	for(int i = 0; i < int(ex1.size()); i++){
                if(ex1[i] == curr){
                        return true;
                }
        }
        return false;
}
