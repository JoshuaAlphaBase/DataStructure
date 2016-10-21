#include<stdio.h>
#include<malloc.h>

struct aa
{
	int data;
	struct aa *ptr;
};

struct aa *head, *tail;

void put(int x)
{
	struct aa *New, *temp;
	temp = head;
	New = (struct aa *)malloc(sizeof(struct aa));
	New->data = x;
	while (temp->ptr != tail)
		temp = temp->ptr;
	New->ptr = tail;
	temp->ptr = New;
}

void init_queue()
{
	head = (struct aa *)malloc(sizeof(struct aa));
	tail = (struct aa *)malloc(sizeof(struct aa));
	head->ptr = tail;
}

void print_queue()
{
	struct aa *Now = head->ptr;
	/*for (Now = head->ptr; Now != tail; Now = Now->ptr)
	{
		printf("%d\t", Now->data);
	}*/
	while (Now != tail) {
		printf("%d\t", Now->data);
		Now = Now->ptr;
	}
	printf("\n");
}

void get()
{
	struct aa *del;
	if (head->ptr == tail)
	{
		printf("queue underflow\n");
		return;
	}
	del = head->ptr;

	head->ptr = del->ptr;
	free(del);
}

void main()
{
	init_queue();

	put(1);
	put(2);
	put(3);
	print_queue();
	get();
	get();
	print_queue();
	get();
	get();
}
