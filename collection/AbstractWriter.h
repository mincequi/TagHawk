#ifndef ABSTRACTWRITER_H
#define ABSTRACTWRITER_H

#include <QObject>

class AbstractWriter : public QObject
{
    Q_OBJECT
public:
    explicit AbstractWriter(QObject *parent = 0);
    ~AbstractWriter();

    virtual void write() const = 0;

signals:
    void writingDirectory(const QString& directory);
    void progress(int, int);
};

#endif // ABSTRACTWRITER_H
