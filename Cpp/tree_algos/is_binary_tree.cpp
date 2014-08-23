#include <iostream>
#include <limits>
#include <queue>

typedef struct Node {
  Node(int _d, Node *_left, Node *_right) :
    data(_d), left(_left), right(_right) {}

  int data;
  Node *left;
  Node *right;
};

Node* insertNode(Node *root, int data) {
  if (root->data <= data) {
    if (root->right == NULL) {
      root->right = new Node(data, NULL, NULL);
    } else {
      insertNode(root->right, data);
    }
  } else {
    if (root->left == NULL) {
      root->left = new Node(data, NULL, NULL);
    } else {
      insertNode(root->left, data);
    }
  }
  return root;
}


// print level with newline at each level
// we track the number of nodes at each level
// by using a counter
void printBstByLevel(Node *root) {
  if (root == NULL) return;

  int currentLevel = 1;
  int nextLevel = 0;

  std::queue<Node *> Queue;
  Queue.push(root);
  Node *temp;
  while (!Queue.empty()) {
    temp = Queue.front();
    currentLevel -= 1;
    Queue.pop();
    std::cout << temp->data <<" ";
    if (temp -> left != NULL) {
      Queue.push(temp->left);
      nextLevel += 1;
    }
    if (temp -> right != NULL) {
      Queue.push(temp -> right);
      nextLevel += 1;
    }
    if (currentLevel == 0) {
      std::cout << "" << std::endl;
      currentLevel = nextLevel;
      nextLevel = 0;
    }
  }
}

// level order traversal
void printBinaryTreeByLevel(Node *root) {
  if (root == NULL) return;

  std::queue<Node *> Queue;
  Queue.push(root);

  Node *temp;
  while(!Queue.empty()) {
    temp = Queue.front();
    Queue.pop();
    std::cout << temp->data <<" ";
    if (temp -> left != NULL) {
      Queue.push(temp->left);
    }
    if (temp -> right != NULL) {
      Queue.push(temp -> right);
    }
  }
}

Node * create_binary_tree(){
  Node *root = new Node(6, NULL, NULL);
  root = insertNode(root, 7);
  root = insertNode(root, 4);
  root = insertNode(root, 3);
  root = insertNode(root, 2);
  root = insertNode(root, 12);
  root = insertNode(root, 16);
  root = insertNode(root, 22);
  root = insertNode(root, 32);
  root = insertNode(root, 62);
  root = insertNode(root, 0);

  if (root->left == NULL || root->right == NULL) {
    std::cout << "Dammit" << std::endl;
  }
  return root;
}

// check if tree is a binary search tree
// use range to determine
bool isBst(Node *root, int min, int max) {
  if (root == NULL || (root->data < max &&
      root -> data > min &&
      isBst(root->left, min, root->data) &&
      isBst(root->right, root->data, max)))
    return true;
   else
    return false;
}

int main(void) {
  int max = std::numeric_limits<int>::max();
  int min = std::numeric_limits<int>::min();

  Node *root = create_binary_tree();
  // printBinaryTreeByLevel(root);
  printBstByLevel(root);
  std::cout << std::boolalpha << isBst(root, min, max) << std::endl;
  return EXIT_SUCCESS;
}
