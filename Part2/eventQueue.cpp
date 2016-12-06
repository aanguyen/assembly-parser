#include "eventQueue.h"
using namespace std;

struct Node {
	const Event *val;
	Node *right = NULL;
};

Node* root = NULL;

bool enqueue (const Event *e) {
	if (e->time < 0)
		return false;
	if (root == NULL) {
		root = new Node();
		root->val = e;
	} else {
		Node *start = root;
		Node *prev = NULL;
		while (root != NULL) {
			if (root->val == e)
				return true;
			if (root->val->time > e->time) {
				Node *newNode = new Node();
				newNode->val = e;
				newNode->right = root;
				if (prev != NULL) {
					prev->right = newNode;
				} else {
					start = newNode;
				}
				break;
			}
			prev = root;
			root = root->right;
		}
		if (root == NULL) {
			root = new Node();
			root->val = e;
			prev->right = root;
		}
		root = start;
	}
	return true;
}

const Event* dequeue () {
	if (root == NULL)
		return NULL;
	const Event *ret = root->val;
	root = root->right;
	return ret;
}