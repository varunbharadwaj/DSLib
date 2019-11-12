/*
	Suhas Kashyap		01FB14ECS255
	Varun Bharadwaj		01FB14ECS278
	Varun M 			01FB14ECS280
*/

#ifndef list_h
#define list_h

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

long int_hash(int* t)
{
	return *t;
}

void* reference(void* value)
{
	return value;
}

#define List_declare(type)																					\
																											\
typedef struct list_node_##type										/*stringification*/						\
{																											\
	type data;																								\
	struct list_node_##type* next;																			\
	struct list_node_##type* prev;																			\
}list_node_##type;																							\
																											\
typedef struct list_##type																					\
{																											\
	/*Members of a struct*/																					\
	list_node_##type* head;																					\
	long size;																								\
																											\
	/*Member functions declaration*/																		\
	long (*list_length)(struct list_##type*);																\
	void (*insert_head)(struct list_##type*, type);															\
	void (*insert_tail)(struct list_##type*, type);															\
	void (*list_insert)(struct list_##type*, type, long);													\
	void (*replace)(struct list_##type*, type, long);														\
	void (*drop_head)(struct list_##type*);																	\
	void (*drop_tail)(struct list_##type*);																	\
	void (*drop)(struct list_##type*, long position);														\
	void (*dslib_free_ds)(struct list_##type*);																\
	void (*list_disp)(struct list_##type*,void (*)(type*));													\
	struct list_##type* (*chain)(struct list_##type*,struct list_##type*);									\
	type* (*list_to_array)(struct list_##type*);															\
	long (*list_search)(struct list_##type*,type,long (*)(type*));											\
	void (*list_reverse)(struct list_##type*);																\
	type (*list_get)(struct list_##type*,long);																\
}list_##type;																								\
																											\
list_node(type) new_node_##type(type value)																	\
{																											\
	list_node(type) newNode=(list_node(type)) malloc(sizeof(list_node_##type));								\
	newNode->next=NULL;																						\
	newNode->prev=NULL;																						\
	newNode->data=value;																					\
	return newNode;																							\
}																											\
																											\
long list_length_##type(List(type) l)																		\
{																											\
	return l->size;																							\
}																											\
																											\
void list_disp_##type(List(type) list,void (*nodePrinter)(type*))											\
{																											\
	if(list->head==NULL)																					\
	{																										\
		printf("length: %ld\n",list_length(list));															\
		return;																								\
	}																										\
	printf("\n");																							\
	list_node(type) p=list->head;																			\
	if(nodePrinter==NULL)																					\
	{																										\
		while(p)																							\
		{																									\
			_Generic((p->data),int:printf("%d",p->data),long:printf("%ld",p->data),float:printf("%lf",p->data),double:printf("%lf",p->data),char*:printf("%s",p->data),default:printf("%p",&(p->data)));	\
			p=p->next;																						\
			if(p)																							\
				printf(" -> ");																				\
		}																									\
	}																										\
	else																									\
	{																										\
		while(p)																							\
		{																									\
			_Generic((p->data),int:printf("%d",p->data),long:printf("%ld",p->data),float:printf("%lf",p->data),double:printf("%lf",p->data),char*:printf("%s",p->data),default:nodePrinter(&(p->data)));	\
			p=p->next;																						\
			if(p)																							\
				printf(" -> ");																				\
		}																									\
	}																										\
	printf("\tlength: %ld\n",list_length(list));															\
}																											\
																											\
/*Insert node at beginning*/																				\
void insert_head_##type(List(type) list,type value)															\
{																											\
	list_node(type) newNode = new_node_##type(value);														\
																											\
	if(list->head==NULL)																					\
		list->head=newNode;																					\
	else																									\
	{																										\
		newNode->next=list->head;																			\
		(list->head)->prev=newNode;																			\
		list->head=newNode;																					\
	}																										\
	++(list->size);																							\
	/*return list;*/																						\
}																											\
																											\
/*Insert node at end of link-list*/																			\
void insert_tail_##type(List(type) list,type value)															\
{																											\
	list_node(type) newNode=new_node_##type(value);															\
																											\
	if(list->head==NULL)																					\
		list->head=newNode;																					\
	else																									\
	{																										\
		list_node(type) p=list->head;																		\
		list_node(type) q;																					\
		while(p)		/*p!=NULL*/																			\
		{																									\
			q=p;																							\
			p=p->next;																						\
		}																									\
		q->next=newNode;																					\
		newNode->prev=q;																					\
	}																										\
	++(list->size);																							\
	/*return list;*/																						\
}																											\
																											\
/*Insert node at specified position*/																		\
void list_insert_##type(List(type) list,type value,long position)											\
{																											\
	long list_len=(list->list_length)(list)+1;																\
	assert(position>0 && position<=list_len);																\
																											\
	if(position==1)																							\
	{																										\
		insert_head_##type(list,value);																		\
	}																										\
	else if(position==list_len)																				\
	{																										\
		insert_tail_##type(list,value);																		\
	}																										\
	else																									\
	{																										\
		list_node(type) newNode=new_node_##type(value);														\
		long pos=2;																							\
																											\
		list_node(type) p=list->head->next;																	\
		list_node(type) q=list->head;																		\
		while(pos!=position && p)		/*p!=NULL*/															\
		{																									\
			q=p;																							\
			p=p->next;																						\
			pos+=1;																							\
		}																									\
		q->next=newNode;																					\
		newNode->prev=q;																					\
		newNode->next=p;																					\
		p->prev=newNode;																					\
	}																										\
	++(list->size);																							\
	/*return list;*/																						\
}																											\
																											\
/*Replace data of a node at speified position*/																\
void replace_##type(List(type) list,type rdata,long position)												\
{																											\
	assert(position>0 && position<=list_length(list));														\
																											\
	long pos=1;																								\
	list_node(type) p=list->head;																			\
	while(pos!=position && p->next)		/*p!=NULL*/															\
	{																										\
		p=p->next;																							\
		pos+=1;																								\
	}																										\
	p->data=rdata;																							\
}																											\
																											\
/*Drop node at beginning of link list*/																		\
void drop_head_##type(List(type) list)																		\
{																											\
	if(list->head!=NULL)																					\
	{																										\
		list_node(type) p=list->head;																		\
		list->head=p->next;																					\
		free(p);																							\
		if(list->head)																						\
			list->head->prev=NULL;																			\
		--(list->size);																						\
	}																										\
	/*return list;*/																						\
}																											\
																											\
/*Drop node at end of link list*/																			\
void drop_tail_##type(List(type) list)																		\
{																											\
	if(list->head==NULL)return;																				\
	else if(list->head->next==NULL)																			\
	{																										\
		list_node(type) ref=list->head;																		\
		free(ref);																							\
		list->head=NULL;																					\
		--(list->size);																						\
	}																										\
	else																									\
	{																										\
		list_node(type) p=list->head;																		\
		list_node(type) q;																					\
		while(p)		/*p!=NULL*/																			\
		{																									\
			q=p;																							\
			p=p->next;																						\
		}																									\
		list_node(type) ref=q;																				\
		q->prev->next=NULL;																					\
		free(ref);																							\
		--(list->size);																						\
	}																										\
	/*return list;*/																						\
}																											\
																											\
/*Drop node at specified position*/																			\
void drop_##type(List(type) list,long position)																\
{																											\
	long list_size=(list->list_length)(list);																\
	assert(position>0 && position<=list_size);																\
																											\
	if(position==1)																							\
	{																										\
		drop_head_##type(list);																				\
	}																										\
	else if(position==list_size)																			\
	{																										\
		drop_tail_##type(list);																				\
	}																										\
	else																									\
	{																										\
		long pos=2;																							\
		list_node(type) p=list->head->next;																	\
		list_node(type) q=list->head;																		\
		while(pos!=position && p)		/*p!=NULL*/															\
		{																									\
			q=p;																							\
			p=p->next;																						\
			pos+=1;																							\
		}																									\
		q->next=p->next;																					\
		p->next->prev=q;																					\
		free(p);																							\
	}																										\
	--(list->size);																							\
	/*return list;*/																						\
}																											\
																											\
List(type) chain_##type(List(type) l1,List(type) l2)														\
{																											\
	if(l1->head==NULL) return l2;																			\
	else if(l2==NULL || l2->head==NULL) return l1;															\
																											\
	list_node(type) p=l1->head;																				\
	list_node(type) q;																						\
	while(p)																								\
	{																										\
		q=p;																								\
		p=p->next;																							\
	}																										\
	q->next=l2->head;																						\
	l2->head->prev=q;																						\
	return l1;																								\
}																											\
																											\
type* list_to_array_##type(List(type) l)																	\
{																											\
	type* array=malloc(list_length(l)*sizeof(type));														\
	list_node(type) p=l->head;																				\
	long i=0;																								\
	while(p)																								\
	{																										\
		array[i]=p->data;																					\
		i+=1;																								\
		p=p->next;																							\
	}																										\
	return array;																							\
}																											\
																											\
long list_search_##type(List(type) list, type key, long (*hash_code)(type*))								\
{																											\
	if(list->head==NULL)return -1;																			\
	long pos=1;																								\
	list_node(type) p;																						\
	if(hash_code==NULL)																						\
	{																										\
		p=list->head;																						\
		while(p)																							\
		{																									\
			if(_Generic((key),int:int_hash,default:reference)(&(p->data))==_Generic((key),int:int_hash,default:reference)(&key))		\
				return 	pos;																				\
			p=p->next;																						\
			++pos;																							\
		}																									\
	}																										\
	else																									\
	{																										\
		list_node(type) p=list->head;																		\
		while(p)																							\
		{																									\
			if(_Generic((key),int:int_hash,default:(hash_code))(&(p->data))==_Generic((key),int:int_hash,default:hash_code)(&key))		\
				return 	pos;																				\
			p=p->next;																						\
			++pos;																							\
		}																									\
	}																										\
	return -1;																								\
}																											\
																											\
void list_reverse_##type(List(type) list)																	\
{																											\
	if(list->head==NULL)return;																				\
	list_node(type) p=list->head;																			\
	list_node(type) q=NULL;																					\
	list_node(type) ref;																					\
	while(p)																								\
	{																										\
		q=p->prev;																							\
		p->prev=p->next;																					\
		p->next=q;																							\
																											\
		ref=p;																								\
		p=p->prev; 																							\
	}																										\
	list->head=ref;																							\
}																											\
																											\
/*De-allocate memory*/																						\
void list_destroy_##type(List(type) list)																	\
{																											\
	if(list==NULL) return;																					\
	list_node(type) p=list->head;																			\
	list_node(type) q;																						\
	while(p!=NULL)																							\
	{																										\
		q=p->next;																							\
		free(p);																							\
		p=q;																								\
	}																										\
	/*free(list);*/																							\
	list->head=NULL;																						\
}																											\
																											\
type list_get_##type(List(type) list, long position)														\
{																											\
	assert(position>0 && position<=list_length(list));														\
	long pos=1;																								\
	list_node(type) p;																						\
	p=list->head;																							\
	while(p)																								\
	{																										\
		if(pos==position)																					\
			return p->data;																					\
		p=p->next;																							\
		++pos;																								\
	}																										\
}																											\
																											\
List(type)	new_List_##type()																				\
{																											\
	List(type) l=malloc(sizeof(list_##type));																\
																											\
	l->head=NULL;																							\
	l->size=0;																								\
																											\
	l->list_length=list_length_##type;																		\
	l->insert_head=insert_head_##type;																		\
	l->insert_tail=insert_tail_##type;																		\
	l->list_insert=list_insert_##type;																		\
	l->replace=replace_##type;																				\
	l->drop_head=drop_head_##type;																			\
	l->drop_tail=drop_tail_##type;																			\
	l->drop=drop_##type;																					\
	l->dslib_free_ds=list_destroy_##type;																	\
	l->list_disp=list_disp_##type;																			\
	l->chain=chain_##type;																					\
	l->list_to_array=list_to_array_##type;																	\
	l->list_search=list_search_##type;																		\
	l->list_reverse=list_reverse_##type;																	\
	l->list_get=list_get_##type;																			\
																											\
	return l;																								\
}

#define list_node(type) list_node_##type*
#define new_List(type) new_List_##type()
#define List(type) list_##type*

#define list_length(l) l->list_length(l)
#define list_disp(l,nodePrinter) l->list_disp(l,nodePrinter)

#define insert_head(l,type) l->insert_head(l,type)
#define insert_tail(l,type) l->insert_tail(l,type)
#define insert(l,type,position) l->list_insert(l,type,position)
#define replace(l,type,position) l->replace(l,type,position)
#define drop_head(l) l->drop_head(l)
#define drop_tail(l) l->drop_tail(l)
#define drop(l,position) l->drop(l,position)

#define chain(l1,l2) l1->chain(l1,l2)
#define list_to_array(l) l->list_to_array(l)
#define list_search(l,value,hc) l->list_search(l,value,hc)
#define list_reverse(l) l->list_reverse(l)
#define list_get(l,val) l->list_get(l,val)
/*#define list_destroy(l) l->list_destroy(l)*/
#endif