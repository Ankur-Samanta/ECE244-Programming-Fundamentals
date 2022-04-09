//
//  ShapeList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeList class below


#include "ShapeList.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;


ShapeList::ShapeList() {
    head = NULL;
}

ShapeList::~ShapeList() {
        ShapeNode* ptr;
        while (head != NULL) {
            ptr = head;
            ptr->~ShapeNode();
            head = ptr->getNext();
            ptr->setShape(NULL);
            delete ptr;
        }
}

ShapeNode* ShapeList::getHead() const {
    return (head);
}         // returns the head pointer

void ShapeList::setHead(ShapeNode* ptr) {
    head = ptr;
}       // sets the head pointer to ptr
    
ShapeNode* ShapeList::find(string name) const {
    if (head == NULL) {
        return NULL;
    }
    
    ShapeNode* tptr = head;
    while (tptr != NULL) {
        if(tptr->getShape()->getName() == name) break;
        tptr = tptr->getNext();
        if (tptr == NULL) {
            return NULL;
        }
    }
    return tptr;
} // finds a shape node with the specified shape name
                                        // returns a pointer to the node if found, otherwise
                                        // returns nullptr if the node is not found
void ShapeList::insert(ShapeNode* s) {
    if (head == NULL) {
        head = s;
        //s->setNext(NULL);
        return;
    } 
    ShapeNode* tptr = head;
    while (tptr->getNext() != NULL) {
        tptr = tptr->getNext();
    }
    tptr->setNext(s);
    return; 
}          // inserts the node pointed to by s at the end
                                        // of the list; s should never be nullptr (check this)
ShapeNode* ShapeList::remove(string name) {
    if (head == NULL) return NULL;
    ShapeNode* tptr = head;
    ShapeNode* pptr = NULL;
    while (tptr != NULL) {
        if (tptr->getShape()->getName() == name) break;
        pptr = tptr;
        tptr= tptr->getNext();
    }
    if (tptr == NULL) return tptr; 
    if (tptr == head) {
        head = head->getNext(); return tptr; //return or delete?
    }
    pptr->setNext(tptr->getNext());
    return tptr; //return or delete?
}     // removes the node with the shape called name
                                        // returns a pointer to the removed node or
                                        // nullptr is a node with name does not exist
void ShapeList::print() const {
    ShapeNode* tptr = head;
    while (tptr != NULL) {
        tptr->print();
        tptr = tptr->getNext();
    }
}                // prints the list