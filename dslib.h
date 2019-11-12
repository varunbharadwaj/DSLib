#ifndef dslib_h
#define dslib_h

#include <stdio.h>
#include <string.h>

// to support types with a * or a space
typedef char* charp ;
typedef int*  intp;
typedef double* doublep;
typedef float* floatp;
typedef long* longp;
typedef long long long_long;
typedef long double long_double;
typedef short int short_int;

// comparators 
int cmp_int(int a, int b)
{
	if(a==b)
		return 0;
	else
		return 1;
}

int cmp_short_int(short int a, short int b)
{
	if(a==b)
		return 0;
	else
		return 1;
}

int cmp_long(long a, long b)
{
	if(a==b)
		return 0;
	else
		return 1;
}

int cmp_long_long(long long a, long long b)
{
	if(a==b)
		return 0;
	else
		return 1;
}

int cmp_double(double a, double b)
{
	if(a==b)
		return 0;
	else
		return 1;
}

int cmp_long_double(long double a, long double b)
{
	if(a==b)
		return 0;
	else
		return 1;
}

int cmp_float(float a, float b)
{
	if(a==b)
		return 0;
	else
		return 1;
}

int cmp_char(char a, char b)
{
	if(a==b)
		return 0;
	else
		return 1;
}

int cmp_charp(char* a, char* b)
{
	if(strcmp(a,b)==0)
		return 0;
	else
		return 1;
}


/*  
	hash functions:
	- can be modified to use efficient hashing algorithms
	- new hash function must be created to allow different key types
*/

long hash_int(int key, long size)
{
	return key%size;
}

long hash_short_int(short int key, long size)
{
	return key%size;
}

long hash_double(double key, long size)
{
	return ((long)key)%size;
}

long hash_long_double(long double key, long size)
{
	return ((long)key)%size;
}

long hash_long(long key, long size)
{
	return key%size;
}

long hash_long_long(long long key, long size)
{
	return key%size;
}

long hash_float(float key, long size)
{
	return ((long)key)%size;
}

long hash_char(char key, long size)
{
	return ((int)key)%size;
}

long hash_charp(char* key, long size)
{
	long res = 0;
	long l = strlen(key);
	long i;
	for(i=0;i<l;i++)
	{
		res += (int)key[i];
	}

	return res%size;
}


#define Hash(type,key,size)																									\
hash_##type(key,size);


/* Common Functions , calls required function */

#define add(x,...) 																											\
(x->dslib_insert)(x,__VA_ARGS__)

#define remove(x,y) 																										\
(x->dslib_remove)(x,y)

#define getSize(x)																											\
(x->num_elements)

#define find(x,key)																											\
(x->dslib_search)(x,key)

#define free_ds(x)																											\
(x->dslib_free_ds)(x)

#include "dictionary.h"
#include "set.h"
#include "list.h"

#endif