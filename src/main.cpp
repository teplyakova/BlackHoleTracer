#include "Tracer.h"
#include "config/Config.h"
#include <iostream>
#include <boost/program_options.hpp>
#include <stdio.h>

namespace po = boost::program_options;
using namespace std;

int main(const int argc, const char** argv) {
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "produce help message")
            ("config-file,c", po::value<string>(), "config file")
            ("output-file,o", po::value<string>(), "output file")
            ;

    po::positional_options_description p;
    p.add("output-file", 1);

    po::variables_map vm;
    try
    {
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);

        if (vm.count("help"))
        {
            cout << "Usage: [options] output-file\n";
            std::cout << desc << std::endl;

            return 0;
        }

        po::notify(vm);

        Config config = Config ();

        if (vm.count("config-file"))
        {
            read_json (vm["config-file"].as<string>().c_str(), config);
        }
        else
        {
            printf("No config file, using default parameters!\n");
        }

        if (!vm.count("output-file"))
        {
            printf("No name for output file!\n");

            return 0;
        }

        Tracer tracer(config);

        tracer.RenderImage();
        tracer.SaveImageToFile(vm["output-file"].as<string>());
    }
    catch(po::error& e)
    {
        std::cerr << "Options error: " << e.what() << std::endl << std::endl;
        std::cerr << desc << std::endl;
        return 0;
    }
    catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return 1;
    }

    return 0;
}