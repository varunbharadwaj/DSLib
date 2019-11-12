#include <stdio.h>
#include <string.h>
#include "dslib.h"

Set_declare(charp);

int main()
{

	Set(charp) set = new_Set(charp,10);

	printf("At start: size = %ld\n",getSize(set));

	add(set,"apple");
	add(set,"mango");
	add(set,"a2");
	add(set,"a10");
	add(set,"hello");
	
	if(find(set,"apple"))
		printf("apple found in the set\n");
	
	printf("Before deleting: size = %ld\n",getSize(set));
	
	remove(set,"apple");

	printf("After deleting: size = %ld\n",getSize(set));

	if(find(set,"mango"))
		printf("mango found in set\n");

	if(find(set,"apple"))
		printf("apple found in set\n");

	char** arr = getSetValues(set);
	int i;
	printf("Printing set values:\n");
	for(i=0;i<getSize(set);i++)
		printf("%s ",arr[i]);

	printf("\n");

	Set(charp) set2 = new_Set(charp,10);
	add(set2,"a1");
	add(set2,"a2");
	add(set2,"a3");
	add(set2,"a4");
	add(set2,"a5");

	Set(charp) t1 = duplicate(set);
	arr = getSetValues(t1);
	printf("Printing duplicate set values:\n");
	for(i=0;i<getSize(t1);i++)
		printf("%s ",arr[i]);

	printf("\n");
	arr = getSetValues(set2);
	printf("Printing set2 values:\n");
	for(i=0;i<getSize(set2);i++)
		printf("%s ",arr[i]);

	Set(charp) t2 = intersection(set,set2);
	printf("\n");
	arr = getSetValues(t2);
	printf("Printing intersection of set and set2: (blank line if no common element is present)\n");
	for(i=0;i<getSize(t2);i++)
		printf("%s ",arr[i]);


	Set(charp) t3 = union(set,set2);
	printf("\n");
	arr = getSetValues(t3);
	printf("Printing union of set and set2:\n");
	for(i=0;i<getSize(t3);i++)
		printf("%s ",arr[i]);


	free(arr);
	free_ds(set);
	free_ds(set2);
	free_ds(t1);
	free_ds(t2);
	free_ds(t3);

}