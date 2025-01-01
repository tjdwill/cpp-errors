// typederr.t.cpp
/// Test TypedException
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
#include "../src/exception.hpp"
//- STL
#include <cassert>
#include <iostream>


using cpperrors::TypedException; using cpperrors::Exception;
using IntErr = TypedException<int>;


int VAL = 27;

void throw_typed()
{
    throw IntErr(VAL, "Found a rogue int.");
}

int main()
{

    try {
        throw_typed();
    } catch (IntErr& e) {

        e.err_mut().log("Caught an IntErr.");
        std::cerr << e.err().report(true) << "\n" << "Provided data: " << e.data() << "\n";


        // test mutation
        e.data_mut() += 10;
        assert(e.data() == VAL + 10);
    } catch (const Exception& e) {
        std::cerr << e.report();
        exit(2);
    } catch (...) {
        std::cerr << "Unknown error." << "\n";
        exit(3);
    }
}
