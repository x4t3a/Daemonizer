#ifndef X4_DAEMONIZER_HEADER_GUARD
#   define X4_DAEMONIZER_HEADER_GUARD

#   include <csignal>
#   include <cstdio>
#   include <cstdlib>
#   include <map>
#   include <string>

namespace sys::posix {
    extern "C" {
#       include <unistd.h>
#       include <sys/types.h>
#       include <sys/stat.h>
#       include <syslog.h>
    } /// "C"
} /// sys::lin

namespace x4t3a::util {

    class Daemonizer {
        public:
            enum class DaemonFailure : char {
                FORKING_FAILURE,
            };
    
            using Signal = int;
            using SignalHandler = sighandler_t;
            using SignalsMap = std::map<Signal, SignalHandler>;
    
        private:
            static pid_t pid;
            static bool log;
            static bool daemon;
            static std::string name;
            static SignalsMap signals_n_handlers;
    
            inline static void setSignalHandlers(void) noexcept;
            inline static void closeAllFiles(void) noexcept;

            static void daemonize(bool log) noexcept;
    
        public:
            Daemonizer(std::string name, bool log = true);
            ~Daemonizer(void);
    };

} /// x4t3a::util

#endif /// X4_DAEMONIZER_HEADER_GUARD
