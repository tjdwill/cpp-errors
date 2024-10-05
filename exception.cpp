/// exception.cpp

#include "exception.hpp"
#include <sstream>
#include <string>
#include <cpptrace/cpptrace.hpp>
#include <source_location>

namespace err {
    using String = std::string;

    void Exception::log(const String& msg) { d_msg += "\n" + msg; }

    const String& Exception::what() const { return d_msg; }

    const String Exception::where() const {
        std::stringstream info {};
        info << "Source File: " << d_src_location.file_name() << ":" << d_src_location.line() << ":" << d_src_location.column() << " in function " << '<' << d_src_location.function_name() << '>';

        return info.str();
    }

    String Exception::how(bool color) const { return d_strace.to_string(color); }

    const String Exception::report(bool color) const {
        std::stringstream report {};
        report << how(color) << "\n" <<
            "\n" << what() << "\n" 
            << where() << "\n";

        return report.str();

    }
} // namespace err
