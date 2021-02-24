#pragma once

#include <util/HashMap.h>

namespace Driver{
    class Driver{
        public:
        Driver();
        ~Driver();
        virtual void init();
        virtual void close();
        private:
        //static HashMap<const char *> drivers;
    };
}