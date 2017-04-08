#include <iostream>
#include <fstream>
#include <sstream>
#include <getopt.h>
#include "Network.h"


const char* SPACE = " ";

static int parallel = false;

static struct option const long_options[] =
        {
                {"help",     no_argument,       NULL, 'h'},
                {"in",       required_argument, NULL, 'i'},
                {"out",      required_argument, NULL, 'o'},
                {"parallel", no_argument, &parallel,  true}
        };


void putVideosInCaches(Network& network)
{
    for (unsigned int id = 0; id < network.caches.size(); ++id)
    {
        network.caches[id].rateAndInsertVideos(network.videos, network.endpoints, parallel);
    }
}

void writeCachesContents(Network& network, std::ofstream& ofs)
{
    ofs << network.caches.size() << std::endl;
    for (const Cache& cache: network.caches)
    {
        ofs << cache.getId();
        for (unsigned int videoId: cache.getVideosInCache())
        {
            ofs << SPACE << videoId;
        }
        ofs << std::endl;
    }
}

unsigned long calculateSolutionScore(Network& network)
{
    unsigned long score = 0;
    for(Endpoint& e: network.endpoints)
    {
        for(unsigned int i = 0; i < network.videos.size(); i++)
        {
            if(e.getNumRequests(i) != 0)
            {
                // the i'th video is requested by this endpoint
                // (L_d - min{}) * R_n
                score += (e.getDataCenterLatency() - e.getVideoDistance(i)) * e.getNumRequests(i);
            }
        }
    }
    return (score * 1000) / network.getTotalRequests();
}


void run(std::ifstream& ifs, std::ofstream& ofs, int parallel)
{
    Network network(ifs);

    // give scores and spread videos between caches
    putVideosInCaches(network);

    // write solution to output file
    writeCachesContents(network, ofs);

    //calculate the score of this solution
    unsigned long score = calculateSolutionScore(network);
    std::cout << "Videos placed in caches. Total score: " << score << std::endl;

}


/**
 * print usage
 */
void usage()
{
    std::cout << \
"Google's HashCode 2017 problem solver\n\n\
Usage: Organizer [OPTIONS]\n\
\
-h, --help              display this help and exit\n\
-i, --in                input file\n\
-o, --out               output file\n";
    // todo add parallel option after implementing
    // -p, --parallel          parallel mode
}

int error()
{
    perror("Error");
    return EXIT_FAILURE;
}

int main(int argc, char** argv)
{

    int c;
    bool inProvided = false, outProvided = false;
    std::ifstream ifs;
    std::ofstream ofs;

    while ((c = getopt_long(argc, argv, "i:o:ph", long_options, NULL)) != -1)
    {
        switch (c)
        {
            case 0:
                // flag has been raised
                break;
            case 'i':
                inProvided = true;
                ifs.open(optarg, std::ios_base::in);
                if (!ifs.is_open())
                    return error();
                break;
            case 'o':
                outProvided = true;
                ofs.open(optarg, std::ios_base::out);
                if (!ofs.is_open())
                    return error();
                break;
            case 'p':
                parallel = true;
                break;
            case 'h':
                usage();
                return EXIT_SUCCESS;
            default:
                usage();
                return EXIT_FAILURE;
        }
    }


    if (!inProvided || !outProvided)
    {
        std::cout << "must provide input and output files" << std::endl;
        return EXIT_FAILURE;
    }

    run(ifs, ofs, parallel);

    ifs.close();
    ofs.close();

    return EXIT_SUCCESS;
}