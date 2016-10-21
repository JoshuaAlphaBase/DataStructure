#include "stdio.h"
#include "stdlib.h"
#define ON 1
#define OFF 0
struct node {
	int data;
	struct node *link;
};

struct node *head, *get_node();
void main()
{
	int data, SW;
	char opcode="";
	int count = 0;
	struct node *p, *q;
	void ins_search(), del_search(), ins_link(), del_link(), free_node();
	head = get_node();
	SW = ON;

	while (SW) {
		printf("\n Insert Opcode(I:Insert,D:Delele,Q:Quit,P:Print): ");
		scanf_s(" %c", &opcode);
		// Opcode를 얻는다 
		printf("** Opcode= %c \n", opcode);
		switch (opcode) {
			//주어진 명령 유형(Opcode)에 따라 처리
		case 'I':
			printf("\n Enter a number to insert:");
			scanf_s("%d", &data);
			printf("Inserted Data= %d \n", data);
			ins_search(&p, &q, data);
			ins_link(p, q, data);
			break;
		case 'D':
			if (head->link != NULL) {
				printf("\n Enter a number to delete:");
				scanf_s("%d", &data);
				printf("Inserted Data= %d \n", data);
				del_search(&p, &q, data);
				if (p == NULL && q == NULL)
					printf("Can not find%d in the list\n", data);
				else {
					del_link(p, q);
					printf("Removed Data= %d \n", data);
				}
			}
			else
				printf("Empty List \n");
			break;
		case 'Q':
			SW = OFF;
			break;
		case 'P':
			count = 0;
			p = head->link;
			while (p != NULL) {
				printf("%3d", p->data);
				p = p->link;
				count++;
			}
			printf("\n 총 %d개",count);
			break;
		default:
			printf("\n *** Unexceptable Command! \n");
			break;
		}
	}
}
struct node *get_node()
{
	struct node *p;
	p = (struct node *)malloc(sizeof(struct node));
	p->link = NULL;
	return(p);
}

void free_node(struct node *p)
{
	free(p);
}
void ins_link(struct node *p, struct node *q, int s)
{ // s는 삽입될 data로 p와 q 사이에 삽입
	struct node *x;
	x = get_node();
	x->data = s;

	if (p == NULL)
		head->link = x; //head의 link는 새로 생성된 x의 시작주소
	else
		p->link = x;
	x->link = q;
}
void del_link(struct node *p, struct node *q)
{// p node 다음의 q node를 삭제한다 
	if (p == NULL)
		head->link = q->link;
	else
		p->link = q->link;
	free_node(q);
}
void ins_search(struct node **p, struct node **q, int d)
{
	if (head->link == NULL) {    //empty list 경우
		*p = NULL;
		*q = NULL;
	}
	else {
		*q = head->link;
		if ((*q)->data < d) {
			*p = NULL;
			*q = head->link;
		}
		else {
			*p = head->link;     *q = (*p)->link;
			while (((*q) != NULL) && ((*q)->data > d)) {
				*p = *q;
				*q = (*q)->link;
			}
		}
	}
}
void del_search(struct node **p, struct node **q, int d)
{

	if (head->link == NULL) {
		printf("empty list \n");
		*p = NULL;
		*q = NULL;
	}
	else {
		if (d == head->link->data) {
			*p = NULL;
			*q = head->link;
		}
		else {
			*p = head->link;
			*q = (*p)->link;
			while ((*q != NULL) && ((*q)->data != d)) {
				*p = *q;
				*q = (*q)->link;
			}
			if ((*q) == NULL) {
				*p = NULL;
				*q = NULL;
			}
		}
	}
}
