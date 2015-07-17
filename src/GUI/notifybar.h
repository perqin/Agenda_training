#ifndef NOTIFYBAR_H
#define NOTIFYBAR_H

#include <QLabel>
#include <QString>
#include <QWidget>

class NotifyBar : public QLabel
{
public:
    enum NotifyColor { TextNormal, TextRed, TextGreen };
    NotifyBar(const QString & text, QWidget * parent = 0);
    void setTextColor(NotifyColor color);
};

#endif // NOTIFYBAR_H
