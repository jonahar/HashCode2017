
#include "Endpoint.h"

Endpoint::Endpoint(unsigned int id, unsigned int dataCenterLatency)
{
    this->id = id;
    this->dataCenterLatency = dataCenterLatency;
}

bool Endpoint::addVideo(const Video& video, unsigned int numRequests)
{
    if (this->videos.find(video.getId()) != this->videos.end())
    {
        // this video is already in the list
        return false;
    }
    this->videos.insert({video.getId(), {video, numRequests, this->dataCenterLatency}});
    return true;
}

bool Endpoint::updateVideoDistance(const Video& video, unsigned int newDistance)
{
    auto it = this->videos.find(video.getId());
    if (it != this->videos.end())
    {
        // the video is in the list
        if (it->second.latency > newDistance)
        {
            // new latency is better
            it->second.latency = newDistance;
            return true;
        }
    }
    return false;
}

unsigned int Endpoint::getVideoDistance(const Video& video) const
{
    auto it = this->videos.find(video.getId());
    if (it != this->videos.end())
    {
        // the video is in the list
        return it->second.latency;
    }
    return 0;
}

unsigned int Endpoint::getNumRequests(const Video& video) const
{
    auto it = this->videos.find(video.getId());
    if (it != this->videos.end())
    {
        // the video is in the list
        return it->second.numRequests;
    }
    return 0;
}

unsigned int Endpoint::getId() const
{
    return this->id;
}