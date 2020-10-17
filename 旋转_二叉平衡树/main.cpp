#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define true 1
#define false 0

#define LH 1
#define EH 0
#define RH -1

typedef int Boolean;
typedef int stutas;

typedef struct BSTNode
{
	int data;
	int bf;
	struct BSTNode *lchild;
	struct BSTNode *rchild;
}BSTree,*pBSTree;

void RR_Rotate(pBSTree &p);
void LL_Rotate(pBSTree &p);
void LR_Rotate(pBSTree &p);
void RL_Rotate(pBSTree &p);

void LeftBalance(pBSTree &T);
void RightBalance(pBSTree &T);

stutas InsertAVL(pBSTree &T, int e, Boolean &taller);
pBSTree Search(pBSTree T, int key);						//查找函数

void bianli(pBSTree T);

int main()
{
	pBSTree p=nullptr;
	pBSTree vt = nullptr;
	Boolean taller;
	int cy = 0;
	int num[20];
	printf("请输入元素个数：");
	scanf_s("%d", &cy);
	for (int i = 1; i <= cy; i++)
	{
		printf("请输入第%d个元素:", i);
		scanf_s("%d", &num[i]);
	}
	for (int i = 1; i <= cy; i++)
		InsertAVL(p, num[i], taller);
	bianli(p);
	printf("\n");
	int key;
	printf("请输入要查找的元素：");
	scanf_s("%d", &key);
	vt = Search(p, key);
	if (!vt) printf("查找失败！\n");
	else printf("输出查找到的元素:%d\n", vt->data);
	bianli(p);
	printf("\n");
	system("pause");
	return 0;
}

void RR_Rotate(pBSTree &p)
{
	pBSTree lc;
	lc = p->lchild;
	p->lchild = lc->rchild;
	lc->rchild = p;
	p = lc;
	return;
}
void LL_Rotate(pBSTree &p)
{
	pBSTree rc;
	rc = p->rchild;
	p->rchild = rc->lchild;
	rc->lchild = p;
	p = rc;
	return;
}
void LR_Rotate(pBSTree &p)
{
	pBSTree rc;
	rc = p->rchild;
	p->rchild = rc->lchild;
	rc->lchild = p;
	p = rc;
	return;
}
void RL_Rotate(pBSTree &p)
{
	pBSTree lc;
	lc = p->lchild;
	p->lchild = lc->rchild;
	lc->rchild = p;
	p = lc;
	return;
}
void LeftBalance(pBSTree &T)
{
	pBSTree lc;
	pBSTree rd;
	lc = T->lchild;
	switch (lc->bf)
	{
		case LH:
			T->bf = lc->bf = EH;
			RR_Rotate(T);
			break;
		case RH:
			rd = lc->rchild;
			switch (rd->bf)
			{
				case LH:
					T->bf = RH;
					lc->bf = EH; break;
				case EH:
					T->bf = lc->bf = EH; break;
				case RH:
					T->bf = EH; lc->bf = LH; break;
			}
			rd->bf = EH;
			LR_Rotate(T->lchild);
			RR_Rotate(T);
	}
	return;
}
void RightBalance(pBSTree &T)
{
	pBSTree rc;
	pBSTree ld;
	rc = T->rchild;
	switch (rc->bf)
	{
		case LH:
			ld = rc->lchild;
			switch (ld->bf)
			{
				case LH:
					T->bf = EH;
					rc->bf = LH; break;
				case EH:
					T->bf = rc->bf = EH; break;
				case RH:
					T->bf = LH;
					rc->bf = EH; break;
			}
			ld->bf = EH;
			RL_Rotate(T->rchild);
			LL_Rotate(T);
			break;
		case RH:
			T->bf = rc->bf = EH;
			LL_Rotate(T);
			break;
	}
	return;
}
stutas InsertAVL(pBSTree &T, int e, Boolean &taller)
{
	if (!T)
	{
		T = new BSTree;
		if (!T)	exit(-1);
		T->data = e;
		T->lchild = NULL;
		T->rchild = NULL;
		T->bf = EH;
		taller = true;
	}
	else
	{
		if (T->data == e)
		{
			taller = false;
			return 0;
		}
		if (T->data > e)
		{
			if (!InsertAVL(T->lchild, e, taller)) return 0;
			if (taller)
			{
				switch (T->bf)
				{
					case LH:
						LeftBalance(T); taller = false; break;
					case EH:
						T->bf = LH; taller = true; break;
					case RH:
						T->bf = EH; taller = false; break;
				}
			}
		}
		else
		{
			if (!InsertAVL(T->rchild, e, taller)) return 0;
			if (taller)
			{
				switch (T->bf)
				{
					case LH:
						T->bf = EH; taller = false; break;
					case EH:
						T->bf = RH; taller = true; break;
					case RH:
						RightBalance(T); taller = false; break;
				}
			}
		}
	}
 	return 1;
}
pBSTree Search(pBSTree T, int key)
{
	if (!T) return NULL;
	else
	{
		if (T->data == key) return T;
		else if (T->data > key) Search(T->lchild, key);
		else Search(T->rchild, key);
	}
	//return;
}
void bianli(pBSTree T)
{
	if (T)
	{
		bianli(T->lchild);
		printf("%d\t", T->data);
		bianli(T->rchild);
	}
	return;
}