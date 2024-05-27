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

	printf("[----- 허제완 2020069031 -----]\n");

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
		inorderTraversal(ptr->left); // 좌측 노드부터 순회
		printf("[%d] ", ptr->key); // 가운데 노드(root) 출력
		inorderTraversal(ptr->right); // 이후 우측 노드 순회
	}
}

void preorderTraversal(Node* ptr)
{
	if (ptr != NULL) {
		printf("[%d] ", ptr->key); // 가운데 노드(root) 출력
		preorderTraversal(ptr->left); // 이후 좌측 노드 순회하며 출력
		preorderTraversal(ptr->right); // 마지막으로 우측 노드 순회하며 출력
	}
}

void postorderTraversal(Node* ptr)
{
	if (ptr != NULL) {
		postorderTraversal(ptr->left); // 좌측 노드부터 순회 및 출력
		postorderTraversal(ptr->right); // 이후 우측 노드 순회 및 출력
		printf("[%d] ", ptr->key); // 마지막으로 가운데(root)노드 출력
	}
}


int insert(Node* head, int key)
{
	// 입력받은 key를 이용하여 새로운 노드 생성
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = newNode->right = NULL;

	// head가 NULL인지 확인하고, NULL이면 입력 받은 key를 head가 가리키도록 함.
	if(head->left == NULL) {
		head->left = newNode;
	} else { 
		Node* curr = head->left;
		
		// head가 NULL이 아닌 경우, curr를 head로 지정. curr의 key와 입력받은 key를 비교하여 작으면 왼쪽, 크면 오른쪽으로 curr 이동.
		while(1) {
			if(curr->key > key) {
				if(curr->left == NULL) { // 입력받은 key가 더 작은 경우, 현재 노드의 좌측 자식 노드가 없으면 새로운 노드 삽입 후 루프 종료.
					curr->left = newNode;
					break;
				} else {
					curr = curr->left; // 현재 노드 갱신
				}
			} else {
				if(curr->right == NULL) { // 입력받은 key가 더 큰 경우, 현재 노드의 우측 자식 노드가 없으면 새로운 노드 삽입 후 루프 종료.
					curr->right = newNode;
					break;
				} else {
					curr = curr->right; // 현재 노드 갱신
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
		printf("트리가 비어있습니다.\n");
		return 0; // 트리가 비어있는 경우 0 반환
  }

	while (curr != NULL && curr->key != key) { // 노드가 null이거나, 입력받은 key 값을 찾을 때까지 반복
		parent = curr; // 노드 삭제를 위한 부모 노드 업데이트

		if (curr->key > key) { 
			curr = curr->left; // 노드의 key가 입력된 key보다 크면 왼쪽으로 이동
		} else { 
			curr = curr->right; // 노드의 key가 입력된 key보다 작으면 오른쪽으로 이동
		}
	}

	if(curr == NULL) {
		printf("입력한 key가 존재하지 않습니다.\n");
		return 0; // key를 찾지 못한 경우 0 반환
	}
	
	if (curr->left == NULL && curr->right == NULL) { // 리프 노드인지 확인
		if (parent->left == curr) {
			parent->left = NULL; // 해당 노드가 부모 노드의 좌측 자식이면 부모 노드의 left를 NULL로 초기화
		} else {
			parent->right = NULL; // 해당 노드가 부모 노드의 우측 자식이면 부모 노드의 right를 NULL로 초기화
		}

		free(curr); // 해당 노드 삭제
		
		return 1;
	}

	printf("the node [%d] is not a leaf", key); // 리프 노드가 아닌 경우 출력
	
	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) { // 탐색 후 해당 key가 존재하지 않는 경우
		printf("입력한 key가 존재하지 않습니다.\n");
		return NULL;
	}

	if(ptr->key == key) {
		return ptr; // 입력받은 key가 ptr의 key와 동일한 경우
	} else if(ptr->key > key){
		return searchRecursive(ptr->left, key); // ptr의 key가 입력받은 key보다 크면 왼쪽으로 이동 후 searchRecursive
	} else {
		return searchRecursive(ptr->right, key); // ptr의 key가 입력받은 key보다 작으면 오른쪽으로 이동 후 searchRecursive
	}	
}

Node* searchIterative(Node* head, int key)
{
	Node* curr = head;

	while(curr != NULL && curr->key != key) { // curr이 가리키는 노드의 key가 입력받은 key와 동일할 때까지 반복
		if (curr->key > key) { 
			curr = curr->left; // 노드의 key가 입력된 key보다 크면 왼쪽으로 이동
		} else { 
			curr = curr->right; // 노드의 key가 입력된 key보다 작으면 오른쪽으로 이동
		}
	}

	if(curr == NULL) {				
		printf("입력한 key가 존재하지 않습니다.\n");
		return NULL; // key를 찾지 못한 경우 NULL 반환
	}

	return curr;
}


int freeBST(Node* head)
{
	if(head->left == NULL) return 1;

	Node* curr = head->left;

	freeBST(curr->left); // root 노드의 좌측 노드들을 삭제
	freeBST(curr->right); // root 노드의 우측 노드들을 삭제

	free(curr);
	free(head);

	return 1;
}





