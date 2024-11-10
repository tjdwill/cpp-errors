/// Test TypedException
#include "../include/exception.hpp"
#include <iostream>
#include <cassert>

using cpperrors::TypedException; using cpperrors::Exception;
using IntErr = TypedException<int>;

int VAL = 27;

void throw_typed() {
    throw IntErr(VAL, "Found a rouge int.");
}

int main() {

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
