#include <stdio.h>
#include <string.h>
#include "dslib.h"

Set_declare(charp);

int main()
{

	Set(charp) set = new_Set(charp,10);

	printf("At start: size = %ld\n",getSize(set));

	char a[10] = "abcd";
	char b[10] = "xyz";
	char c[10] = "hello";
	char d[10] = "qwe";

	add(set,a);
	add(set,b);
	add(set,c);
	add(set,d);
	
	if(find(set,a))
		printf("abcd found in the set\n");
	
	printf("Before deleting: size = %ld\n",getSize(set));
	
	remove(set,d);

	printf("After deleting: size = %ld\n",getSize(set));

	if(find(set,c))
		printf("hello found in set\n");

	if(find(set,d))
		printf("qwe found in set\n");

	char** arr = getSetValues(set);
	int i;
	printf("Printing set values:\n");
	for(i=0;i<getSize(set);i++)
		printf("%s ",arr[i]);

	printf("\n");

	printf("Inserting repeated values: ('repeated' 3 times)\n ");
	
	add(set,"repeated");
	add(set,"repeated");
	add(set,"repeated");

	arr = getSetValues(set);
	printf("Printing set values:\n");
	for(i=0;i<getSize(set);i++)
		printf("%s ",arr[i]);

	printf("\n");

	free(arr);
	free_ds(set);

}