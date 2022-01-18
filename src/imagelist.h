#ifndef IMAGELIST_H
#define IMAGELIST_H

#include "mainwindow.h"
#include "image.h"

#include <QListWidget>

#include <string>
using namespace std;

class ImageList : public QListWidget
{
    Q_OBJECT
public:
    MainWindow *root = NULL;
    map<string, Image*> images;

    ImageList(MainWindow *parent=nullptr);

    void addImagesFromDirectory(string path);

public slots:
    void redraw();

private slots:
    void removeSavedImage(string path);
    void saveImageList();
    void loadImageList();
    void addTagToCurrentItem();
    void setShortcuts();
    void setStyle();
    void currentItemChanged();
    void copyImage();
};

#endif // IMAGELIST_H
