#ifndef JOB_H
#define JOB_H

#include <QVariant>


class Job
{
public:
    enum class Type
    {
        RenameArtist,
        CategorizeArtist,
    };

    Job(Type type_, const QVariant& originalValue_, const QVariant& newValue_, bool confirmed_ = true, const QString& subject_ = QString());
    ~Job();

    Type        type;
    QString     field;
    QVariant    originalValue;
    QVariant    newValue;
    bool        confirmed;
    QString     subject;

    QString     typeAsString() const;
};

#endif // JOB_H
