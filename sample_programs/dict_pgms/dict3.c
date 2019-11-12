#include <stdio.h>
#include <string.h>
#include "dslib.h"

Dict_declare(double,char);

int main()
{
	Dict(double,char) d = new_Dict(double,char,10);
	add(d,1.0,'a');
	add(d,1.1,'b');
	add(d,1.2,'c');
	add(d,1.3,'d');
	add(d,1.4,'e');
	add(d,10.0,'A');

	if(find(d,1.1))
		printf("1- key=10  value=%c\n",get(d,10));
	
	printf("size = %ld\n",getSize(d));
	
	remove(d,1.1);

	printf("size = %ld\n",getSize(d));

	if(find(d,10))
		printf("2- key=10 value=%c\n",get(d,10));

	free_ds(d);

}