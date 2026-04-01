#include <stdio.h>
#include <stdlib.h>

/*Aturan BST: Cabang node di kiri harus lebih kecil 
daripada root, dan cabang node di kanan harus lebih besar daripada root. */

//Siapkan structnya.
struct Node{
	int value;
	struct Node *left;
	struct Node *right;
};

//Untuk membuat node baru.
struct Node *newNode(int value){
	struct Node *node = (struct Node*) malloc(sizeof(struct Node));
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	
	return node;
}

//Untuk menambahkan value ke BST.
struct Node *insert(struct Node *root, int value){
	
	//Cek dahulu apakah root = NULL seperti di linkedlist biasa.
	if (root == NULL){
		return newNode(value); /*Kalau masih null, kirim 
								ke function newNode agar dibuatkan 
								node dan dimasukkan valuenya. */
	} else if (value < root->value){
		root->left = insert(root->left, value); /*Kalau value yang mau dimasukkan ke 
												  BST lebih kecil daripada root, 
												  masukkan ke kiri. */
	} else if (value > root->value){
		root->right = insert(root->right, value); /*Kalau value yang mau dimasukkan ke BST 
													lebih besar daripada root, 
													masukkan ke kanan. */
	} else {
		// value sama (duplikat)
    	printf("Value %d sudah ada, tidak boleh duplikat!\n", value);
	}
	return root;
}

void search(struct Node *root, int value){
	if (root == NULL){ /*Kalau root masih kosong / NULL, berarti ga ada value apa-apa 
						 yaitu masih kosong dan langsung print aja. */
		printf("Data tidak ditemukan di dalam Binary Tree menggunakan metode BST.\n");
		return;
	}
	
	if(root->value == value){ /*Cek apakah root saat ini merupakan value yang 
								dicari, apabila ya maka langsung print aja dan 
								return untuk menghentikan function search. */
		printf("Value ditemukan!\n");
		return;
	} else if (root->value > value){
		search(root->left, value);
	} else {
		search(root->right, value);
	}
}

void update(struct Node *root, int value, int newValue){
	if (root == NULL){ /*Kalau root masih kosong / NULL, 
						 berarti ga ada value apa-apa yaitu 
						 masih kosong dan langsung print aja.*/
		printf("Data tidak ditemukan di dalam Binary Tree menggunakan metode BST.\n");
		return;
	}
	
	if(root->value == value){ /*Cek apakah root saat ini merupakan value yang dicari, 
								apabila ya maka langsung print aja dan return untuk 
								menghentikan function search. */
		root->value = newValue;
		return;
	} else if (root->value > value){
		update(root->left, value, newValue);
	} else {
		update(root->right, value, newValue);
	}
}

struct Node *findMin(struct Node *root){
    while(root->left != NULL){
        root = root->left;
    }
    return root;
}

struct Node *deleteNode(struct Node *root, int value){
    if(root == NULL){
        printf("Data tidak ditemukan!\n");
        return NULL;
    }

    if(value < root->value){
        root->left = deleteNode(root->left, value);
    } else if(value > root->value){
        root->right = deleteNode(root->right, value);
    } else {
        // Node ditemukan

        // CASE 1: Tidak punya anak
        if(root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        }

        // CASE 2: Punya 1 anak
        else if(root->left == NULL){
            struct Node *temp = root->right;
            free(root);
            return temp;
        } else if(root->right == NULL){
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        /* CASE 3: Punya 2 anak, menggunakan inorder
        successor yang dibuat pada function terpisah */
        struct Node *temp = findMin(root->right);
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->value);
    }

    return root;
}

void inOrder(struct Node *root){
	if (root != NULL){
		inOrder(root->left);
		printf("%d\n", root->value);
		inOrder(root->right);
	}
}

void postOrder(struct Node *root){
	if (root != NULL){
		postOrder(root->left);
		postOrder(root->right);
		printf("%d\n", root->value);
	}
}

void preOrder(struct Node *root){
	if (root != NULL){
		printf("%d\n", root->value);
		preOrder(root->left);
		preOrder(root->right);
	}
}

//Root disimpan di local, bukan di global.
int main(){
	struct Node *root = NULL;
	
	root = insert(root, 14);
	root = insert(root, 14);
	root = insert(root, 99);
	root = insert(root, 98);
	root = insert(root, 50);
	root = insert(root, 18);
	root = insert(root, 76);
	update(root, 76, 67);
	printf("Inorder:\n");
	inOrder(root);
	printf("Postorder:\n");
	postOrder(root);
	printf("Preorder:\n");
	preOrder(root);
	
	printf("Setelah melakukan penghapusan node tertentu\n");
	root = deleteNode(root, 14); // hapus root
	root = deleteNode(root, 50); // node dengan 2 child
	root = deleteNode(root, 99); // leaf
	printf("Inorder:\n");
	inOrder(root);
	printf("Postorder:\n");
	postOrder(root);
	printf("Preorder:\n");
	preOrder(root);
	
	return 0;
}
