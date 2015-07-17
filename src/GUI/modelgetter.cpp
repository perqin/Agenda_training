#include "modelgetter.h"

void ModelGetter::getIt(const std::list<User> ul, QStandardItemModel * model) {
    //model->clear();
    //model->setColumnCount(3);
    if (!model->removeRows(0, model->rowCount()))
        qDebug() << "Clear Users Fails";
    model->setRowCount(ul.size());
    std::list<User>::const_iterator it = ul.begin();
    for (unsigned i = 0; i < ul.size(); ++i) {
        model->setItem(i, 0, new QStandardItem(it->getName().c_str()));
        model->setItem(i, 1, new QStandardItem(it->getEmail().c_str()));
        model->setItem(i, 2, new QStandardItem(it->getPhone().c_str()));
        ++it;
    }
}

void ModelGetter::getIt(const std::list<Meeting> ml, QStandardItemModel * model) {
    //model->clear();
    //model->setColumnCount(5);
    //qDebug() << ml.size();
    if (!model->removeRows(0, model->rowCount()))
        qDebug() << "Clear Meetings Fails";
    model->setRowCount(ml.size());
    std::list<Meeting>::const_iterator it = ml.begin();
    for (unsigned i = 0; i < ml.size(); ++i) {
        model->setItem(i, 0, new QStandardItem(it->getTitle().c_str()));
        model->setItem(i, 1, new QStandardItem(it->getSponsor().c_str()));
        model->setItem(i, 2, new QStandardItem(it->getParticipator().c_str()));
        model->setItem(i, 3, new QStandardItem(Date::dateToString(it->getStartDate()).c_str()));
        model->setItem(i, 4, new QStandardItem(Date::dateToString(it->getEndDate()).c_str()));
        ++it;
    }
    //qDebug() << model->item(0, 0)->text();
//    qDebug() << "";
}
