/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	
}

void preorderTraversal(Node* ptr)
{

}

void postorderTraversal(Node* ptr)
{

}


int insert(Node* head, int key)
{
	// �Է¹��� key�� �̿��Ͽ� ���ο� ��� ����
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = newNode->right = NULL;

	// head�� NULL���� Ȯ���ϰ�, NULL�̸� �Է� ���� key�� head�� ����Ű���� ��.
	if(head->left == NULL) {
		head->left = newNode;
	} else { 
		Node* curr = head->left;
		
		// head�� NULL�� �ƴ� ���, curr�� head�� ����. curr�� key�� �Է¹��� key�� ���Ͽ� ������ ����, ũ�� ���������� curr �̵�.
		while(1) {
			if(curr->key > key) {
				if(curr->left == NULL) { // �Է¹��� key�� �� ���� ���, ���� ����� ���� �ڽ� ��尡 ������ ���ο� ��� ���� �� ���� ����.
					curr->left = newNode;
					break;
				} else {
					curr = curr->left; // ���� ��� ����
				}
			} else {
				if(curr->right == NULL) { // �Է¹��� key�� �� ū ���, ���� ����� ���� �ڽ� ��尡 ������ ���ο� ��� ���� �� ���� ����.
					curr->right = newNode;
					break;
				} else {
					curr = curr->right; // ���� ��� ����
				}
			}
		}
	}

	return 1;
}

int deleteLeafNode(Node* head, int key)
{

}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) { // Ž�� �� �ش� key�� �������� �ʴ� ���
		printf("�Է��� key�� �������� �ʽ��ϴ�.\n");
		return NULL;
	}
	if(ptr->key == key) {
		return ptr; // �Է¹��� key�� ptr�� key�� ������ ���
	} else if(ptr->key > key){
		return searchRecursive(ptr->left, key); // ptr�� key�� �Է¹��� key���� ũ�� �������� �̵� �� searchRecursive
	} else {
		return searchRecursive(ptr->right, key); // ptr�� key�� �Է¹��� key���� ������ ���������� �̵� �� searchRecursive
	}	
}

Node* searchIterative(Node* head, int key)
{
	Node* curr = head;
	while(curr != NULL) { // curr�� ����Ű�� ����� key�� �Է¹��� key�� ������ ������ �ݺ�
		if(curr->key == key) {
			return curr; // key���� �����ϸ� �ش� ��� ��ȯ
		} else if(curr->key > key) {
			curr = curr->left; // curr�� key�� �Է¹��� key���� ũ�� �������� �̵�
		} else {
			curr = curr->right; // curr�� key�� �Է¹��� key���� ������ ���������� �̵�
		}
	}
	printf("�Է��� key�� �������� �ʽ��ϴ�.\n");
	return NULL; // key�� ã�� ���� ��� NULL ��ȯ
}


int freeBST(Node* head)
{

}





