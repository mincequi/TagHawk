#ifndef WRITER_H
#define WRITER_H

class Media;

class Writer
{
public:
    Writer();

    bool write(const Media& media);
};

#endif // WRITER_H
