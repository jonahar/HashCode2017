#include <algorithm>
#include <iostream>
#include <set>
#include "Cache.h"


// this comparator is needed for using std::set<ConnectedEndpoint>
bool operator<(const ConnectedEndpoint& ce1, const ConnectedEndpoint& ce2)
{
    return ce1.endpointId < ce2.endpointId;
}


Cache::Cache(unsigned int id, unsigned int capacity)
{
    this->id = id;
    this->capacity = capacity;
    this->size = 0;
}

unsigned int Cache::getId() const
{
    return this->id;
}

bool Cache::addEndpoint(unsigned int endpointId, unsigned int latency)
{
    return this->endpoints.insert({endpointId, latency}).second;
}


/**
 * holds a video id with a cache score.
 * used in the rateAndChoose function.
 */
struct ScoredVideo
{
    unsigned int id;
    double score;

    /**
     * less-than operator for ScoredVideo.
     * @return true iff this score is less than other's score
     */
    bool operator<(const ScoredVideo& other) const
    {
        return (this->score < other.score);
    }

};


void Cache::rateAndInsertVideos(const std::vector<Video>& videos, std::vector<Endpoint> endpoints)
{
    // todo support parallel computation

    std::vector<ScoredVideo> scores(videos.size());
    for (unsigned int videoId = 0; videoId < videos.size(); ++videoId)
    {
        double score = 0;
        for (const ConnectedEndpoint& ce: this->endpoints)
        {
            score += endpoints[ce.endpointId].getNumRequests(videoId) *
                     (endpoints[ce.endpointId].getVideoDistance(videoId) - ce.latency);
        }
        score /= videos[videoId].getSize() * videos[videoId].getSize();
        scores[videoId] = {videoId, score};
    }

    std::sort(scores.rbegin(), scores.rend()); // sort in descending order

    auto it = scores.begin();
    while (this->size < this->capacity && it != scores.end())
    {
        if (videos[it->id].getSize() <= (capacity - size))
        {
            // there is enough space to insert video to the cache
            this->videosInCache.push_back(it->id);
            size += videos[it->id].getSize();

            // notify all endpoints that the video is available in this cache
            for (const ConnectedEndpoint& ce: this->endpoints)
            {
                endpoints[ce.endpointId].updateVideoDistance(it->id, ce.latency);
            }
        }
        it++;
    }
}


const std::vector<unsigned int>& Cache::getVideosInCache() const
{
    return this->videosInCache;
}
