#include <stdio.h>
#include <string.h>

struct data{
	int id;
	char name[50];
}	staff[10];

int max = 10;

void pushQueue(int id, char name[], int* rear){
	if(*rear == max){
		printf("Fail: No space left.\n");
		return;
	}
	staff[*rear].id = id;
	strcpy(staff[*rear].name, name);
	(*rear) += 1;
}

void popQueue(int* front, int *rear){
	if(*front == *rear){
		printf("Fail : No data in queue.\n");
		return;
	}
	*front += 1;
}

void viewQueue(int front, int rear){
	if((front == 0 && rear == 0) || front == rear){
		printf("Fail : No data in queue.\n");
		return;
	}
	int i;
	for(i = front; i < rear; i++){
		printf("%d - %s\n", staff[i].id, staff[i].name);
	}
}

void peekQueue(int front, int rear){
	if(front == rear){
		printf("Fail : No data in queue.\n");
		return;
	}
	printf("%d - %s\n", staff[front].id, staff[front].name);
}

int main(){
	int front = 0;
	int rear = 0;
	pushQueue(1, "Udin", &rear);
	pushQueue(2, "Jopan", &rear);
	pushQueue(3, "Ipin", &rear);
	pushQueue(4, "Apin", &rear);
	pushQueue(5, "Apin", &rear);
	pushQueue(6, "Apin", &rear);
	pushQueue(7, "Apin", &rear);
	pushQueue(8, "Apin", &rear);
	viewQueue(front, rear);
	popQueue(&front, &rear);
	viewQueue(front, rear);
	popQueue(&front, &rear);
	viewQueue(front, rear);
	popQueue(&front, &rear);
	viewQueue(front, rear);
	popQueue(&front, &rear);
	viewQueue(front, rear);
	popQueue(&front, &rear);
	viewQueue(front, rear);
	popQueue(&front, &rear);
	viewQueue(front, rear);
	popQueue(&front, &rear);
	viewQueue(front, rear);
	popQueue(&front, &rear);
	viewQueue(front, rear);
	return 0;
}
