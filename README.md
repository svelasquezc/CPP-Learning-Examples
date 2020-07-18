# CPP Learning Exaples Readme

In this repository I implement some examples on how to use different C++ features like:

 - Nested namespaces -- C++17
 - Special Members -- C++98 (Move constructor and move assignment -- C++11)
 - Smart Pointers -- C++11 
 - operator+ -- C++98
 - operator[] -- C++98
 - cast to int operator -- C++98
 - explicit -- C++98
 - std::move -- C++11
 - std::bind -- C++11
 - 5/3/0 Rule -- C++98 (Move constructor and move assignment -- C++11)
 - for_each and transform with lambdas -- C++11
 - String Literals -- C++98 (But extended in C++03 and C++11)
 - Chrono Literals -- C++14 (But extended in C++20)
 - User-defined literals -- C++11
 - auto -- C++11
 - virtual -- C++98
 - Inheritance -- C++98
 - Abstract classes -- C++98
 - Interfaces -- C++98
 - RAII -- C++98
 - Templates -- C++98
 - Exceptions -- C++98
 - Structured Bindings -- C++17
 - Enum classes -- C++11
 - string_view -- C++17
 - Attributes -- C++11
 - decltype -- C++11
 - Initializer list -- C++11
 - constexpr -- C++11
 - RVO -- C++11
 - pimpl -- (It could be done before, but with unique_ptr C++11)
 - async -- C++11
 - filesystem -- C++17
 - SFINAE -- C++98
 - regex -- C++11
 - noexcept -- C++11

Those examples can be found mixed in multiple source codes in src/ folder, and some of then have their respective include headers, the most prominent example, using multiple of these features, is the MatrixExample.

In addition to those examples, I want to discuss what I find interesting about C++11, C++14, C++17 and C++20, explaining how their main features improve the C++ syntax or allow for bigger and more flexible implementations.

## C++11

With the arrival of the new Standard C++11, a lot of improvements came in, both in language extensions and the possibility of making even faster applications by working with Rvalue references, and move semantics. Also, the inclusion of lambda expressions to the language, allowing for having closures with zero or almost zero memory overhead in multiple computations requiring function objects. In terms of the syntax, the automatic deduction of types, using auto allows for much more manageable types in variable definitions and shorter codes. Moreover, the inclusion of variadic templates and forwarding references, which permit having functions with infinite parameters.

## C++14

In C++14 there were not a lot of inclusion, but the generic lambdas and the init-captures allowed for more powerful computations and lesser effort in coding. Also, by including variable templates and relaxing constexpr functions, some features on metaprogramming became more readable.

## C++17

There were various extensions in C++17 STL, the addition of execution policies, which allow for a parallel execution of almost every algorithm in the library. The addition of multiple headers, like any, variant, filesystem, which were before in libraries like boost and now are part of the standard.

## C++20

In my opinion, the most prominent extension for C++20 is the addtion of concepts and restrictions, which make metaprogramming even nearer to formal logic. However, this revision has other interesting additions like modules, which allow for organizing the code in logical parts. In addition, they include coroutines, for a more transparent concurrent and parallel programming.