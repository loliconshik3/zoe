#ifndef SEARCHBOX_H
#define SEARCHBOX_H

#include "mainwindow.h"

#include <QLineEdit>

class SearchBox : public QLineEdit
{
    Q_OBJECT
public:
    MainWindow *root = NULL;

    SearchBox(MainWindow *parent);

private slots:
    void previousItem();
    void nextItem();

    void filterImageList();
    void setShortcuts();
    void setStyle();
};

#endif // SEARCHBOX_H
