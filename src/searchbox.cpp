#include "searchbox.h"
#include "imagelist.h"

#include <QShortcut>

SearchBox::SearchBox(MainWindow *parent) : QLineEdit(parent)
{
    root = parent;

    setShortcuts();
    setStyle();
}

void SearchBox::filterImageList() {
    root->imageList->redraw();
}

void SearchBox::previousItem() {
    int itemIndex   = root->imageList->currentIndex().row();
    auto ilist      = root->imageList;
    int maxIndex    = 0;

    if (itemIndex > maxIndex) {
        ilist->setCurrentItem(ilist->item(itemIndex-1));
    }
    else {
        ilist->setCurrentItem(ilist->item(ilist->count()-1));
    }
}

void SearchBox::nextItem() {
    int itemIndex   = root->imageList->currentIndex().row();
    int maxIndex    = root->imageList->count()-1;
    auto ilist      = root->imageList;

    if (itemIndex < maxIndex) {
        ilist->setCurrentItem(ilist->item(itemIndex+1));
    }
    else {
        ilist->setCurrentItem(ilist->item(0));
    }
}

void SearchBox::setStyle() {
    setPlaceholderText("Type to filter...");
    setTextMargins(2, 0, 2, 0);
    setStyleSheet("QLineEdit { background: #44475a; border: none; color: #d3d3d3; } ");
}

void SearchBox::setShortcuts() {
    connect(this, &SearchBox::textChanged, this, &SearchBox::filterImageList);

    QShortcut *shortcut = new QShortcut(QKeySequence("Down"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(nextItem()));

    shortcut = new QShortcut(QKeySequence("Up"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(previousItem()));
}
