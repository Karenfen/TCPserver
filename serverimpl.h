#ifndef SERVERIMPL_H
#define SERVERIMPL_H

#include <QObject>


class serverImpl : QObject
{
    Q_OBJECT
public:
    serverImpl(QObject* parent = nullptr);
    ~serverImpl();
};

#endif // SERVERIMPL_H
