#include <iostream>
#include <fstream>
#include <sstream>
#include "Network.h"

#define NUM_ARGS 2
#define PATH_INDEX 1


void run(std::ifstream& fs, std::ofstream& ofs)
{
    Network network(fs);

    // give scores and spread videos between caches
    for (unsigned int id = 0; id < network.caches.size(); ++id)
    {
        network.caches[id].rateAndInsertVideos(network.videos, network.endpoints);
    }

}


/**
 * print usage
 */
void usage()
{
    std::cout << "Usage: VideosOrganizer path/to/input/file" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc != NUM_ARGS)
    {
        usage();
        return EXIT_FAILURE;
    }

    std::ifstream ifs(argv[PATH_INDEX], std::ios_base::in);
    std::ofstream ofs(std::string(argv[PATH_INDEX])+".out", std::ios_base::out);

    if (!ifs.is_open() || !ofs.is_open())
    {
        perror("Error");
        return EXIT_FAILURE;
    }

    run(ifs, ofs);

    ifs.close();
    ofs.close();

    return EXIT_SUCCESS;
}