#ifndef HASHCODE2017_CACHE_HPP
#define HASHCODE2017_CACHE_HPP

#include <unordered_map>
#include <vector>
#include <memory>
#include "Video.h"
#include "Endpoint.h"


/**
 * an endpoint connected to the cache
 */
struct ConnectedEndpoint
{
    const Endpoint& endpoint;
    unsigned int latency;
};



class Cache
{
private:

    unsigned int id, size;
    std::unordered_map<int, ConnectedEndpoint> endpoints;
    std::vector<Video*> videosInCache;

public:

    Cache(unsigned int id, unsigned int size);

    unsigned int getId() const;

    /**
     * add an endpoint connected to this cache
     *
     * @return true iff the given endpoint was added to this cache
     */
    bool addEndpoint(const Endpoint& endpoint, unsigned int latency);

    bool rateAndChoose(/* TODO get videos here - choose type of the videos container */);

};


#endif //HASHCODE2017_CACHE_HPP
