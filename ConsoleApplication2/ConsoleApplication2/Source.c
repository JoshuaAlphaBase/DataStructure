#include <stdio.h>
#include <stdlib.h>
struct node {
	int data;
	struct node *link;
};
struct node *get_node() {
	struct node *p;
	p = (struct node *)malloc(sizeof(struct node));
	return p;
}
void free_node(struct node *p) {
	free(p);
}
int main() {
	struct node *p;
	p = (struct node *)malloc(sizeof(struct node));
	printf("%d\n", sizeof(p));
}