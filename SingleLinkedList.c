#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data{
	char id[6];
	char name[50];
	int age;
	struct data *next;
}	*head = NULL, 
	*tail = NULL;

struct data *createNode(char *idNode, char *nameNode, int ageNode){
	struct data *node = (struct data *)malloc(sizeof(struct data));
	strcpy(node->id, idNode);
	strcpy(node->name, nameNode);
	node->age = ageNode;		//(*node).age = ageNode
	node->next = NULL;
	return node;
}

void pushHead(char *idNode, char *nameNode, int ageNode){
	struct data *node = createNode(idNode, nameNode, ageNode);
	if(head == NULL){
		head = node;
		tail = node;
	}
	else{
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
		tail = node;
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
		else head = curr->next;
		free(curr);
	}
}

void popTail(){
	if(tail == NULL) printf("data not found.");
	else{
		struct data *curr = head;
		if(head == tail){
			head == NULL;
			tail == NULL;
		}
		else{
			while(curr->next != tail){
				curr = curr->next;
			}
			tail = curr;
			curr = curr->next;
			tail->next = NULL;
		}
		free(curr);
	}
}
void printData(){
	struct data *curr = head;
	while(curr != NULL){
		printf("%s %s %d\n",curr->id, curr->name, curr->age);
		curr = curr->next;
	};
}

int main(){
	pushHead("A001", "Si Paling Budi", 43);
	pushHead("A002", "Si Paling Ceri", 7627);
	pushHead("A003", "Si Paling Erlangga", 78);
	pushTail("A004", "Gensin Impek", 3);
	pushTail("A005", "Kikir Impek", 4);
	pushTail("A006", "UpinIpinOpah", 632836816);
	printData();
	puts("");
	popHead();
	printData();
	puts("");
	popHead();
	printData();
	puts("");
	popTail();
	printData();
	puts("");
	pushTail("001", "WDB", 1);
	printData();
	return 0;
}
