#ifndef PARSE_H
#define PARSE_H

#include <vector>
#include <string>

using namespace std;

std::vector<std::string> readfile(std::string);
std::vector<std::string> punct(std::vector<std::string>);
std::vector<std::string> cap(std::vector<std::string>);
std::vector<int> cnt(std::vector<std::string>);
std::vector<std::string> Wordscnt(std::vector<std::string>);

#endif
