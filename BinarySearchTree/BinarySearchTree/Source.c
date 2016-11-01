#include "stdio.h"
#include "string.h"
#define YES 1
#define NO 0
#define LIST struct list
LIST{
	char *name;
char *tel;
LIST *left;
LIST *right;
};
void main()
{
	LIST *root, *insert(), *srch(), *modi(), *delet(), *temp;
	char name[15], tel[15];
	int key;
	void prnt(), inpt();
	FILE *fp;
	root = NULL;
	do {
		printf("\n Input(file)-1 Input(keyboard)-2 Display-3 Search-4 Update-5 Delete-6 End-7 \n");
		printf("\n Select a key --->");
		scanf("%d", &key);
		if (key == 1) {
			printf("\n---input---\n");
			fp = fopen("binary.dat", "r");
			if (fp != NULL)
				while (fscanf(fp, "%s %s", name, tel) != EOF) {
					printf("name=%s tel=%s\n", name, tel);
					root = insert(root, name, tel);
				}
			else{
				printf("fopen error\n");
				exit(1);
			}
		}
		if (key == 2) {// 키보드에서 삽입할 데이터값을 입력받음
			inpt(name, tel);
			root = insert(root, name, tel);
		}
		if (key == 3) {
			printf("\n---display ---\n");
			printf("\nlevel   name   tel \n");
			prnt(root, 1);
		}
		if (key == 4) {
			printf("\n---search ---\n");
			printf(" name---> ");
			scanf("%s", &name);
			temp = srch(root, name);
		}
		if (key == 5) {
			printf("\n---update---\n");
			printf("name---> ");
			scanf("%s", &name);
			modi(root, name);
		}
		if (key == 6) {
			printf("\n---delete---\n");
			printf(" name---> ");
			scanf("%s", &name);
			root = delet(root, name);
		}
		if (key == 7) {
			printf("\n---end---\n");
		}
	} while (key < 7);
}
LIST *insert(LIST *rp, char *name, char *tel)
{
	LIST *create_node();
	char *strsv();
	int cmp;
	if (rp == NULL) {
		rp = create_node();
		rp->name = strsv(name);
		rp->tel = strsv(tel);
		rp->left = rp->right = NULL;
	}
	else if ((cmp = strcmp(name, rp->name)) == 0) {
		printf("\n------------------------------\n");
		printf("Existing NAME = %-15s  TEL = %-13s \n",
			rp->name, rp->tel);
		printf("\n------------------------------\n");
	}
	else if (cmp < 0)//왼쪽 부트리로 이동
		rp->left = insert(rp->left, name, tel);
	else                    //오른쪽 부트리로 이동
		rp->right = insert(rp->right, name, tel);
	return(rp);
}
void inpt(char *name, char *tel)
{
	printf("\nname ---> ");
	scanf("%s", name);
	printf("\n tel--->");
	scanf("%s", tel);
}

LIST *create_node()
{
	char *malloc();
	return((LIST *)malloc(sizeof(LIST)));
}
char *strsv(char *sl)
{ //입력받은 데이터크기+1 만큼의 공간을 확보하여 데이터를 복사한다
	char *p, *malloc();
	if ((p = malloc(strlen(sl) + 1)) != NULL)//EOL을 위한 공간 확보
		strcpy(p, sl);
	return(p);
}
void prnt(LIST *pp, int lev)
{
	if (pp != NULL) {//중위 순회 알고리즘을 활용한 출력
		prnt(pp->left, lev + 1);
		printf("%2d  %-14s  %15s \n", lev, pp->name, pp->tel);
		prnt(pp->right, lev + 1);
	}
}
LIST *srch(LIST *sp, char *snam)
{
	int cmp;
	if (sp != NULL) {
		if ((cmp = strcmp(snam, sp->name)) == 0) {
			printf("\n  name   tel \n");   printf("-------------------\n");
			printf("%-14s %-15s \n", sp->name, sp->tel);
		}
		else if (cmp < 0)
			sp->left = srch(sp->left, snam);
		else
			sp->right = srch(sp->right, snam);
	}
	else
		printf("Search Fail: %s is not exist in the tree \n", snam);
	return(sp);
}
LIST *modi(LIST *mp, char *mnam)
{
	char mtel[15];     int cmp;  char *temp;
	if (mp != NULL) {
		if ((cmp = strcmp(mnam, mp->name)) == 0) {
			printf("tel--> ");     scanf("%s", mtel);
			temp = mp->tel;            mp->tel = strsv(mtel);       free(temp);
		}
		else if (cmp < 0)
			mp->left = modi(mp->left, mnam);
		else
			mp->right = modi(mp->right, mnam);
	}
	else
		printf("Search Fail: %s is not exist in the tree \n", mnam);
	return(mp);
}
LIST *delet(LIST *dp, char *dnam)
{
	LIST *findmin(), *temp;
	int cmp;
	if (dp == NULL)
		printf("Search Fail No search name exist \n");
	else if ((cmp = strcmp(dnam, dp->name)) < 0)
		dp->left = delet(dp->left, dnam);
	else if (cmp > 0)
		dp->right = delet(dp->right, dnam);
	else if (dp->left && dp->right) {// 삭제될 노드를 검색
		temp = findmin(dp->right);//두개의 자식이 있는 노드
		strcpy(dp->name, temp->name);//데이터의 복사(크기문제발생)
		strcpy(dp->tel, temp->tel);		//공간재설정 필요
		dp->right = delet(dp->right, dp->name); // 최소 노드를 결정한다
	}
	else { //하나의 자식 또는 없는 경우
		temp = dp;
		if (dp->left == NULL)
			dp = dp->right;
		else if (dp->right == NULL)
			dp = dp->left;
		free(temp);
	}
	return(dp);
}
LIST *findmin(LIST *node)
{
	LIST *temp, *save;
	save = node;
	temp = save->left;
	//오른쪽 부트리의 최소값을 찾는다
	while (temp != NULL) {
		save = temp;
		temp = temp->left;
	}
	return(save);
}