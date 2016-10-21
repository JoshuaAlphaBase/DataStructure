// Main module for liked list (Array) 
#include <stdio.h>
#include <stdlib.h>
#define ON 1
#define OFF 0
#define NODE_NUM 200
struct node {
	int data;
	int link;
};

struct node link_lst[NODE_NUM];
int head = -1;
int freehead;
void main()
{
	int data, SW, p, q, i, temp;
	char opcode="";
	void del_link(int p, int q);
	void del_search(int *p, int *q, int d);
	void ins_link(int p, int q, int s);
	void ins_search(int *p, int * q, int d);
	freehead = 0;

	for (i = 0; i < NODE_NUM - 1; i++)
		link_lst[i].link = i + 1;
	link_lst[NODE_NUM - 1].link = -1;
	SW = ON;
	while (SW) {
		opcode = "";
		printf("Insert Opcode(I:Insert, D:Delele, Q:Quit, P: Print): ");
		scanf_s(" %c", &opcode);
		printf("** Opcode= %c\n", opcode);

		switch (opcode) {
		case 'I':
			printf("Enter a number to insert:");
			scanf_s("%d", &data);
			printf("Inserted Data= %d \n", data);

			ins_search(&p, &q, data);
			ins_link(p, q, data);
			break;
		case 'D':
			printf("Enter a number to delete:");
			scanf_s("%d", &data);
			del_search(&p, &q, data);
			if (q != -1) {
				del_link(p, q);
				printf("Removed Data= %d \n", data);
			}
			break;
		case 'P':
			temp = head;
			while (temp != -1) {
				printf("%4d ", link_lst[temp].data);
				temp = link_lst[temp].link;
			}
			printf("\n");
				break;
		case 'Q':
			SW = OFF;
			break;

		default:
			printf("*** Unexceptable Command! \n");
			break;
		}
	}
}

int get_node()
{
	int P;
	if (freehead == -1) {
		printf("linked list is full \n");
		exit(1);
	}
	P = freehead;
	freehead = link_lst[freehead].link;
	return(P);
}

void free_node(int P)
{
	link_lst[P].link = freehead;
	freehead = P;        // 앞 쪽에 연결 
}
void ins_link(int p, int q, int s)
// s는 삽입될 data,  p와 q 사이에 삽입 
{
	int x;
	int get_node();
	x = get_node();
	link_lst[x].data = s;

	if (p == -1)
		head = x;
	else
		link_lst[p].link = x;

	link_lst[x].link = q;
}
void ins_search(int *p, int *q, int d) // 삽입을 위한 검색 
{
	printf("search head=%4d \n", head);
	if (head == -1) {
		*p = -1;
		*q = -1;
	}

	else if (link_lst[head].data > d) {
		*p = -1;
		*q = head;
	}

	else {
		*p = head;        *q = link_lst[*p].link;
		while ((*q != -1) && (link_lst[*q].data < d)) {
			*p = *q;           *q = link_lst[*q].link;
		}
	}
}
void del_link(int p, int q)
// p는 q node의 앞 node 
{
	void free_node(int P);

	if (p == -1)
		head = link_lst[q].link;
	else
		link_lst[p].link = link_lst[q].link;
	free_node(q);
}
void del_search(int *p, int *q, int d)
{
	if (head == -1) {
		printf("empty list \n");
		*p = -1;
		*q = -1;
	}
	else {
		if (d == link_lst[head].data) {
			*p = -1;
			*q = head;    // 첫 째 노드의 삭제 
		}
		else {
			*p = head;    *q = link_lst[*p].link;
			while ((*q != -1) && (link_lst[*q].data != d)) {
				*p = *q;
				*q = link_lst[*q].link;
			}
			if (*q == -1) {
				printf("검색 실패 \n");
				*p = -1;
				*q = -1;
			}
		}
	}
}