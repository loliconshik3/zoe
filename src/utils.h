#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

using namespace std;

void log(string text);
string getHomeDir();
void split(string &str, char delim, vector<string> &out);
vector<string> tagsStringToVector(string tagsString);

#endif // UTILS_H
