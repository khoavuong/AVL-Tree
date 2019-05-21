/* Copyright (C) 2018
* Course: CO2003
* Author: Rang Nguyen
* Ho Chi Minh City University of Technology
*/

#include "pch.h"
#include "TreeSet.h"

TreeSet::TreeSet()
{
	root = NULL;
	count = 0;
}
TreeSet::~TreeSet()
{
	clear();
}

bool isPowerOfTwo(int n)
{
	if (n == 0)
		return false;
	while (n != 1)
	{
		if (n % 2 != 0)
			return 0;
		n = n / 2;
	}
	return true;
}

void TreeSet::clearRec(AVLNode* root) {
	if (root != NULL) {
		clearRec(root->left);
		clearRec(root->right);
		delete root;
	}
}
void TreeSet::clear() {
	clearRec(root);
	root = NULL;
	count = 0;
}
void TreeSet::rotateLeft(AVLNode *&root)
{
	AVLNode *temp = root->right;
	root->right = root->right->left;
	temp->left = root;
	root = temp;
}
void TreeSet::rotateRight(AVLNode *&root)
{
	AVLNode *temp = root->left;
	root->left = root->left->right;
	temp->right = root;
	root = temp;
}
void TreeSet::leftBalance(AVLNode *&root)
{
	AVLNode *leftTree = root->left;
	if (leftTree->balance != 1)
	{
		rotateRight(root);
		root->balance = 0;
		root->right->balance = 0;
	}
	else
	{
		AVLNode *rightTree = leftTree->right;
		if (rightTree->balance == -1)
		{
			root->balance = 1;
			leftTree->balance = 0;
		}
		else if (rightTree->balance == 0)
		{
			root->balance = 0;
			leftTree->balance = 0;
		}
		else
		{
			root->balance = 0;
			leftTree->balance = -1;
		}

		rightTree->balance = 0;
		rotateLeft(root->left);
		rotateRight(root);
	}
}
void TreeSet::rightBalance(AVLNode *&root)
{
	AVLNode *rightTree = root->right;
	if (rightTree->balance != -1)
	{
		rotateLeft(root);
		root->balance = 0;
		root->left->balance = 0;
	}
	else
	{
		AVLNode *leftTree = rightTree->left;
		if (leftTree->balance == 1)
		{
			root->balance = -1;
			rightTree->balance = 0;
		}
		else if (leftTree->balance == 0)
		{
			root->balance = 0;
			rightTree->balance = 0;
		}
		else
		{
			root->balance = 0;
			rightTree->balance = 1;
		}

		leftTree->balance = 0;
		rotateRight(root->right);
		rotateLeft(root);
	}
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------

bool TreeSet::add(AVLNode *&root, int val)
{
	if (root == NULL)
	{
		AVLNode *newNode = new AVLNode(val);
		root = newNode;
		count++;
		return true;
	}

	if (val == root->key)
	{
		return false;
	}

	if (val < root->key)
	{
		if (add(root->left, val) == true) // insert -> sau do neu cay cao len.
		{
			if (root->balance == -1)
			{
				leftBalance(root);
				return false;
			}
			else if (root->balance == 0)
			{
				root->balance = -1;
				return true;
			}
			else
			{
				root->balance = 0;
				return false;
			}
		}
	}

	else if (add(root->right, val) == true) // insert -> sau do neu cay cao len.
	{
		if (root->balance == -1)
		{
			root->balance = 0;
			return false;
		}
		else if (root->balance == 0)
		{
			root->balance = 1;
			return true;
		}
		else
		{
			rightBalance(root);
			return false;
		}
	}
}

bool TreeSet::add(int val) {
	// TODO
	return add(root, val);
}

//-----------------------------------------------------------------------------------------

bool TreeSet::remove(AVLNode *&root, int val)
{
	if (root == NULL) return false;
	if (root->key == val)
	{
		if (root->left == NULL && root->right == NULL)
		{
			delete root;
			root = NULL;
			count--;
			return true;
		}

		if (root->left == NULL && root->right != NULL)
		{
			AVLNode *temp = root;
			root = root->right;
			delete temp;
			count--;
			return true;
		}

		if (root->left != NULL && root->right == NULL)
		{
			AVLNode *temp = root;
			root = root->left;
			delete temp;
			count--;
			return true;
		}

		AVLNode *temp = root->right;
		while (temp->left != NULL) temp = temp->left;
		root->key = temp->key;

		if (remove(root->right, temp->key) == true)
		{
			if (root->balance == 1)
			{
				root->balance = 0;
				return true;
			}
			else if (root->balance == 0)
			{
				root->balance = -1;
				return false;
			}
			else
			{
				leftBalance(root);
				if (isPowerOfTwo(count + 1)) return true;
				return false;
			}
		}
		return false;
	}

	if (val < root->key)
	{
		if (remove(root->left, val) == true)
		{
			if (root->balance == -1)
			{
				root->balance = 0;
				return true;
			}
			else if (root->balance == 0)
			{
				root->balance = 1;
				return false;
			}
			else
			{
				rightBalance(root);
				if (isPowerOfTwo(count+1)) return true;
				return false;
			}
		}
	}

	else if (remove(root->right, val) == true)
	{
		if (root->balance == 1)
		{
			root->balance = 0;
			return true;
		}
		else if (root->balance == 0)
		{
			root->balance = -1;
			return false;
		}
		else
		{
			leftBalance(root);
			if (isPowerOfTwo(count + 1)) return true;
			return false;
		}
	}
}

bool TreeSet::remove(int val) {
	// TODO
	return remove(root, val);
}

//-----------------------------------------------------------------------------------------

bool TreeSet::contains(AVLNode *root, int val)
{
	if (root == NULL) return false;
	if (root->key == val) return true;
	if (val < root->key) return contains(root->left, val);
	else return contains(root->right, val);
}

bool TreeSet::contains(int val) {
	// TODO
	return contains(root, val);
}

//-----------------------------------------------------------------------------------------

void TreeSet::copy(AVLNode *&root, AVLNode *set_root)
{
	if (set_root == NULL) return;
	root = new AVLNode(set_root->key);
	copy(root->right, set_root->right);
	copy(root->left, set_root->left);
}

void TreeSet::copy(const TreeSet& set) {
	// TODO
	copy(root, set.root);
	count = set.count;
}

//-----------------------------------------------------------------------------------------

int TreeSet::first() {	
	if (root == NULL) {
		throw "NoSuchElementException";
	}

	// TODO
	AVLNode *temp = root;
	while (temp->left != NULL)
		temp = temp->left;
	return temp->key;
}

int TreeSet::last() {
	if (root == NULL) {
		throw "NoSuchElementException";
	}

	// TODO
	AVLNode *temp = root;
	while (temp->right != NULL)
		temp = temp->right;
	return temp->key;
}

//-----------------------------------------------------------------------------

void TreeSet::higher(AVLNode *root, int val, int &temp)
{
	if (root == NULL) return;
	if (root->key > val) temp = root->key;
	if (val < root->key) higher(root->left, val, temp);
	else higher(root->right, val, temp);
}

int TreeSet::higher(int val) {
	// TODO
	int temp = -1;
	higher(root, val, temp); 
	return temp;
}

//-----------------------------------------------------------------------------

void TreeSet::lower(AVLNode *root, int val, int &temp)
{
	if (root == NULL) return;
	if (root->key < val) temp = root->key;
	if (val <= root->key) lower(root->left, val, temp);
	else lower(root->right, val, temp);
}

int TreeSet::lower(int val) {
	// TODO
	int temp = -1;
	lower(root, val, temp);
	return temp;
}

//-----------------------------------------------------------------------------------------

void TreeSet::subSet(TreeSet *&subTree, int fromVal, int toVal, AVLNode *root)
{
	if (root == NULL) return;

	if (root->key >= fromVal && root->key < toVal) subTree->add(root->key);

	if (root->key > fromVal) subSet(subTree, fromVal, toVal, root->left);
	if (root->key < toVal) subSet(subTree, fromVal, toVal, root->right);
}

TreeSet* TreeSet::subSet(int fromVal, int toVal) {
	// TODO
	TreeSet *subTree = new TreeSet();
	subSet(subTree, fromVal, toVal, root);
	return subTree;
}

//-----------------------------------------------------------------------------------------

int TreeSet::size() {
	// TODO
	return count;
}

/*

note: Co the cai thien:
_ goi de quy return / khong return ?
_ dieu kien subset co phai AVL?

*/