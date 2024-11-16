// exception.hpp
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

#ifndef INCLUDED_STACKTRACE
#include <cpptrace/cpptrace.hpp>
#define INCLUDED_STACKTRACE
#endif

namespace cpperrors
{
    using cpptrace::stacktrace; using String = std::string; using std::source_location;

    /// A general base class for creating a generalized exception.
    /// Specified as `final` because this is meant to be a general exception; we don't want exception hierarchies.
    /// Provides:
    ///     1. A mutable general error message, and a way to get a read-only reference to it.
    ///     2. Source location: Where the exception was generated (file, line, col, and function).
    ///     3. Stack trace
    class Exception final {
        public:
            /* ~~Constructors~~ */
            explicit Exception(
                    const String& msg = "",
                    source_location src=source_location::current()
            )
                : d_msg{ msg }, d_src_location{ src }, d_strace{ stacktrace::current() }
            {}

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

        private:
            String d_msg {};                        // the message string
            source_location d_src_location;         // source location
            stacktrace d_strace;                    // stacktrace
    };
    
    /// An exception that has a payload attached to it. Allows user to send data along with the exception.
    /// If an error of this type is thrown, the user must ensure that it is caught. 
    /// Semantically, this is meant to bring specificity where the Exception brings generality.
    /// Since there's no need for inheritance in the Exception class, this class is designed using
    /// composition.
    template<typename T> 
    class TypedException final {
        public:
            TypedException(const T& data, const String& msg, source_location src=source_location::current() ) 
                : d_data { data }, d_err{ msg, src }
            {}            
            TypedException(const T& data, const Exception& e)
                : d_data { data }, d_err { e }
            {}            

            /// mutable references to allow modification to data and log message, respectively.
            T& data_mut() { return d_data; };  
            Exception& err_mut() { return d_err; }   // enables access to the `log` method.

            /// immutable references for error reporting
            const T& data() const { return d_data; };  
            const Exception& err() const { return d_err; };

        private:
            T d_data;
            Exception d_err;
            TypedException(); // A default constructor doesn't make sense in this context, so it's private.
    };
}

#endif // LIB_EXCEPTION
