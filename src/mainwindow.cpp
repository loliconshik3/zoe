#include "mainwindow.h"
#include "imagelist.h"

#include <string>
#include <fstream>
#include <iostream>

#include <QShortcut>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setShortcuts();
    setStyle();
}

void MainWindow::openDirectory() {
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
          "",
          QFileDialog::DontResolveSymlinks);

    if (directory.isEmpty()) {
        return;
    }

    imageList->addImagesFromDirectory(directory.toStdString());
}

void MainWindow::setShortcuts() {
    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+o"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(openDirectory()));
}

void MainWindow::setStyle() {
    setStyleSheet("QWidget { background: #282a36; } ");
}

MainWindow::~MainWindow()
{
    std::cout << "deallocation";
}
