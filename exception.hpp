#ifndef LIB_EXCEPTION
#define LIB_EXCEPTION

// Redundant include guards *a la* John Lakos' "Large-Scale C++ Software Design"

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
#include <cpptrace/cpptrace.hpp>
#define INCLUDED_STACKTRACE
#endif

namespace err {
    using cpptrace::stacktrace; using String = std::string;
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
    class Exception final {
        private:
            String d_msg {};                        // the message string
            std::source_location d_src_location;    // source location
            stacktrace d_strace;                    // stacktrace
        public:
            /* ~~Constructors~~ */
            Exception()
                : d_msg("An error has occurred."), d_src_location(std::source_location::current()), d_strace(stacktrace::current()) {}
            Exception(const String msg)
                : d_msg(msg), d_src_location(std::source_location::current()), d_strace(stacktrace::current()) {}

            // Rule of five (unneeded as I'm not managing any resources)
            // Exception(const Exception&);            // copy constructor
            // Exception operator=(const Exception&);  // copy assignment
            // Exception(Exception&&);                 // move constructor
            // Exception operator=(Exception&&);       // move assignment
            // ~Exception();                           // destructor

            /* ~~Methods~~ */

            /// Appends the provided message to the current one.
            /// Useful for propagating the exception.
            void log(const String& msg);

            /// View the error message.
            const String& what() const;
            /// View the source location in which the exception was thrown.
            const String where() const;
            /// View the stacktrace leading to this exception.
            String how(bool color=false) const;
            
            /// Generate a (possibly colored) string of the entire report (err_msg, stacktrace, and source information)
            const String report(bool color=false) const;  
    };
}

#endif // LIB_EXCEPTION
