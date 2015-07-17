#include "notifybar.h"

NotifyBar::NotifyBar(const QString & text, QWidget * parent)
    : QLabel(text, parent)
{

}

void NotifyBar::setTextColor(NotifyColor color)
{
    switch (color) {
    case TextNormal:
        setStyleSheet("QLabel { color : Black; }");
        break;
    case TextRed:
        setStyleSheet("QLabel { color : Red; }");
        break;
    case TextGreen:
        setStyleSheet("QLabel { color : Green; }");
        break;
    default:
        break;
    }
}
