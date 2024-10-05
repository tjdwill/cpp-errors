#include "../exception.hpp"
#include <iostream>


void error () { throw err::Exception("Found error when attempting to <do something>."); }
int main() {
    try{ 
        error();
    }
    catch (const err::Exception& e) {
        std::cerr << e.report(true);
        exit(1);
    }
    catch (...) {
        std::cerr << "Unexpected error." << "\n";
        exit(2);
    }
}
