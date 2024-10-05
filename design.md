# General Error Handling Utilities

The C++ community has yet to converge on the best way to handle errors. Do we use exceptions? Error codes? Algebraic data types? The practical answer appears to be a combination of all three—or at least the spirit of all three.

## General Exception

The purpose of an exception is to provide information about some unusual circumstance in which the program in question did not perform properly. It is a diagnostic tool. Given how expensive they are, exceptions are not for simple "didn't work, let's retry" operations; they are more suitable (in my opinion) for unrecoverable operations.

In his talk, [*Exceptions in C++: Better Design Through Analysis of Real World Usage*](https://youtu.be/HXJmrMnnDYQ?si=COR_q_9IgNFKteFz), Peter Muldoon walks through the mechanics of exceptions, the original philosophic intent behind them, and how they are (incorrectly) used in production. Throughout the talk, Muldoon profers his opinion on the proper way to use the mechanism. The climax of the presentation is the unveiling of a general exception class. This class is meant to encompass the most general needs and wants for this type of error handling:

- What was the error (error message)
- Where did the error occur? (line num, col num, file name, function name)
- Execution context (stacktrace)
- A means of propagating and appending information (mutable string for logging)
- Relevant object data the developer may desire 

Inspired by this, I want to make my own implementation of such a class. It'd be a great learning experience, so let's go.

### Data or No Data?

Unlike Muldoon's implementation, I won't include the ability to store an object in mine. His version used a templatized class to allow any type to be stored, but one loses the ability to catch a general exception class as a result. Therefore, I propose implementing two classes: the generalized exception and the typed exception. The only difference between the two is that the typed exception can store data. 

However, what I *don't* propose doing is inheriting from the general exception. I don't think it serves a purpose. If we were to have a `catch(const general_exception& e)` block, if `e` is a typed exception, this information is lost because the general form is used. Since the only reason to have a typed exception is to include data, it makes no sense to inherit and then use a general catch. 

Instead, the typed version can consist of the included data + a general exception object. This can then be thrown. Since typed exceptions are meant to be semantically specific, if one is thrown, the thrower must ensure that it is caught.


### Question(s)

0. When setting a default value for a class data member, this initialization method:

```c++
// function called in member initialization list

Exception(
    const String msg = ""
)
    : d_msg{ msg }, d_src_location{ source_location::current() }, d_strace{ stacktrace::current() }
{}
```

resulted in the source location of the *header* file to be used for all invocations of `Exception`.

However, this version with the default in the argument list resulted in proper behavior:

```c++

Exception(
        const String msg = "",
        source_location src=source_location::current()
)
    : d_msg{ msg }, d_src_location{ src }, d_strace{ stacktrace::current() }
{}
```

Why?


0. Is it possible to use C++>=20 features in a C++<20 application, provided the C++20 features are compiled as a library and aren't exposed to users?

## To-Do
Design Notes and TODO
                                                                                  
- [x] What do I need? Rule of five? 
    Nope. I don't do any resource management.
- [x] Does anything need to be virtual?
    Nope. I am making this class uninheritable.
- [x] Error Message
- [x] Diagnostic Information
- [x] Useful Functions
- [x] Do I need to use cpptrace, or can I use C++23 and be backwards-compatible? 
    Yep! Primarily because my own compiler doesn't support C++23.
