/*
	Suhas Kashyap		01FB14ECS255
	Varun Bharadwaj		01FB14ECS278
	Varun M 			01FB14ECS280
*/

#ifndef dictionary_h
#define dictionary_h

#include <stdlib.h>
#include <string.h>


#define Dict_declare(type1,type2)																						\
																														\
/* structure for each key,value pair */																					\
typedef struct pair_node_##type1##_##type2																				\
{																														\
	type1 key;																											\
	type2 value;																										\
	struct pair_node_##type1##_##type2* next;																			\
} pair_node_##type1##_##type2;																							\
																														\
/* dictionary structure holding references to required functions and the Pair array/hashset */							\
typedef struct dict_##type1##_##type2																					\
{																														\
	Pair(type1,type2)* parray; /* Pair(type1,type2) array */															\
	long size;																											\
	long num_elements;																									\
	type2 (*get_value)(struct dict_##type1##_##type2* , type1 );														\
	void (*dslib_insert)(struct dict_##type1##_##type2* ,type1 , type2 );												\
	int (*dslib_search)(struct dict_##type1##_##type2* , type1);														\
	int (*dslib_remove)(struct dict_##type1##_##type2* , type1);														\
	void (*dslib_free_ds)(struct dict_##type1##_##type2*);																\
	type1* (*get_key_arr)(struct dict_##type1##_##type2*);																\
} dict_##type1##_##type2;																								\
																														\
/*  fn is a comparator function , inserts a (key,value) pair  */														\
void insert_pair_##type1##_##type2( Dict(type1,type2) d, Pair(type1,type2) node, type1 key, type2 value, int (*fn)(type1,type1) )			\
{																														\
	if(node->next == NULL)																								\
	{																													\
		Pair(type1,type2) p = (Pair(type1,type2)) malloc( sizeof(pair_node_##type1##_##type2) );						\
		p->next = NULL;																									\
		p->key = key;																									\
		p->value = value;																								\
		node->next = p;																									\
		d->num_elements = d->num_elements + 1;																			\
	}																													\
	else																												\
	{																													\
		Pair(type1,type2) ref = node->next;																				\
		while( fn(ref->key,key)!=0 && ref->next != NULL)																\
		{																												\
			ref = ref->next;																							\
		}																												\
																														\
		if(fn(ref->key,key)==0)																							\
		{																												\
			ref->value = value; /* value updated */																		\
		}																												\
		else																											\
		{																												\
			Pair(type1,type2) pair = (Pair(type1,type2)) malloc( sizeof(pair_node_##type1##_##type2) ) ;				\
			pair -> key = key;																							\
			pair -> value = value;																						\
			pair -> next = NULL;																						\
			ref->next = pair;	/* new (key,value) pair added */														\
			d->num_elements = d->num_elements + 1;																		\
		}																												\
	}																													\
}																														\
/* delete (key,value) pair , returns 1 if successful , 0 otherwise */													\
int remove_pair_##type1##_##type2( Dict(type1,type2) d, Pair(type1,type2) node, type1 key, int (*fn)(type1,type1) )		\
{																														\
	if(node->next == NULL)																								\
	{																													\
			return 0;																									\
	}																													\
	else																												\
	{																													\
		Pair(type1,type2) p = node->next;																				\
		Pair(type1,type2) q = node;																						\
		while( p != NULL && fn(p->key,key)!=0 )																			\
		{																												\
			q = p;																										\
			p = p->next;																								\
		}																												\
																														\
		if(p == NULL)																									\
		{																												\
			return 0;																									\
		}																												\
		else																											\
		{																												\
			q->next = p->next;																							\
			free(p);																									\
			d->num_elements = d->num_elements - 1;																		\
			return 1;																									\
		}																												\
	}																													\
}																														\
																														\
																														\
/* get the value corresponding to the given key  */																		\
type2 get_##type1##_##type2( Dict(type1,type2) dict, type1 key)															\
{																														\
	long hash_value = Hash(type1,key,dict->size);																		\
	Pair(type1,type2) p = (dict->parray)[hash_value];																	\
	int (*fn)(type1,type1) = getcmp(type1);																				\
																														\
	if(p->next != NULL)																									\
	{																													\
		p = p->next;																									\
		while( fn(p->key,key)!=0 && p != NULL)																			\
		{																												\
			p = p->next;																								\
		}																												\
		if(p != NULL)																									\
			return p->value;																							\
	}																													\
}																														\
																														\
/* returns 1 if key is found , 0 otherwise */																			\
int search_##type1##_##type2( Dict(type1,type2) dict, type1 key)														\
{																														\
	long hash_value = Hash(type1,key,dict->size);																		\
	Pair(type1,type2) p = (dict->parray)[hash_value];																	\
	int (*fn)(type1,type1) = getcmp(type1);																				\
																														\
	if(p->next != NULL)																									\
	{																													\
		p = p->next;																									\
		while( p != NULL && fn(p->key,key)!=0)																			\
		{																												\
			p = p->next;																								\
		}																												\
		if(p == NULL)																									\
			return 0;																									\
		else																											\
			return 1;																									\
	}																													\
	else																												\
		return 0;																										\
}																														\
																														\
/*insert (key,value) pair in the list corresponding to the hash value of the key by calling the insert_pair function*/	\
void insert_##type1##_##type2( Dict(type1,type2) dict, type1 key, type2 value)											\
{																														\
	long hash_value = Hash(type1,key,dict->size);																		\
	Pair(type1,type2)* parray = dict->parray;																			\
																														\
	insert_pair_##type1##_##type2(dict,parray[hash_value],key,value,getcmp(type1));										\
}																														\
																														\
/*remove (key,value) pair in the list corresponding to the hash value of the key by calling the remove_pair function*/	\
int remove_##type1##_##type2( Dict(type1,type2) dict, type1 key)														\
{																														\
	long hash_value = Hash(type1,key,dict->size);																		\
	Pair(type1,type2)* parray = dict->parray;																			\
																														\
	return remove_pair_##type1##_##type2(dict,parray[hash_value],key,getcmp(type1));									\
}																														\
																														\
/* free allocated memory */																								\
void dict_destroy_##type1##_##type2(Dict(type1,type2) d)																\
{																														\
	Pair(type1,type2)* x = d->parray;																					\
	Pair(type1,type2) p;																								\
	Pair(type1,type2) q;																								\
																														\
	long i;																												\
	for(i=0;i<d->size;i++)																								\
	{																													\
		p = x[i];																										\
		while(p != NULL)																								\
		{																												\
			q = p->next;																								\
			free(p);																									\
			p = q;																										\
		}																												\
	}																													\
	free(x);																											\
}																														\
																														\
type1* get_key_arr_##type1##_##type2(Dict(type1,type2) d)																\
{																														\
	type1* arr = (type1*) malloc((d->num_elements) * sizeof(type1));													\
	Pair(type1,type2)* x = d->parray;																					\
	Pair(type1,type2) p;																								\
	long i,j=0;																											\
	for(i=0;i<d->size;i++)																								\
	{																													\
		p = x[i]->next;																									\
		while(p != NULL)																								\
		{																												\
			arr[j++] = p->key;																							\
			p = p->next;																								\
		}																												\
	}																													\
	return arr;																											\
}																														\
																														\
/* creates and returns array/hashset of size 'size'  */																	\
Dict(type1,type2) Dict_create_##type1##_##type2(long size)																\
{																														\
	Pair(type1,type2)* pair_array = (Pair(type1,type2)*) malloc(size * sizeof(Pair(type1,type2)));						\
	/*  create pair header node for each element of dict  */															\
	long i;																												\
	for(i=0;i<size;i++)																									\
	{																													\
		pair_array[i] = (Pair(type1,type2)) malloc( sizeof(pair_node_##type1##_##type2) );								\
		(pair_array[i]) -> next = NULL;																					\
	}																													\
																														\
	Dict(type1,type2) dict = (Dict(type1,type2)) malloc( sizeof(dict_##type1##_##type2) );								\
	dict->parray = pair_array;																							\
	dict->size = size;																									\
	dict->num_elements = 0;																								\
	dict->get_value = get_##type1##_##type2;																			\
	dict->dslib_insert = insert_##type1##_##type2;																		\
	dict->dslib_search = search_##type1##_##type2;																		\
	dict->dslib_remove = remove_##type1##_##type2;																		\
	dict->dslib_free_ds = dict_destroy_##type1##_##type2;																\
	dict->get_key_arr = get_key_arr_##type1##_##type2;																	\
	return dict;																										\
}																														\


// get correct comparator function
#define getcmp(type)																										\
cmp_##type

/* call the correct function pointed to by the function pointer in the dictionary structure */

#define getDictKeys(dict)																									\
(dict->get_key_arr)(dict)

#define get(dict,key)																										\
(dict->get_value)(dict,key)

#define new_Dict(type1,type2,size)																							\
Dict_create_##type1##_##type2(size)

#define Pair(type1,type2)																									\
pair_node_##type1##_##type2*

#define Dict(type1,type2)																									\
dict_##type1##_##type2*  


#endif