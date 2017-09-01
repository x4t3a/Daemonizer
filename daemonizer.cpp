#include "daemonizer.hpp"

namespace x4t3a::util {

    bool Daemonizer::daemon{ false };
    bool Daemonizer::log{ true };
    pid_t Daemonizer::pid{ 0 };
    std::string Daemonizer::name{ "MyDaemon" };
    Daemonizer::SignalsMap Daemonizer::signals_n_handlers{
        { SIGCHLD, SIG_IGN },
        { SIGHUP,  SIG_IGN }
    };

    inline void
    Daemonizer::setSignalHandlers(void) noexcept
    {
        for (const auto& signal_n_handler : signals_n_handlers)
        {
            std::signal(signal_n_handler.first,
                        signal_n_handler.second);
        }
    }

    inline void
    Daemonizer::closeAllFiles(void) noexcept
    {
        for (auto f{ sys::posix::sysconf(sys::posix::_SC_OPEN_MAX) }; f >= 0; --f)
        { sys::posix::close(f); }
    }

    Daemonizer::Daemonizer(std::string name,
                           bool log /* = true */)
    {
        Daemonizer::name = std::move(name);
        Daemonizer::daemonize(log);
    }

    void
    Daemonizer::daemonize(bool log) noexcept
    {
        Daemonizer::pid = sys::posix::fork();

        if (Daemonizer::pid < 0)
        { std::exit(EXIT_FAILURE); }

        if (Daemonizer::pid > 0)
        { std::exit(EXIT_SUCCESS); }

        if (sys::posix::setsid() < 0)
        { std::exit(EXIT_FAILURE); }

        Daemonizer::setSignalHandlers();

        Daemonizer::pid = sys::posix::fork();

        if (Daemonizer::pid < 0)
        { std::exit(EXIT_FAILURE); }

        if (Daemonizer::pid > 0)
        { std::exit(EXIT_SUCCESS); }

        sys::posix::umask(0);

        sys::posix::chdir("/");

        Daemonizer::closeAllFiles();
        
        if (Daemonizer::log)
        {
            sys::posix::openlog(Daemonizer::name.c_str(), LOG_PID, LOG_DAEMON);
            sys::posix::syslog(LOG_NOTICE, "Daemonized.");
        }
    }

    Daemonizer::~Daemonizer(void)
    {
        if (Daemonizer::log)
        {
            sys::posix::syslog(LOG_NOTICE, "Terminated.");
            sys::posix::closelog();
        }
    }

} /// x4t3a::util

