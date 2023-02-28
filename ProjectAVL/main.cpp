#include "AVLcommands.h" 
using namespace std;

int main() {

	AVLTree tree;
	string call;
	int op;
	Node* r = nullptr;
	cin >> op;

	for (int i = 0; i < op; i++) {
		cin >> call;
		if (call == "insert") {
			r = tree.Insert(r);
		}
		else if (call == "search") {
			tree.Search(r);
		}
		else if (call == "remove") {
			r = tree.Delete(r);
		}
		else if (call == "removeInorder") {
			r = tree.inorderDelete(r);
		}
		else if (call == "printPreorder") {
			tree.printPre(r);
		}
		else if (call == "printPostorder") {
			tree.printPost(r);
		}
		else if (call == "printInorder") {
			tree.printIn(r);
		}
		else if (call == "printLevelCount") {
			tree.printlevelVal(r);
		}
		else {
			return 0;
		}
	}
}
