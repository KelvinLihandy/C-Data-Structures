//AVL Tree -> balanced binary search tree
#include <stdio.h>
#include <stdlib.h>
//binary tree
struct node{
	int key;
	int height; 
	
	struct node *left, *right;
};

//untuk mendapatkan height dari sebuah node
int getHeight(struct node *curr){
	//AVL Tree tidak memiliki node sama sekali
	if(curr == NULL) return 0;
	return curr->height;	
}

int getBF(struct node *curr){
	//AVL Tree tidak memiliki node sama sekali
	if(curr == NULL) return 0;
	//BF = height left child - height right child
	return getHeight(curr->left) - getHeight(curr->right);
}

int getMax(int a, int b){
	if(a > b) return a;
	else return b;
}

//right rotation
/*
		 C*		          B
	   /  \			    /   \
	  B*   y	=> 	   A	 C
	 / \  				    / \
	A   x*			       x   y
	
	*yang terdampak/posisi yang berubah
*/
struct node *rightRotation(struct node *C){
	//tentukan posisi dari B dan x
	struct node *B = C->left;
	struct node *x = B->right;
	
	//update posisinya / rotation
	B->right = C;
	C->left = x;
	
	//update height dari C dan B
	C->height = getMax( getHeight(C->left), getHeight(C->right) ) + 1;
	B->height = getMax( getHeight(B->left), getHeight(B->right) ) + 1;
	
	return B;
}

//left Rotation
/*
		   A*			      B
		 /   \ 			    /   \
		x	  B*	=>	   A	 C
			/  \		  / \	
			y*  C		 x   y
			
	* => posisi yang berubah
*/
struct node *leftRotation(struct node *A){
	//tentukan posisi yang berubah
	struct node *B = A->right;
	struct node *y = B->left;
	
	//rotation
	B->left = A;
	A->right = y;
	
	//update height
	A->height = getMax( getHeight(A->left), getHeight(A->right) ) + 1;
	B->height = getMax( getHeight(B->left), getHeight(B->right) ) + 1;
	
	return B;
}

struct node *push(struct node *curr, int insertedKey){
	//cek posisi node, apakah sedang posisi kosong atau tidak
	if(curr == NULL){
		struct node *temp = (struct node *)malloc(sizeof(struct node));
		temp->key = insertedKey;
		temp->height = 1; //karena insert selalu leaf kasi height 1
		temp->left = temp->right = NULL;
		
		return temp;
	}
	else if(insertedKey < curr->key){
		//anak kiri dari curr
		curr->left = push(curr->left, insertedKey);
	}
	else if(insertedKey > curr->key){
		//anak kanan dari curr
		curr->right = push(curr->right, insertedKey);
	}
	
	//update Height dari parent sampai root
	curr->height = getMax(getHeight(curr->left), getHeight(curr->right)) + 1;
	
	//cek terjadi violation
	int BF = getBF(curr);
	
	//cek lebih berat kanan atau kiri
	//jika nilai BF positif dan > 1 dan nilai yang diinsert lebih kecil dari left child, LL Rotation
	if(BF > 1 && insertedKey < curr->left->key){
		//laksanakan right rotation
		return rightRotation(curr);
	}
	//jika nilai BF negatif dan < -1 dan nilai yang diinsert lebih besar dari right child, RR Rotation
	else if(BF < -1 && insertedKey > curr->right->key){
		//laksanakan left rotation	
		return leftRotation(curr);
	}
	//jika nilai BF positif dan > 1 dan nilai yang diinsert lebih besar dari left child, LR Rotation
	else if(BF > 1 && insertedKey > curr->left->key){
		//laksanakan double rotation 
			//laksanakan left Rotation supaya jadi LL Rotation
			curr->left = leftRotation(curr->left);
			return rightRotation(curr);
	}
	//jika nilai BF negatif dan < -1 dan nilai yang diinsert lebih besar dari right child, RL Rotation
	else if(BF < -1 && insertedKey < curr->right->key){
		//laksanakan double rotation
			//laksanakan right rotation supaya jadi RR Rotation
			curr->right = rightRotation(curr->right);
			return leftRotation(curr);
	}
	
	//jika tidak terjadi violation apapun
	return curr;
}

struct node *predecessor(struct node *curr){
	struct node *temp = curr->left;
	while(temp->right != NULL){
		temp = temp->right;
	}
	return temp;
}

struct node *pop(struct node *curr, int deletedKey){
	//cek datanya ditemukan atau tidak
	if(curr == NULL) return NULL;
	
	//mencari pengganti dari node yang dihapus
	if(deletedKey < curr->key ){
		//pencariannya laksanakan ke kiri	
		curr->left = pop(curr->left, deletedKey);
	}
	else if( deletedKey > curr->key ){
		//pencariannya laksanakan ke kanan
		curr->right = pop(curr->right, deletedKey);
	}
	else{
		//punya 1 anak atau tidak punya anak sama sekali
		if(curr->left == NULL || curr->right == NULL){
			struct node * temp = NULL;
			//punya anak kiri
			if(curr->left != NULL) temp = curr->left;
			else temp = curr->right;
			
			if(temp == NULL){
				//curr -> leaves
				temp = curr;
				curr = NULL;	
			}
			else{
				//kalau nodenya sudah ditemukan anak kiri atau anak kanan
				//copy data dari temp ke curr
				*curr = *temp;				
			}
			free(temp);
		}
		//punya 2 anak
		else{
			struct node *temp = predecessor(curr);
			//copy data dari temp ke curr, kecuali left dan right
			curr->key = temp->key;
			curr->left = pop(curr->left, temp->key);			
		}
	}
	
	//setelah dihapus cek violation
	if(curr == NULL) return curr;
	
	curr->height = getMax( getHeight(curr->left), getHeight(curr->right) ) + 1;
	
	int BF = getBF(curr);
	
	//jika BF > 1 violation dan cek kalau node left nya berat ke kiri (nilai BF positif) -> LL Rotattion
	if(BF > 1 && getBF(curr->left) >= 0){
		return rightRotation(curr);
	}
	//jika BF < -1 violation dan cek node rightnya berat ke kanan (nilai BF negatif) -> RR Rotation
	if(BF < -1 && getBF(curr->right) < 0){
		return leftRotation(curr);
	}
	//jika BF > 1 violation dan cek node leftnya berat ke kanan (nilai BF negatif) -> LR Rotation
	if(BF > 1 && getBF(curr->left) < 0){
		curr->left = leftRotation(curr->left);
		return rightRotation(curr);
	}
	//jika BF < -1 violation dan cek node rightnya berat ke kiri (nilai BF positif) -> RL Rotation
	if(BF < -1 && getBF(curr->right) >= 0){
		curr->right = rightRotation(curr->right);
		return leftRotation(curr);
	} 
	
	//jika tidak terjadi violation apapun
	return curr;
}

void inOrder(struct node *curr){
	if(curr == NULL) return;
	inOrder(curr->left);
	
	//cara print
	printf("%2d ", curr->key);
		
	inOrder(curr->right);
}

int main(){
	struct node *root = NULL;
	root = push(root, 10);
	root = push(root, 6);
	root = push(root, 17);
	root = push(root, 2);
	root = push(root, 7);
	root = push(root, 14);
	root = push(root, 16);
	// for(int i = 0; i < 1000; i++){
	// 	root = push(root, i);
	// }
	inOrder(root);
	
	root = pop(root, 10);
	inOrder(root);
	return 0;
}


