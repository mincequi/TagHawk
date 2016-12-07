#include "Job.h"

#include <QDebug>


Job::Job(Type type_, const QVariant& originalValue_, const QVariant& newValue_, bool confirmed_, const QString& subject_)
    : type(type_),
      originalValue(originalValue_),
      newValue(newValue_),
      confirmed(confirmed_),
      subject(subject_)
{
}

Job::~Job()
{
}

QString Job::typeAsString() const
{
    switch (type) {
    case Type::RenameArtist:
        return "Rename Artist";
        break;
    case Type::CategorizeArtist:
        return "Categorize " + subject;
        break;
    default:
        qWarning() << "Unhandled type:" << static_cast<int>(type);
        return QString();
    }
}
