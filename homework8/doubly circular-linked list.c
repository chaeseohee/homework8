/* doubly circular linked list */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    struct Node* llink;
    struct Node* rlink;
}listNode;

int initialize(listNode** h);
int freeList(listNode* h);

int insertLast(listNode* h, int key);
int deleteLast(listNode* h);

int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);

int invertList(listNode* h);
void printList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);


int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("Doubly Circular Linked List ----- [chae seohee] [2022041084] -----\n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
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

	}while(command != 'q' && command != 'Q');
}

int initialize(listNode** h)
{
    /* 연결리스트가 이미 존재하는 경우 */ //어떻게 구현할지 모르겠다.. 생각대로 했더니 오류남

    /* 헤드노드에 메모리 할당 받기 */
    (*h) = (listNode*)malloc(sizeof(listNode));
    return 0;
}

int freeList(listNode* h)
{
    /* 헤드노드부터 차례로 메모리 해제(마지막 노드 제외) */
    listNode* p = h;
    while(p->rlink != h)
    {
        free(p->llink);
        p = p->rlink;
    }
    /* 마지막 노드 메모리 해제 */
    free(p);

    return 0;
}

int insertLast(listNode* h, int key) 
{
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

int deleteLast(listNode* h)
{
    /* 연결리스트에 노드가 하나도 없는 경우 */
    if(h->rlink == h)
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

int insertFirst(listNode* h, int key)
{
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

int deleteFirst(listNode* h)
{
    /* 연결리스트에 노드가 하나도 없는 경우 */
    if(h->rlink == h)
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

int insertNode(listNode* h, int key) 
{
    /* 삽입할 새로운 노드 생성 */
    listNode* newnode = (listNode*)malloc(sizeof(listNode));
    newnode->key = key;

    /* 새로운 노드가 삽입될 위치 찾고 삽입 */
    listNode* p = h->rlink;
    while(p != h)
    {
        if(key <= p->key)
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

int deleteNode(listNode* h, int key)
{
    /* 연결리스트에 노드가 하나도 없는 경우 */
    if(h->rlink == h)
    {
        printf("No node to delete \n");
        return 1;
    }

    /* 삭제할 노드 찾기 */

    /* 삭제할 key값을 가진 노드가 없는 경우 */
}

void printlist(listNode* h)
{
    listNode* p = h->rlink;
    int i = 0;

    printf("[ ");
    while(p != h)
    {
        printf("[%d] %d, ", i,  p->key);
        p = p->rlink; i++;
    }
    printf("] \n");

    return;
}

int invertlist(listNode* h)
{

}