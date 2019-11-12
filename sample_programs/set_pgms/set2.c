#include <stdio.h>
#include <string.h>
#include "dslib.h"

Set_declare(char);

int main()
{

	Set(char) set = new_Set(char,10);

	printf("At start: size = %ld\n",getSize(set));

	add(set,'a');
	add(set,'b');
	add(set,'c');
	
	if(find(set,'a'))
		printf("a found in the set\n");
	
	printf("Before deleting: size = %ld\n",getSize(set));
	
	remove(set,'a');

	printf("After deleting: size = %ld\n",getSize(set));

	if(find(set,'c'))
		printf("c found in set\n");

	if(find(set,'b'))
		printf("b found in set\n");

	char* arr = getSetValues(set);
	int i;
	printf("Printing set values:\n");
	for(i=0;i<getSize(set);i++)
		printf("%c ",arr[i]);

	printf("\n");

	Set(char) set2 = new_Set(char,10);
	add(set2,'a');
	add(set2,'a');
	add(set2,'b');
	add(set2,'q');
	add(set2,'w');

	Set(char) t1 = duplicate(set);
	arr = getSetValues(t1);
	printf("Printing duplicate set values:\n");
	for(i=0;i<getSize(t1);i++)
		printf("%c ",arr[i]);

	printf("\n");
	arr = getSetValues(set2);
	printf("Printing set2 values:\n");
	for(i=0;i<getSize(set2);i++)
		printf("%c ",arr[i]);

	Set(char) t2 = intersection(set,set2);
	printf("\n");
	arr = getSetValues(t2);
	printf("Printing intersection of set and set2:\n");
	for(i=0;i<getSize(t2);i++)
		printf("%c ",arr[i]);


	Set(char) t3 = union(set,set2);
	printf("\n");
	arr = getSetValues(t3);
	printf("Printing union of set and set2:\n");
	for(i=0;i<getSize(t3);i++)
		printf("%c ",arr[i]);


	free(arr);
	free_ds(set);
	free_ds(set2);
	free_ds(t1);
	free_ds(t2);
	free_ds(t3);

}