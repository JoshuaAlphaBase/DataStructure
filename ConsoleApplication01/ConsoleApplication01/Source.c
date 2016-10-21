#include <stdio.h>
struct node {
	int expo;
	int coef;
};
struct poly {
	int node_num;
	struct node list[10];
};

void main() {
	int i;
	struct poly M, N, S;
	void poly_add(struct poly M, struct poly N, struct poly *S);

	M.node_num = 3;
	M.list[0].expo = 4;
	M.list[1].expo = 3;
	M.list[2].expo = 1;
	M.list[0].coef = 2;
	M.list[1].coef = -5;
	M.list[2].coef = 3;

	N.node_num = 3;
	N.list[0].expo = 5;
	N.list[1].expo = 3;
	N.list[2].expo = 2;
	N.list[0].coef = 4;
	N.list[1].coef = -5;
	N.list[2].coef = 3;

	for (i = 0; i < M.node_num; i++) 
		printf("%dx%d ", M.list[i].coef, M.list[i].expo);
	printf("\n");
	for (i = 0; i < N.node_num; i++)
		printf("%dx%d ", N.list[i].coef, N.list[i].expo);
	printf("\n");
	poly_add(M, N, &S);
	printf("Result = ");
	for (i = 0; i < S.node_num; i++) {
		if ((S.list[i].coef > 0) && (i > 0)) {
			printf("+");
		}
		printf("%dx%d", S.list[i].coef, S.list[i].expo);
	}
	printf("\n");
}
void poly_add(struct poly M, struct poly N, struct poly *S) {
	int tmp, i, j;
	void new_node(int c, int e, struct poly *S);
	i = 0; j = 0;
	while (i < M.node_num && j < N.node_num) {
		if (M.list[i].expo == N.list[i].expo) {
			tmp = M.list[i].coef + N.list[i].coef;
			if (tmp != 0)
				new_node(tmp, M.list[i].expo, S);
			i++;
			j++;
		}
		else if (M.list[i].expo > N.list[j].expo) {
			new_node(M.list[i].coef, M.list[i].expo, S);
			i++;
		}
		else {
			new_node(N.list[j].coef, N.list[j].expo, S);
			j++;
		}
	}
	while (i < M.node_num) {
		new_node(M.list[i].coef, M.list[i].expo, S);
		i++;
	}
	while (j < N.node_num) {
		new_node(N.list[j].coef, M.list[j].expo, S);
		j++;
	}
}
void new_node(int c, int e, struct poly *S) {
	static int i = 0;
	S->list[i].coef = c;
	S->list[i].expo = e;
	S->node_num = ++i;
}