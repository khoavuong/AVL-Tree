/* Copyright (C) 2018
* Course: CO2003
* Author: Rang Nguyen
* Ho Chi Minh City University of Technology
*/

#pragma once
#include"AVLNode.h"
class TreeSet
{
private:
	AVLNode *root;
	int count;

protected:
	void clearRec(AVLNode *root);
	//---------------------------------
	void rotateLeft(AVLNode *&root);
	void rotateRight(AVLNode *&root);
	void leftBalance(AVLNode *&root);
	void rightBalance(AVLNode *&root);
	//---------------------------------
	bool add(AVLNode *&root, int val);
	bool remove(AVLNode *&root, int val);
	bool contains(AVLNode *root, int val);
	void copy(AVLNode *&root, AVLNode *set_root);
	void subSet(TreeSet *&subTree, int fromVal, int toVal, AVLNode *root);
	void higher(AVLNode *root, int val, int &temp);
	void lower(AVLNode *root, int val, int &temp);
public:
	TreeSet();
	~TreeSet();
	void clear();
	// print out the set in ascending order
	friend ostream& operator<<(ostream& os, const TreeSet& t);

	// YOUR TASKS START HERE	
	bool add(int val);		
	bool contains(int val);
	void copy(const TreeSet& set);
	int first();
	int higher(int val);
	int last();
	int lower(int val);
	bool remove(int val);
	TreeSet* subSet(int fromVal, int toVal);
	int size();
	// END HERE
};

