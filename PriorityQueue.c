#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data{
	int queue;
	char name[50];
	int health; //for priority
	struct data *next;
	struct data *prev;
}	*head = NULL,
	*tail = NULL;
	
struct data* newNode(int queue, char name[], int health){
	struct data *node = (struct data*) malloc(sizeof(struct data));
	node->queue = queue;
	strcpy(node->name, name);
	node->health = health;
	node->prev = NULL;
	node->next = NULL;
	return node;
}

void pushHead(int queue,char name[], int health){
	struct data *current = newNode(queue, name, health);
	if(head == NULL && tail == NULL){
		head = current;
		tail = current;
	}
	else{
		head->prev = current;
		current->next = head;
		head = current;
	}
}

void pushTail(int queue, char name[], int health){
	struct data *current = newNode(queue, name, health);
	if(head == NULL){
		head = current;
		tail = current;
	}
	else{
		tail->next = current;
		current->prev = tail;
		tail = current;
	}
}

void pushMiddle(int queue, char name[], int health){
	if(head == NULL || health < head->health ){
		pushHead(queue, name, health);
	}
	else if(health >= tail->health){
		pushTail(queue, name, health);
	}	
	else{
		struct data *current = head;
		while(health >= current->health){
			current = current->next;
		}
		struct data *node = newNode(queue, name, health);
		node->next = current;
		node->prev = current->prev;
		node->prev->next = node;
		current->prev = node;
	}
}

void popAll(){
	struct data *current = head;
	while(current != NULL){
		head = head->next;
		free(current);
		current = head;
	}
	head = NULL;
	tail = NULL;
}

void print(){
	struct data *current = head;
	while(current != NULL){
		printf("%d. %s (%d)\n", current->queue, current->name, current->health);
		current = current->next;
	}
}

int main(){
	pushMiddle(1, "apel", 132);
	pushMiddle(2, "apel", 32423);
	pushMiddle(3, "apel", 34);
	pushMiddle(4, "apel", 3244);
	pushMiddle(5, "apel", 5243);
	pushMiddle(6, "apel", 32);
	pushMiddle(7, "apel", 234);
	pushMiddle(8, "apel", 96);
	pushMiddle(9, "apel", 96);
	pushMiddle(10, "apel", 234);
	pushMiddle(11, "apel", 132);
	pushMiddle(12, "apel", 132);
	// popAll();
	pushMiddle(212, "apels", 723);
	print();
	return 0;
}
