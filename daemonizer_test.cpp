#include <iostream>

#include "daemonizer.hpp"

int
main(int argc, char* argv[])
{
    x4t3a::util::Daemonizer daemon{ "DAE" };

    while (1)
    {
        //TODO: Insert daemon code here.
        sys::posix::sleep(20);
        break;
    }

    return EXIT_SUCCESS;
}
