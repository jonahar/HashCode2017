#include <sstream>
#include <fstream>
#include <iostream>
#include "Cache.h"
#include "Network.h"


// ------------------------------ Declarations ------------------------------

std::vector<Video> buildVideos(std::ifstream& fs, unsigned int numVideos);

std::vector<Cache> buildCaches(unsigned int numCaches, unsigned int capacity);

std::vector<Endpoint> buildEndpoints(std::ifstream& fs, unsigned int numEndpoints,
                                     std::vector<Cache>& caches);

void readRequests(std::ifstream& fs, unsigned int requestDescriptions,
                  std::vector<Endpoint>& endpoints);


// ------------------------------ Definitions ------------------------------



Network::Network(std::ifstream& fs)
{
    unsigned int numVideos, numEndpoints, totalRequestDescriptions, numCaches, cacheCapacity;
    std::string line;
    std::getline(fs, line);
    std::stringstream lineStream(line);

    // extract all values in the first line
    lineStream >> numVideos >> numEndpoints >> totalRequestDescriptions >> numCaches
               >> cacheCapacity;


    this->videos = buildVideos(fs, numVideos);

    this->caches = buildCaches(numCaches, cacheCapacity);

    this->endpoints = buildEndpoints(fs, numEndpoints, this->caches);

    readRequests(fs, totalRequestDescriptions, this->endpoints);

}


std::vector<Video> buildVideos(std::ifstream& fs, unsigned int numVideos)
{
    std::vector<Video> videos;
    std::string line;
    std::getline(fs, line);
    std::stringstream lineStream(line);
    unsigned int videoSize;
    for (unsigned int id = 0; id < numVideos; ++id)
    {
        lineStream >> videoSize;
        videos.push_back(Video(id, videoSize));
    }
    return videos;
}

/**
 * build the requested number of caches and adds them to the network
 * @param capacity the capacity of a single cache
 */
std::vector<Cache> buildCaches(unsigned int numCaches, unsigned int capacity)
{
    std::vector<Cache> caches;
    for (unsigned int id = 0; id < numCaches; ++id)
    {
        caches.push_back(Cache(id, capacity));
    }
    return caches;
}


std::vector<Endpoint> buildEndpoints(std::ifstream& fs, unsigned int numEndpoints,
                                     std::vector<Cache>& caches)
{
    std::vector<Endpoint> endpoints;
    for (unsigned int id = 0; id < numEndpoints; ++id)
    {
        unsigned int dataCenterLatency, connectedCaches;
        std::string line;
        std::getline(fs, line);
        std::stringstream stringStream(line);
        stringStream >> dataCenterLatency >> connectedCaches;

        // build the endpoint
        endpoints.push_back(Endpoint(id, dataCenterLatency));

        // extract the data about the caches connected to this endpoint
        for (unsigned int i = 0; i < connectedCaches; ++i)
        {
            unsigned cacheId, endpointCacheLatency;
            std::getline(fs, line);
            stringStream = std::stringstream(line);
            stringStream >> cacheId >> endpointCacheLatency;
            caches[cacheId].addEndpoint(id, endpointCacheLatency);
        }
    }
    return endpoints;
}


void readRequests(std::ifstream& fs, unsigned int requestDescriptions,
                  std::vector<Endpoint>& endpoints)
{
    for (unsigned int i = 0; i < requestDescriptions; ++i)
    {
        unsigned int videoId, endpointId, numRequests;
        std::string line;
        std::getline(fs, line);
        std::stringstream stringStream(line);
        stringStream >> videoId >> endpointId >> numRequests;
        endpoints[endpointId].addVideo(videoId, numRequests);
    }
}
