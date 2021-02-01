#pragma once

namespace Shell {
    class Shell {
    public:
        Shell(){}
        ~Shell(){}
        static Shell create();
        void run();
    private:
        int exec(const char * cmd);
    };
}