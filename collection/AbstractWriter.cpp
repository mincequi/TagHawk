#include "AbstractWriter.h"

namespace collection {

AbstractWriter::AbstractWriter(QObject *parent)
    : QObject(parent)
{
}

AbstractWriter::~AbstractWriter()
{
}

} // namespace collection
