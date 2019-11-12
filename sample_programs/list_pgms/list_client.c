#include <stdio.h>
#include <string.h>
#include "list.h"

#include "dslib.h"
List_declare(int);

typedef struct Pokemon
{		
	char* name;
	double age;
	int level;
}Pokemon;

List_declare(Pokemon);

long client_hasher(int* key)
{
	return *key-1234;		//unique hascode for an integer
}

long pkmn_hasher(Pokemon* p1)
{
	return (strlen(p1->name)+p1->age*p1->level)*13;
}

void pkmn_printer(Pokemon* p)
{
	printf("{ Name:%s Age:%lf Level:%d } ",p->name,p->age,p->level);
}

int main()
{
	printf("\nInteger link list example:\n");
	List(int) l1=new_List(int);

	insert_head(l1,3);
	insert_head(l1,23);
	insert_head(l1,1);
	list_disp(l1,NULL);
	
	drop_head(l1);
	list_disp(l1,NULL);
	
	insert_tail(l1,5);
	insert_tail(l1,1);
	list_disp(l1,NULL);

	drop_tail(l1);
	list_disp(l1,NULL);

	printf("\nLinkList to Array: ");
	int* a=list_to_array(l1);
	int i=0;
	while(i<list_length(l1))
	{	
		printf("%d ",a[i]);
		i++;
	}
	printf("\n");

	int subject=3;
	printf("\n%d found at position %d",subject,list_search(l1,3,client_hasher));

	drop(l1,list_search(l1,3,NULL));
	printf("\n");	
	list_disp(l1,NULL);
	list_reverse(l1);
	list_disp(l1,NULL);
	list_reverse(l1);
	list_disp(l1,NULL);
	free_ds(l1);
	list_disp(l1,NULL);


	printf("\n\nPokemon struct link list example:\n");
	

	List(Pokemon) my_favorite=new_List(Pokemon);
	Pokemon p1={"Pikachu",20.2,94};
	Pokemon p2={"Zorua",3.4,36};
	Pokemon p3={"Giratina",50000.0,100};
	Pokemon p4={"Pacharisu",5.6,45};
	Pokemon p5={"Emolga",5.6,42};
	Pokemon p6={"Snivy",4.2,28};

	insert_head(my_favorite,p1);
	insert_tail(my_favorite,p2);
	insert_tail(my_favorite,p3);

	list_disp(my_favorite,pkmn_printer);
	Pokemon pq=p1;
	printf("\n%s found at position %d",pq.name,list_search(my_favorite,pq,pkmn_hasher));

	//drop_head(my_favorite);
	//list_disp(my_favorite,pkmn_printer);
	
	insert_tail(my_favorite,p4);	
	//list_disp(my_favorite,pkmn_printer);

	//drop_tail(my_favorite);
	//list_disp(my_favorite,pkmn_printer);

	printf("\nLinkList to Array: ");
	Pokemon* b=list_to_array(my_favorite);
	int j=0;
	while(j<list_length(my_favorite))
	{	
		pkmn_printer(&b[j]);
		j++;
	}
	printf("\n");

	insert(my_favorite,p5,2);
	list_disp(my_favorite,pkmn_printer);

	replace(my_favorite,p6,3);

	list_reverse(my_favorite);
	list_disp(my_favorite,pkmn_printer);
	list_reverse(my_favorite);
	list_disp(my_favorite,pkmn_printer);
	free_ds(my_favorite);

	printf("\n");
	return 0;
}