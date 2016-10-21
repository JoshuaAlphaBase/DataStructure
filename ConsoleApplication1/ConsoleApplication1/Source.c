#define NODE_NUM 10
#include <stdio.h>
#include <stdlib.h>
#define ON 1
#define OFF 0
struct node {
	int data;
	int link;
};
struct node lnk_lst[NODE_NUM];
int head = -1;  //초기에 비어있다.
int freehead;

void main() {
	int data, sw, p, q, i, tmp;
	char op_code="", inp_string[5];
	void del_link(int p, int q);
	void del_search(int *p, int *q, int d);
	void ins_link(int p, int q, int s);
	void ins_search(int *p, int *q, int d);
	freehead = 0;

	for (i = 0; i < NODE_NUM; i++) {
		lnk_lst[i].link = i + 1;
	}
	lnk_lst[NODE_NUM - 1].link = -1; //끝을 알리는 -1
	sw = ON;
	while (sw) {
		printf("Insert (I:insert, D:delete, P:print, Q:quit) -> ");
		scanf_s(" %c", &op_code);
		printf("** Op_code = %c\n", op_code);
		switch (op_code) {
		case 'I':
			printf("Enter a number to Insert! : ");
			scanf_s("%d", &data);
			printf("Inserted Data = %d\n", data);
			ins_search(&p, &q, data);
			ins_link(p, q, data);
			break;
		case 'D':
			printf("Enter a number to Delete! : ");
			scanf_s("%d", &data);
			del_search(&p, &q, data);
			if (q != -1) {
				del_link(p, q);
				printf("Removed Data = %d\n", data);
			}
			break;
		case 'Q':
			sw = OFF;
			break;
		case 'P':
			tmp = head;
			while (tmp != -1) {
				printf(" %4d ", lnk_lst[tmp].data);
				tmp = lnk_lst[tmp].link;
			}
			printf("\n");
			break;
		default:
			printf("***Unexceptable Command!***\n");
			break;
		}
	}
}

int get_node() {
	int P;
	if (freehead == -1) {
		printf("list is full\n");
		exit(1);
	}
	P = freehead;
	freehead = lnk_lst[freehead].link;
	return(P);
}
void ins_search(int *p, int *q, int d)
{
	printf("search head = %4d\n", head);
	if (head == -1) { //lnk_lst의 data가 모두 비어있다.
		*p = -1;
		*q = -1;
	}
	else if (lnk_lst[head].data > d) {  //lnk_lst의 맨 앞에 삽입한다.
		*p = -1;
		*q = head;
	}
	else {
		*p = head;
		*q = lnk_lst[*p].link;
		while ((*q != -1) && (lnk_lst[*q].data < d)) {
			*p = *q;
			*q = lnk_lst[*q].link;
		}
	}
}

void ins_link(int p, int q, int s) {
	int x;
	int get_node();
	x = get_node();
	lnk_lst[x].data = s;

	if (p == -1)
		head = x;
	else
		lnk_lst[p].link = x;
	lnk_lst[x].link = q;

}

void del_link(int p, int q) {
	void free_node(int P);
	if (p == -1)
		head = lnk_lst[q].link;
	else
		lnk_lst[p].link = lnk_lst[q].link;
	free_node(q);
}

void del_search(int *p, int *q, int d) {
	if (head == -1) {
		printf("empty list\n");
		*p = -1;
		*q = -1;
	}
	else {
		if (d == lnk_lst[head].data) {
			*p = -1;
			*q = head;
		}
		else {
			*p = head;
			*q = lnk_lst[*p].link;
			while ((*q != -1) && (lnk_lst[*q].data!= d)) {
				*p = *q;
				*q = lnk_lst[*q].link;
			}
			if (*q == -1) {
				printf("검색 실패\n");
				*p = -1;
				*q = -1;
			}
		}
	}
}
void free_node(int P) {
	lnk_lst[P].link = freehead;
	freehead = P;
}