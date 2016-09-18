#ifndef READERUTIL_H
#define READERUTIL_H

#include <ostream>


namespace TagLib {
class Tag;
namespace ID3v1 {
class Tag;
} // namespace ID3v1
namespace ID3v2 {
class Tag;
} // namespace ID3v2
} // namespace TagLib

namespace reader
{

// We test here, wether ID3v1 tags are present in ID3v2 tag as well.
bool operator==(const TagLib::ID3v1::Tag& lhs, const TagLib::ID3v2::Tag& rhs);
std::ostream& operator<< (std::ostream& stream, const TagLib::Tag& tag);

} // namespace reader

#endif // READERUTIL_H
