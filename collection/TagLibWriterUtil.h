#ifndef TAGLIBWRITERUTIL_H
#define TAGLIBWRITERUTIL_H

#include <taglib/id3v2tag.h>


namespace collection
{

TagLib::ID3v2::Tag& operator+=(TagLib::ID3v2::Tag& lhs, const TagLib::ID3v2::Tag& rhs);

} // namespace reader

#endif // TAGLIBWRITERUTIL_H
