#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf(" Doubly Circular Linked List [----- [chaeseohee] [2022041084] -----] \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {

	/* 헤드노드부터 차례로 메모리 해제(마지막 노드 제외) */
	listNode* p = h;
	while (p->rlink != h)
	{
		free(p->llink);
		p = p->rlink;
	}
	/* 마지막 노드 메모리 해제 */
	free(p);

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}
}

int insertLast(listNode* h, int key) {

	/* 삽입할 새로운 노드 생성 */
	listNode* newnode = (listNode*)malloc(sizeof(listNode));
	newnode->key = key;

	/* newnode링크 설정 */
	newnode->llink = h->llink;
	newnode->rlink = h;

	/* newnode의 앞뒤 링크 이어주기 */
	h->llink->rlink = newnode;
	h->llink = newnode;

	return 1;
}

int deleteLast(listNode* h) {

	/* 연결리스트에 노드가 하나도 없는 경우 */
	if (h->rlink == h)
	{
		printf("No node to delete \n");
		return 0;
	}

	listNode* p = h->llink; // 삭제할 노드를 가리키는 포인터 

	h->llink = p->llink;
	p->llink->rlink = h;
	free(p);

	return 1;
}

int insertFirst(listNode* h, int key) {

	/* 삽입할 새로운 노드 생성 */
	listNode* newnode = (listNode*)malloc(sizeof(listNode));
	newnode->key = key;

	/* newnode의 링크 설정 */
	newnode->llink = h;
	newnode->rlink = h->rlink;

	/* newnode의 앞뒤노드 링크 이어주기 */
	h->rlink->llink = newnode;
	h->rlink = newnode;

	return 1;
}

int deleteFirst(listNode* h) {

	/* 연결리스트에 노드가 하나도 없는 경우 */
	if (h->rlink == h)
	{
		printf("No node to delete \n");
		return 0;
	}

	listNode* p = h->rlink; // 삭제할 노드를 가리키는 포인터

	h->rlink = p->rlink;
	p->rlink = h;
	free(p);

	return 1;
}

int invertList(listNode* h) {

	/* 노드개수 파악 */
	int n = 1; // 헤드노드
	listNode* p = h->rlink;
	while (p != h)
	{
		n++;
		p = p->rlink;
	}

	/* (헤드노드부터) 각 노드의 llink와 rlink값을 맞바꾸기 */
	p = h;
	listNode* temp = NULL;
	for (int i = 0; i < n; i++)
	{
		temp = p->llink;
		p->llink = p->rlink;
		p->rlink = temp;

		p = p->rlink;
	}

	return 0;
}

int insertNode(listNode* h, int key) {

	/* 삽입할 새로운 노드 생성 */
	listNode* newnode = (listNode*)malloc(sizeof(listNode));
	newnode->key = key;

	/* 새로운 노드가 삽입될 위치 찾고 삽입 */
	listNode* p = h->rlink;
	while (p != h)
	{
		if (key <= p->key)
		{
			newnode->llink = p->llink;
			newnode->rlink = p;
			p->llink->rlink = newnode;
			p->llink = newnode;
			return 1;
		}
		p = p->rlink;
	}

	/* 연결리스트에 newnode의 key값보다 큰 key값을 가진 노드가 없을 경우 */   //비효율적인 것 같기도..
	newnode->llink = p->llink;
	newnode->rlink = p;
	p->llink->rlink = newnode;
	p->llink = newnode;
	return 1;
}

int deleteNode(listNode* h, int key) {

	/* 연결리스트에 노드가 하나도 없는 경우 */
	if (h->rlink == h)
	{
		printf("No node to delete \n");
		return 0;
	}

	/* 삭제할 노드 찾고 삭제 */
	listNode* p = h->rlink;
	while (p != h)
	{
		if (key == p->key)
		{
			p->llink->rlink = p->rlink;
			p->rlink->llink = p->llink;
			return 0;
		}
		p = p->rlink;
	}

	/* 삭제할 key값을 가진 노드가 없는 경우 */
	printf("No node to delete that have key you enter");
	return 0;
}
