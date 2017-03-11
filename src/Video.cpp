#include "Video.h"

Video::Video(unsigned int id, unsigned int size)
{
    this->id = id;
    this->size = size;
}

unsigned int Video::getId() const
{
    return this->id;
}

unsigned int Video::getSize() const
{
    return this->size;
}

bool Video::operator==(const Video& other) const
{
    return this->id == other.id;
}