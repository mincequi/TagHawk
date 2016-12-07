#ifndef WRITER_H
#define WRITER_H

#include "AbstractWriter.h"

#include <taglib/fileref.h>
#include <taglib/id3v2tag.h>


namespace collection {

class Collection;

class TagLibWriter : public AbstractWriter
{
public:
    explicit TagLibWriter(Collection& collection, QObject *parent = 0);

    virtual void write() const override;

private:
    Collection& m_collection;
};

} // namespace collection

#endif // WRITER_H
