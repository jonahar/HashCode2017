#include <iostream>
#include <fstream>
#include <sstream>
#include "Network.h"

#include <getopt.h>


const char* SPACE = " ";

static int parallel = false;

static struct option const long_options[] =
        {
                {"in",       required_argument, NULL, 'i'},
                {"out",      required_argument, NULL, 'o'},
                {"parallel", no_argument, &parallel,  true}
        };


void run(std::ifstream& fs, std::ofstream& ofs, int parallel)
{
    Network network(fs);

    // give scores and spread videos between caches
    for (unsigned int id = 0; id < network.caches.size(); ++id)
    {
        network.caches[id].rateAndInsertVideos(network.videos, network.endpoints);
    }

    // write result to output file
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


/**
 * print usage
 */
void usage()
{
    std::cout << \
"Google's HashCode 2017 problem solver\n\n\
Usage: Organizer [OPTIONS]\n\
\
-i, --in                input file\n\
-o, --out               output file\n\
-p, --parallel          parallel mode (noticeably for large input files)\n";
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

    while ((c = getopt_long(argc, argv, "i:o:p", long_options, NULL)) != -1)
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