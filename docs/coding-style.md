# The HELIOS coding standard

### The nomination of objects

* *only the names of macros are in uppercase, all the others (variables, functions, types, files, rep ...) are lowercase.*

-is said naming or denomination
-"the name 's "

Classic error.

The real rule of thumb concerns identifiers defining constant expressions or strings of characters, such as __certain__ macros (but not function-like macros) and enums.

### Overview

```
int     get_type(char type_char)
{
  t_types   *types;


  types = types_tab;
  while (types->type_val)
  {
    if (types->type_val == type_char)
      return (types->type_val);
    types++;
  }
  return (FALSE);
}
```

Several things shock me in this example of presentation.

1 - the use of the TAB character in the source, which has the effect of creating surreal spaces ...

2 - 2 empty lines whereas one is enough.

3 - no {} with the code structure if, which slows down the development and evolution of the code.

4 - unnecessary parentheses with return.

On the pure C plane, there would be fault, but i suppose that was not the purpose of this example.

If we stick to the presentation, my indenter proposes:
```
int get_type (char type_char)
{
   t_types *types;

   types = types_tab;
   while (types->type_val)
   {
      if (types->type_val == type_char)
         return (types->type_val);
      types++;
   }
   return (FALSE);
}
```

Let me complete this:
```
int get_type (char type_char)
{
   t_types *types = types_tab;

   while (types->type_val)
   {
      if (types->type_val == type_char)
      {
         return types->type_val;
      }
      types++;
   }
   return FALSE;
}
 ```
 __EDIT__: Removal of () from 1st return.



* *We always pass to the line after '{', '}' or a control structure. We indent once for the braces, then a second for their contents.*

No agreement for the 2nd time. This overloads the encoding unnecessarily and creates an excess of indentation that hinders readability.



 * *The names of the variables will be aligned on the name of the function that contains them and only the name of the function.*

No. We follow the indentation by default, it is much clearer (and automated)... Moreover, we can define variables at the beginning of any block, unless that too is prohibited!

### Continued

* *This concerns while, etc ... and also return, but not sizeof which is an expression returning a value.*

return? Why? Do we need parentheses to return?

when at sizeof, the syntax is
 ```
sizeof variable
sizeof (type)
 ```

therefore, it depends on the cases. Some authors claim that the parentheses around the type can be likened to a 'cast' and therefore belong to the type (not to sizeof).



* *Note that return is a control structure of C, and exit a function, so pay attention to the spaces in front of the parenthesis.*

Instead of wasting time counting spaces, do not put parentheses to return ...

Curious sense of productivity for a private school ...



* *When return takes an argument, the argument must be enclosed in parentheses:*

The icing on the cake ...

### Local presentations

* *There is no space between the name of a function and the '(', but always a space between a keyword C (with argument) and the '('*

 OK in principle, unfortunately, the indenters that I know do not make the difference, and it is unthinkable that I go back behind to correct by hand ... Not that to do ..



* _The pointer symbol_ _(*)_ _always refers to the variable (or function), and never to the type:_
```
char    *cp;    /* Correct */
char*   cp; /* Incorrect */
```

One reaches the vertices of the absurdity ... It would be better to impose a prefix p to the identifiers of pointers. It would be much more useful ...



* *Declarations will be aligned with tabs*

Not in theory, but in practice, the behavior of a TAB is not portable, so no TAB at home. So no alignment of identifiers ...



* *When a variable is declared one can not at the same time assign a value except when using a static variable.*

Very big nonsense. There are cases where non-initialization is useful and others where initialization is useful.

It is absurd to make a fix on the declaration of the data which are only a detail of C implementation. In many languages, the type is given automatically on the first assignment of the variable (the only one that actually counts ).

```
x := 12 // INTEGER
y := 12. // REAL
z := 'A' // CHARACTER
t := "hello" // STRING
```



* *The #if and #ifdef indent the following cpp directives. The #else and #endif mark the conditions from which they are derived.*

Not against the theory, except that one day, in a big industrial project, i spent two days understanding that an obscure intermediate mill (basically, she used the preprocessing instructions of a codewritten in C for to generate a source code in assembler who used the same constants ... did not support this syntax ... Since then I avoid the exotic, even standard ...

### Forbidden

* *You do not have the right to switch and for words.*

OK, we can do without it, but again, it's counterproductive.

Moreover a well-written switch-case (constants in order with a simple relationship between them) is often very well optimized by the compiler ...



* *Multi-line macros*

We could be more flexible (say 3/4 lines max) ...

### Headers

* *If the file is foo.h, the control macro is FOO_H_*

OK in principle, but several remarks:
- The final _ is unnecessarily ugly. FOO_H is OK and more readable.
- I advise you to write H_FOO. This avoids the names forbidden as ERREUR_H (E followed by a capital letter is reserved for the implementation).
- It has been forgotten an essential point is that a guard must be unique (a case of duplication is catastrophic). Personally, I add the initials of the author and a dating in the form YYYYMMDDHHMMSS



* *#foo.c always includes foo.h.*
*#Headers do not have to include themselves. At the extreme limit we can include non-system headers, but never include headers systems.*

OK for the 1st point. On the other hand the 2nd is absurd ... It is indeed useful that a header is 'autonomous' and that it can compile even if it is included first in a source code (foo.c, for example, like, recommended).

If a function prototype uses a parameter or a return of type size_t, div_t (not at least forbidden?) Or FILE , respectively **<stddef.h>**, **<stdlib.h>** and **<stdio.h>** are included in the header, otherwise there is an error. This is the same approach as for the user types for which this action seems tolerated by blocking the nose ...

There really is not much, and this principle is widely used successfully in the industry. It also relies on protections against multiple inclusions in the same compilation unit whose use is universally recommended (including this document).

I do not strongly agree with some of the **recommendations** that follow, but since they are not mandatory, i do not insist.

I do not comment on **Makefiles** .


# Conclusion

It is good to give rules, but we must not forget those that make the code better and not be content with arbitrary constraints.
