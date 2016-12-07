#ifndef READER_H
#define READER_H

#include "AbstractReader.h"


namespace collection {

class Collection;

class TagLibReader : public AbstractReader
{
    Q_OBJECT
public:
    explicit TagLibReader(Collection& collection, QObject *parent = 0);

    virtual void readFolder(const QString& folder) override;
    virtual void readFiles(const QStringList& files) override;

private:
    Collection& m_collection;
};

} // namespace reader

#endif // READER_H
