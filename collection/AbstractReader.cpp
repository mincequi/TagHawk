#ifndef ABSTRACTREADER_H
#define ABSTRACTREADER_H

#include <QObject>
#include <QAbstractAnimation>

namespace collection {

class AbstractReader : public QObject
{
    Q_OBJECT
public:
    explicit AbstractReader(QObject *parent = 0) {}
    ~AbstractReader() {}

    virtual void readFolder(const QString& folder) = 0;
    virtual void readFiles(const QStringList& files) = 0;

signals:

public slots:
};

} // namespace collection

#endif // ABSTRACTREADER_H
