#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <cstddef>

template <class T>
class BinaryTree;

template <class T>
class TreeNode {
public:
    TreeNode(T el, TreeNode<T>* lf=NULL, TreeNode<T>* rt=NULL)
	    :elem(el), left(lf), right(rt) { }
    TreeNode<T>* getLeft() const
        { return left; }
    TreeNode<T>* getRight() const
        { return right; }
    T getElem() const
        { return elem; }
    int size(TreeNode<T>* iter) const;
    int height(TreeNode<T>* iter) const;
    TreeNode<T>* copy();
private:
    T elem;
    TreeNode<T> *left, *right;
    friend class BinaryTree<T>;
};

template <class T>
int TreeNode<T>::size(TreeNode<T>* iter) const {
    if(iter == NULL)
        return 0;
    return 1 + size(iter->left) + size(iter->right);
}

template <class T>
int TreeNode<T>::height(TreeNode<T>* iter) const {
    if(iter == NULL)
        return -1;
    int lth = height(iter->left);
    int rth = height(iter->right);
    return (lth > rth) ? 1+lth : 1+rth;
}

template <class T>
TreeNode<T>* TreeNode<T>::copy() {
	TreeNode<T>* root = new TreeNode<T>(elem);
	if(left != NULL)
	    root->left = left->copy();
	if(right != NULL)
	    root->right = right->copy();
    return root;
}

template <class T>
class BinaryTree {
public:
    BinaryTree()
        :root(NULL) { }
    BinaryTree(T el)
        { root = new TreeNode<T>(el); }
    ~BinaryTree()
        { deleteTree(root); root = NULL; }
    TreeNode<T>* getRoot() const
        { return root; }
    bool isEmpty() const
        { return root==NULL; }
    int size() const 
        { return (root==NULL) ? 0 : root->size(root); }
    int height() const 
        { return (root==NULL) ? 0 : root->height(root); }
    void copy(BinaryTree<T>& rhs);
    void merge(int el, BinaryTree<T>& lt, BinaryTree<T>& rt);
private:
    TreeNode<T>* root;
    void deleteTree(TreeNode<T>* root);
};

template <class T>
void BinaryTree<T>::merge(T el, BinaryTree<T>& lt, BinaryTree<T>& rt) {
	if(lt.getRoot() == rt.getRoot() && lt.getRoot() != NULL) {
		cerr << "Trees are the same, merge aborted" << endl;
		return;
	}
	if(this != &lt && this != &rt)
	    deleteTree(root);
	root = new TreeNode<T>(el,lt.getRoot(),rt.getRoot());
	if(this != &lt)  lt.root = NULL;
	if(this != &rt)  rt.root = NULL;
}

template <class T>
void BinaryTree<T>::deleteTree(TreeNode<T>* root) {
	if(root == NULL)  return;
	if(root->left != NULL)
	    deleteTree(root->left);
	if(root->right != NULL)
	    deleteTree(root->right);
	delete root;
}

#endif
