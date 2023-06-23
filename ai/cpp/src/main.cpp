#include <string>
#include <algorithm>
#include <vector>
#include <tuple>
#include <iostream>
#include <optional>
#include "Args.hpp"
#include "Core.hpp"

// class cmdline_args_parser{
//     public:
//         cmdline_args_parser (const int argc, char **argv){
//             for (int i=0; i < argc; ++i)
//                 tokens.push_back(std::string(argv[i]));
//         }

//         const std::optional<std::string> getCmdOption(const std::string &amp;option) const{
//             auto  itr =  std::find(tokens.begin(), tokens.end(), option);
//             if (itr != tokens.end() &amp;&amp; ++itr != tokens.end())
//                 return std::optional(*(itr));
//            return std::nullopt;
//         }

//         template<typename... Options>
//         const auto get_all_options(const Options... ops) const{
//             std::vector<std::optional<std::string>> v;
//             (v.push_back(getCmdOption(ops)), ...);
//             return v;
//         }

//         bool cmdOptionExists(const std::string &amp;option) const{
//             return
//                 std::find(tokens.begin(), tokens.end(), option) != tokens.end();
//         }

//         template<typename... Options>
//         bool all_options_exists(const Options... opts) const{
//             return (... &amp;&amp; cmdOptionExists(opts));
//         }
//         template<typename... Options>
//         bool any_options_exists(const Options... opts) const{
//             return (... || cmdOptionExists(opts));
//         }

//         const std::string&amp; get_program_name() const{ return tokens[0]; }

//     private:
//         std::vector<std::string> tokens;
// };

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
