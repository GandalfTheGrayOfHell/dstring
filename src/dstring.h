#ifndef DS_MAX_PREALLOC
	#define DS_MAX_PREALLOC 1024
#endif // DS_MAX_PREALLOC

#ifndef DSTRING_H
#define DSTRING_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	uint64_t len;
	uint64_t free;
	char * buf;	
} * dstring;

/**
 * Creates a new dstring from char[].
 * 
 * @param  str String
 * @return     dstring
 */
dstring ds_new(char str[]);

/**
 * Creates a new dstring from char[] with no free space. Only the length of `str` is allocated.
 * 
 * @param  str String
 * @return     dstring
 */
dstring ds_new_f(char str[]);

/**
 * Creates an empty dstring with preallocated memory.
 * 
 * @return dstring
 */
dstring ds_empty();

/**
 * Creates an empty dstring with no preallicated memory.
 * 
 * @return dstring
 */
dstring ds_empty_f();

/**
 * Creates a copy of the passed dstring. New memory is allocated for the copied dstring.
 * 
 * @param  src dstring to be copied
 * @return     dstring
 */
dstring ds_cpy(dstring src);

/**
 * Creates a new dstring from the range passed over the param. New memory is allocated for the resulting dstring.
 * 
 * @param  d Source dstring
 * @param  a Lower bound index
 * @param  b Higher bound index
 * @return   dstring
 */
dstring ds_range(dstring src, uint64_t lower, uint64_t higher);

/**
 * Returns the length of the dstring.
 * 
 * @param  src Source dstring
 * @return     uint64_t
 */
inline uint64_t ds_len(dstring src) { return src->len; };

/**
 * Returns the free space available in the dstring.
 * 
 * @param  src Source dstring
 * @return     uint64_t
 */
inline uint64_t ds_space(dstring src) { return src->free; };

/**
 * Compares two dstrings.
 * 
 * @param  a dstring
 * @param  b dstring
 * @return   int
 */
inline int ds_cmp(dstring a, dstring b) { return strcmp(a->buf, b->buf); };

/**
 * Appends the given string to the dstring. If enough memory is not available at the time, memory will be reallocated.
 * 
 * @param  dest Destination dstring 
 * @param  str  String
 * @return      int
 */
int ds_append(dstring src, char str[]);

/**
 * Concatenates the source dstring to the dest dstring. If enough memory is not available at the time, memory will be reallocated.
 * 
 * @param  dest Destination dstring
 * @param  src  Source dstring
 * @return      int
 */
int ds_concat(dstring dest, dstring src);

/**
 * Concatenates the source dstring to the dest dstring and also frees the source dstring. If enough memory is not available at the time, memory will be reallocated.
 * 
 * @param  dest Destination dstring
 * @param  src  Source dstring
 * @return      int
 */
int ds_concat(dstring dest, dstring src);

/**
 * Replaces a substring with another string. If enough memory is not available at the time, memory will be reallocated.
 * 
 * @param dest Destination dstring
 * @param src  Substring
 * @param repl Replacement
 */
void ds_replace(dstring dest, char src[], char repl[]);

/**
 * Applies a left trim on the dest dstring removing the given character(ASCII code). After the operation, memory is moved back and free space is updated accordingly.
 * 
 * @param dest Destination dstring
 * @param code ASCII code of the symbol
 */
void ds_ltrim(dstring dest, int code);

/**
 * Applies a right trim on the dest dstring removing the given character(ASCII code). After the operation, only the NULL terminator(\0) is added at an apt position. No memory changes are performed.
 * 
 * @param dest Destination dstring
 * @param code ASCII code of the symbol
 */
void ds_rtrim(dstring dest, int code);

/**
 * Performs trim operation on both sides removing the given character(ASCII code). Under the hood, it calls `ds_ltrim` and `ds_rtrim`.
 * 
 * @param dest Destination dstring
 * @param code ASCII code of the symbol
 */
void ds_trim(dstring dest, int code);

/**
 * Applies a left trim on the dest dstring removing whitespaces. After the operation, memory is moved back and free space is updated accordingly. Under the hood, calls `ds_ltrim` with character code as 32.
 * 
 * @param dest Destination dstring
 */
void ds_ltrim_w(dstring dest);

/**
 * Applies a right trim on the dest dstring removing whitespace. After the operation, only the NULL terminator(\0) is added at an apt position. No memory changes are performed. Under the hood, calls `ds_rtrim` with character code as 32.
 * 
 * @param dest Destination dstring
 */
void ds_rtrim_w(dstring dest);

/**
 * Performs trim operation on both sides removing whitespace. Under the hood, it calls `ds_ltrim_w` and `ds_rtrim_w` with character code as 32.
 * 
 * @param dest Destination dstring
 */
void ds_trim_w(dstring dest);

/**
 * Converts the dstring to uppercase.
 * 
 * @param dest Destination dstring
 */
void ds_lower(dstring dest);

/**
 * Converts the dstring to lowercase.
 * 
 * @param dest Destination dstring
 */
void ds_upper(dstring dest);

/**
 * Deallocates all the free space available in the dstring.
 *  
 * @param dest Destination dstring
 */
void ds_rmfree(dstring dest);

/**
 * Frees the entire dstring.
 * 
 * @param dest [description]
 */
void ds_free(dstring dest);

#endif // DSTRING_H
