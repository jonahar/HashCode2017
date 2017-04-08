#ifndef HASHCODE2017_NETWORK_H
#define HASHCODE2017_NETWORK_H


#include "Cache.h"

class Network
{
public:
    std::vector<Video*> videos;
    std::vector<Endpoint*> endpoints;
    std::vector<Cache*> caches;

    /**
     * parses a network specification input file (as described in the HashCode2017 pdf) and
     * constructs its corresponding network
     */
    Network(std::ifstream& fs);

    ~Network();

    /**
     * @return total number of requests in all requests descriptions
     */
    unsigned long getTotalRequests();

private:
    unsigned long totalRequests;


    void buildVideos(std::ifstream& fs, unsigned int numVideos);

    /**
     * build the requested number of caches and adds them to the network
     * @param capacity the capacity of a single cache
     */
    void buildCaches(unsigned int numCaches, unsigned int capacity);

    void buildEndpoints(std::ifstream& fs, unsigned int numEndpoints);

    /**
     * parses all requests descriptions
     * @param requestDescriptions total number of lines of requests descriptions
     */
    void parseRequests(std::ifstream& fs, unsigned int requestDescriptions);

};


#endif //HASHCODE2017_NETWORK_H
