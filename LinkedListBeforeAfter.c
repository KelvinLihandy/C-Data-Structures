#include <stdio.h>
#include <stdlib.h>

struct node{
    int value;
    struct node* next;
    struct node* prev;
}   *head = NULL,
    *tail = NULL;

struct node* create(int value){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->value = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void pushHead(struct node* newNode){
    if(head == NULL){
        head = newNode;
        tail = newNode;
    }
    else{
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void pushTail(struct node* newNode){
    if(tail == NULL){
        head = newNode;
        tail = newNode;
    }
    else{
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

void print(){
	struct node* curr = head;
	while(curr != NULL){
		printf("%d ", curr->value);
		curr = curr->next;
	}
	printf("\n");
}

void pushBefore(int value, int before){
    struct node* newNode = create(value);
    if(head == NULL || head->value == before){
        pushHead(newNode);
    }
    else if(tail->value == before){
        newNode->next = tail;
        newNode->prev = tail->prev;
        tail->prev->next = newNode;
        tail->prev = newNode;
    }
    else{
        struct node* curr = head;
        while(curr != NULL && curr->value != before) curr = curr->next;
        if(curr == NULL){
            pushTail(newNode);
        }
        else{
            newNode->next = curr;
		    newNode->prev = curr->prev;
		    curr->prev->next = newNode;
		    curr->prev = newNode;
        } 
    }
}

void pushAfter(int value, int after){
	struct node* newNode = create(value);
    if(head->value == after){
    	newNode->next = head->next;
    	newNode->prev = head;
    	head->next->prev = newNode;
    	head->next = newNode;
    }
    else if(tail == NULL || tail->value == after){
        pushTail(newNode);
    }
    else{
        struct node* curr = head;
        while(curr != NULL && curr->value != after) curr = curr->next;
        if(curr == NULL){
            pushTail(newNode);
        }
        else{
        	newNode->next = curr->next;
        	newNode->prev = curr;
        	curr->next->prev = newNode;
        	curr->next = newNode;
        } 
    }
}
int main(){
    pushBefore(1, 10);
    pushHead(create(10));
    pushBefore(23, 1);
    pushBefore(100, 3);
    pushAfter(33, 10);
	print();
    return 0;
}
