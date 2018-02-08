#ifndef READERUTIL_H
#define READERUTIL_H

#include <ostream>

#include <taglib/id3v1tag.h>
#include <taglib/id3v2tag.h>

// We test here, wether ID3v1 tags are present in ID3v2 tag as well.
bool operator==(const TagLib::ID3v1::Tag& lhs, const TagLib::ID3v2::Tag& rhs);
std::ostream& operator<< (std::ostream& stream, const TagLib::Tag& tag);

#endif // READERUTIL_H
