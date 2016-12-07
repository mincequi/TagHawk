#ifndef ABSTRACTREADER_H
#define ABSTRACTREADER_H

#include <QObject>


namespace collection {

class AbstractReader : public QObject
{
    Q_OBJECT
public:
    explicit AbstractReader(QObject *parent = 0);
    ~AbstractReader();

    virtual void readFolder(const QString& folder) = 0;
    virtual void readFiles(const QStringList& files) = 0;

signals:
    void scanningDirectory(const QString& directory);
    void progress(int, int);
    void ambiguousTagsFound(const QString& file);
    void noTagsFound(const QString& file);
};

} // namespace collection

#endif // ABSTRACTREADER_H
