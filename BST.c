#include <stdio.h>
#include <stdlib.h>

struct Node {

	int data;
	int count;

	struct Node *left;
	struct Node *right;

};

struct Node *makeNewNode(int value) {

	struct Node *newNode = malloc(sizeof(*newNode));
	newNode->data = value;
	newNode->count = 1;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

struct Node *findMin(struct Node *nodeRoot) {

	while (nodeRoot->left != NULL) {

		nodeRoot = nodeRoot->left;
	}

	return nodeRoot;
}

struct Node *append(struct Node *nodeRoot, int value) {

	if (nodeRoot == NULL) {

		nodeRoot = makeNewNode(value);
	}
	else if (nodeRoot->data == value) {

		nodeRoot->count++;
	}
	else if (value < nodeRoot->data) {

		nodeRoot->left = append(nodeRoot->left, value);
	}
	else if (value > nodeRoot->data) {

		nodeRoot->right = append(nodeRoot->right, value);
	}

	return nodeRoot;
}

struct Node *terminate(struct Node *nodeRoot, int value) {

	if (nodeRoot == NULL) {

		return nodeRoot;
	}
	else if (value < nodeRoot->data) {

		nodeRoot->left = terminate(nodeRoot->left, value);
	}
	else if (value > nodeRoot->data) {

		nodeRoot->right = terminate(nodeRoot->right, value);
	}
	else if (nodeRoot->data == value) {

		if (nodeRoot->count > 1) {

			nodeRoot->count--;
		}
		else if (nodeRoot->left == NULL && nodeRoot->right == NULL) {

			nodeRoot = NULL;
			free(nodeRoot);
		}
		else if (nodeRoot->left == NULL) {

			struct Node *temp = nodeRoot;
			nodeRoot = nodeRoot->right;
			free(temp);
		}
		else if (nodeRoot->right == NULL) {

			struct Node *temp = nodeRoot;
			nodeRoot = nodeRoot->right;
			free(temp);
		}
		else {

			struct Node *temp = findMin(nodeRoot->right);
			nodeRoot->data = temp->data;
			free(temp);
		}
	}

	return nodeRoot;
}

struct Node *deleteBST(struct Node *nodeRoot) {

	if (nodeRoot == NULL) {

		return nodeRoot;
	}
	else if (nodeRoot->left == NULL && nodeRoot->right == NULL) {

		nodeRoot = NULL;
		free(nodeRoot);
	}
	else if (nodeRoot->left == NULL) {

		nodeRoot = deleteBST(nodeRoot->right);
	}
	else if (nodeRoot->right == NULL) {

		nodeRoot = deleteBST(nodeRoot->left);
	}
	else {

		nodeRoot = deleteBST(nodeRoot->right);
	}

	return nodeRoot;
}

int find(struct Node *nodeRoot, int value) {

	if (nodeRoot == NULL) {

		return 0;
	}
	else if (value < nodeRoot->data) {

		return find(nodeRoot->left, value);
	}
	else if (value > nodeRoot->data) {

		return find(nodeRoot->right, value);
	}
	else if (value == nodeRoot->data) {

		return nodeRoot->count;
	}

	return 0;
}

struct Node *printInOrder(struct Node *nodeRoot) {

	if (nodeRoot != NULL){

		printInOrder(nodeRoot->left);
		printf("%d ", nodeRoot->data);
		printInOrder(nodeRoot->right);
	}
}

int main() {

	struct Node *root = NULL;
	int nrOfInputs = 0;
	scanf_s("%d", &nrOfInputs);

	for (int i = 0; i < nrOfInputs; i++) {

		int action = 0;
		int number = 0;
		scanf_s("%d %d", &action, &number);

		if (action == 0) {

			root = append(root, number);
		}
		else if (action == 1) {

			printf("There are %d instances of %d\n", find(root, number), number);
		}
		else if (action == 2) {

			root = terminate(root, number);
		}
	}

	printInOrder(root);
	printf("\n before delete function");
	while (root != NULL) {
		
		deleteBST(root);
	}
	printf("\n after delete function");
	printInOrder(root);

	system("PAUSE");
	return 0;
}
