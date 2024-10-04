#ifndef LIB_EXCEPTION
#define LIB_EXCEPTION

// Redundant include guards *a la* John Lakos' "Large-Scale C++ Software Design"

#ifndef INCLUDED_STD_EXCEPTION
#include <exception>
#define INCLUDED_STD_EXCEPTION
#endif

#ifndef INCLUDED_STD_STRING
#include <string>
#define INCLUDED_STD_STRING
#endif 

#ifndef INCLUDED_STD_SRCLOCATION
#include <source_location>
#define INCLUDED_STD_SRCLOCATION
#endif
// Try to use <stacktrace>. This will be an edifying experiment in C++ compatibility.
// My thinking is that since a user of this class would only need the string representation of the stacktrace, no stacktrace-dependent types are exposed directly.
// Compatibility shouldn't be an issue, right?
#ifndef INCLUDED_STACKTRACE
#include <stacktrace>
#define INCLUDED_STACKTRACE
#endif

namespace err {
    /*  Design Notes and TODO
     *
     *  - [ ] What do I need? Rule of five?
     *  - [ ] Does anything need to be virtual?
     *  - [ ] Error Message
     *  - [ ] Diagnostic Information
     *  - [ ] Useful Functions
     *  - [ ] Do I need to use cpptrace, or can I use C++23 and be backwards-compatible? 
    */

    /// A general base class for creating a generalized exception.
    /// Specified as `final` because this is meant to be a general exception; we don't want exception hierarchies.
    /// Provides:
    ///     1. A mutable general error message, and a way to get a read-only reference to it.
    ///     2. Source location: Where the exception was generated (file, line, col, and function).
    ///     3. Stack trace
    class ErrReport final {
        private:
            std::string d_msg {};                   // the message string
            std::source_location d_src_location;    // source location
            std::stacktrace d_strace;               // stacktrace
        public:
            ErrReport()
                : d_msg("An error has occurred.\n"), d_src_location(std::source_location::current()), d_strace(std::stacktrace())
            {}
    };
}

#endif // LIB_EXCEPTION
