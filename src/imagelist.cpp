#include "imagelist.h"
#include "imagelabel.h"
#include "searchbox.h"
#include "utils.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QPixmap>
#include <QShortcut>
#include <QApplication>
#include <QClipboard>
#include <QInputDialog>
#include <QTextStream>

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
using namespace std;

ImageList::ImageList(MainWindow *parent) : QListWidget(parent)
{
    root = parent;

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    loadImageList();
    setShortcuts();
    setStyle();
}

void ImageList::saveImageList() {
    string homedir = getHomeDir();
    string imagesPath = homedir + "/.config/zoe/images";

    for (const auto &image : images) {
        Image *img = images[image.first];

        auto hash = std::hash<string>()(img->path);
        string totalPath = imagesPath + "/" + to_string(hash);

        QFile file(totalPath.c_str());
        if (!file.exists() && file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);

            out << img->path.c_str() + QString("\n") + img->tagsToString().c_str();

            file.close();
        }
    }
}

void ImageList::loadImageList() {
    string homedir = getHomeDir();
    string path = homedir + "/.config/zoe/images";

    for (const auto & entry : fs::directory_iterator(path)){
        string path = entry.path();

        QFile file(path.c_str());
        if (file.open(QIODevice::ReadOnly)) {
            vector<string> lineList;
            QTextStream in(&file);
            while (!in.atEnd())
            {
               QString line = in.readLine();
               lineList.push_back(line.toStdString());
            }

            string filepath = lineList[0];
            string filetags = "";
            vector<string> tagList;
            if (lineList.size() > 1) {
                filetags = lineList[1];
                tagList = tagsStringToVector(filetags);
            }

            QFile imgFile(filepath.c_str());
            QFileInfo imgFileInfo(imgFile);
            if (imgFile.exists()) {
                string filename = imgFileInfo.fileName().toStdString();
                Image *img = new Image(filepath, filename);

                if (!tagList.empty()) {
                    img->setTags(tagList);
                    filename += " (" + img->tagsToString() + ")";
                }

                images[filename] = img;
                addItem(filename.c_str());
            }
            file.close();
        }
    }

    sortItems();
    if (count() > 0) {
        setCurrentItem(item(0));
    }
    currentItemChanged();
}

void ImageList::removeSavedImage(string path) {
    string homedir = getHomeDir();
    string imagesPath = homedir + "/.config/zoe/images";

    auto hash = std::hash<string>()(path);
    string totalPath = imagesPath + "/" + to_string(hash);
    string rmCom = "rm " + totalPath;

    system(rmCom.c_str());
}

void ImageList::copyImage() {
    if (count() == 0) {
        return;
    }

    string cname = currentItem()->text().toStdString();
    Image *im = images[cname];
    string path = im->path;

    QClipboard *clipboard = QApplication::clipboard();
    QPixmap image = QPixmap(path.c_str());

    clipboard->setPixmap(image);
}

void ImageList::currentItemChanged() {
    if (count() == 0) {
        root->imageLabel->setPixmap(QPixmap());
        return;
    }

    string cname = currentItem()->text().toStdString();
    Image *im = images[cname];
    string path = im->path;

    string tags = im->tagsToString();
    root->imageLabel->setToolTip(tags.c_str());

    QPixmap img(path.c_str());
    int maxWidth = img.width() * 1;
    int maxHeight = img.height() * 1;

    if (maxWidth > 640) {maxWidth = 640;}
    if (maxHeight > 360) {maxHeight = 360;}

    auto image = img.scaled(maxWidth, maxHeight, Qt::KeepAspectRatio);
    root->imageLabel->setPixmap(image);
}

void ImageList::addImagesFromDirectory(string path) {
    string fileName;

    //images.clear();
    //clear();

    for (const auto & entry : fs::directory_iterator(path)){
        string path = entry.path();
        QFile file(path.c_str());
        QFileInfo info(file);

        QString extension = info.completeSuffix();

        list<QString> extList = {
            "png", "jpg", "jpeg", "webp"
        };
        bool isFileImage = (std::find(extList.begin(), extList.end(), extension) != extList.end());
        bool isLoaded = false;

        for (const auto img : images) {
            Image *image = images[img.first];
            if (image->path == path) {
                isLoaded = true;
            }
        }

        if ( !isLoaded && file.exists() && !entry.is_directory() && isFileImage ) {
            fileName = entry.path().filename();
            Image *img = new Image(entry.path(), fileName);

            images[fileName] = img;
            addItem(fileName.c_str());
        }
    }

    sortItems();
    if (count() > 0) {
        setCurrentItem(item(0));
        saveImageList();
    }
}

void ImageList::addTagToCurrentItem() {
    if (count() == 0) {
        return;
    }

    bool ok;
    QString text = QInputDialog::getText(this, tr("Add new tag"),
                                         tr("Tag:"), QLineEdit::Normal,
                                         "name", &ok);
    if (ok && !text.isEmpty()) {
        string cname = currentItem()->text().toStdString();
        Image *im = images[cname];

        im->addTag(text.toStdString());

        map<string, Image*>::iterator it;
        it = images.find(cname);
        images.erase(it);

        string totalName = im->name + " (" + im->tagsToString() + ")";
        images[totalName] = im;

        currentItem()->setText(totalName.c_str());
        removeSavedImage(im->path);

        saveImageList();
        currentItemChanged();
    }
}

void ImageList::redraw() {
    clear();

    string searchQuery = root->searchBox->text().toLower().toStdString();
    for (const auto & image : images) {
        Image *im = images[image.first];

        string fileName = QString(image.first.c_str()).toLower().toStdString();
        bool nameSearch = fileName.find(searchQuery) != string::npos;
        bool tagsSearch = false;

        for (const auto tag : im->tags) {
            if (tag.find(searchQuery) != string::npos) {
                tagsSearch = true;
                break;
            }
        }

        if ( nameSearch || tagsSearch ) {
            QString name = image.first.c_str();
            addItem(name);
        }
    }

    sortItems();
    setCurrentItem(item(0));
    currentItemChanged();
}

void ImageList::setStyle() {
    setStyleSheet("QListWidget { background: #383a46; color: #d3d3d3; } ");
}

void ImageList::setShortcuts() {
    QShortcut *shortcut = new QShortcut(QKeySequence("Return"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(copyImage()));

    shortcut = new QShortcut(QKeySequence("Ctrl+t"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(addTagToCurrentItem()));

    connect(this, &ImageList::itemSelectionChanged, this, &ImageList::currentItemChanged);
}
