#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree{
	int key;
	struct tree* parent;
	struct tree* left;
	struct tree* right;
};

struct tree* root = NULL;

struct tree* createNode(int key, struct tree* parent){
	struct tree* node = (struct tree*)malloc(sizeof(struct tree));
	node->key = key;
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;
	return node;
}

struct tree* insert(struct tree* curr, int key, struct tree* parent){
	if(curr == NULL) curr = createNode(key, parent);
	else{
		if(key < curr->key) curr->left = insert(curr->left, key, curr);
		else if(key > curr->key) curr->right = insert(curr->right, key, curr);
	}
	return curr;
}

void inOrderView(struct tree* curr){
	if(curr->left != NULL) inOrderView(curr->left);
	printf("%d ", curr->key);
	if(curr->right != NULL) inOrderView(curr->right);
}

struct tree* search(struct tree* curr, int key){
	if(curr == NULL) return NULL;
	else if(key == curr->key) return curr;
	else if(key < curr->key) search(curr->left, key);
	else if(key > curr->key) search(curr->right, key);
} 

struct tree* deleteData(struct tree* curr, int key){
	if(curr == NULL) return NULL;
	else if(key < curr->key) curr->left = deleteData(curr->left, key);
	else if(key > curr->key) curr->right = deleteData(curr->right, key);
	else{
// 		one child or no child
		if(curr->left == NULL || curr->right == NULL){
			struct tree* temp = NULL;
			if(curr->left != NULL) temp = curr->left;
			else temp = curr->right;
//			leafy green
			if(temp == NULL){
				temp = curr;
				curr = NULL;
			}
//			one child
			else{
				temp->parent = curr->parent;
				*curr = *temp;
			}
			free(temp);
		}
//		two child
		else{
//			find predecessor
			struct tree* temp = curr->left;
			while(temp->right != NULL) temp = temp->right;
			curr->key = temp->key;
			curr->left = deleteData(curr->left, temp->key);
		}
	}	
	return curr;
}

struct tree* popAll(struct tree* curr){
	if(curr == NULL) return NULL;
	curr->left = popAll(curr->left);
	curr->right = popAll(curr->right);
	free(curr);
	return NULL;
}

int main(){
	int choice;
	int key;
	do{
		printf("\n\n1. Add Data\n2. View Data\n3. Search Data\n4. Delete Data\n5. Exit\n>> ");
		scanf("%d", &choice);
		getchar();
		switch(choice){
			case 1:
				printf("Input key: ");
				scanf("%d", &key);
				getchar();
				if(search(root, key) == NULL) root = insert(root, key, NULL);
				else printf("FAIL: DUPLICATE\n");
				break;
			case 2:
				if(root == NULL) printf("FAIL: EMPTY TREE\n");
				else inOrderView(root);
				break;
			case 3:
				printf("Input key: ");
				scanf("%d", &key);
				getchar();
				if(search(root, key) == NULL) printf("FAIL: NOT FOUND\n");
				else printf("%d is found!\n", search(root, key)->key);
				break;
			case 4:
				printf("Input key: ");
				scanf("%d", &key);
				getchar();
				if(deleteData(root, key) == NULL) printf("FAIL: NOT FOUND\n");
				else printf("%d is deleted and overwrited by %d!\n", key, deleteData(root, key)->key);
				break;
			case 5:
				exit(0);
				break;
		}
	}while(choice != 5);
	root = popAll(root);
	return 0;
}