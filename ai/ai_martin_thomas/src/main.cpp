#include <string>
#include <algorithm>
#include <vector>
#include <tuple>
#include <iostream>
#include <optional>
#include "Args.hpp"
#include "Core.hpp"

int tryRun(const my::Args &args) {
    try {
        my::Core core(args);
        core.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 84;
    }
    return 0;
}

int main(int ac, char **av)
{
    my::Args args(ac, av);
    if (args.isFlagSet("-help")) {
        std::cout << "Usage: " << av[0] << " -p port -n name -h machine" << std::endl;
        std::cout << "\tport is the port number" << std::endl;
        std::cout << "\tname is the name of the team" << std::endl;
        std::cout << "\tmachine is the name of the machine; localhost by default" << std::endl;
        return 0;
    }
    return tryRun(args);
}
