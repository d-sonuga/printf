# Problems
Most of the problems that stopped the compiler from accepting your code has to do with formatting, using
functions that don't exist and unimplemented functions. I've made some changes in the code related to
formatting but the changes I made could affect the code logic.

To see the difference between the code as is now and the code before, use `git diff`.

* In `handle_specifier.c`, the function's don't have implementations.
The error: `error: control reaches end of non-void function [-Werror=return-type]` is shown
because the functions in the file specify return type `int` but none of them return anything.
To fix this, you need to write the implementations for those functions that return the `int`.

* The error: `error: unused parameter ‘param_name’ [-Werror=unused-parameter]` is outputted when a function
doesn't use a parameter. To get rid of it, use the parameter `param_name` or mark it unused with the `UNUSED`
macro.

* In an if statement or a while statement, if the body has more than one line, you have to enclose it in
curly braces. For example, the following is correct:

```c
if(boolfunc())
    do_something()
```

But the following is not:

```c
if(boolfunc())
    do_one()
    do_two()
    do_three()
```

The above is the reason an error like `error: this ‘if’ clause does not guard... [-Werror=misleading-indentation]`
will be outputted. The compiler sees the above code like this:

```c
if(boolfunc())
    do_one()
do_two()
do_three()
```

To make the above correct, you have to surround it with curly braces:

```c
if(boolfunc())
{
    do_one()
    do_two()
    do_three()
}
```

The same applies to while statements.

I added the curly braces for most of these errors in `non_printable.c`, `printable.c`, 
`functions_specifier.c` and `all_handle.c` but it may have affected the correctness of your code so
you should check them out to see if they're still doing what they're supposed to be doing.

* The error: `error: implicit declaration of function ‘func_name’ [-Werror=implicit-function-declaration]`
is outputted when you try to use functions that are not defined. Like the `print_hex` in `printable.c`
and the `convert_size_unsgnd` in `printable.c`.
You need to either include a header file that has this function or write your own implementation of it.

