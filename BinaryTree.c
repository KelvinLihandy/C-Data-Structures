#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree{
	struct tree* parent;
	struct tree* left;
	struct tree* right;
	int value;
};
struct tree* root = NULL;

int menu(){
	int choice;
	printf("1. Add data\n");
	printf("2. View data\n");
	printf("3. Exit\n");
	printf("Choose>>");
	scanf("%d", &choice);
	getchar();
	return choice;
}

struct data* insert(struct tree* curr, int value, struct tree* parent){
	char direction;
	if(curr == NULL){
		curr = (struct tree*) malloc(sizeof(struct tree));
		curr->value = value;
		curr->left = NULL;
		curr->right = NULL;
		curr->parent = parent;
	}
	else{
		printf("Direction (L / R)>>");
		scanf("%c", &direction);
		getchar();
		if(direction == 'L' || direction == 'l'){
			curr->left = insert(curr->left, value, curr);
		}
		else if(direction == 'R' || direction == 'r'){
			curr->right = insert(curr->right, value, curr);
		}
	}
	return curr;
}

void preOrder(struct tree* curr){
	printf("%d ", curr->value);
	if(curr->left != NULL) preOrder(curr->left);
	if(curr->right != NULL) preOrder(curr->right);
}

void inOrder(struct tree* curr){
	if(curr->left != NULL) inOrder(curr->left);
	printf("%d ", curr->value);
	if(curr->right != NULL) inOrder(curr->right);
}

void postOrder(struct tree* curr){
	if(curr->left != NULL) postOrder(curr->left);
	if(curr->right != NULL) postOrder(curr->right);
	printf("%d ", curr->value);
}
struct tree* pop(struct tree* curr){
	if(curr == NULL) return NULL;
	curr->left= pop(curr->left);
	curr->right = pop(curr-left>right);
	free(curr);
	return NULL;
}

int main(){
	int choice;
	int value;
	do{
		choice = menu();
		switch(choice){
			case 1:
				printf("Input value>>");
				scanf("%d", &value);
				getchar();
				root = insert(root, value, NULL);
				break;
			case 2:
				printf("Preorder>>");
				preOrder(root);
				puts("");
				printf("inorder>>");
				inOrder(root);
				puts("");
				printf("Postorder>>");
				postOrder(root);
				puts("");
				break;
			case 3:
				printf("Program exited\n")
				pop(root);
				break;
		}
	}while(choice != 3);
	return 0;
}
