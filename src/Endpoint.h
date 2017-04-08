#ifndef HASHCODE2017_ENDPOINT_HPP
#define HASHCODE2017_ENDPOINT_HPP

#include <unordered_map>
#include "Video.h"


/**
 * a video requested by the endpoint
 */
struct RequestedVideoData
{
    unsigned int numRequests;
    unsigned int distance;
};


class Endpoint
{
private:
    unsigned int id, dataCenterLatency;
    // videos requested by this endpoint
    std::unordered_map<int, RequestedVideoData*> videos;

public:

    Endpoint(unsigned int id, unsigned int dataCenterLatency);

    ~Endpoint();

    /**
     * @return true if the given video was added, and wasn't already in the videos list
     */
    bool addVideo(unsigned int videoId, unsigned int numRequests);

    /**
     * notify this endpoint that a new latency is available for the given video.
     * If the current latency is less than the new distance or the given video is not requested
     * by this endpoint, does nothing
     *
     * @return true iff latency was updated
     */
    bool updateVideoDistance(unsigned int videoId, unsigned int newDistance);

    /**
     * @return the latency between this endpoint and the given video. return 0 if the given video
     * is not in this endpoint' videos list
     *
     * The latency between an endpoint and a video is the minimum from all latencies between the
     * endpoint to some location (data-center or a cache) that holds this video.
     */
    unsigned int getVideoDistance(unsigned int videoId) const;

    /**
     * @return number of requests from this endpoint to the given video. return 0 if the given video
     * is not in this endpoint' videos list
     */
    unsigned int getNumRequests(unsigned int videoId) const;

    unsigned int getId() const;

    unsigned int getDataCenterLatency();

};


#endif //HASHCODE2017_ENDPOINT_HPP
