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
