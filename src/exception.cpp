/// exception.cpp

#include "exception.hpp"
#include <sstream>
#include <string>
#include <cpptrace/cpptrace.hpp>

namespace err {
    using String = std::string;

    // ~~ Exception  ~~
    void Exception::log(const String& msg) { d_msg += "\n" + msg; }

    const String& Exception::what() const { return d_msg; }

    const String Exception::where() const {
        std::stringstream info {};

        info << "THROWN FROM:\n" << d_src_location.file_name() << ":" << d_src_location.line()
            << ":" << d_src_location.column() << " in function " 
            << '`' << d_src_location.function_name() << '`';

        return info.str();
    }

    String Exception::how(bool color) const { return d_strace.to_string(color); }

    const String Exception::report(bool color) const {
        std::stringstream report {};

        report << how(color) << "\n" <<
            "\nERROR LOG:\n" << what() << "\n\n" 
            << where() << "\n";

        return report.str();

    }


    // ~~ TypedException  ~~

    /* Defining the methods here resulted in a linking error. Why?
     * UPDATE: https://old.reddit.com/r/cpp_questions/comments/1catg5f/include_header_but_still_undefined_reference_to/
     *
     * Turns out, template functions and classes must be defined in the same files as declared.
    */ 

} // namespace err
