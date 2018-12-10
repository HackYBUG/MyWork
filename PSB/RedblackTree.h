//---------------------------------------------------------------------------

#ifndef RedblackTreeH
#define RedblackTreeH
//---------------------------------------------------------------------------
/*
*(1) ÿ���ڵ�����Ǻ�ɫ�������Ǻ�ɫ��
*(2) ���ڵ��Ǻ�ɫ��
*(3) ÿ��Ҷ�ӽڵ��Ǻ�ɫ�� [ע�⣺����Ҷ�ӽڵ㣬��ָΪ�յ�Ҷ�ӽڵ㣡]
*(4) ���һ���ڵ��Ǻ�ɫ�ģ��������ӽڵ�����Ǻ�ɫ�ġ�
*(5) ��һ���ڵ㵽�ýڵ������ڵ������·���ϰ�����ͬ��Ŀ�ĺڽڵ㡣
*/

enum RBTColor{RED,BLACK};

template<class T>
class RBTNode{
	public:
		RBTColor color;		//��ɫ
		T	key;            //�ؼ���
		RBTNode *left; 		//����
		RBTNode *right;		//�Һ���
		RBTNode *parent;	//���ڵ�

		RBTNode(T value, RBTColor c,RBTNode *p, RBTNode *l,RBTNode *r):key(value),
		color(c),parent(p),left(l),right(r){}
};

template<class T>
class RBTree{
	private:
		RBTNode<T> *mRoot; 		//���ڵ�
	public:
		RBTree();
		~RBTree();

         //�����(keyΪ�ڵ��ֵ)���뵽�������
		 void insert(T key);


	private:
		//�ڲ��ӿ� -- insert(root, node)�������ǽ�"node"�ڵ���뵽������С����У�root�Ǹ���node�Ǳ�����ڵ㡣
		//�ⲿ�ӿ� -- insert(key)�������ǽ�"key"��ӵ�������С�
		void insert(RBTNode<T>* &root, RBTNode<T>* node);
		//����
		void insertFixUp(RBTNode<T>* &root,RBTNode<T> *node);
		//����
		void leftRotate(RBTNode<T>* &root,RBTNode<T>* x);
		//����
		void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);


#define rb_parent(r)    ((r)->parent)
#define rb_color(r)		((r)->color)
#define rb_is_red(r)	((r)->color == RED)
#define rb_is_black(r)	((r)->color == BLACK)
#define rb_set_black(r) do {(r)->color = BLACK;} while(0)
#define rb_set_red(r)	do {(r)->color = RED;}   while(0)
#define rb_set_parent(r,p) do{(r)->parent = (p);} while(0)
#define rb_set_color(r,c)  do{(r)->color = (c);}  while(0)

};


#endif
