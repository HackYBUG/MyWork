//---------------------------------------------------------------------------

#pragma hdrstop

#include "RedblackTree.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


/*
 * �Ժ�����Ľڵ�(x)��������ת
 *
 * ����ʾ��ͼ(�Խڵ�x��������)��
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(����)-->           / \                #
 *  lx   y                          x  ry
 *     /   \                       /  \
 *    ly   ry                     lx  ly
 *
 *
 */
 template<class T>
 void RBTree<T>::leftRotate(RBTNode<T>* &root,RBTNode<T>* x)
 {
	//����x���Һ���Ϊy
	RBTNode<T>* y = x->right;
	//����y�����ӣ�����Ϊ��x���Һ���"
	//���y�����ӷǿգ���x��Ϊ��y�����ӵĸ��ס�
	x->right = y->left;
	if(y->left != NULL)
		y->parent = x;
	//��x�ĸ�����ΪY�ĸ���
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
	//����x" ��Ϊ��Y�����ӡ�
	y->left = x;
	//����x�ĸ��ڵ�����Ϊy
	x->parent = y;

 }
 /*
 * �Ժ�����Ľڵ�(y)��������ת
 *
 * ����ʾ��ͼ(�Խڵ�y��������)��
 *            py                               py
 *           /                                /
 *          y                                x
 *         /  \      --(����)-->            /  \                     #
 *        x   ry                           lx   y
 *       / \                                   / \                   #
 *      lx  rx                                rx  ry
 *
 */
 template<class T>
 void RBTree<T>::rightRotate(RBTNode<T>* &root, RBTNode<T>* y)
 {
	 //��y����������Ϊ x
	 RBTNode<T>* x = y->left;
	 //��x���Һ�������Ϊy�����ӣ�
	 //���x���Һ��ӷǿգ������ĸ��ڵ�����Ϊy
	 y->left = x->right;
	 if(x->right != NULL)  x->right->parent = y;
	 //��Y�ĸ�������Ϊx�ĸ��ڵ�
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
	 //��x���ҽڵ�����Ϊy
	 x->right = y;
	 //��y�ĸ��ڵ�����Ϊ x
	 y->parent = x;

 }


/*
 * �������뵽�������
 *
 * ����˵����
 *     root ������ĸ����
 *     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�node
 */
 template<class T>
 void RBTree<T>::insert(RBTNode<T>* &root, RBTNode<T>* node)
 {
	RBTNode<T>* y = NULL;
	RBTNode<T> *x = root;
	// 1. �����������һ�Ŷ�������������ڵ����ӵ�����������С�
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
	//���ýڵ���ɫΪ��ɫ
	node->color = RED;
	//������������Ϊһ�Ŷ����ѯ��
 //	node->



 }
 /*
 * �����(keyΪ�ڵ��ֵ)���뵽�������
 *
 * ����˵����
 *     tree ������ĸ����
 *     key ������ļ�ֵ
 */
 template<class T>
 void RBTree<T>::insert(T key)
 {
	 RBTNode<T> *z = NULL;
	 //����½ڵ�ʧ�ܣ��򷵻�
	 if((z = new RBTNode<T>(key,BLACK,NULL,NULL,NULL)) == NULL)
		return ;
	 insert(mRoot,z);
 }
 /*
 * �����������������
 *
 * ���������в���ڵ�֮��(ʧȥƽ��)���ٵ��øú�����
 * Ŀ���ǽ������������һ�ź������
 *
 * ����˵����
 *     root ������ĸ�
 *     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�z
 */
 template<class T>
 void RBTree<T>::insertFixUp(RBTNode<T>* &root,RBTNode<T> *node)
 {
	RBTNode<T> *parent, *gparent;
	// �������ڵ���ڣ����Ҹ��ڵ����ɫ�Ǻ�ɫ��
	while((parent = rb_parent(node)) && rb_is_Red(parent))
	{
	   gparent = rb_parent(parent);

	   //�������ڵ㡰���游������
	   if( parent  == gparent->left)
	   {
			RBTNode<T> *uncle = gparent->right;
			// Case 1����������ڵ��Ǻ�ɫ
			if(uncle && rb_is_Red(uncle))
			{
				rb_set_black(uncle)
				rb_set_black(parent);
				rb_set_red(gparent);
				node = gparent;
				continue;
			}
			// Case 2�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ���
			if(parent->right == node)
			{
				RBTNode<T> *tmp;
				leftRotate(root,parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			else
			{  // Case 3�����������Ǻ�ɫ���ҵ�ǰ�ڵ������ӡ�
				rb_is_black(parent);
				rb_set_red(gparent);
				rightRotate(root,gparent);
			}
	   }
	   else //����z�ĸ��ڵ㡱�ǡ�z���游�ڵ���Һ��ӡ�
	   {
			RBTNode<T> *uncle = gparent->left;

			// Case 1����������ڵ��Ǻ�ɫ
			if(uncle && rb_is_red(uncle))
			{
				rb_set_black(uncle)
				rb_set_black(parent);
				rb_set_red(gparent);
				node = gparent;
				continue;
			}
			else{
				// Case 2�����������Ǻ�ɫ���ҵ�ǰ�ڵ�������
				if(parent->left == node)
				{
					RBTNode<T> *tmp;
					rightRotate(root,parent);
					tmp = parent;
					parent = node;
					node = tmp;
				}
				else
				{  // Case 3�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ��ӡ�
					rb_is_black(parent);
					rb_set_red(gparent);
					leftRotate(root, gparent);
				}
			}
	   }

	}
	// �����ڵ���Ϊ��ɫ
	rb_set_black(root);

 }