

#include "Cache.h"
#include "Endpoint.h"




Cache::Cache(unsigned int id, unsigned int size)
{
    this->id = id;
    this->size = size;
}

unsigned int Cache::getId() const
{
    return this->id;
}

bool Cache::addEndpoint(const Endpoint& endpoint, unsigned int latency)
{
    return this->endpoints.insert({endpoint.getId(), {endpoint, latency}}).second;
}


bool Cache::rateAndChoose()
{
    // TODO implement
    return false;
}