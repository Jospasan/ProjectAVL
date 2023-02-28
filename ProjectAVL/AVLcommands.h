#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
using namespace std;

class Node {
public:
	int height = 1; // start with 1 to account for the root
	string Name;
	string ufID;
	Node* Left;
	Node* Right;
	Node(string x, string y) : ufID(x), Name(y), Left(nullptr), Right(nullptr) {
	}
	Node() : ufID("number"), Name("name"), Left(nullptr), Right(nullptr) {
	}
};

class AVLTree {
public:
	bool checkID(string ufid); //fin
	bool checkName(string name); //fin
	int height(Node* r); //fin
	Node* updateHeight(Node* r); //fin
	Node* LR(Node* r); //fin
	Node* RR(Node* r); //fin
	void preorder(Node* r, bool& first); //fin
	void postorder(Node* r, bool& first); //fin
	void inorder(Node* r, bool& first); //fin
	Node* insertNameID(string name, string ufid, Node* r); //fin
	void nameSearch(Node* r, string name); //fin
	void ufidSearch(Node* r, int ufid); //fin
	Node* helperNode(Node* r); //fin
	void inorderNode(Node* r, int count, string& ufid); //fin
	Node* ufidDelete(Node* r, int ufid); //fin
	Node* inorderDelete(Node* r); //fin
	void printPre(Node* r); //fin
	void printPost(Node* r); //fin
	void printIn(Node* r); //fin
	void printlevelVal(Node* r); //fin
	Node* Insert(Node* r); //fin
	void Search(Node* r); //fin
	Node* Delete(Node* r); //fin
};

//catch cases to make sure the inputs are valid
bool AVLTree::checkID(string ufid) {
	for (int i = 0; i < ufid.length(); i++) {
		//check if the id is a num
		if (isdigit(ufid[i]) == false) {
			return false;
		}
		return true;
	}
}

bool AVLTree::checkName(string name) {
	for (int i = 0; i < name.length(); i++) {
		//check if name is not a num
		if (isdigit(name[i])) {
			return false;
		}
		return true;
	}
}

//height functions
int AVLTree::height(Node* r) {
	//check first if there is a root
	if (r == nullptr) {
		return 0;
	}
	return (r->height);

}

Node* AVLTree::updateHeight(Node* r) {
	//update the height after each insertion or deletion
	r->height = 1 + max(height(r->Left), height(r->Right));

	return r;
}

//rotation functions (left rotate and right rotate)
Node* AVLTree::LR(Node* r) { //make sure to update the heights for rotations that are made
	Node* Parent = r->Right;
	Node* Child = r->Right->Left;
	Parent->Left = r;
	r->Right = Child;

	r = updateHeight(r);
	Parent = updateHeight(Parent);

	return Parent;
}

Node* AVLTree::RR(Node* r) {
	Node* Parent = r->Left;
	Node* Child = Parent->Right;
	Parent->Right = r;
	r->Left = Child;

	r = updateHeight(r);
	Parent = updateHeight(Parent);

	return Parent;
}

void AVLTree::preorder(Node* r, bool& first) {
	if (r == nullptr) {
		return;
	}
	if (!first) {
		cout << ", ";
	}
	first = false;
	cout << r->Name;
	preorder(r->Left, first);
	preorder(r->Right, first);
}

void AVLTree::postorder(Node* r, bool& first) {
	if (r == nullptr) {
		return;
	}
	postorder(r->Left, first);
	postorder(r->Right, first);
	if (!first) {
		cout << ", ";
	}
	first = false;
	cout << r->Name;
}

void AVLTree::inorder(Node* r, bool& first) {
	if (r == nullptr) {
		return;
	}
	inorder(r->Left, first);
	if (!first) {
		cout << ", ";
	}
	first = false;
	cout << r->Name;
	inorder(r->Right, first);
}

//Insertion function

Node* AVLTree::insertNameID(string name, string ufid, Node* r) {
	if (r == nullptr) {
		cout << "successful" << endl; // if the insertion works

		return new Node(ufid, name);
	}

	if (stoi(ufid) == stoi(r->ufID)) {
		cout << "unsuccessful" << endl; // if the ufid is not unique (a doup)

		return r;
	}

	//go through the left and right of the tree depedning on the # size
	if (stoi(ufid) < stoi(r->ufID)) {
		r->Left = insertNameID(name, ufid, r->Left);
	}

	if (stoi(ufid) > stoi(r->ufID)) {
		r->Right = insertNameID(name, ufid, r->Right);
	}
	r = updateHeight(r);

	//rotate tree after insertion to balance if needed using the balance factor method (above 1 or below -1) 
	int bFactor = height(r->Left) - height(r->Right);

	//4 balance (1. LR, 2. RR, 3. LL, 4. RL)
	//1. 
	if (1 < bFactor && stoi(ufid) > (stoi(r->Left->ufID))) {
		r->Left = LR(r->Left);

		return RR(r);
	}
	//2. 
	if (1 < bFactor && stoi(ufid) < (stoi(r->Left->ufID))) {
		return RR(r);
	}
	//3. 
	if (-1 > bFactor && stoi(ufid) > (stoi(r->Right->ufID))) {
		return LR(r);
	}
	//4.
	if (-1 > bFactor && stoi(ufid) < (stoi(r->Right->ufID))) {
		r->Right = RR(r->Right);

		return LR(r);
	}

	return r;
}

//Search functions, **use queues**

void AVLTree::nameSearch(Node* r, string name) {
	if (r == nullptr) {
		cout << "unsuccessful" << endl;
		return;
	}

	queue<Node*> queue;
	queue.push(r);
	Node* search;
	bool found = false;

	while (!queue.empty()) { // run the queue until the search is found 
		if (queue.front()->Name == name) {
			found = true;
			search = queue.front();
			cout << search->ufID << endl;
		}

		if (queue.front()->Left) {
			queue.push(queue.front()->Left);
		}
		if (queue.front()->Right) {
			queue.push(queue.front()->Right);
		}

		queue.pop();
	}
	if (found == false) {
		cout << "unsuccessful" << endl;
		return;
	}
}

//print NAME not the UFID*****
void AVLTree::ufidSearch(Node* r, int ufid) {
	if (r == nullptr) {
		cout << "unsuccessful" << endl;
		return;
	}

	queue<Node*> queue;
	queue.push(r);
	Node* search;
	bool found = false;

	while (!queue.empty()) {
		string id = queue.front()->ufID;
		int check = (id.length() / 8);
		for (int i = 0; i < check; i++) {
			if (stoi(id.substr(0, 8)) == ufid) { //check to see if the string of the id found is the same one inputed
				found = true;
				search = queue.front();
				cout << search->Name << endl;
				return;
			}
			id = id.substr(8, id.length());
		}

		if (queue.front()->Left) {
			queue.push(queue.front()->Left);
		}
		if (queue.front()->Right) {
			queue.push(queue.front()->Right);
		}

		queue.pop();
	}
	if (found == false) {
		cout << "unsuccessful" << endl;
		return;
	}
}

//helper for when there is a node with two children that needs to be removed
Node* AVLTree::helperNode(Node* r) {
	Node* goleft = r;
	while (goleft && goleft->Left) {
		goleft = goleft->Left;
	}

	return goleft;
}

void AVLTree::inorderNode(Node* r, int count, string& ufid) {
	if (r == nullptr) {
		return;
	}
	static int temp = 0;
	if (temp <= count) {
		inorderNode(r->Left, count, ufid);
		temp++;
		if (temp == count) {
			ufid = r->ufID;
		}
		inorderNode(r->Right, count, ufid);
	}
}

//Delete functions, no need to rotate or balance

Node* AVLTree::ufidDelete(Node* r, int ufid) {
	if (r == nullptr) {
		return nullptr;
	}

	if (ufid < stoi(r->ufID.substr(0, 8))) { //left of tree
		r->Left = ufidDelete(r->Left, ufid);
	}
	else if (ufid > stoi(r->ufID.substr(0, 8))) {//right of tree
		r->Right = ufidDelete(r->Right, ufid);
	}
	else if (ufid == stoi(r->ufID.substr(0, 8))) {//delete with cases of children
		if (r->Left == nullptr && r->Right == nullptr) {//0
			delete r;
			r = nullptr;
		}
		else if (r->Left == nullptr) { //1 (left)
			Node* Temp = r;
			r = r->Right;
			delete Temp;
		}
		else if (r->Right == nullptr) {//1 (Right)
			Node* Temp = r;
			r = r->Left;
			delete Temp;
		}
		else {//2 (left and right)
			Node* Temp = helperNode(r->Right);
			r->ufID = Temp->ufID;
			r->Name = Temp->Name;
			r->Right = ufidDelete(r->Right, stoi(Temp->ufID));
		}
	}
	else {
		cout << "unsuccessful" << endl;

		return r;
	}
	return r;
}

Node* AVLTree::inorderDelete(Node* r) {
	AVLTree tree;
	string find;
	string id;
	cin >> find;
	int num = (stoi(find) + 1);
	tree.inorderNode(r, num, id);
	r = tree.ufidDelete(r, stoi(id));

	cout << "successful" << endl;
	return r;
}


//Print traversals
void AVLTree::printPre(Node* r) {
	bool first = true;
	AVLTree tree;
	tree.preorder(r, first);
	cout << endl;
}

void AVLTree::printPost(Node* r) {
	bool first = true;
	AVLTree tree;
	tree.postorder(r, first);
	cout << endl;
}

void AVLTree::printIn(Node* r) {
	bool first = true;
	AVLTree tree;
	tree.inorder(r, first);
	cout << endl;
}

void AVLTree::printlevelVal(Node* r) {
	if (r == nullptr) {
		cout << 0 << endl;
		return;
	}
	else {
		cout << 1 + max(height(r->Left), height(r->Right)) << endl;
		return;
	}
}

//print insertion, search, and delete
Node* AVLTree::Insert(Node* r) {
	AVLTree tree;
	string name;
	string id;
	Node* Temp = r;
	cin >> quoted(name);
	cin >> id;

	if (id.length() == 8 && tree.checkName(name) && tree.checkID(id)) {//make sure the ufid is 8 digits long
		r = tree.insertNameID(name, id, r);
	}
	else {
		cout << "unsuccessful" << endl;
	}
	return r;
}

//*use substr to get rid of the "" and spaces*
void AVLTree::Search(Node* r) {
	AVLTree tree;
	string find;
	getline(cin, find);

	if (tree.checkName(find.substr(2, (find.length() - 3)))) { //if its a name
		tree.nameSearch(r, find.substr(2, (find.length() - 3)));
	}
	else if (tree.checkID(find.substr(1, (find.length() - 1)))) { //if its a ufid
		if ((find.substr(1, (find.length() - 1))).length() == 8) {
			tree.ufidSearch(r, stoi(find.substr(1, (find.length() - 1))));
		}
	}
	else {
		cout << "unsuccessful" << endl;
	}
}

Node* AVLTree::Delete(Node* r) {
	AVLTree tree;
	string find;
	cin >> find;

	if (tree.checkID(find)) {
		r = tree.ufidDelete(r, atoi(find.c_str()));
		cout << "successful" << endl;
	}

	else {
		cout << "unsuccessful" << endl;
	}
	return r;
}
