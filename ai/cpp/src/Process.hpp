#pragma once

#include <iostream>
#include <functional>
#include <unistd.h>
#include <sys/wait.h>

namespace my {
    class Process {
        public:
            Process();
            Process(const Process &other) = delete;
            Process(Process &&other);
            ~Process();

            Process &operator=(const Process &other) = delete;
            Process &operator=(Process &&other);

            void kill();
            pid_t getPid() const;
            void exec(std::function<void()> &&func) const;

        private:
            pid_t _pid;
    };
}
