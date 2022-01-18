#include "image.h"
#include "utils.h"

#include <QString>

Image::Image(string path, string name)
{
    this->path = path;
    this->name = name;
}

void Image::addTag(string tag) {
    if (std::find(tags.begin(), tags.end(), tag) == tags.end()) {
        this->tags.insert(tags.end(), tag);
    }
}

void Image::setTags(vector<string> tags) {
    this->tags = tags;
}

string Image::tagsToString() {
    QString text = "";
    for (const auto tag : this->tags) {
        text += tag.c_str() + QString(",");
    }
    QStringRef tags(&text, 0, text.length()-1);

    return tags.toString().toStdString();
}
