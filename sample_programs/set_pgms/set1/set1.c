#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "dslib.h"

/* Sample program - insert 15000 integers into a set */

Set_declare(int);

int main()
{

	Set(int) set = new_Set(int,500);
	int n = 15000;
	int x;

	while(n--)
	{
		scanf("%d",&x);
		add(set,x);
	}
	
	int* values = getSetValues(set);
	int num = getSize(set);

	while(num--)
	{
		printf("%d\n",values[num]);
	}

	free(values);
	free_ds(set);

}