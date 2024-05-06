#include <stdio.h>
#include <string.h>

struct data{
	int id;
	char name[50];
}	staff[10];

int max = 10;
int count = 0;
void pushQueue(int id, char name[], int* rear){
	if(count == max){
		printf("Fail: No space left.\n");
		return;
	}
	count += 1;
	staff[*rear].id = id;
	strcpy(staff[*rear].name, name);
	(*rear) += 1;
	if(*rear == max){
		*rear = 0;
	}
}

void popQueue(int* front, int *rear){
	if(count == 0){
		printf("Fail : No data in queue.\n");
		return;
	}
	*front += 1;
	if(*front == max){
		*front = 0;
	}
	count -= 1;
}

void viewQueue(int front, int rear){
	if(count == 0){
		printf("Fail : No data in queue.\n");
		return;
	}
	int i;
	if(front < rear){
		for(i = front; i < rear; i++){
			printf("%d - %s\n", staff[i].id, staff[i].name);
		}
	}
	else{
		for(i = front; i < max; i++){
			printf("%d - %s\n", staff[i].id, staff[i].name);
		}
		for(i = 0; i < rear; i++){
			printf("%d - %s\n", staff[i].id, staff[i].name);
		}
	}
}

void peekQueue(int front){
	if(count == 0){
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
	pushQueue(9, "Apin", &rear);
	pushQueue(10, "Apin", &rear);
	popQueue(&front, &rear);
	popQueue(&front, &rear);
	popQueue(&front, &rear);
	pushQueue(11, "Apin", &rear);
	pushQueue(12, "Apin", &rear);
	pushQueue(13, "Apin", &rear);
	pushQueue(7, "Apin", &rear);
	viewQueue(front, rear);
	return 0;
}
