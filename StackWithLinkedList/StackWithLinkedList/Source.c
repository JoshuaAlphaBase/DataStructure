#include <stdio.h>
#include <stdlib.h>
#define ON 1
#define OFF 0
typedef struct stack *stackptr;
struct stack {
	int data;
	stackptr next;
};

void main()
{
	int data, SW, Pop(stackptr *top);
	char opcode = "";
	stackptr top;
	void Push(stackptr *top, int x);
	int Top(stackptr top), Pop(stackptr top);
	SW = ON;
	top = NULL;
	while (SW) {
		printf("Insert Opcode(P:Push, O:Pop, T:Top, Q:Quit): ");
		scanf_s(" %c", &opcode);
		printf("** Opcode= %c\n", opcode);
		switch (opcode) {
		case 'P':
			printf("Enter a number to push:");
			scanf_s("%d", &data);
			printf("Pushed Data= %d \n", data);
			Push(&top, data);
			break;
		case 'O':
			if (top) {
				data = Pop(&top);
				printf("Popped Data= %d \n", data);
			}
			else
				printf("** 스택이 비어있음 \n");
			break;
		case 'T':
			if (top) {
				data = Top(top);
				printf("Top Data= %d \n", data);
			}
			else
				printf("** 스택이 비어있음 \n");
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
void Push(stackptr *top, int x)
{
	stackptr temp;
	temp = (stackptr)malloc(sizeof(struct stack));
	if (temp) {
		temp->data = x;
		temp->next = *top;
		*top = temp;
	}
	else
		printf("** Memory Overflow! \n");
}
int Pop(stackptr *top)
{
	int x;
	stackptr temp;

	temp = *top;
	x = temp->data;
	*top = temp->next;
	free(temp);
	return(x);
}
int Top(stackptr top)
{
	int x;

	x = top->data;
	return(x);
}