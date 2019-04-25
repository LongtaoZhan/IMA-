/*tree.h--����������*/
/*���в���������ͬ����Ŀ*/
#pragma once

#include <stdbool.h>

/*���԰�Item�ض���Ϊ���ʵ�����*/
typedef struct item
{
	char petname[20];
	char petkind[20];
}Item;

#define MAXITEMS 10

typedef struct node
{
	Item item;
	struct node * left;		/*ָ�����֧�Ľڵ�*/
	struct node * right;	/*ָ���ҷ�֧�Ľڵ�*/
}Node;

typedef struct tree
{
	Node * root;		/*ָ��������ָ��*/
	int size;			/*���е���Ŀ����*/
}Tree;

/*����ԭ��											*/	
/*���� : ��һ������ʼ��Ϊһ������						*/
/*����ǰ: ptreeָ��һ����								*/
/*������: ������ʼ��Ϊ��								*/
void InitializeTree(Tree * ptree);
				
/*���� : ȷ�����Ƿ�Ϊ��									*/
/*����ǰ: ptreeָ��һ����								*/
/*������: If(����) return ture;   else return false;	*/
bool TreeIsEmpty(const Tree * ptree);

/*���� : ȷ�����Ƿ�����									*/
/*����ǰ: ptreeָ��һ����								*/
/*������: If(����) return ture;   else return false;	*/
bool TreeIsFull(const Tree * ptree);

/*���� : ȷ��������Ŀ�ĸ���								*/
/*����ǰ: ptreeָ��һ����								*/
/*������: ���� return ���е���Ŀ�ĸ���					*/
int TreeItemCount(const Tree * ptree);

/*���� : ���������һ����Ŀ								*/
/*����ǰ: pi�Ǵ������Ŀ�ĵ�ַ							*/
/*	     ptreeָ��һ���Ѿ���ʼ������					*/
/*������: �������, �����Ѹ���Ŀ							*/
/*������: ��ӵ����в�����true;							*/
/*������: ����������false	;							*/
bool AddItem(const Item * pi, Tree * ptree);

/*���� : �����в���һ����Ŀ								*/
/*����ǰ: piָ��һ����Ŀ								*/
/*	     ptreeָ��һ���Ѿ���ʼ������					*/
/*������: �������Ŀ������,��������true;				*/
/*������: ��ӵ����в�����true							*/
/*������: ����������false;							*/
bool InTree(const Item * pi, Tree * ptree);

/*���� : ������ɾ��һ����Ŀ								*/
/*����ǰ: pi�Ǵ�ɾ������Ŀ�ĵ�ַ							*/
/*	     ptreeָ��һ���Ѿ���ʼ������					*/
/*������: �������,����������ɾ������Ŀ					*/
/*������: ������true; ����������false					*/
bool DeleteItem(const Item * pi, Tree * ptree);

/*���� : ��һ���������������е�ÿһ����Ŀ					*/
/*����ǰ: ptreeָ��һ����								*/
/*	     pfun ָ��һ��û�з���ֵ�ĺ���					*/
/*������: �ú�������һ��Item��Ϊ����						*/
/*������: pfunָ��ĺ�����������							*/
/*������: ����ÿ����Ŀһ��								*/
void Traverse(const Tree * ptree, void (* pfun)(Item item));

/*���� : ������ɾ�����нڵ�								*/
/*����ǰ: ptreeָ��һ���Ѿ���ʼ������					*/
/*������: ����Ϊ����(boom!)							*/
void DeleteAll(Tree * ptree);




