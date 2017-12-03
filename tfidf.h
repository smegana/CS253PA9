#ifndef TFIDF_H
#define TFIDF_H

#include <vector>
#include <string>

using namespace std;

std::vector< std::vector<double> > tfidf(std::vector< std::vector<std::string> >,
	std::vector< std::vector<int> >);

std::vector< std::vector<double> > totaltfidf(std::vector< std::vector<std::string> >, 
	std::vector< std::vector<double> >);

double doctfidf(std::vector<std::string>, std::vector<std::string>,
                std::vector<double>, std::vector<double>);

int numDocs(std::string, std::vector< std::vector<std::string> >);

#endif

