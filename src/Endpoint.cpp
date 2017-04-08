
#include "Endpoint.h"

struct ConnectedEndpoint
{
    unsigned int endpointId, latency;
};


Endpoint::Endpoint(unsigned int id, unsigned int dataCenterLatency)
{
    this->id = id;
    this->dataCenterLatency = dataCenterLatency;
}

Endpoint::~Endpoint()
{
    for(std::pair<int, RequestedVideoData*> p: videos)
    {
        delete p.second;
    }
}

bool Endpoint::addVideo(unsigned int videoId, unsigned int numRequests)
{
    if (this->videos.find(videoId) != this->videos.end())
    {
        // this video is already in the list
        return false;
    }
    RequestedVideoData * rvd = new RequestedVideoData;
    *rvd = {numRequests, this->dataCenterLatency};
    this->videos.insert({videoId, rvd});
    return true;
}

bool Endpoint::updateVideoDistance(unsigned int videoId, unsigned int newDistance)
{
    auto it = this->videos.find(videoId);
    if (it != this->videos.end())
    {
        // the video is in the list
        if (it->second->distance > newDistance)
        {
            // new distance is better
            it->second->distance = newDistance;
            return true;
        }
    }
    return false;
}

unsigned int Endpoint::getVideoDistance(unsigned int videoId) const
{
    auto it = this->videos.find(videoId);
    if (it != this->videos.end())
    {
        // the video is in the list
        return it->second->distance;
    }
    return 0;
}

unsigned int Endpoint::getNumRequests(unsigned int videoId) const
{
    auto it = this->videos.find(videoId);
    if (it != this->videos.end())
    {
        // the video is in the list
        return it->second->numRequests;
    }
    return 0;
}

unsigned int Endpoint::getId() const
{
    return id;
}

unsigned int Endpoint::getDataCenterLatency()
{
    return dataCenterLatency;
}