// AvlTree class - implements a basic dictionary/table ADT 
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// Comparable find( x )   --> Return item that matches x
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree structure (including deleted nodes)
// void traverse(process) --> Apply function process to each node's data in sorted order


#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

// Node and forward declaration for AvlTree to give it friend access in AvlNode

#include <list>

template <class Comparable>
class AvlTree;

struct WordInfo
{
	std::list<int> lines;
	std::list<int> pages;
	int occurence = 1;
};

template <class Comparable>
class AvlNode
{
	Comparable element;
	AvlNode   *left;
	AvlNode   *right;
	int        height;
	WordInfo info;
	bool erased = false;
	AvlNode(const Comparable & theElement, AvlNode *lt, AvlNode *rt, int h = 0)
		: element(theElement), left(lt), right(rt), height(h) { }
	friend class AvlTree<Comparable>;
};


template <class Comparable>
class AvlTree
{
public:
	explicit AvlTree(const Comparable & notFound);

	AvlTree(const AvlTree & rhs);
	const AvlTree & operator=(const AvlTree & rhs);
	~AvlTree();

	const Comparable & find(const Comparable & x) const;
	bool isEmpty() const;
	void printTree() const;

	void insert(const Comparable & x);
	void remove(const Comparable & x);
	void makeEmpty();
	int size() const ; //error file
	void traverse(void f(Comparable &, int, std::list<int>, std::list<int>)); //error file
	void incOccurence(const Comparable & e);
	int getOccurence(const Comparable & e) const;
	void setLines(int l, const Comparable & e);
	std::list<int> getLines(const Comparable & e) const;
	void setPages(int l, const Comparable & e);
	std::list<int> getPages(const Comparable & e) const;

private:
	// data members
	AvlNode<Comparable> *root;
	const Comparable ITEM_NOT_FOUND;
	int numberOfNodes = 0;

	// private counterparts of public methods - all require a ptr to root of current (sub)tree

	AvlNode<Comparable> * find(const Comparable & x, AvlNode<Comparable> *t) const;
	void printTree(AvlNode<Comparable> *t, int depth) const;

	void traverse(void f(Comparable &, int, std::list<int>, std::list<int>), AvlNode<Comparable> * & t);
	void insert(const Comparable & x, AvlNode<Comparable> * & t);
	void remove(const Comparable & x, AvlNode<Comparable> * & t);
	void makeEmpty(AvlNode<Comparable> * & t);

	// helper methods
	AvlNode<Comparable> * clone(AvlNode<Comparable> *t) const;
	const Comparable & elementAt(AvlNode<Comparable> *t) const;
	int height(AvlNode<Comparable> *t) const;
	int max(int lhs, int rhs) const;
	void rotateWithLeftChild(AvlNode<Comparable> * & k2);
	void rotateWithRightChild(AvlNode<Comparable> * & k1);
	void doubleWithLeftChild(AvlNode<Comparable> * & k3);
	void doubleWithRightChild(AvlNode<Comparable> * & k1);
};

#include "AvlTree.cpp"
#endif
