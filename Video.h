
#ifndef HASHCODE2017_VIDEO_HPP
#define HASHCODE2017_VIDEO_HPP

/**
 * representing a video instance
 */
class Video
{
private:
    unsigned int id, size;

public:
    Video(unsigned int id, unsigned int size);
    unsigned int getId() const;
    unsigned int getSize() const;
    bool operator ==(const Video& other) const;
};


#endif //HASHCODE2017_VIDEO_HPP
