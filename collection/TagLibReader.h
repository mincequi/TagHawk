#ifndef READER_H
#define READER_H

#include <QFuture>
#include <QObject>

class Collection;


namespace reader
{

class Reader : public QObject
{
    Q_OBJECT
public:
    enum Error {
        NoError = 0,
        FileNotFoundError,
        TagLibError,
        UnknownError
    };

    explicit Reader(Collection& database, QObject *parent = 0);

    void read(const QStringList& locations);

signals:
    void scanningDirectory(const QString& directory);
    void progress(int, int);

    void stripId3v1(const QString& file);

    void finished();
    void error(Reader::Error error);

public slots:

private:
    void readTags(const QStringList& files);

    Collection&       m_collection;
    QFuture<void>   m_currentTask;

    int m_currentProgress;
};

} // namespace reader

#endif // READER_H
