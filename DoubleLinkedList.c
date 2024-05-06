#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data{
	char id[6];
	char name[50];
	int age;
	struct data *next;
	struct data *prev;
}	*head = NULL, 
	*tail = NULL;

struct data *createNode(char *idNode, char *nameNode, int ageNode){
	struct data *node = (struct data*)malloc(sizeof(struct data));
	strcpy(node->id, idNode);
	strcpy(node->name, nameNode);
	node->age = ageNode;		//(*node).age = ageNode
	node->next = NULL;
	node->prev = NULL;
	return node;
}

void pushHead(char *idNode, char *nameNode, int ageNode){
	struct data *node = createNode(idNode, nameNode, ageNode);
	if(head == NULL){
		head = node;
		tail = node;
	}
	else{
		head->prev = node;
		node->next = head;
		head = node;
	}
}

void pushTail(char *idNode, char *nameNode, int ageNode){
	struct data *node = createNode(idNode, nameNode, ageNode);
	if(tail == NULL){
		head = node;
		tail = node;
	}
	else{
		tail->next = node;
		node->prev = tail;
		tail = node;
	}
}

void pushMid(char *idNode, char *nameNode, int ageNode){
	//this is just push data actually
	struct data *node = createNode(idNode, nameNode, ageNode);
	if (head == NULL){
		head = node;
		tail = node;
	}
	else if(head->age > node->age){
		pushHead(idNode, nameNode, ageNode);
	}else if(tail->age < node->age){
		pushTail(idNode, nameNode, ageNode);
	}
	else{
		struct data *curr = head;
		while((curr != NULL) && curr->age < node->age){
			curr = curr->next;
		}
		//curr is behind the node that is about to be inserted
		curr->prev->next = node;
		node->prev = curr->prev;
		curr->prev = node;
		node->next = curr;
	}
}
void popHead(){
	if(head == NULL) printf("data not found.\n");
	else{
		struct data *curr = head;
		if(head == tail){
			head == NULL;
			tail == NULL;
		}
		else{
			head = curr->next;
			head->prev = NULL;
		}
		free(curr);
	}
}

void popTail(){
	if(tail == NULL) printf("data not found.");
	else{
		struct data *curr = tail;
		if(head == tail){
			head == NULL;
			tail == NULL;
		}
		else{
			tail = tail->prev;
			tail->next = NULL;
		}
		free(curr);
	}
}
void printData(){
	struct data *curr = head;
	if(curr == NULL){
		printf("Empty data\n");
		return;
	}
	while(curr != NULL){
		printf("%s %s %d\n",curr->id, curr->name, curr->age);
		curr = curr->next;
	};
}

void popAll(){
	while(head != NULL){
		struct data* temp = head;
		head = head->next;
		free(temp);
	}
}

int main(){
	pushHead("A001", "Si Paling Budi", 43);
	pushHead("A002", "Si Paling Ceri", 7627);
	pushHead("A003", "Si Paling Erlangga", 78);
	pushTail("A004", "Gensin Impek", 3);
	pushTail("A005", "Kikir Impek", 4);
	pushTail("A006", "UpinIpinOpah", 632836816);
	printData();
	puts("2");
	popHead();
	printData();
	puts("3");
	popHead();
	printData();
	puts("4");
	popTail();
	printData();
	puts("5");
	pushTail("001", "WDB", 1);
	printData();
	popAll();
	puts("6");
	printData();
	return 0;
}
