#pragma once

namespace Shell {
    class Shell {
    public:
        Shell(){}
        ~Shell(){}

        static Shell create();
        int exec(const char * cmd);
        void run();
    };
}