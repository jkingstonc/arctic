#pragma once

namespace Driver{
    class Driver{
        public:
        Driver();
        ~Driver();
        virtual void init();
        virtual void close();
    };
}