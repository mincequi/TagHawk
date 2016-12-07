#include "AbstractReader.h"

namespace collection {

AbstractReader::AbstractReader(QObject *parent)
    : QObject(parent)
{
}

AbstractReader::~AbstractReader()
{
}

} // namespace collection
