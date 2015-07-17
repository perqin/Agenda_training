#ifndef MODELGETTER_H
#define MODELGETTER_H

#include <QDebug>

#include <QStandardItemModel>
#include <QModelIndex>
#include <QString>
#include <list>
#include "../Core/User.h"
#include "../Core/Meeting.h"
#include "../Core/Date.h"

class ModelGetter {
public:
    static void getIt(const std::list<User> ul, QStandardItemModel * model);
    static void getIt(const std::list<Meeting> ml, QStandardItemModel * model);
};

#endif // MODELGETTER_H
