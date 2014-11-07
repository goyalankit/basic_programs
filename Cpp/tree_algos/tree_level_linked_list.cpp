#include <iostream>
#include <queue>
#include "tree.h"
#include <unordered_map>

typedef struct LinkedListItem {
  LinkedListItem(int _data) : data(_data) {}

  int data;
  LinkedListItem *next;
};

LinkedListItem *addNode(LinkedListItem *head, int data) {
  LinkedListItem *item = (LinkedListItem *)malloc(sizeof(LinkedListItem));
  item->data = data;
  std::cout << "adding node " << data << std::endl;

  if (head == NULL) {
    head = item;
    return head;
  }

  LinkedListItem *tempNode = head;
  while (tempNode -> next != NULL) {
    tempNode = tempNode->next;
  }

  tempNode->next = item;
  return head;
}

void printLinkedList(LinkedListItem *head) {
  while(head != NULL) {
    std::cout << head->data << std::endl;
    head = head->next;
  }
}

std::unordered_map<int, LinkedListItem*> *createLinkedList(Tree::Node *root) {
  int currentLevel= 0;
  int nodesInLevel = 1;
  std::unordered_map<int, LinkedListItem*> *nodeLevelList =
    new std::unordered_map<int, LinkedListItem*>();
  (*nodeLevelList)[0] = NULL;

  std::queue<Tree::Node *> Queue;
  Queue.push(root);

  while (!Queue.empty()) {
    Tree::Node *item = Queue.front();
    Queue.pop();

    (*nodeLevelList)[currentLevel] = addNode((*nodeLevelList)[currentLevel], item->data);
    nodesInLevel--;

    if (nodesInLevel == 0) {
      currentLevel++;
      (*nodeLevelList)[currentLevel] = NULL;
      nodesInLevel = 0;
    }
    if (item->left != NULL) {
      Queue.push(item->left);
      nodesInLevel++;
    }

    if (item->right != NULL) {
      Queue.push(item->right);
      nodesInLevel++;
    }
  }
  return nodeLevelList;
}

int main(void) {
  Tree::Node *root = Tree::create_binary_tree();
  std::unordered_map<int, LinkedListItem *> *listLevelMap = createLinkedList(root);

  for (auto it = listLevelMap->begin(), ie = listLevelMap->end(); it!=ie; ++it) {
    //std::cout << "Level: " << it->first << std::endl;
    printLinkedList(it->second);
  }

  return EXIT_SUCCESS;
}

