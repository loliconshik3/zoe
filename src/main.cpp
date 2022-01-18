#include "mainwindow.h"
#include "imagelabel.h"
#include "imagelist.h"
#include "searchbox.h"

#include <QApplication>
#include <QGridLayout>

//TODO: Save tags, load tags feauters

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;

    system("mkdir ~/.config/zoe");
    system("mkdir ~/.config/zoe/images");

    window.searchBox = new SearchBox(&window);
    window.imageLabel = new ImageLabel(&window);
    window.imageList = new ImageList(&window);

    //Set layout
    QGridLayout *layout = new QGridLayout;

    layout->addWidget(window.searchBox, 0, 0);
    layout->addWidget(window.imageList, 1, 0);
    layout->addWidget(window.imageLabel, 1, 1);

    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(5);
    layout->setContentsMargins(5, 5, 5, 5);

    window.setLayout(layout);

    window.show();

    return app.exec();
}
