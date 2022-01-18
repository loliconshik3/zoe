#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
using namespace std;

class Image
{
public:
    Image(string path, string name="");

    string name = "";
    string path = "";
    vector<string> tags;

    string tagsToString();
    void addTag(string tag);
    void setTags(vector<string> tags);
};

#endif // IMAGE_H
