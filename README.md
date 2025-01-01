## General Exception

```c++
#include "../src/exception.hpp"
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
```

Results in the following outout:

```console 
Stack trace (most recent call first):
#0 0x0000560579432364 at /home/tj/programming/cpp/.libraries/cpp-errors/build/TestExcept
#1 0x0000560579431fed at /home/tj/programming/cpp/.libraries/cpp-errors/build/TestExcept
#2 0x000056057943204f at /home/tj/programming/cpp/.libraries/cpp-errors/build/TestExcept
#3 0x00007fa31e633d67 at /lib/x86_64-linux-gnu/libc.so.6
#4 0x00007fa31e633e24 at /lib/x86_64-linux-gnu/libc.so.6
#5 0x0000560579431ed0 at /home/tj/programming/cpp/.libraries/cpp-errors/build/TestExcept

ERROR LOG:
Found error when attempting to <do something>.

THROWN FROM:
/home/tj/programming/cpp/.libraries/cpp-errors/tests/exception.t.cpp:5:86 in function `void error()`
```

## Typed Exception

```c++
/// Test TypedException
#include "../src/exception.hpp"
#include <iostream>
#include <cassert>

using err::TypedException; using err::Exception;
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
        
        exit(1);
    } catch (const Exception& e) {
        std::cerr << e.report();
        exit(2);
    } catch (...) {
        std::cerr << "Unknown error." << "\n";
        exit(3);
    }
}
```

Results in the following output:

```console
Stack trace (most recent call first):
#0 0x000055600786a564 at /home/tj/programming/cpp/.libraries/cpp-errors/build/TestTyped
#1 0x000055600786aa8a at /home/tj/programming/cpp/.libraries/cpp-errors/build/TestTyped
#2 0x000055600786a037 at /home/tj/programming/cpp/.libraries/cpp-errors/build/TestTyped
#3 0x000055600786a09c at /home/tj/programming/cpp/.libraries/cpp-errors/build/TestTyped
#4 0x00007f6f9bc33d67 at /lib/x86_64-linux-gnu/libc.so.6
#5 0x00007f6f9bc33e24 at /lib/x86_64-linux-gnu/libc.so.6
#6 0x0000556007869f10 at /home/tj/programming/cpp/.libraries/cpp-errors/build/TestTyped

ERROR LOG:
Found a rogue int.
Caught an IntErr.

THROWN FROM:
/home/tj/programming/cpp/.libraries/cpp-errors/tests/typederr.t.cpp:12:43 in function `void throw_typed()`

Provided data: 27
```
