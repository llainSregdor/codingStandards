5.1 Formatting Your Source Code
Please keep the length of source lines to 79 characters or less, for maximum readability in the widest range of environments.

It is important to put the open-brace that starts the body of a C function in column one, so that they will start a defun. Several tools look for open-braces in column one to find the beginnings of C functions. These tools will not work on code not formatted that way.

Avoid putting open-brace, open-parenthesis or open-bracket in column one when they are inside a function, so that they won’t start a defun. The open-brace that starts a struct body can go in column one if you find it useful to treat that definition as a defun.

It is also important for function definitions to start the name of the function in column one. This helps people to search for function definitions, and may also help certain tools recognize them. Thus, using Standard C syntax, the format is this:

static char *
concat (char *s1, char *s2)
{
  …
}
or, if you want to use traditional C syntax, format the definition like this:

static char *
concat (s1, s2)        /* Name starts in column one here */
     char *s1, *s2;
{                     /* Open brace in column one here */
  …
}
In Standard C, if the arguments don’t fit nicely on one line, split it like this:

int
lots_of_args (int an_integer, long a_long, short a_short,
              double a_double, float a_float)
…
For struct and enum types, likewise put the braces in column one, unless the whole contents fits on one line:

struct foo
{
  int a, b;
}
or
struct foo { int a, b; }
The rest of this section gives our recommendations for other aspects of C formatting style, which is also the default style of the indent program in version 1.2 and newer. It corresponds to the options

-nbad -bap -nbc -bbo -bl -bli2 -bls -ncdb -nce -cp1 -cs -di2
-ndj -nfc1 -nfca -hnl -i2 -ip5 -lp -pcs -psl -nsc -nsob
We don’t think of these recommendations as requirements, because it causes no problems for users if two different programs have different formatting styles.

But whatever style you use, please use it consistently, since a mixture of styles within one program tends to look ugly. If you are contributing changes to an existing program, please follow the style of that program.

For the body of the function, our recommended style looks like this:

if (x < foo (y, z))
  haha = bar[4] + 5;
else
  {
    while (z)
      {
        haha += foo (z, z);
        z--;
      }
    return ++x + bar ();
  }
We find it easier to read a program when it has spaces before the open-parentheses and after the commas. Especially after the commas.

When you split an expression into multiple lines, split it before an operator, not after one. Here is the right way:

if (foo_this_is_long && bar > win (x, y, z)
    && remaining_condition)
Try to avoid having two operators of different precedence at the same level of indentation. For example, don’t write this:

mode = (inmode[j] == VOIDmode
        || GET_MODE_SIZE (outmode[j]) > GET_MODE_SIZE (inmode[j])
        ? outmode[j] : inmode[j]);
Instead, use extra parentheses so that the indentation shows the nesting:

mode = ((inmode[j] == VOIDmode
         || (GET_MODE_SIZE (outmode[j]) > GET_MODE_SIZE (inmode[j])))
        ? outmode[j] : inmode[j]);
Insert extra parentheses so that Emacs will indent the code properly. For example, the following indentation looks nice if you do it by hand,

v = rup->ru_utime.tv_sec*1000 + rup->ru_utime.tv_usec/1000
    + rup->ru_stime.tv_sec*1000 + rup->ru_stime.tv_usec/1000;
but Emacs would alter it. Adding a set of parentheses produces something that looks equally nice, and which Emacs will preserve:

v = (rup->ru_utime.tv_sec*1000 + rup->ru_utime.tv_usec/1000
     + rup->ru_stime.tv_sec*1000 + rup->ru_stime.tv_usec/1000);
Format do-while statements like this:

do
  {
    a = foo (a);
  }
while (a > 0);
Please use formfeed characters (control-L) to divide the program into pages at logical places (but not within a function). It does not matter just how long the pages are, since they do not have to fit on a printed page. The formfeeds should appear alone on lines by themselves.

5.2 Commenting Your Work
Every program should start with a comment saying briefly what it is for. Example: ‘fmt - filter for simple filling of text’. This comment should be at the top of the source file containing the ‘main’ function of the program.

Also, please write a brief comment at the start of each source file, with the file name and a line or two about the overall purpose of the file.

Please write the comments in a GNU program in English, because English is the one language that nearly all programmers in all countries can read. If you do not write English well, please write comments in English as well as you can, then ask other people to help rewrite them. If you can’t write comments in English, please find someone to work with you and translate your comments into English.

Please put a comment on each function saying what the function does, what sorts of arguments it gets, and what the possible values of arguments mean and are used for. It is not necessary to duplicate in words the meaning of the C argument declarations, if a C type is being used in its customary fashion. If there is anything nonstandard about its use (such as an argument of type char * which is really the address of the second character of a string, not the first), or any possible values that would not work the way one would expect (such as, that strings containing newlines are not guaranteed to work), be sure to say so.

Also explain the significance of the return value, if there is one.

Please put two spaces after the end of a sentence in your comments, so that the Emacs sentence commands will work. Also, please write complete sentences and capitalize the first word. If a lower-case identifier comes at the beginning of a sentence, don’t capitalize it! Changing the spelling makes it a different identifier. If you don’t like starting a sentence with a lower case letter, write the sentence differently (e.g., “The identifier lower-case is …”).

The comment on a function is much clearer if you use the argument names to speak about the argument values. The variable name itself should be lower case, but write it in upper case when you are speaking about the value rather than the variable itself. Thus, “the inode number NODE_NUM” rather than “an inode”.

There is usually no purpose in restating the name of the function in the comment before it, because readers can see that for themselves. There might be an exception when the comment is so long that the function itself would be off the bottom of the screen.

There should be a comment on each static variable as well, like this:

/* Nonzero means truncate lines in the display;
   zero means continue them.  */
int truncate_lines;
Every ‘#endif’ should have a comment, except in the case of short conditionals (just a few lines) that are not nested. The comment should state the condition of the conditional that is ending, including its sense. ‘#else’ should have a comment describing the condition and sense of the code that follows. For example:

#ifdef foo
  …
#else /* not foo */
  …
#endif /* not foo */
#ifdef foo
  …
#endif /* foo */
but, by contrast, write the comments this way for a ‘#ifndef’:

#ifndef foo
  …
#else /* foo */
  …
#endif /* foo */
#ifndef foo
  …
#endif /* not foo */


5.3 Clean Use of C Constructs
Please explicitly declare the types of all objects. For example, you should explicitly declare all arguments to functions, and you should declare functions to return int rather than omitting the int.

Some programmers like to use the GCC ‘-Wall’ option, and change the code whenever it issues a warning. If you want to do this, then do. Other programmers prefer not to use ‘-Wall’, because it gives warnings for valid and legitimate code which they do not want to change. If you want to do this, then do. The compiler should be your servant, not your master.

Don’t make the program ugly just to placate static analysis tools such as lint, clang, and GCC with extra warnings options such as -Wconversion and -Wundef. These tools can help find bugs and unclear code, but they can also generate so many false alarms that it hurts readability to silence them with unnecessary casts, wrappers, and other complications. For example, please don’t insert casts to void or calls to do-nothing functions merely to pacify a lint checker.

Declarations of external functions and functions to appear later in the source file should all go in one place near the beginning of the file (somewhere before the first function definition in the file), or else should go in a header file. Don’t put extern declarations inside functions.

It used to be common practice to use the same local variables (with names like tem) over and over for different values within one function. Instead of doing this, it is better to declare a separate local variable for each distinct purpose, and give it a name which is meaningful. This not only makes programs easier to understand, it also facilitates optimization by good compilers. You can also move the declaration of each local variable into the smallest scope that includes all its uses. This makes the program even cleaner.

Don’t use local variables or parameters that shadow global identifiers. GCC’s ‘-Wshadow’ option can detect this problem.

Don’t declare multiple variables in one declaration that spans lines. Start a new declaration on each line, instead. For example, instead of this:

int    foo,
       bar;
write either this:

int foo, bar;
or this:

int foo;
int bar;
(If they are global variables, each should have a comment preceding it anyway.)

When you have an if-else statement nested in another if statement, always put braces around the if-else. Thus, never write like this:

if (foo)
  if (bar)
    win ();
  else
    lose ();
always like this:

if (foo)
  {
    if (bar)
      win ();
    else
      lose ();
  }
If you have an if statement nested inside of an else statement, either write else if on one line, like this,

if (foo)
  …
else if (bar)
  …
with its then-part indented like the preceding then-part, or write the nested if within braces like this:

if (foo)
  …
else
  {
    if (bar)
      …
  }
Don’t declare both a structure tag and variables or typedefs in the same declaration. Instead, declare the structure tag separately and then use it to declare the variables or typedefs.

Try to avoid assignments inside if-conditions (assignments inside while-conditions are ok). For example, don’t write this:

if ((foo = (char *) malloc (sizeof *foo)) == NULL)
  fatal ("virtual memory exhausted");
instead, write this:

foo = (char *) malloc (sizeof *foo);
if (foo == NULL)
  fatal ("virtual memory exhausted");
  
  5.4 Naming Variables, Functions, and Files
The names of global variables and functions in a program serve as comments of a sort. So don’t choose terse names—instead, look for names that give useful information about the meaning of the variable or function. In a GNU program, names should be English, like other comments.

Local variable names can be shorter, because they are used only within one context, where (presumably) comments explain their purpose.

Try to limit your use of abbreviations in symbol names. It is ok to make a few abbreviations, explain what they mean, and then use them frequently, but don’t use lots of obscure abbreviations.

Please use underscores to separate words in a name, so that the Emacs word commands can be useful within them. Stick to lower case; reserve upper case for macros and enum constants, and for name-prefixes that follow a uniform convention.

For example, you should use names like ignore_space_change_flag; don’t use names like iCantReadThis.

Variables that indicate whether command-line options have been specified should be named after the meaning of the option, not after the option-letter. A comment should state both the exact meaning of the option and its letter. For example,

/* Ignore changes in horizontal whitespace (-b).  */
int ignore_space_change_flag;
When you want to define names with constant integer values, use enum rather than ‘#define’. GDB knows about enumeration constants.

You might want to make sure that none of the file names would conflict if the files were loaded onto an MS-DOS file system which shortens the names. You can use the program doschk to test for this.

Some GNU programs were designed to limit themselves to file names of 14 characters or less, to avoid file name conflicts if they are read into older System V systems. Please preserve this feature in the existing GNU programs that have it, but there is no need to do this in new GNU programs. doschk also reports file names longer than 14 characters.

5.5 Portability between System Types
In the Unix world, “portability” refers to porting to different Unix versions. For a GNU program, this kind of portability is desirable, but not paramount.

The primary purpose of GNU software is to run on top of the GNU kernel, compiled with the GNU C compiler, on various types of CPU. So the kinds of portability that are absolutely necessary are quite limited. But it is important to support Linux-based GNU systems, since they are the form of GNU that is popular.

Beyond that, it is good to support the other free operating systems (*BSD), and it is nice to support other Unix-like systems if you want to. Supporting a variety of Unix-like systems is desirable, although not paramount. It is usually not too hard, so you may as well do it. But you don’t have to consider it an obligation, if it does turn out to be hard.

The easiest way to achieve portability to most Unix-like systems is to use Autoconf. It’s unlikely that your program needs to know more information about the host platform than Autoconf can provide, simply because most of the programs that need such knowledge have already been written.

Avoid using the format of semi-internal data bases (e.g., directories) when there is a higher-level alternative (readdir).

As for systems that are not like Unix, such as MSDOS, Windows, VMS, MVS, and older Macintosh systems, supporting them is often a lot of work. When that is the case, it is better to spend your time adding features that will be useful on GNU and GNU/Linux, rather than on supporting other incompatible systems.

If you do support Windows, please do not abbreviate it as “win”. See Trademarks.

Usually we write the name “Windows” in full, but when brevity is very important (as in file names and some symbol names), we abbreviate it to “w”. In GNU Emacs, for instance, we use ‘w32’ in file names of Windows-specific files, but the macro for Windows conditionals is called WINDOWSNT. In principle there could also be ‘w64’.

It is a good idea to define the “feature test macro” _GNU_SOURCE when compiling your C files. When you compile on GNU or GNU/Linux, this will enable the declarations of GNU library extension functions, and that will usually give you a compiler error message if you define the same function names in some other way in your program. (You don’t have to actually use these functions, if you prefer to make the program more portable to other systems.)

But whether or not you use these GNU extensions, you should avoid using their names for any other meanings. Doing so would make it hard to move your code into other GNU programs.

5.6 Portability between CPUs
Even GNU systems will differ because of differences among CPU types—for example, difference in byte ordering and alignment requirements. It is absolutely essential to handle these differences. However, don’t make any effort to cater to the possibility that an int will be less than 32 bits. We don’t support 16-bit machines in GNU.

You need not cater to the possibility that long will be smaller than pointers and size_t. We know of one such platform: 64-bit programs on Microsoft Windows. If you care about making your package run on Windows using Mingw64, you would need to deal with 8-byte pointers and 4-byte long, which would break this code:

printf ("size = %lu\n", (unsigned long) sizeof array);
printf ("diff = %ld\n", (long) (pointer2 - pointer1));
Whether to support Mingw64, and Windows in general, in your package is your choice. The GNU Project doesn’t say you have any responsibility to do so. Our goal is to replace proprietary systems, including Windows, not to enhance them. If people pressure you to make your program run on Windows, and you are not interested, you can respond with, “Switch to GNU/Linux — your freedom depends on it.”

Predefined file-size types like off_t are an exception: they are longer than long on many platforms, so code like the above won’t work with them. One way to print an off_t value portably is to print its digits yourself, one by one.

Don’t assume that the address of an int object is also the address of its least-significant byte. This is false on big-endian machines. Thus, don’t make the following mistake:

int c;
…
while ((c = getchar ()) != EOF)
  write (file_descriptor, &c, 1);
Instead, use unsigned char as follows. (The unsigned is for portability to unusual systems where char is signed and where there is integer overflow checking.)

int c;
while ((c = getchar ()) != EOF)
  {
    unsigned char u = c;
    write (file_descriptor, &u, 1);
  }
Avoid casting pointers to integers if you can. Such casts greatly reduce portability, and in most programs they are easy to avoid. In the cases where casting pointers to integers is essential—such as, a Lisp interpreter which stores type information as well as an address in one word—you’ll have to make explicit provisions to handle different word sizes. You will also need to make provision for systems in which the normal range of addresses you can get from malloc starts far away from zero.

5.7 Calling System Functions
Historically, C implementations differed substantially, and many systems lacked a full implementation of ANSI/ISO C89. Nowadays, however, all practical systems have a C89 compiler and GNU C supports almost all of C99 and some of C11. Similarly, most systems implement POSIX.1-2001 libraries and tools, and many have POSIX.1-2008.

Hence, there is little reason to support old C or non-POSIX systems, and you may want to take advantage of standard C and POSIX to write clearer, more portable, or faster code. You should use standard interfaces where possible; but if GNU extensions make your program more maintainable, powerful, or otherwise better, don’t hesitate to use them. In any case, don’t make your own declaration of system functions; that’s a recipe for conflict.

Despite the standards, nearly every library function has some sort of portability issue on some system or another. Here are some examples:

open
Names with trailing /’s are mishandled on many platforms.

printf
long double may be unimplemented; floating values Infinity and NaN are often mishandled; output for large precisions may be incorrect.

readlink
May return int instead of ssize_t.

scanf
On Windows, errno is not set on failure.

Gnulib is a big help in this regard. Gnulib provides implementations of standard interfaces on many of the systems that lack them, including portable implementations of enhanced GNU interfaces, thereby making their use portable, and of POSIX-1.2008 interfaces, some of which are missing even on up-to-date GNU systems.

Gnulib also provides many useful non-standard interfaces; for example, C implementations of standard data structures (hash tables, binary trees), error-checking type-safe wrappers for memory allocation functions (xmalloc, xrealloc), and output of error messages.

Gnulib integrates with GNU Autoconf and Automake to remove much of the burden of writing portable code from the programmer: Gnulib makes your configure script automatically determine what features are missing and use the Gnulib code to supply the missing pieces.

The Gnulib and Autoconf manuals have extensive sections on portability: Introduction in Gnulib and see Portable C and C++ in Autoconf. Please consult them for many more details.

5.8 Internationalization
GNU has a library called GNU gettext that makes it easy to translate the messages in a program into various languages. You should use this library in every program. Use English for the messages as they appear in the program, and let gettext provide the way to translate them into other languages.

Using GNU gettext involves putting a call to the gettext macro around each string that might need translation—like this:

printf (gettext ("Processing file '%s'..."), file);
This permits GNU gettext to replace the string "Processing file '%s'..." with a translated version.

Once a program uses gettext, please make a point of writing calls to gettext when you add new strings that call for translation.

Using GNU gettext in a package involves specifying a text domain name for the package. The text domain name is used to separate the translations for this package from the translations for other packages. Normally, the text domain name should be the same as the name of the package—for example, ‘coreutils’ for the GNU core utilities.

To enable gettext to work well, avoid writing code that makes assumptions about the structure of words or sentences. When you want the precise text of a sentence to vary depending on the data, use two or more alternative string constants each containing a complete sentences, rather than inserting conditionalized words or phrases into a single sentence framework.

Here is an example of what not to do:

printf ("%s is full", capacity > 5000000 ? "disk" : "floppy disk");
If you apply gettext to all strings, like this,

printf (gettext ("%s is full"),
        capacity > 5000000 ? gettext ("disk") : gettext ("floppy disk"));
the translator will hardly know that "disk" and "floppy disk" are meant to be substituted in the other string. Worse, in some languages (like French) the construction will not work: the translation of the word "full" depends on the gender of the first part of the sentence; it happens to be not the same for "disk" as for "floppy disk".

Complete sentences can be translated without problems:

printf (capacity > 5000000 ? gettext ("disk is full")
        : gettext ("floppy disk is full"));
A similar problem appears at the level of sentence structure with this code:

printf ("#  Implicit rule search has%s been done.\n",
        f->tried_implicit ? "" : " not");
Adding gettext calls to this code cannot give correct results for all languages, because negation in some languages requires adding words at more than one place in the sentence. By contrast, adding gettext calls does the job straightforwardly if the code starts out like this:

printf (f->tried_implicit
        ? "#  Implicit rule search has been done.\n",
        : "#  Implicit rule search has not been done.\n");
Another example is this one:

printf ("%d file%s processed", nfiles,
        nfiles != 1 ? "s" : "");
The problem with this example is that it assumes that plurals are made by adding ‘s’. If you apply gettext to the format string, like this,

printf (gettext ("%d file%s processed"), nfiles,
        nfiles != 1 ? "s" : "");
the message can use different words, but it will still be forced to use ‘s’ for the plural. Here is a better way, with gettext being applied to the two strings independently:

printf ((nfiles != 1 ? gettext ("%d files processed")
         : gettext ("%d file processed")),
        nfiles);
But this still doesn’t work for languages like Polish, which has three plural forms: one for nfiles == 1, one for nfiles == 2, 3, 4, 22, 23, 24, ... and one for the rest. The GNU ngettext function solves this problem:

printf (ngettext ("%d files processed", "%d file processed", nfiles),
        nfiles);


5.9 Character Set
Sticking to the ASCII character set (plain text, 7-bit characters) is preferred in GNU source code comments, text documents, and other contexts, unless there is good reason to do something else because of the application domain. For example, if source code deals with the French Revolutionary calendar, it is OK if its literal strings contain accented characters in month names like “Floréal”. Also, it is OK (but not required) to use non-ASCII characters to represent proper names of contributors in change logs (see Change Logs).

If you need to use non-ASCII characters, you should normally stick with one encoding, certainly within a single file. UTF-8 is likely to be the best choice.

5.10 Quote Characters
In the C locale, the output of GNU programs should stick to plain ASCII for quotation characters in messages to users: preferably 0x22 (‘"’) or 0x27 (‘'’) for both opening and closing quotes. Although GNU programs traditionally used 0x60 (‘`’) for opening and 0x27 (‘'’) for closing quotes, nowadays quotes ‘`like this'’ are typically rendered asymmetrically, so quoting ‘"like this"’ or ‘'like this'’ typically looks better.

It is ok, but not required, for GNU programs to generate locale-specific quotes in non-C locales. For example:

printf (gettext ("Processing file '%s'..."), file);
Here, a French translation might cause gettext to return the string "Traitement de fichier ‹ %s ›...", yielding quotes more appropriate for a French locale.

Sometimes a program may need to use opening and closing quotes directly. By convention, gettext translates the string ‘"`"’ to the opening quote and the string ‘"'"’ to the closing quote, and a program can use these translations. Generally, though, it is better to translate quote characters in the context of longer strings.

If the output of your program is ever likely to be parsed by another program, it is good to provide an option that makes this parsing reliable. For example, you could escape special characters using conventions from the C language or the Bourne shell. See for example the option --quoting-style of GNU ls.

5.11 Mmap
If you use mmap to read or write files, don’t assume it either works on all files or fails for all files. It may work on some files and fail on others.

The proper way to use mmap is to try it on the specific file for which you want to use it—and if mmap doesn’t work, fall back on doing the job in another way using read and write.

The reason this precaution is needed is that the GNU kernel (the HURD) provides a user-extensible file system, in which there can be many different kinds of “ordinary files”. Many of them support mmap, but some do not. It is important to make programs handle all these kinds of files.

