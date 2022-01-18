#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include "mainwindow.h"

#include <QLabel>

class ImageLabel : public QLabel
{
    Q_OBJECT
public:
    MainWindow *root = NULL;

    ImageLabel(MainWindow *parent);

    void setStyle();
};

#endif // IMAGELABEL_H
