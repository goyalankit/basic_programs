/*
 * =====================================================================================
 *
 *       Filename:  dup_elements.cpp
 *
 *    Description: Remove duplicates from linked list using hash table
 *
 *        Version:  1.0
 *        Created:  11/06/2013 11:28:48
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Ankit Goyal
 *   Organization:
 *
 * =====================================================================================
 */

#include<iostream>
#include<unordered_map>
#include "string"

using namespace std;

typedef std::unordered_map< int, bool > hashmap;

struct list{
    int data;
    struct list *next;

    public:
    list(){
        next = NULL;
    }
};

void findDup(struct list *head);

int main(void){

    struct list head, node1, node2, node3, node4, node5, *temp;
    head.data = 1;
    node1.data = 3;
    node2.data = 2;
    node3.data = 5;
    node4.data = 3;
    node5.data = 1;
    head.next = &node1;
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    node5.next = NULL;

    std::cout << "found dups" << std::endl;
    findDup(&head);

    temp = &head;
    while(temp){
        std::cout << temp -> data << std::endl;
        temp = temp -> next;
    }
    return 0;
}

void findDup(struct list *head)
{
    hashmap elements;
    struct list *temp;
    temp = head;

    std::cout << "enering" << std::endl;
    while(temp){
        std::cout << "ran" << std::endl;
        if(elements.find(temp->data) == elements.end()){
            elements[temp-> data] = true ;
            head = temp;
            temp = temp -> next;
        }else{
            std::cout << "removing duplicate " << temp->data << std::endl;
            head->next = temp -> next;
            temp = head -> next;
        }
    }
}
