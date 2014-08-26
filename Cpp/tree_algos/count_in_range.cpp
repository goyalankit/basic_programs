/**
 * count number of nodes in the binary search tree in the specified
 * range.


                    6
              4        7
         3                 12
     2                   11    16
 0                    10            22
                                          32
                                              62

 *
 *
 * */
#include <iostream>
#include <limits>
#include <queue>

typedef struct Node {
  Node(int _d, Node *_left, Node *_right) :
    data(_d), left(_left), right(_right) {}

  int incrementLeft() {
    return leftCount++;
  }

  int incrementRight() {
    return rightCount++;
  }

  int data;
  Node *left;
  Node *right;
  int leftCount;
  int rightCount;
};

Node* insertNode(Node *root, int data) {
  if (root->data <= data) {
    root -> incrementRight();
    if (root->right == NULL) {
      root->right = new Node(data, NULL, NULL);
    } else {
      insertNode(root->right, data);
    }
  } else {
    root -> incrementLeft();
    if (root->left == NULL) {
      root->left = new Node(data, NULL, NULL);
    } else {
      insertNode(root->left, data);
    }
  }
  return root;
}

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
    std::cout << temp->data <<" (" << temp->leftCount << ", " << temp->rightCount << ")  ";
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
  root = insertNode(root, 11);
  root = insertNode(root, 10);

  if (root->left == NULL || root->right == NULL) {
    std::cout << "Dammit" << std::endl;
  }
  return root;
}

int countInRange(Node *root, int min, int max, int &count) {
  if (root == NULL) return 0;

  if (root->data <=  min && root->right != NULL) {
    countInRange(root->right, min, max, count);
  } else if (root -> data >= max && root->left != NULL) {
    countInRange(root->left, min, max, count);
  } else if (root->data > min && root -> data < max) {
    std::cout << "[A] " << root->data << std::endl;
    count++;
    countInRange(root->left, min, max, count); // only increment it once.
    countInRange(root->right, min, max, count);
  }

  return count;
}

int main(void) {
  int max = std::numeric_limits<int>::max();
  int min = std::numeric_limits<int>::min();
  int count = 0;

  Node *root = create_binary_tree();
  std::cout << "---------------------" << std::endl;
  std::cout << countInRange(root, 1, 11, count) << std::endl;
  std::cout << "---------------------" << std::endl;
  printBstByLevel(root);
  return EXIT_SUCCESS;
}
