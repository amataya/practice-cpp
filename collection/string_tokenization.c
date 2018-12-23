// People working with strings in C using the standard library
// should familiarize themselves with the Snobol-inspired functions
// strspn, strcspn and strpbrk.
//
// The actions of strtok can easily be coded using strspn and strcspn.
// strspn(s, bag) calculates the length of the prefix of string s which
// consists only of the characters in string bag.
// strcspn(s, bag) calculates the length of the prefix of s consisting of
// characters not in bag.
//
// The bag is like a one-character regex class; so that is to
// say strspn(s, "abcd") is like calculating the length of the token at the
// front of input s matching the regex [abcd]* , and in the case of strcspn,
// that becomes [^abcd]* .
// It’s nicer, since you can pass in a const char * and use it in concurrent code.
//
// https://news.ycombinator.com/item?id=18687774
//
// strtok is broken. It's not thread safe (yes there is strtok_r). That's
// because it uses a static buffer internally. It's needlessly hard to use.
// And it writes zeros to the input array. The latter means it's unfit for most
// use cases, including non-trivial tokenization where you want e.g.
// to split "a+1" into three tokens.
//
// Parsing FIX messages in finance - arse the tag/value pairs with
// no memory allocations


#include <string.h>
#include <stdio.h>

/*
 * To use this function, initialize a pointer P
 * to point to the start of the string. Then extract
 * tokens T like this:
 * T = get_next_token(&P, delimiters);
 * When it returns a null pointer, there are no more,
 * and P is set to null value as well.
 */

char* get_next_token(char **context, const char *delim)
{
    char *ret;

    /* A null context indicates no more tokens. */
    if (*context == 0)
        return 0;

    /* Skip delimiters to find start of token */
    ret = (*context += strspn(*context, delim));

    /* skip to end of token */
    *context += strcspn(*context, delim);

    /* If the token has zero length, we just
       skipped past a run of trailing delimiters, or
       were at the end of the string already.
       There are no more tokens. */

    if (ret == *context)
    {
        *context = 0;
        return 0;
    }

    /* If the character past the end of the token is the end of the string,
       set context to 0 so next time we will report no more tokens.
       Otherwise put a 0 there, and advance one character past. */

    if (**context == 0)
    {
        *context = 0;
    }
    else
    {
        **context = 0;
        (*context)++;
    }

    return ret;
}

/*
 * Handy macro wrapper for get_next_token
 */

#define FOR_EACH_TOKEN(CTX, I, S, D) \
    for (CTX = (S), (I) = get_next_token(&(CTX), D); \
         (I) != 0; \
         (I) = get_next_token(&(CTX), D))

int main(int argc, char **argv)
{
    char *context, *iter;

    if (argc >= 2)
        FOR_EACH_TOKEN (context, iter, argv[1], ":")puts(iter);

    return 0;
}
