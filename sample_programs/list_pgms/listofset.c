#include <stdio.h>
#include <string.h>
#include "dslib.h"

Set_declare(int);
typedef Set(int) set_integer;

List_declare(set_integer);

void print(Set(int) s)
{
	int* arr = getSetValues(s);
	long n = getSize(s);
	int i;
	for(i=0;i<n;i++)
	{
		printf("%d ",arr[i]);
	}

	free(arr);
	printf("\n");
}

int main()
{
	Set(int) set1 = new_Set(int,10);
	add(set1,1);
	add(set1,2);

	Set(int) set2 = new_Set(int,10);
	add(set2,10);
	add(set2,20);

	Set(int) set3 = new_Set(int,10);
	add(set3,100);
	add(set3,200);

	List(set_integer) list = new_List(set_integer);
	insert_tail(list,set1);
	insert_tail(list,set2);
	insert_tail(list,set3);

	Set(int) a;
	Set(int) b;
	Set(int) c;
	a = list_get(list,1);
	b = list_get(list,2);
	c = list_get(list,3);

	print(a);
	print(b);
	print(c);

	free_ds(set1);
	free_ds(set2);
	free_ds(set3);
	free_ds(list);
}