#include<iostream>
using namespace std;
template <class T>
struct node
{
	T data;
	node<T>* left;
	node<T>* right;
	node(T val)
	{
		data = val;
		left = NULL;
		right = NULL;
	}
};
template <class T>
class BST
{
public:
	node<T>* Root;
	T count;
	BST();
	~BST();
	void Insert(T val);
	void deleteNode(T Val, node<T>*& Ptr);
	void makeDeletion(node<T>*& Ptr);
	void Search(T data);
	void MaxValue(node<T>* tmp);
	void MinValue(node<T>* tmp);
	void inorderTraversal(node<T>* Temp);
	void preorderTraversal(node<T>* Temp);
	void postorderTraversal(node<T>* Temp);
	T treeheight(node<T>* r);
	T treeNodeCount();
	T getLeafCount(node<T>* node);
	void printGivenLevel(node<T>* r, T level);
	node<T>* MinHeightTree(T arr[], T start, T end);
private:
};
template <class T>
BST<T>::BST()
{
	Root = NULL;
}
template <class T>
node<T>* BST<T>::MinHeightTree(T arr[], T start, T end)
{
	if (start > end)
		return NULL;
	int mid = (start + end) / 2;
	int dat = arr[mid];//iserted as root node
	node <T>* n = new node<T>(dat);
	this->Insert(dat);
	n->left = MinHeightTree(arr, start, mid - 1);
	n->right = MinHeightTree(arr, mid + 1, end);

	return n;
}
template<class T>
BST<T>::~BST() {}
template <class T>
T BST<T>::treeNodeCount()
{
	return count;
}
template<class T>
T BST<T>::treeheight(node<T>* r)
{
	int hei;
	if (r == NULL)
	{
		return -1;
	}
	else
	{

		int leftheight = treeheight(r->left);
		int rightheight = treeheight(r->right);
		if (leftheight > rightheight)
			hei = (leftheight + 1);
		else hei = (rightheight + 1);
		return hei;
	}
}
template <class T>
void BST<T>::Insert(T val)
{
	node<T>* temp = Root;
	node<T>* n = new node<T>(val);
	if (temp == NULL)
	{
		Root = n;
		count++;
		cout << "\nValue Inserted \n";
		return;
	}
	else
	{
		while (temp != NULL)
		{
			if (n->data < temp->data && temp->left == NULL)
			{
				temp->left = n;
				cout << "\nValue Inserted \n";
				count++;
				return;
			}
			else if (n->data < temp->data)
			{
				temp = temp->left;
			}
			else if (n->data > temp->data && temp->right == NULL)
			{
				temp->right = n;
				cout << "\nValue Inserted \n";
				count++;
				return;
			}
			else if (n->data > temp->data)
			{
				temp = temp->right;
			}
			else
			{
				cout << "\nDuplicate Values are not Allowed\n";
				return;
			}

		}
	}
}
template<class T>
void BST<T>::inorderTraversal(node<T>* Temp)
{
	if (Temp == NULL)
	{
		return;
	}
	inorderTraversal(Temp->left);
	cout << Temp->data << "  ";
	inorderTraversal(Temp->right);

}
template <class T>
void BST<T>::preorderTraversal(node<T>* Temp)
{
	if (Temp == NULL)
	{
		return;
	}
	cout << Temp->data << "  ";
	preorderTraversal(Temp->left);
	preorderTraversal(Temp->right);
}
template <class T>
void BST<T>::postorderTraversal(node<T>* Temp)
{
	if (Temp == NULL)
	{
		return;
	}
	postorderTraversal(Temp->left);
	postorderTraversal(Temp->right);
	cout << Temp->data << "  ";
}
template <class T>
void BST<T>::Search(T data)
{
	node<T>* temp = Root;
	while (temp != NULL)
	{
		if (temp->data == data)
		{
			cout << "\nData found \nData = " << temp->data << " ";
			return;
			cout << endl;
		}
		else if (temp->data > data)
			temp = temp->left;
		else
			temp = temp->right;
	}
	cout << "\nData not found";
	return;
}
template <class T>
void BST<T>::MaxValue(node<T>* tmp)
{
	tmp = Root;
	while (tmp->right != NULL)
	{
		tmp = tmp->right;
	}
	cout << "\nMaximum Value  " << tmp->data;
	cout << "\n";
}
template <class T>
void BST<T>::MinValue(node<T>* tmp)
{
	tmp = Root;
	while (tmp->left != NULL)
	{
		tmp = tmp->left;
	}
	cout << "\nMinimum Value   " << tmp->data;
}
template <class T>
void BST<T>::deleteNode(T Val, node<T>*& Ptr)
{
	if (Ptr == NULL) // node does not exist in the tree
	{
		cout << Val << "Tree is Empty\n";
		return;
	}
	else if (Val < Ptr->data)
		deleteNode(Val, Ptr->left);
	else if (Val > Ptr->data)
		deleteNode(Val, Ptr->right);
	else
		makeDeletion(Ptr);
}
template <class T>
void BST<T>::makeDeletion(node<T>*& Ptr)
{
	node<T>* Temp;
	if (Ptr->right == NULL) {
		Temp = Ptr;
		Ptr = Ptr->left;
		delete Temp;
		cout << "\nValue Deleted\n";
		count--;
	}
	else if (Ptr->left == NULL)
	{ // case for one (right) child
		Temp = Ptr;
		Ptr = Ptr->right;
		count--;
		delete Temp;
	}
	else
	{ // case for two children.
		Temp = Ptr->right;
		while (Temp->left)
		{
			Temp = Temp->left;
		}
		Temp->left = Ptr->left;
		Temp = Ptr;
		Ptr = Ptr->right;
		count--;
		delete Temp;
	}
}
template <class T>
void BST<T>::printGivenLevel(node<T>* r, T level)
{
	if (r == NULL)
	{
		cout << "\ntree empty\n";
		return;
	}//root data 
	else if (level == 0)
		cout << r->data << " ";
	else {
		printGivenLevel(r->left, level - 1);
		printGivenLevel(r->right, level - 1);
	}
}

template <class T>
T BST<T>::getLeafCount(node<T>* node)
{
	T leaf = 0;
	if (node == NULL)
	{
		return 0;
	}
	if (node->left == NULL && node->right == NULL)
		return 1;
	else
		leaf = (getLeafCount(node->left) + getLeafCount(node->right));
	return leaf;
}
