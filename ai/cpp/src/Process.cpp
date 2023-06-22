#include "Process.hpp"

using namespace my;

Process::Process(): _pid(::fork()) {}

Process::~Process()
{
    ::waitpid(_pid, NULL, 0);
}

void Process::kill()
{
    if (_pid != 0)
        ::kill(_pid, SIGKILL);
}

pid_t Process::getPid() const
{
    return _pid;
}

void Process::exec(std::function<void()> &&func) const
{
    if (_pid == 0) {
        func();
        exit(0);
    }
}
