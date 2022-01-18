#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SearchBox;
class ImageLabel;
class ImageList;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    SearchBox *searchBox = NULL;
    ImageLabel *imageLabel = NULL;
    ImageList *imageList = NULL;

private slots:
    void openDirectory();
    void setShortcuts();
    void setStyle();
};
#endif // MAINWINDOW_H
