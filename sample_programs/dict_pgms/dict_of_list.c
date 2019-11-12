#include <stdio.h>
#include <string.h>
#include "dslib.h"

/*  Dictionary - key=integer , value=list  */

List_declare(int);
typedef List(int) list_integer; 

Dict_declare(int,list_integer);

// print function for list
void print(int* a)
{
	printf("%d ",*a);
}

int main()
{
	Dict(int,list_integer) d = new_Dict(int,list_integer,10);

	List(int) l1 = new_List(int);
	insert_tail(l1,1);
	insert_tail(l1,2);
	insert_tail(l1,3);
	insert_tail(l1,4);

	List(int) l2 = new_List(int);
	insert_tail(l2,10);
	insert_tail(l2,20);
	insert_tail(l2,30);
	insert_tail(l2,40);

	// add both lists to dictionary
	add(d,1,l1);
	add(d,2,l2);

	// print list2,list1
	List(int) newlist2 = get(d,2);	// get list having key=2
	List(int) newlist1 = get(d,1);	// get list having key=1
	printf("List2:\n");
	list_disp(newlist2,print);
	printf("List1:\n");
	list_disp(newlist1,print);	

	free_ds(d);
	free_ds(l1);
	free_ds(l2);
	free_ds(newlist1);
	free_ds(newlist2);
}