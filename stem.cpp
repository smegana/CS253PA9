#include "stem.h"
#include "parse.h"
#include "except.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


string stem(string curr){
	string s = step1(curr);
	s = step2(s);
	s = step3(s);
	s = step4(s);
	s = step5(s);
	s = step6(s);
	s = step7(s);
	s = step8(s);
	return s; 
}


bool hasSuffix(string str, string suffix){
	if(str.length() >= suffix.length()){
		return (0 == (str.compare(str.length() - suffix.length(), 
			suffix.length(), suffix)));
	}
	else{
		return false;
	}
}

string getRegion(int region, string str){
	int vow = 0;
	
	for(int i = 0; i < int (str.length()); i++){
		char c = str[i];
		if(c=='a' || c=='A' || c=='e' || c=='E' ||
                	c=='i' || c=='I' || c=='o' ||
                	c=='O' || c=='u' || c=='U' ||
                	c == 'y' || c == 'Y'){
			vow++;
							
			}
		else if(vow >= 1){
			if (region == 2){
                        	return getRegion(1, str.substr(i+1, str.length()-1));
                        }
			//cout << "getRegion " << region << " in "
                        //        << str << " substring: " <<
                        //        str.substr(i+1, str.length()-1) << "\n";
                        return str.substr(i+1, str.length()-1);
		}
	}
	return "";
}


bool isVowel(string str, int index){
	char c = str[index];
	if(c=='a' || c=='A' || c=='e' || c=='E' ||
        	c=='i' || c=='I' || c=='o' ||
        	c=='O' || c=='u' || c=='U' ||
		c == 'y' || c == 'Y'){
		return true;
	}

	else{
		return false;
	}
}


bool isDouble(string str){
	if(str == "bb" || str == "dd" || str == "ff" ||
		str == "gg" || str == "mm" || str == "nn" ||
		str == "pp" || str == "rr" || str == "tt"){
		return true;
	}

	else{
		return false;
	}
}


bool isShort(string str){
	if(isShortSyll(str) && (getRegion(1, str) == "")){
		return true;		
	}

	return false;
}

bool isShortSyll(string str){
	//cout << !isVowel(str, str.length()-3)  << "\n";
	if((str.length() > 2) && (!isVowel(str, str.length()-1) && 
		isVowel(str, str.length()-2) &&
                !isVowel(str, str.length()-3))){
                if(str[str.length() - 1] != 'w' && str[str.length() - 1] != 'x' &&
                        str[str.length() - 1] != 'y'){
			return true;
                }
        }

	else if(((str.length() == 2) && isVowel(str, 0) && !isVowel(str, 1))){
		//cout << str << "\n";
                return true;
        }
	//cout << str << "\n";
	return false;
}


string step1(string curr){
	//Determine where it is and what comes after it
	if (curr.find('\'') == 0){
		return curr.substr(1, curr.length());
	}

	else if (hasSuffix(curr, "'s'")){
		return curr.substr(0, curr.length() - 3);
	}
	
	else if (hasSuffix(curr, "'s")){
                return curr.substr(0, curr.length() - 2);
        }

	else if (hasSuffix(curr, "'")){
                return curr.substr(0, curr.length() - 1);
        }

	return curr;
}


string step2(string curr){
	if (hasSuffix(curr, "sses")){
                return curr.substr(0, curr.length() - 2);
        }

	else if (hasSuffix(curr, "ied") || hasSuffix(curr, "ies")){
		if (curr.length() == 4){
                	return curr.substr(0, curr.length() - 1);
		}
		else {
			return curr.substr(0, curr.length() - 2);
		}
        }

	else if (hasSuffix(curr, "us")){
		return curr;
	}

	else if (hasSuffix(curr, "ss")){
		return curr;
	}

	else if (hasSuffix(curr, "s")){
		int vow = 0;
		for(int i = 0; i < int(curr.length()); i++){
			char c = curr[i];
			if(c=='a' || c=='A' || c=='e' || c=='E' ||
                		c=='i' || c=='I' || c=='o' ||
                		c=='O' || c=='u' || c=='U' ||
                		c == 'y' || c == 'Y'){
				vow++;
			}
		}

		if (!isVowel(curr, curr.length() - 2) || (vow >= 2)){
			return curr.substr(0, curr.length() - 1);
		}
	}

	return curr;
}


string step3(string curr){
	if(hasSuffix(curr, "eedly") || hasSuffix(curr, "eed")){
		string R1 = getRegion(1, curr);
		//cout << R1 << "\n";
		if(hasSuffix(R1, "eed")){
			return curr.substr(0, (curr.length()-1));
		}
		else if(hasSuffix(R1, "eedly")){
			return curr.substr(0, (curr.length()-3));
		}
	}

	else if(hasSuffix(curr, "ed") || hasSuffix(curr, "edly") ||
		hasSuffix(curr, "ing") || hasSuffix(curr, "ingly")){
		int minNum;
		int suffLen = 0;
		if (hasSuffix(curr, "ed")){
			minNum = 2;
			suffLen = 2;
		}
	
		else if(hasSuffix(curr, "ing")){
			minNum = 2;
			suffLen = 3;
		}
	
		else if(hasSuffix(curr, "edly")){
			minNum = 3;
			suffLen = 4;
		}

		else if(hasSuffix(curr, "ingly")){
                        minNum = 3;
                        suffLen = 5;
                }

		int cnt = 0;
		for (int i = 0; i < int(curr.length()); i++){
			if(isVowel(curr, i)){
				cnt++;
			}
		}
		
		if(cnt < minNum){
			return curr;
		}
	
		int b = curr.length()-suffLen-2;
		string sub = curr.substr(b, 2);
		//cout << "Substring: " << sub << "\n";
		if(sub == "at" || sub == "bl" || sub == "iz" ||
			isShort(curr.substr(0, curr.length()-suffLen))){
			//cout << (curr.substr(0, (curr.length()-suffLen)) + "e") << "\n";
			return (curr.substr(0, (curr.length()-suffLen)) + "e");
		}

		else if(isDouble(sub)){
			return curr.substr(0, (curr.length()-suffLen-1));
		}
	
		return curr.substr(0, (curr.length()-suffLen));	
	}

	return curr;

}


string step4(string curr){
	if(hasSuffix(curr, "y")){
		if((curr.length() > 2) && !isVowel(curr, curr.length()-2)){
			return (curr.substr(0, curr.length()-1) + "i");
		}
	}
	return curr;
}


string step5(string curr){
	
	if(hasSuffix(curr, "enci")){
		return (curr.substr(0, curr.length()-1) + "e");
	}

	if(hasSuffix(curr, "anci")){
		return (curr.substr(0, curr.length()-1) + "e");
        }

	if(hasSuffix(curr, "abli")){
		(curr.substr(0, curr.length()-1) + "e");
        }

	if(hasSuffix(curr, "entli")){
		return curr.substr(0, curr.length()-2);
        }

	if(hasSuffix(curr, "izer") || hasSuffix(curr, "ization")){
		if(hasSuffix(curr, "izer")){
			return (curr.substr(0, curr.length()-1));
		}
		
		if(hasSuffix(curr, "ization")){
			return (curr.substr(0, curr.length()-5) + "e");
		}
        }

        if(hasSuffix(curr, "ational") || hasSuffix(curr, "ation") ||
                hasSuffix(curr, "ator")){
                int suffLen;
                if(hasSuffix(curr, "ational")){
                        suffLen = 7;
                }

                else if(hasSuffix(curr, "ation")){
                        suffLen = 5;
                }

                else if(hasSuffix(curr, "ator")){
                        suffLen = 4;
                }

		//cout << (curr.substr(0, curr.length()-suffLen) + "ate") << "\n";
                return (curr.substr(0, curr.length()-suffLen) + "ate");

        }

	if(hasSuffix(curr, "tional")){
                return curr.substr(0, curr.length()-2);
        }

	if(hasSuffix(curr, "alism") || hasSuffix(curr, "aliti") ||
		hasSuffix(curr, "alli")){
		if(hasSuffix(curr, "alism") ||
			hasSuffix(curr, "aliti")){
			return curr.substr(0, curr.length()-3);
		}
		
		else{
			return curr.substr(0, curr.length()-2);
		}
        }

	if(hasSuffix(curr, "fulness")){
		return curr.substr(0, curr.length()-4);
        }

	if(hasSuffix(curr, "ousli") || hasSuffix(curr, "ousness")){
		if(hasSuffix(curr, "ousli")){
			return curr.substr(0, curr.length()-2);
		}

		else{
			return curr.substr(0, curr.length()-4);
		}
        }

	if(hasSuffix(curr, "iveness") || hasSuffix(curr, "iviti")){
		if(hasSuffix(curr, "iveness")){
			return curr.substr(0, curr.length()-4);
		}

		else{
			return (curr.substr(0, curr.length()-3) + "e");
		}
        }

	if(hasSuffix(curr, "biliti") || hasSuffix(curr, "bli")){
		if(hasSuffix(curr, "biliti")){
			return (curr.substr(0, curr.length()-5) + "le");
		}

		else{
			return (curr.substr(0, curr.length()-1) + "e");
		}
        }

	if(hasSuffix(curr, "ogi")){
		if(curr[curr.length()-4] == 'l'){
			return curr.substr(0, curr.length()-1);
		}
        }

	if(hasSuffix(curr, "fulli")){
		return curr.substr(0, curr.length()-2);
        }

	if(hasSuffix(curr, "lessli")){
		return curr.substr(0, curr.length()-2);
        }

	if(hasSuffix(curr, "li")){
		char c = curr[curr.length()-3];
		if(c=='c' || c == 'd' || c == 'e' || 
			c == 'g' || c == 'h' || c == 'k' || 
			c == 'm' || c == 'n' || c == 'r' || c == 't'){
			return curr.substr(0, curr.length()-2);
		}
        }

	return curr;
}


string step6(string curr){
	string R1 = getRegion(1, curr);
	
	if(hasSuffix(R1, "ational")){
		return (curr.substr(0, curr.length()-5) + "e");
	}	

	else if(hasSuffix(R1, "tional")){
		return (curr.substr(0, curr.length()-2));
	}

	else if(hasSuffix(R1, "alize")){
		return (curr.substr(0, curr.length()-3));
	}

	else if(hasSuffix(R1, "icate") || hasSuffix(R1, "iciti") || 
		hasSuffix(R1, "ical")){
		if(hasSuffix(R1, "ical")){
			return (curr.substr(0, curr.length()-2));
		}
                return (curr.substr(0, curr.length()-3));
        }

	else if(hasSuffix(R1, "ful")){
		return (curr.substr(0, curr.length()-3));
	}

	else if(hasSuffix(R1, "ness")){
		return (curr.substr(0, curr.length()-4));
	}

	string R2 = getRegion(2, curr);
	if(hasSuffix(R2, "ative")){
		return (curr.substr(0, curr.length()-5));
	}

	return curr;
}


string step7(string curr){
	string R2 = getRegion(2, curr);
	//cout << curr << ": "  << R2 << "\n";
	if(hasSuffix(R2, "ement")){
		return (curr.substr(0, curr.length()-5));
	}

	else if(hasSuffix(R2, "ance") || hasSuffix(R2, "ence") ||
                hasSuffix(R2, "able") || hasSuffix(R2, "ible") ||
                hasSuffix(R2, "ment")){
		//cout << curr << "\n";
		return (curr.substr(0, curr.length()-4));
	}

	else if(hasSuffix(R2, "ant") || (hasSuffix(R2, "ent") 
		&& (curr[curr.length()-4] != 'm')) || 
		hasSuffix(R2, "ism") || hasSuffix(R2, "ate") ||
		hasSuffix(R2, "iti") || hasSuffix(R2, "ous") ||
		hasSuffix(R2, "ive") || hasSuffix(R2, "ize")){
		return (curr.substr(0, curr.length()-3));
	}

	else if(hasSuffix(R2, "al") || hasSuffix(R2, "er") || hasSuffix(R2, "ic")){
                return (curr.substr(0, curr.length()-2));
        }
	
	char c = curr[curr.length() - 4];
	//cout << curr << " ion char: " << c << "\n";
	if(hasSuffix(R2, "ion") && (c == 't' || c == 's')){
		return (curr.substr(0, curr.length()-3));
	}

	return curr;
}


string step8(string curr){
	string R1 = getRegion(1, curr);
	string R2 = getRegion(2, curr);
	if(hasSuffix(R2, "e") || (hasSuffix(R1, "e") && 
		!isShortSyll(curr.substr(0, curr.length()-1)))){
		//cout << !isShortSyll(curr.substr(0, curr.length()-1)) << "\n";
		return curr.substr(0, curr.length()-1);
	}

	else if(hasSuffix(R2, "l") && curr[curr.length() - 2] == 'l'){
		return curr.substr(0, curr.length()-1);
	}

	return curr;
}

