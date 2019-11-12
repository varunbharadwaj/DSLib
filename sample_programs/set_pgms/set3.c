#include <stdio.h>
#include <string.h>
#include "dslib.h"

Set_declare(double);

int main()
{

	Set(double) set = new_Set(double,10);

	printf("At start: size = %ld\n",getSize(set));

	add(set,1.1);
	add(set,2.2);
	add(set,3.3);
	
	if(find(set,1.1))
		printf("1.1 found in the set\n");
	
	printf("Before deleting: size = %ld\n",getSize(set));
	
	remove(set,2.2);

	printf("After deleting: size = %ld\n",getSize(set));

	if(find(set,3.3))
		printf("3.3 found in set\n");

	if(find(set,2.2))
		printf("2.2 found in set\n");

	double* arr = getSetValues(set);
	int i;
	printf("Printing set values:\n");
	for(i=0;i<getSize(set);i++)
		printf("%lf ",arr[i]);

	printf("\n");

	Set(double) set2 = new_Set(double,10);
	add(set2,11.1);
	add(set2,12.12);
	add(set2,23.1);
	add(set2,5.322);
	add(set2,111.111);

	Set(double) t1 = duplicate(set);
	arr = getSetValues(t1);
	printf("Printing duplicate set values:\n");
	for(i=0;i<getSize(t1);i++)
		printf("%lf ",arr[i]);

	printf("\n");
	arr = getSetValues(set2);
	printf("Printing set2 values:\n");
	for(i=0;i<getSize(set2);i++)
		printf("%lf ",arr[i]);

	Set(double) t2 = intersection(set,set2);
	printf("\n");
	arr = getSetValues(t2);
	printf("Printing intersection of set and set2: (blank line if no common element is present)\n");
	for(i=0;i<getSize(t2);i++)
		printf("%lf ",arr[i]);


	Set(double) t3 = union(set,set2);
	printf("\n");
	arr = getSetValues(t3);
	printf("Printing union of set and set2:\n");
	for(i=0;i<getSize(t3);i++)
		printf("%lf ",arr[i]);


	free(arr);
	free_ds(set);
	free_ds(set2);
	free_ds(t1);
	free_ds(t2);
	free_ds(t3);

}