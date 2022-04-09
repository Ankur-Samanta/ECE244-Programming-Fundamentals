//
//  GroupList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupList class below


#include "GroupList.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

GroupList::GroupList() {
    head = NULL;
}

GroupList::~GroupList() {
    GroupNode* ptr;
    while (head != NULL) {
        ptr = head;
        ptr->~GroupNode();
        head = ptr->getNext();
        delete ptr;
    }    
}

GroupNode* GroupList::getHead() const {
    return head;
}       // returns the head pointer
void GroupList::setHead(GroupNode* ptr) {
    head = ptr;
}     // sets the head pointer to ptr
void GroupList::insert(GroupNode* s) {
    if (head == NULL) {
        head = s;
        s->setNext(NULL);
    }
    else {
        GroupNode* tptr = head;
        while (tptr->getNext() != NULL) {
            tptr = tptr->getNext();
        }
        tptr->setNext(s);
        s->setNext(NULL);
    }
}       // inserts the node pointed to by s at the end of the list
GroupNode* GroupList::remove(string name) {
    if (head == NULL) return NULL;
    GroupNode* tptr = head;
    GroupNode* pptr = NULL;
    while (tptr != NULL) {
        if (tptr -> getName() == name) break;
        pptr = tptr;
        tptr = tptr->getNext();
    }
    if (tptr == NULL) return NULL;
    if (tptr == head) {
        head = head->getNext();
        return tptr;
    }
    pptr->setNext(tptr->getNext());
    return tptr;
}   // removes the group with the name "name" from the list
                                      // and returns a pointer to the removed GroupNode
                                      // returns nullptr is name is not found on list
void GroupList::print() const {
    GroupNode* tptr = head;
    while (tptr != NULL) {
        tptr->print();
        tptr = tptr->getNext();
    }
}               // prints the list, one GroupNode at a time
