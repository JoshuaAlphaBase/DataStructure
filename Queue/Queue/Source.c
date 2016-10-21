#include "stdio.h"
#define ON 1
#define OFF 0
#define Queue_size 20

void main()
{
	int data, temp, SW, Q[Queue_size];
	int front = -1, rear = -1;
	int dequeue();
	char opcode="";
	void enqueue();
	SW = ON;
	while (SW) {
		printf("\n Insert Opcode(E: Enqueue, D: Dequeue, P: Print, Q: Quit): ");
		scanf_s(" %c", &opcode);
		printf("** Opcode= %c \n", opcode);
		switch (opcode) {
		case 'E':
			printf("\n Enter a number to insert:");
			scanf_s("%d", &data);
			printf("Inserted Data= %d \n", data);
			enqueue(Q, data, &rear);
			break;
		case 'D':
			data = dequeue(Q, &front, &rear);
			printf("Dequeue data is %3d \n", data);
			break;
		case 'P':
			temp = front + 1;
			while (temp <= rear)
				printf("%5d\n", Q[temp++]);
			break;
		case 'Q':
			SW = OFF;
			break;
		default:
			printf("\n *** Unexceptable Command! \n");
			break;
		}
	}
}
void enqueue(int Q[], int data, int *rear)
{
	if (*rear == Queue_size - 1) {
		printf("Queue is full\n");
		exit(0);
	}
	(*rear)++;
	Q[*rear] = data;
}
int dequeue(int Q[], int *front, int *rear)
{
	int data;
	if (*front == *rear) {
		printf("Queue is empty\n");	exit(0);
	}
	(*front)++;
	data = Q[*front];
	if (*front == *rear) {
		*front = -1;
		*rear = -1;
	}
	return(data);
}
