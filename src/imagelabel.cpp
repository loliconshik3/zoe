#include "imagelabel.h"

ImageLabel::ImageLabel(MainWindow *parent) : QLabel(parent)
{
    root = parent;

    setStyle();
}

void ImageLabel::setStyle() {
    setStyleSheet("QLabel { background: #282a36; } ");
}
