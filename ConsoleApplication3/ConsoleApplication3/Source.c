#include <stdio.h>

struct poly_node {
	float coef;
	int exp;
	struct poly_node *link;
};
newterm(struct poly_node **rp, struct poly_node **rp_tail, int c, int e) {
	struct poly_node *temp;
	temp = get_node();
	temp->coef = c;
	temp->exp = e;
	if (*rp == NULL) {
		*rp = temp;
		*rp_tail = temp;
	}
	else {
		(*rp_tail)->link = temp;
		*rp_tail = temp;
	}
}
poly_add(struct poly_node *p1, struct poly_node *p2, struct poly_node **rp) {
	float c;
	struct poly_node *a, *b, *rp_tail;
	a = p1;
	b = p2;
	while (a != NULL && b != NULL) {
		if (a->exp == b->exp) {
			c = a->coef + b->coef;
			if (c != 0) {
				newterm(rp, &rp_tail, c, a->exp);
			}
			else if (a->exp > b->exp) {
				newterm(rp, &rp_tail, a->coef, a->exp);
				a = a->link;
			}
			else if (a->exp > b->exp) {
				newterm(rp, &rp_tail, b->coef, b->exp);
				b=b->link;
			}
		}
		while (a != NULL) {
			newterm(rp, &rp_tail, a->coef, a->exp);
			a = a->link;
		}
		while (b != NULL) {
			newterm(rp, &rp_tail, b->coef, b->exp);
			b = b->link;
		}
	}
	
}
void main() {
	int i;
	struct poly_node
}