#include "../exception.hpp"
#include <iostream>


int main() {
    try{ 
        throw err::Exception("Testing the exception.");
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
