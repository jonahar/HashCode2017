#ifndef HASHCODE2017_CACHE_HPP
#define HASHCODE2017_CACHE_HPP

#include <set>
#include <vector>
#include <memory>
#include "Video.h"
#include "Endpoint.h"


/**
 * an endpoint connected to a cache
 */
struct ConnectedEndpoint
{
    unsigned int endpointId, latency;
};


class Cache
{
private:

    unsigned int id, size, capacity;
    std::set<ConnectedEndpoint> endpoints; // endpoints id's
    std::vector<unsigned int> videosInCache;


public:

    Cache(unsigned int id, unsigned int capacity);

    unsigned int getId() const;

    /**
     * add an endpoint connected to this cache
     *
     * @return true iff the given endpoint was added to this cache
     */
    bool addEndpoint(unsigned int endpointId, unsigned int latency);


    /**
     * calculate the score this cache gives to any of the given videos, and adds the videos with
     * the top scores to this cache.
     * this function also notify its connected endpoints in case a video is added to the cache
     * (so they can update their distance from this video).
     *
     * @param videos vector of Video objects s.t. videos[k] = video with id k
     * @param endpoints vector of Endpoint objects s.t. endpoints[k] = endpoint with id k
     */
    void rateAndInsertVideos(const std::vector<Video>& videos, std::vector<Endpoint> endpoints);

};


#endif //HASHCODE2017_CACHE_HPP
