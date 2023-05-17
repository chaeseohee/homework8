

#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* llink; //left link
	struct Node* rlink; //right link
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

int initialize(headNode** h);
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);

int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);

int invertList(headNode* h);
void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("  Doubly Linked  List [----- [Chae seohee] [2022041084] -----]  \n");
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

	return 1;
}

int initialize(headNode** h) {
	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	return 1;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함. */
	listNode* p = h->first;
	listNode* prev = NULL;

	while(p != NULL) { 
		prev = p; //prev는 p를 따라가고
		p = p->rlink; //p는 다음 노드를 가리킴
		free(prev); //prev가 가리키는 노드 삭제
	}
	free(h);
	return 0;
}

void printList(headNode* h) {
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //헤드포인터가 NULL이면
		printf("Nothing to print....\n"); //출력할 노드가 없음을 알리고
		return; //printList함수 종료
	}

	p = h->first; //listNode포인터 p가 첫번째 노드를 가리키게 하고

	int i=0; //while문용 변수
	while(p != NULL) { 
		printf("[ [%d]=%d ] ", i, p->key); //노드번호와 순서를 출력
		p = p->rlink; //p는 다음 노드를 가리키게하고
		i++; //노드번호도 하나 증가시키기
	}

	printf("  items = %d\n", i); //while문을 돌며 노드의 숫자만큼 증가한 i변수를 통해 노드의 개수 출력
}

int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //동적할당으로 새로운 노드를 하나 만들어주기
	node->key = key; //새로운 노드의 key값에는 main에서 입력받은 key값 대입
	node->rlink = NULL; //right link는 NULL로 초기화
	node->llink = NULL; //left link도 NULL로 초기화

	if (h->first == NULL) //연결리스트에 노드가 하나도 없으면
	{
		h->first = node; //headNode h의 first의 값만 node로 바꿔주고
		return 0; //종료
	}

	/* listNode포인터 하나를 선언해서 while문을 통해 마지막 노드를 가리키게 함 */
	listNode* n = h->first; 
	while(n->rlink != NULL) {
		n = n->rlink;
	}

	n->rlink = node; //(아직 새로운 노드를 넣기 전 기준)마지막 노드의 rlink값에 node를 저장해주고
	node->llink = n; //node의 llink값에는 (아직 새로운 노드를 넣기 전 기준)마지막 노드의 주소를 저장
	return 0;
}

int deleteLast(headNode* h) {

	if (h->first == NULL) //연결리스트에 노드가 하나도 없으면
	{
		printf("nothing to delete.\n"); //지울 노드가 없음을 알리고
		return 0; //deleteLast함수 종료
	}

	listNode* n = h->first; 
	listNode* trail = NULL; 

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) {
		h->first = NULL; //헤드노드의 first값을 NULL로 바꾸고
		free(n); //하나있는 노드 free
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) {
		trail = n; //trail은 n을 따라가고
		n = n->rlink; //n은 다음 노드로 이동
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL; 
	free(n);

	return 0;
}

/* list 처음에 key에 대한 노드하나를 추가 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //노드포인터 하나 만들어서 동적할당으로 새로운 노드 하나 만들기
	node->key = key; //새로운 노드의 key값에 main에서 입력받은 key값 대입
	node->rlink = node->llink = NULL; //새로운 노드의 rlink와 link는 모두 NULL로 초기화

	/* 연결리스트에 노드가 하나도 없는 경우 */
	if(h->first == NULL)
	{
		h->first = node; //h의 first가 새로운 노드를 가리키게 함
		return 1; //insertFirst함수 종료
	}

	/* 연결리스트에 노드가 하나 이상 있는 경우 */
	node->rlink = h->first; //node의 rlink에 기존의 첫번째 노드값 넣어주기
	node->llink = NULL; //node가 첫번째 노드가 될 것이기 때문에 node의 llink는 NULL로 초기화

	listNode *p = h->first; 
	p->llink = node; //기존의 첫번째 노드의 llink가 node를 가리키게 하고
	h->first = node; //h의 first는 node를 가리키게 함

	return 0;
}

/* list의 첫번째 노드 삭제 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) //연결리스트에 노드가 하나도 없는 경우
	{
		printf("nothing to delete.\n"); //삭제할 노드가 없음을 알리고
		return 0; //deleteFirst함수 종료
	}
	listNode* n = h->first; //listNode포인터 n을 만들어서 첫번째 노드를 가리키게 하고
	h->first = n->rlink; //h의 first값에 첫번째 노드의 오른쪽 노드, 즉 두번째 노드주소를 저장

	free(n); //첫번째 노드는 삭제

	return 0;
}

/* 리스트의 링크를 역순으로 재 배치 */
int invertList(headNode* h) {

	if(h->first == NULL) { //연결리스트에 노드가 없는 경우
		printf("nothing to invert...\n"); //invert할 노드가 없음을 알리고 
		return 0; //invertNode함수 종료
	}

	listNode *n = h->first; 
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){
		trail = middle; //trail은 middle을 따라가고
		middle = n; //middle은 n을 따라가고
		n = n->rlink; //n은 다음 노드로 
		middle->rlink = trail; //middle의 rlink는 trail로
		middle->llink = n; //middle의 llink는 n으로 rlink와 llink를 바꿔주기
	}

	h->first = middle; //whilw루프를 돌면서 마지막 노드를 가리키게 된 middle의 값을 h의 first에 저장

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	/* 새로운 노드를 만들어 값설정 */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	/* 기존 연결리스트에 노드가 하나도 없는 경우 */
	if (h->first == NULL)
	{
		h->first = node; //h의 first를 node로 설정 후
		return 0; //insertNode함수 종료
	}

	listNode* n = h->first;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				insertFirst(h, key);
			} else { /* 중간이거나 마지막인 경우 */
			//n은 key값이 node의 key값보다 큰 첫번째 노드를 가리킴 
				node->rlink = n; //node의 rlink는 n으로
				node->llink = n->llink; //node의 llink는 n이전 노드로
				n->llink->rlink = node; //(새로운 노드삽입 전)n이전노드의 rlink는 node로 
			}
			return 0;
		}

		n = n->rlink; //while루프를 위한 문장, n이 다음 노드를 가리키게 함
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}


/* list에서 key에 대한 노드 삭제 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //연결리스트에 노드가 하나도 없는 경우
	{
		printf("nothing to delete.\n"); //지울 노드가 없음을 알리고
		return 1; //deleteNode함수 종료
	}

	listNode* n = h->first;

	while(n != NULL) {
		if(n->key == key) { 
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h);
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; //n이전노드의 rlink를 n다음노드로 변경
				n->rlink->llink = n->llink; //n이후노드의 llink를 n이전노드로 변경
				free(n); //n이 가리키는 노드의 메모리 해제
			}
			return 1;
		}

		n = n->rlink; //while루프를 위한 문장, n이 다음 노드를 가리키게 함
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}