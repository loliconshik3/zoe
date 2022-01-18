#include "utils.h"

void log(string text) {
    cout << text << endl;
}

string getHomeDir() {
    string homedir;

    if ((homedir = getenv("HOME")).c_str() == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }

    return homedir;
}

void split(string &str, char delim, vector<string> &out) {
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

vector<string> tagsStringToVector(string tagsString) {
    char sep = ',';
    vector<string> tags;

    split(tagsString, sep, tags);

    return tags;
}
