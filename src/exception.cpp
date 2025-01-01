/// exception.cpp
/*
* Copyright (C) 2024 Terrance Williams
* 
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
* 
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
* 
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
* USA
*/
#include "exception.hpp"
//- STL
#include <sstream>
#include <string>
//- Third-party
#include <cpptrace/cpptrace.hpp>

namespace cpperrors 
{
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
