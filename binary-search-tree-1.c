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

	printf("[----- ������ 2020069031 -----]\n");

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
	if (ptr != NULL) {
		inorderTraversal(ptr->left); // ���� ������ ��ȸ
		printf("[%d] ", ptr->key); // ��� ���(root) ���
		inorderTraversal(ptr->right); // ���� ���� ��� ��ȸ
	}
}

void preorderTraversal(Node* ptr)
{
	if (ptr != NULL) {
		printf("[%d] ", ptr->key); // ��� ���(root) ���
		preorderTraversal(ptr->left); // ���� ���� ��� ��ȸ�ϸ� ���
		preorderTraversal(ptr->right); // ���������� ���� ��� ��ȸ�ϸ� ���
	}
}

void postorderTraversal(Node* ptr)
{
	if (ptr != NULL) {
		postorderTraversal(ptr->left); // ���� ������ ��ȸ �� ���
		postorderTraversal(ptr->right); // ���� ���� ��� ��ȸ �� ���
		printf("[%d] ", ptr->key); // ���������� ���(root)��� ���
	}
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
	Node* curr = head->left;
	Node* parent = NULL;

	if (head == NULL || head->left == NULL) {
		printf("Ʈ���� ����ֽ��ϴ�.\n");
		return 0; // Ʈ���� ����ִ� ��� 0 ��ȯ
  }

	while (curr != NULL && curr->key != key) { // ��尡 null�̰ų�, �Է¹��� key ���� ã�� ������ �ݺ�
		parent = curr; // ��� ������ ���� �θ� ��� ������Ʈ

		if (curr->key > key) { 
			curr = curr->left; // ����� key�� �Էµ� key���� ũ�� �������� �̵�
		} else { 
			curr = curr->right; // ����� key�� �Էµ� key���� ������ ���������� �̵�
		}
	}

	if(curr == NULL) {
		printf("�Է��� key�� �������� �ʽ��ϴ�.\n");
		return 0; // key�� ã�� ���� ��� 0 ��ȯ
	}
	
	if (curr->left == NULL && curr->right == NULL) { // ���� ������� Ȯ��
		if (parent->left == curr) {
			parent->left = NULL; // �ش� ��尡 �θ� ����� ���� �ڽ��̸� �θ� ����� left�� NULL�� �ʱ�ȭ
		} else {
			parent->right = NULL; // �ش� ��尡 �θ� ����� ���� �ڽ��̸� �θ� ����� right�� NULL�� �ʱ�ȭ
		}

		free(curr); // �ش� ��� ����
		
		return 1;
	}

	printf("the node [%d] is not a leaf", key); // ���� ��尡 �ƴ� ��� ���
	
	return 0;
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

	while(curr != NULL && curr->key != key) { // curr�� ����Ű�� ����� key�� �Է¹��� key�� ������ ������ �ݺ�
		if (curr->key > key) { 
			curr = curr->left; // ����� key�� �Էµ� key���� ũ�� �������� �̵�
		} else { 
			curr = curr->right; // ����� key�� �Էµ� key���� ������ ���������� �̵�
		}
	}

	if(curr == NULL) {				
		printf("�Է��� key�� �������� �ʽ��ϴ�.\n");
		return NULL; // key�� ã�� ���� ��� NULL ��ȯ
	}

	return curr;
}


int freeBST(Node* head)
{
	if(head->left == NULL) return 1;

	Node* curr = head->left;

	freeBST(curr->left); // root ����� ���� ������ ����
	freeBST(curr->right); // root ����� ���� ������ ����

	free(curr);
	free(head);

	return 1;
}





