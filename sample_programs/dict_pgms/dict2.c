#include <stdio.h>
#include <string.h>
#include "dslib.h"

// long long ,char
Dict_declare(long_long,char);

int main()
{
	Dict(long_long,char) d = new_Dict(long_long,char,10);

	printf("At start: size = %ld\n",getSize(d));

	add(d,10,'a');
	add(d,30,'b');
	add(d,12,'c');
	add(d,13,'d');
	add(d,14,'e');
	add(d,100,'A');
	
	if(find(d,10))
		printf("1-> key=10 value=%c\n",get(d,10));
	
	printf("Before deleting: size = %ld\n",getSize(d));
	
	remove(d,14);

	printf("After deleting: size = %ld\n",getSize(d));

	if(find(d,100))
		printf("2-> key=100 value=%c\n",get(d,100));

	free_ds(d);

}