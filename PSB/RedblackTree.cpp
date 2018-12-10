//---------------------------------------------------------------------------

#pragma hdrstop

#include "RedblackTree.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


/*
 * 对红黑树的节点(x)进行左旋转
 *
 * 左旋示意图(对节点x进行左旋)：
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(左旋)-->           / \                #
 *  lx   y                          x  ry
 *     /   \                       /  \
 *    ly   ry                     lx  ly
 *
 *
 */
 template<class T>
 void RBTree<T>::leftRotate(RBTNode<T>* &root,RBTNode<T>* x)
 {
	//设置x的右孩子为y
	RBTNode<T>* y = x->right;
	//将“y的左孩子，设置为”x的右孩子"
	//如果y的左孩子非空，将x设为“y的左孩子的父亲”
	x->right = y->left;
	if(y->left != NULL)
		y->parent = x;
	//将x的父亲设为Y的父亲
	y->parent = x->parent;
	if(x->parent == NULL)
	{
		root = y;
	}
	else
	{
		if(x->parent->left == x)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	//将“x" 设为“Y的左孩子”
	y->left = x;
	//将“x的父节点设置为y
	x->parent = y;

 }
 /*
 * 对红黑树的节点(y)进行右旋转
 *
 * 右旋示意图(对节点y进行左旋)：
 *            py                               py
 *           /                                /
 *          y                                x
 *         /  \      --(右旋)-->            /  \                     #
 *        x   ry                           lx   y
 *       / \                                   / \                   #
 *      lx  rx                                rx  ry
 *
 */
 template<class T>
 void RBTree<T>::rightRotate(RBTNode<T>* &root, RBTNode<T>* y)
 {
	 //将y的左孩子设置为 x
	 RBTNode<T>* x = y->left;
	 //将x的右孩子设置为y的左孩子，
	 //如果x的右孩子非空，将它的父节点设置为y
	 y->left = x->right;
	 if(x->right != NULL)  x->right->parent = y;
	 //将Y的父亲设置为x的父节点
	 x->parent = y->parent;
	 if(y->parent == NULL)
	 {
		 root = x;
	 }
	 else
	 {
		 if(y->parent->left == y)
			y->parent->left = x;
		 else
			y->parent->right = x;
	 }
	 //将x的右节点设置为y
	 x->right = y;
	 //将y的父节点设置为 x
	 y->parent = x;

 }


/*
 * 将结点插入到红黑树中
 *
 * 参数说明：
 *     root 红黑树的根结点
 *     node 插入的结点        // 对应《算法导论》中的node
 */
 template<class T>
 void RBTree<T>::insert(RBTNode<T>* &root, RBTNode<T>* node)
 {
	RBTNode<T>* y = NULL;
	RBTNode<T> *x = root;
	// 1. 将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
	while(x != NULL)
	{
		y = x;
		if(node->key > x->key)
			x = x->right;
		else
			x = x->left;
	}
	node->parent = y;
	if(y != NULL)
	{
		if(node->key < y->key)
			y->left = node;
		else
			y->right = node;
	}
	else
	{
		root = node;
	}
	//设置节点颜色为红色
	node->color = RED;
	//将它重新修正为一颗二叉查询数
 //	node->



 }
 /*
 * 将结点(key为节点键值)插入到红黑树中
 *
 * 参数说明：
 *     tree 红黑树的根结点
 *     key 插入结点的键值
 */
 template<class T>
 void RBTree<T>::insert(T key)
 {
	 RBTNode<T> *z = NULL;
	 //如果新节点失败，则返回
	 if((z = new RBTNode<T>(key,BLACK,NULL,NULL,NULL)) == NULL)
		return ;
	 insert(mRoot,z);
 }
 /*
 * 红黑树插入修正函数
 *
 * 在向红黑树中插入节点之后(失去平衡)，再调用该函数；
 * 目的是将它重新塑造成一颗红黑树。
 *
 * 参数说明：
 *     root 红黑树的根
 *     node 插入的结点        // 对应《算法导论》中的z
 */
 template<class T>
 void RBTree<T>::insertFixUp(RBTNode<T>* &root,RBTNode<T> *node)
 {
	RBTNode<T> *parent, *gparent;
	// 若“父节点存在，并且父节点的颜色是红色”
	while((parent = rb_parent(node)) && rb_is_Red(parent))
	{
	   gparent = rb_parent(parent);

	   //若”父节点“是祖父的左孩子
	   if( parent  == gparent->left)
	   {
			RBTNode<T> *uncle = gparent->right;
			// Case 1条件：叔叔节点是红色
			if(uncle && rb_is_Red(uncle))
			{
				rb_set_black(uncle)
				rb_set_black(parent);
				rb_set_red(gparent);
				node = gparent;
				continue;
			}
			// Case 2条件：叔叔是黑色，且当前节点是右孩子
			if(parent->right == node)
			{
				RBTNode<T> *tmp;
				leftRotate(root,parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			else
			{  // Case 3条件：叔叔是黑色，且当前节点是左孩子。
				rb_is_black(parent);
				rb_set_red(gparent);
				rightRotate(root,gparent);
			}
	   }
	   else //若“z的父节点”是“z的祖父节点的右孩子”
	   {
			RBTNode<T> *uncle = gparent->left;

			// Case 1条件：叔叔节点是红色
			if(uncle && rb_is_red(uncle))
			{
				rb_set_black(uncle)
				rb_set_black(parent);
				rb_set_red(gparent);
				node = gparent;
				continue;
			}
			else{
				// Case 2条件：叔叔是黑色，且当前节点是左孩子
				if(parent->left == node)
				{
					RBTNode<T> *tmp;
					rightRotate(root,parent);
					tmp = parent;
					parent = node;
					node = tmp;
				}
				else
				{  // Case 3条件：叔叔是黑色，且当前节点是右孩子。
					rb_is_black(parent);
					rb_set_red(gparent);
					leftRotate(root, gparent);
				}
			}
	   }

	}
	// 将根节点设为黑色
	rb_set_black(root);

 }
