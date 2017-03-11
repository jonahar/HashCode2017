#ifndef HASHCODE2017_NETWORK_H
#define HASHCODE2017_NETWORK_H


#include "Cache.h"

class Network{
public:
    std::vector<Video> videos;
    std::vector<Endpoint> endpoints;
    std::vector<Cache> caches;

    /**
     * parses a network specification input file (as described in the HashCode2017 pdf) and
     * constructs its corresponding network
     */
    Network(std::ifstream& fs);

};


#endif //HASHCODE2017_NETWORK_H
