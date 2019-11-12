#include <stdio.h>
#include <string.h>
#include "dslib.h"

typedef struct apple
{
	int cost;
} apple;

Dict_declare(charp,apple); // user defined type apple

int main()
{
	Dict(charp,apple) d = new_Dict(charp,apple,15);
	apple a1,a2,a3,a4,a5;
	a1.cost = 10;
	a2.cost = 20;
	a3.cost = 30;
	a4.cost = 40;
	a5.cost = 50;

	printf("At start: size = %ld\n",getSize(d));

	add(d,"a1",a1);
	add(d,"a2",a2);
	add(d,"a3",a3);
	add(d,"a4",a4);
	add(d,"a5",a5);

	int c;
	
	if(find(d,"a1"))
	{
		c = (get(d,"a1")).cost;
		printf("1-> key=a1 value=%d\n",c);
	}
	
	printf("Before deleting: size = %ld\n",getSize(d));
	
	remove(d,"a2");

	printf("After deleting: size = %ld\n",getSize(d));

	if(find(d,"a3"))
	{
		c = (get(d,"a3")).cost;
		printf("2-> key=a3 value=%d\n",c);
	}

	free_ds(d);

}