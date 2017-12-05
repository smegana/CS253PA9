#include "readlevel.h"
#include "tfidf.h"
#include "stem.h"
#include "parse.h"
#include "except.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[])
{
        //Ensure one file has been entered
        if(argc == 5) {
		//Correct
	}

	else{
        	cerr << "Incorrect number of arguments entered. Exiting " << argv[0] << "\n";
        	return -1;
	}

	double lowRL = atof(argv[3]);
	double highRL = atof(argv[4]);

	if(lowRL > highRL){
		cerr << "Invalid high and low reading levels entered. Exiting " << argv[0] << "\n";
                return -1;
	}

	//Read file into vector for processing
	std::vector<string> words = readfile(argv[1]);
        if(words.empty()){
		cerr << "No original file to compare to. Exiting " << argv[0] << "\n";
        	return -1;
        }


	




	std::vector<string> files = readfile(argv[2]);
	if(files.empty()){
		cerr << "No files to compare to. Exiting " << argv[0] << "\n";
		return -1;
	}


	        //Read Exception File
        std::vector<string> except1;
        std::vector<string> except2;

        ifstream infile(files[0]); //open the file

        //Read the file into the words vector
        if (infile.is_open() && infile.good()) {
                //      cout << "File is now open!\n";
                string in;
                string w;
                while (getline(infile, in)){
                        istringstream iss(in);
                        if (iss >> w){
                                except1.push_back(w);
                                if (iss >> w){
                                        except2.push_back(w);
                                        if (iss >> w){
                                                cerr << "Incorrectly formatted exception file.\n";
                                                return -1;
                                        }
                                }
                                else{
                                        cerr << "Incorrectly formatted exception file.\n";
                                        return -1;
                                }
                        }
                }
        }
        else{
                cerr << "Invalid exception file: " << files[0] << " Exiting program." << "\n";
                return -1;
        }

        






	//Process Original File
	std::vector<string> originalFile;

        words = punct(words);
        words = cap(words);
        for (int i = 0; i < int(words.size()); i++){
                string curr = words[i];

                //If has punctuation, digits, or capitalization
                //or is 2 characters or less, add to words4
                if ((ispunct(curr[0]) && (curr[0] != '\''))){
                        //words1.push_back(curr);
                }
                else if (std::any_of(curr.begin(), curr.end(), ::isdigit) ||
                        (std::any_of(curr.begin(), curr.end(), ::isupper)) ||
                        (int(curr.length()) <= 2)){

                         originalFile.push_back(curr);
                }
                else{
                        //Exception check
                        if(ifExcept(curr, except1, except2)){
                                originalFile.push_back(except(curr, except1, except2));
                        }
                        else{
                                originalFile.push_back(stem(curr));
                        }
                }

        }
        sort(originalFile.begin(), originalFile.end());
	std::vector<int> originalFileCount = cnt(originalFile);
        originalFile = Wordscnt(originalFile);











	//final counti of words
        std::vector< vector<string> > allFileWords;
        allFileWords.push_back(originalFile);

        std::vector< vector<int> > allFileCount;
	allFileCount.push_back(originalFileCount);

        std::vector<string> fileNames;


	std::vector<string> tempwords;

	std::vector<double> cl;


        for(int k = 1; k < int(files.size()); k++){
                tempwords = readfile(files[k]);
                if(tempwords.empty()){
			//cerr << "Cannot read file " << files[k] << ". Exiting " << argv[0] << "\n";
                        return -1;
                }

                tempwords = punct(tempwords);
		cl.push_back(CL(tempwords));

		

			fileNames.push_back(files[k]);
                	tempwords = cap(tempwords);

                	std::vector<string> words1;

                	for (int i = 0; i < int(tempwords.size()); i++){
                        	string curr = tempwords[i];

                        	//If has punctuation, digits, or capitalization
                        	//or is 2 characters or less, add to words4
                        	if ((ispunct(curr[0]) && (curr[0] != '\''))){
                                	//words1.push_back(curr);
                        	}
                        	else if (std::any_of(curr.begin(), curr.end(), ::isdigit) ||
                                	(std::any_of(curr.begin(), curr.end(), ::isupper)) ||
                                	(int(curr.length()) <= 2)){

                                	words1.push_back(curr);
                        	}
                        	else{
                                	//Exception check
                                	if(ifExcept(curr, except1, except2)){
                                        	words1.push_back(except(curr, except1, except2));
                                	}
                                	else{
                                        	words1.push_back(stem(curr));
                                	}
                        	}

                	}
                	sort(words1.begin(), words1.end());

                	allFileWords.push_back(Wordscnt(words1));

                	allFileCount.push_back(cnt(words1));
		

        }


	//for(int x = 0; x < (int)allFileWords.size(); x++){
                /*for(int y = 0; y < (int)allFileWords[0].size(); y++){
                        cout << allFileWords[0][y] << " " << allFileCount[0][y] << "\n";
                }
                cout << "\n\n\n";*/
        //}




	double highestTFIDF = 0.0;
	string bestMatch = "";
	double currtfidf;
	
	
	
	std::vector< vector<double> > totaltfidf = tfidf(allFileWords, allFileCount);
        //double currtfidf;
        //
        //
        //
       
	/*for(int x = 0; x < totaltfidf.size(); x++){
		for(int y = 0; y < totaltfidf[x].size(); y++){
			cout << totaltfidf[x][y] << " ";
		}
		cout << "\n";
	}*/

        //
        //
        //
        for(int i = 0; i < int(totaltfidf[0].size()); i++){
		if((cl[i] <= highRL) && (cl[i] >= lowRL)){
                	currtfidf = totaltfidf[0][i+1];
                	//cout << currtfidf << " ";
                	//cout << "File: " << fileNames[i] << " Sim: " << currtfidf << "\n";
                	if(currtfidf > highestTFIDF){
				highestTFIDF = currtfidf;
				bestMatch = fileNames[i];
			}
		}
        }

		/*for(int j = 1; j < int(totaltfidf[0].size()); j++){
			currtfidf = totaltfidf[0][j];
			cout << currtfidf << " ";
		
		cout << "File: " << fileNames[j] << " Sim: " << currtfidf << "\n";
		if(currtfidf > highestTFIDF){
			highestTFIDF = currtfidf;
			bestMatch = fileNames[j];
		}
		//cout << "\n";
		
	}*/	

	if(bestMatch.length() == 0){
		cerr << "No file entered in the given range.\n";
		return -1;
	}

	cout << bestMatch << "\n";
	return 0;
	        
}
