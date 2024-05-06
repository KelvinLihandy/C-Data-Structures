#include <stdio.h>
#include <string.h>

struct data{
	int id;
	char name[50];
}	staff[10];

int max = 10;

void pushStack(int id, char name[], int* current){
	if(*current == max){
		printf("Fail to push : Max data reached.\n");
		return;
	}
	staff[*current].id = id;
	strcpy(staff[*current].name, name);
	(*current) += 1;
}

void popStack(int* current){
	if(*current == 0){
		printf("Pop failed : no data in stack.\n");
		return;
	}
	*current -= 1;
}

void viewStack(int current){
	while(current-1 >= 0){
		printf("%d - %s\n", staff[current - 1].id, staff[current - 1].name);
		current -= 1;
	}
}

void peekStack(int current){
	if(current == 0){
		printf("Peek failed : No data in stack.\n");
		return;
	}
	printf("%d - %s\n", staff[current - 1].id, staff[current - 1].name);
}

int main(){
	int top = 0;
	pushStack(1, "Udin", &top);
	pushStack(2, "Jopan", &top);
	pushStack(3, "Ipin", &top);
	pushStack(4, "Apin", &top);
	viewStack(top);
	popStack(&top);
	viewStack(top);
	popStack(&top);
	viewStack(top);
	popStack(&top);
	viewStack(top);
	return 0;
}
