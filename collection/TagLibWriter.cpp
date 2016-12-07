#include "TagLibWriter.h"

#include <map>

#include <QDebug>
#include <QFileInfo>

#include <taglib/mpegfile.h>

#include "Collection.h"
#include "TagLibWriterUtil.h"


namespace collection {

TagLibWriter::TagLibWriter(Collection& collection, QObject *parent) :
    AbstractWriter(parent),
    m_collection(collection)
{
}

void TagLibWriter::write() const
{
}

} // namespace collection
