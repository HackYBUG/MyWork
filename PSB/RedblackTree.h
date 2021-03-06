//---------------------------------------------------------------------------

#ifndef RedblackTreeH
#define RedblackTreeH
//---------------------------------------------------------------------------
/*
*(1) 每个节点或者是黑色，或者是红色。
*(2) 根节点是黑色。
*(3) 每个叶子节点是黑色。 [注意：这里叶子节点，是指为空的叶子节点！]
*(4) 如果一个节点是红色的，则它的子节点必须是黑色的。
*(5) 从一个节点到该节点的子孙节点的所有路径上包含相同数目的黑节点。
*/

enum RBTColor{RED,BLACK};

template<class T>
class RBTNode{
	public:
		RBTColor color;		//颜色
		T	key;            //关键字
		RBTNode *left; 		//左孩子
		RBTNode *right;		//右孩子
		RBTNode *parent;	//父节点

		RBTNode(T value, RBTColor c,RBTNode *p, RBTNode *l,RBTNode *r):key(value),
		color(c),parent(p),left(l),right(r){}
};

template<class T>
class RBTree{
	private:
		RBTNode<T> *mRoot; 		//根节点
	public:
		RBTree();
		~RBTree();

         //将结点(key为节点键值)插入到红黑树中
		 void insert(T key);


	private:
		//内部接口 -- insert(root, node)的作用是将"node"节点插入到红黑树中。其中，root是根，node是被插入节点。
		//外部接口 -- insert(key)的作用是将"key"添加到红黑树中。
		void insert(RBTNode<T>* &root, RBTNode<T>* node);
		//修正
		void insertFixUp(RBTNode<T>* &root,RBTNode<T> *node);
		//左旋
		void leftRotate(RBTNode<T>* &root,RBTNode<T>* x);
		//右旋
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
