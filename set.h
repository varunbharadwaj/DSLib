/*
	Suhas Kashyap		01FB14ECS255
	Varun Bharadwaj		01FB14ECS278
	Varun M 			01FB14ECS280
*/

#ifndef set_h
#define set_h

#include <stdlib.h>
#include <string.h>


#define Set_declare(type)																								\
																														\
/* structure for each value/node */																						\
typedef struct set_node_##type																							\
{																														\
	type value;																											\
	struct set_node_##type* next;																						\
} set_node_##type;																										\
																														\
/* set structure holding references to required functions and the Pair array/hashset */									\
typedef struct set_##type																								\
{																														\
	Setnode(type)* parray; /* Pair(type1,type2) array */																\
	long size;																											\
	long num_elements;																									\
	void (*dslib_insert)(struct set_##type* ,type);																		\
	int (*dslib_search)(struct set_##type* , type);																		\
	int (*dslib_remove)(struct set_##type* , type);																		\
	void (*dslib_free_ds)(struct set_##type*);																			\
	type* (*get_value_arr)(struct set_##type*);																			\
	struct set_##type* (*set_union)(struct set_##type*,struct set_##type*);												\
	struct set_##type* (*set_intersection)(struct set_##type*, struct set_##type*);										\
	struct set_##type* (*set_duplicate)(struct set_##type*);															\
} set_##type;																											\
																														\
/* Function Prototype */																								\
Set(type) Set_create_##type(long);																						\
																														\
/*  fn is a comparator function , insert_value function inserts a value in a linked list  */							\
void insert_value_##type( Set(type) d, Setnode(type) node, type value, int (*fn)(type,type) )							\
{																														\
	if(node->next == NULL)																								\
	{																													\
		Setnode(type) p = (Setnode(type)) malloc( sizeof(set_node_##type) );											\
		p->next = NULL;																									\
		p->value = value;																								\
		node->next = p;																									\
		d->num_elements = d->num_elements + 1;																			\
	}																													\
	else																												\
	{																													\
		Setnode(type) ref = node->next;																					\
		while( fn(ref->value,value)!=0 && ref->next != NULL)															\
		{																												\
			ref = ref->next;																							\
		}																												\
																														\
		if(fn(ref->value,value)!=0)																						\
		{																												\
			Setnode(type) pair = (Setnode(type)) malloc( sizeof(set_node_##type) ) ;									\
			pair -> value = value;																						\
			pair -> next = NULL;																						\
			ref->next = pair;	/* new value added */																	\
			d->num_elements = d->num_elements + 1;																		\
		}																												\
	}																													\
}																														\
/* delete value , returns 1 if successful , 0 otherwise */																\
int remove_value_##type( Set(type) d, Setnode(type) node, type value, int (*fn)(type,type) )							\
{																														\
	if(node->next == NULL)																								\
	{																													\
			return 0;																									\
	}																													\
	else																												\
	{																													\
		Setnode(type) p = node->next;																					\
		Setnode(type) q = node;																							\
		while( p != NULL && fn(p->value,value)!=0 )																		\
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
																														\
/* returns 1 if value is found , 0 otherwise */																			\
int set_search_##type( Set(type) set, type value)																		\
{																														\
	long hash_value = Hash(type,value,set->size);																		\
	Setnode(type) p = (set->parray)[hash_value];																		\
	int (*fn)(type,type) = getcmp(type);																				\
																														\
	if(p->next != NULL)																									\
	{																													\
		p = p->next;																									\
		while( p != NULL && fn(p->value,value)!=0)																		\
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
/*insert value*/																										\
void set_insert_##type( Set(type) set, type value)																		\
{																														\
	long hash_value = Hash(type,value,set->size);																		\
	Setnode(type)* parray = set->parray;																				\
																														\
	insert_value_##type(set,parray[hash_value],value,getcmp(type));														\
}																														\
																														\
/*deletes the value*/																									\
int remove_##type( Set(type) set, type value)																			\
{																														\
	long hash_value = Hash(type,value,set->size);																		\
	Setnode(type)* parray = set->parray;																				\
																														\
	return remove_value_##type(set,parray[hash_value],value,getcmp(type));												\
}																														\
																														\
/* free allocated memory */																								\
void set_destroy_##type(Set(type) d)																					\
{																														\
	Setnode(type)* x = d->parray;																						\
	Setnode(type) p;																									\
	Setnode(type) q;																									\
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
																														\
																														\
type* get_value_arr_##type(Set(type) set)																				\
{																														\
	type* arr = (type*) malloc((set->num_elements) * sizeof(type));														\
	Setnode(type)* x = set->parray;																						\
	Setnode(type) p;																									\
	long i,j=0;																											\
	for(i=0;i<set->size;i++)																							\
	{																													\
		p = x[i]->next;																									\
		while(p != NULL)																								\
		{																												\
			arr[j++] = p->value;																						\
			p = p->next;																								\
		}																												\
	}																													\
	return arr;																											\
}																														\
																														\
Set(type) intersection_##type(Set(type) s1, Set(type) s2)																\
{																														\
	long newsize = s1->size;																							\
	if (s2->size < newsize)																								\
		newsize = s2->size;																								\
	Set(type) res = new_Set(type,newsize);																				\
																														\
	Setnode(type)* x = s1->parray;																						\
	Setnode(type) p;																									\
	long i,j=0;																											\
	for(i=0;i<s1->size;i++)																								\
	{																													\
		p = x[i]->next;																									\
		while(p != NULL)																								\
		{																												\
			if(find(s2,p->value))																						\
				add(res,p->value);																						\
			p = p->next;																								\
		}																												\
	}																													\
																														\
	x = s2->parray;																										\
	j=0;																												\
	for(i=0;i<s2->size;i++)																								\
	{																													\
		p = x[i]->next;																									\
		while(p != NULL)																								\
		{																												\
			if(find(s1,p->value))																						\
				add(res,p->value);																						\
			p = p->next;																								\
		}																												\
	}																													\
																														\
	return res;																											\
}																														\
																														\
Set(type) union_##type(Set(type) s1, Set(type) s2)																		\
{																														\
	long newsize = s1->size;																							\
	if (s2->size > newsize)																								\
		newsize = s2->size;																								\
	Set(type) res = new_Set(type,newsize);																				\
																														\
	Setnode(type)* x = s1->parray;																						\
	Setnode(type) p;																									\
	long i,j=0;																											\
	for(i=0;i<s1->size;i++)																								\
	{																													\
		p = x[i]->next;																									\
		while(p != NULL)																								\
		{																												\
			add(res,p->value);																							\
			p = p->next;																								\
		}																												\
	}																													\
																														\
	x = s2->parray;																										\
	j=0;																												\
	for(i=0;i<s2->size;i++)																								\
	{																													\
		p = x[i]->next;																									\
		while(p != NULL)																								\
		{																												\
			add(res,p->value);																							\
			p = p->next;																								\
		}																												\
	}																													\
																														\
	return res;																											\
}																														\
																														\
Set(type) duplicate_##type(Set(type) s)																					\
{																														\
	Set(type) res = new_Set(type,s->size);																				\
	Setnode(type)* x = s->parray;																						\
	Setnode(type) p;																									\
	Setnode(type) q;																									\
																														\
	long i;																												\
	for(i=0;i<s->size;i++)																								\
	{																													\
		p = x[i]->next;																									\
		while(p != NULL)																								\
		{																												\
			add(res,p->value);																							\
			p = p->next;																								\
		}																												\
	}																													\
	return res;																											\
}																														\
																														\
/* creates and returns array/hashset of size 'size'  */																	\
Set(type) Set_create_##type(long size)																					\
{																														\
	Setnode(type)* val_array = (Setnode(type)*) malloc(size * sizeof(Setnode(type)));									\
	/*  create pair header node for each element of dict  */															\
	long i;																												\
	for(i=0;i<size;i++)																									\
	{																													\
		val_array[i] = (Setnode(type)) malloc( sizeof(set_node_##type) );												\
		(val_array[i]) -> next = NULL;																					\
	}																													\
																														\
	Set(type) set = (Set(type)) malloc( sizeof(set_##type) );															\
	set->parray = val_array;																							\
	set->size = size;																									\
	set->num_elements = 0;																								\
	set->dslib_insert = set_insert_##type;																				\
	set->dslib_search = set_search_##type;																				\
	set->dslib_remove = remove_##type;																					\
	set->dslib_free_ds = set_destroy_##type;																			\
	set->get_value_arr = get_value_arr_##type;																			\
	set->set_union = union_##type;																						\
	set->set_intersection = intersection_##type;																		\
	set->set_duplicate = duplicate_##type;																				\
	return set;																											\
}																														\


// get correct comparator function
#define getcmp(type)																									\
cmp_##type

/* call the correct function pointed to by the function pointer in the set structure */

#define union(set1,set2)																								\
(set1->set_union)(set1,set2)

#define intersection(set1,set2)																							\
(set1->set_intersection)(set1,set2)

#define duplicate(set)																									\
(set->set_duplicate)(set)

#define getSetValues(set)																								\
(set->get_value_arr)(set)

#define new_Set(type,size)																								\
Set_create_##type(size)

#define Setnode(type)																									\
set_node_##type*

#define Set(type)																										\
set_##type*  


#endif