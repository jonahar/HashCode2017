#include <sstream>
#include <fstream>
#include <iostream>
#include "Network.h"


Network::Network(std::ifstream& fs)
{
    unsigned int numVideos, numEndpoints, totalRequestDescriptions, numCaches, cacheCapacity;
    std::string line;
    std::getline(fs, line);
    std::stringstream lineStream(line);

    totalRequests = 0;

    // extract all values in the first line
    lineStream >> numVideos >> numEndpoints >> totalRequestDescriptions >> numCaches
               >> cacheCapacity;


    buildVideos(fs, numVideos);

    buildCaches(numCaches, cacheCapacity);

    buildEndpoints(fs, numEndpoints);

    parseRequests(fs, totalRequestDescriptions);

}

Network::~Network()
{
    for (Video* video: videos)
    {
        delete video;
    }
    for (Cache* cache: caches)
    {
        delete cache;
    }
    for (Endpoint* endpoint: endpoints)
    {
        delete endpoint;
    }
}


void Network::buildVideos(std::ifstream& fs, unsigned int numVideos)
{
    std::string line;
    std::getline(fs, line);
    std::stringstream lineStream(line);
    unsigned int videoSize;
    for (unsigned int id = 0; id < numVideos; ++id)
    {
        lineStream >> videoSize;
        Video* newVideo = new Video(id, videoSize);
        videos.push_back(newVideo);
    }
}

/**
 * build the requested number of caches and adds them to the network
 * @param capacity the capacity of a single cache
 */
void Network::buildCaches(unsigned int numCaches, unsigned int capacity)
{
    for (unsigned int id = 0; id < numCaches; ++id)
    {
        Cache* newCache = new Cache(id, capacity);
        caches.push_back(newCache);
    }
}


void Network::buildEndpoints(std::ifstream& fs, unsigned int numEndpoints)
{
    for (unsigned int id = 0; id < numEndpoints; ++id)
    {
        unsigned int dataCenterLatency, connectedCaches;
        std::string line;
        std::getline(fs, line);
        std::stringstream stringStream(line);
        stringStream >> dataCenterLatency >> connectedCaches;

        // build the endpoint
        Endpoint* newEndpoint = new Endpoint(id, dataCenterLatency);
        endpoints.push_back(newEndpoint);

        // extract the data about the caches connected to this endpoint
        for (unsigned int i = 0; i < connectedCaches; ++i)
        {
            unsigned cacheId, endpointCacheLatency;
            std::getline(fs, line);
            stringStream = std::stringstream(line);
            stringStream >> cacheId >> endpointCacheLatency;
            caches[cacheId]->addEndpoint(id, endpointCacheLatency);
        }
    }
}


void Network::parseRequests(std::ifstream& fs, unsigned int requestDescriptions)
{
    for (unsigned int i = 0; i < requestDescriptions; ++i)
    {
        unsigned int videoId, endpointId, numRequests;
        std::string line;
        std::getline(fs, line);
        std::stringstream stringStream(line);
        stringStream >> videoId >> endpointId >> numRequests;
        totalRequests += numRequests;
        endpoints[endpointId]->addVideo(videoId, numRequests);
    }
}

unsigned long Network::getTotalRequests()
{
    return totalRequests;
}