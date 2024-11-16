// exception.t.cpp
#include "../src/exception.hpp"
#include <iostream>

using cpperrors::Exception;

void error () { throw Exception("Found error when attempting to <do something>."); }

int main() {
    try{ 
        error();
    }
    catch (const Exception& e) {
        std::cerr << e.report(true);
    }
    catch (...) {
        std::cerr << "Unexpected error." << "\n";
        exit(1);
    }
}
