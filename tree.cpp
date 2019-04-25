/*tree.cpp --树类型的支持函数					*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

/*局部变量类型									*/
typedef struct pair {	
	Node * parrent;					     	//父节点
	Node * child;							//子节点
}Pair;

/*局部函数的原型								*/
static Node * MakeNode(const Item * pi);
static bool ToLeft(const Item * i1, const Item * i2);
static bool ToRight(const Item * i1, const Item * i2);
static void AddNode(Node * new_node, Node * root);
static void InOrder(const Node * root, void(*pfun)(Item item));
static Pair SeekItem(const Item * pi, const Tree * ptree);
static void DeleteNode(Node **ptr);
static void DeleteAllNodes(Node * ptr);

/*函数定义*/
void InitializeTree(Tree * ptree) {
	ptree->root = NULL;
	ptree->root = 0;
}

bool TreeIsEmpty(const Tree * ptree) {
	if (ptree->root == NULL)
		return true;
	else
		return false;
}

bool TreeIsFull(const Tree * ptree) {
	if (ptree->size == MAXITEMS)
		return true;
	else
		return false;
}

int TreeItemCount(const Tree * ptree) {
	return ptree->size;
}

bool  AddItem(const Item * pi, Tree * ptree)
{
	Node * new_node;

	if (TreeIsFull(ptree)) {
		fprintf(stderr, "Tree is full\n");
		return false;
	}
	if (SeekItem(pi, ptree).child != NULL) {
		fprintf(stderr, "Attempted to add duplicate item\n");
		return false;
	}
	new_node = MakeNode(pi);
	if (new_node == NULL) {
		fprintf(stderr, "Couldn't create node\n");
		return false;						/*提前返回						*/	
	}
	/*成功创建了一个新节点*/
	ptree->size++;

	if (ptree->root == NULL)				/*情况1: 树为空树					*/
		ptree->root = new_node;				/*新节点即为树的根节点				*/
	else									/*情况2: 树非空					*/
		AddNode(new_node, ptree->root);		/*把新节点添加到树中				*/
	return true;							/*成功返回						*/
}	

bool InTree(const Item * pi, const Tree * ptree) {
	return (SeekItem(pi, ptree).child == NULL ? false : true);
}

bool DeleteItem(const Item * pi, Tree * ptree)
{
	Pair look;
	look = SeekItem(pi, ptree);
	if (look.child == NULL)
		return false;
	
	if (look.parrent == NULL)				/*删除根项目						*/
		DeleteNode(&ptree->root);
	else if (look.parrent->left == look.child)
		DeleteNode(&look.parrent->left);
	else
		DeleteNode(&look.parrent->right);
	ptree->size--;
	
	return true;
}

void Traverse(Tree * ptree, void(*pfun)(Item item)){
	if (ptree != NULL)
		InOrder(ptree->root, pfun);
}

void DeleteAll(Tree * ptree) {
	if (ptree != NULL)
		DeleteAllNodes(ptree->root);
	ptree->root = NULL;
	ptree->size = 0;
}


/*局部函数*/
static void InOrder(const Node * root, void(*pfun)(Item item)) {
	if (root != NULL)
	{
		InOrder(root->left, pfun);
		(*pfun)(root->item);
		InOrder(root->right, pfun);
	}
}

static void DeleteAllNodes(Node * root) {
	Node * pright;

	if (root != NULL)
	{
		pright = root->right;
		DeleteAllNodes(root->left);
		free(root);
		DeleteAllNodes(pright);
	}
}

bool ToLeft(const Item * i1, const Item * i2)
{
	int comp1;
	
	if ((comp1 = strcmp(i1->petname, i2->petname)) < 0)
		return true;
	else if (comp1 == 0 && strcmp(i1->petkind, i2->petkind) < 0)
		return true;
	else
		return false;
}

bool ToRight(const Item * i1, const Item * i2)
{
	int comp1;

	if ((comp1 = strcmp(i1->petname, i2->petname)) > 0)
		return true;
	else if (comp1 == 0 && strcmp(i1->petkind, i2->petkind) > 0)
		return true;
	else
		return false;
}

static void AddNode(Node * new_node, Node * root) {
	if (ToLeft(&new_node->item, &root->item))
	{
		if (root->left == NULL)				/*空子树							*/
			root->left = new_node;			/*因此把节点添加到此处				*/
		else
			AddNode(new_node, root->left);	/*否则处理子树						*/
	}
	else if (ToRight(&new_node->item, &root->item))
	{
		if (root->right == NULL)
			root->right = new_node;
		else
			AddNode(new_node, root->right);
	}
	else									/*不含有相同的项目				*/	
	{
		fprintf(stderr, "location error in Addnode()\n");
		exit(1);
	}
}

static Node * MakeNode(const Item * pi)
{
	Node * new_node;

	new_node = (Node *)malloc(sizeof(Node));
	if (new_node != NULL)
	{
		new_node->item = *pi;
		new_node->left = NULL;
		new_node->right = NULL;
	}
	return new_node;
}

static Pair SeekItem(const Item * pi, const Tree * ptree)
{
	Pair look;
	look.parrent = NULL;
	look.child = ptree->root;

	if (look.child == NULL)
		return look;						/*提前返回						*/	
	while (look.child!=NULL)
	{
		if (ToLeft(pi, &(look.child->item)))
		{
			look.parrent = look.child;
			look.child = look.child->left;
		}
		else if (ToRight(pi, &(look.child->item)))
		{
			look.parrent = look.child;
			look.child = look.child->right;
		}
		else								/*此时必为相等的情况				*/
			break;							/*look.child是目标项目的节点的地址	*/
	}
	return look;							/*成功返回						*/
}

static void DeleteNode(Node **ptr)
{
	Node * temp;
	puts((*ptr)->item.petname);
	if ((*ptr)->left == NULL)
	{
		temp = *ptr;
		*ptr = (*ptr)->right;
		free(temp);
	}
	else if((*ptr)->right == NULL)
	{
		temp = *ptr;
		*ptr = (*ptr)->left;
		free(temp);
	}
	else									/*被删除节点有两个子节点			*/
	{
		/*找到右子树的依附位置				*/
		for (temp = (*ptr)->left; temp->right != NULL; temp = temp->right)
			continue;
		temp->right = (*ptr)->right;
		temp = *ptr;
		*ptr = (*ptr)->left;
		free(temp);
	}
}












