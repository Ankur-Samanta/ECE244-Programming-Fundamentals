//
//  Triangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class Rectangle here

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include "Shape.h"
#include "Triangle.h"

// Build a Rectangle object
Triangle::Triangle(string n, float xcent, float ycent, float x1, float y1, float x2, float y2, float x3, float y3):Shape(n, xcent, ycent) {
    xone = x1;
    yone = y1;
    xtwo = x2;
    ytwo = y2;
    xthree = x3;
    ythree = y3;
}

Triangle::~Triangle() {
    // Nothing to do
}

// Accessor
float Triangle::getx1() const {
    return xone;
}     

float Triangle::gety1() const {
    return yone;
} 

float Triangle::getx2() const {
    return xtwo;
}    

float Triangle::gety2() const {
    return ytwo;
}

float Triangle::getx3() const {
    return xthree;
}    

float Triangle::gety3() const {
    return ythree;
}


// Mutator
void Triangle::setx1(float x1) {
    xone = x1;
} 

void Triangle::sety1(float y1) {
    yone = y1;
} 
    
void Triangle::setx2(float x2) {
    xtwo = x2;
}  

void Triangle::sety2(float y2) {
    ytwo = y2;
}

void Triangle::setx3(float x3) {
    xthree = x3;
}  

void Triangle::sety3(float y3) {
    ythree = y3;
}

void Triangle::draw() const {
    // Set floating point printing to fixed point with 2 decimals
    cout << std::fixed;
    cout << std::setprecision(2);
    
    // Print the information
    cout << "triangle: " << name << " "
         << x_centre << " " << y_centre
         << " " << xone << " " << yone 
         << " " << xtwo << " " << ytwo 
         << " " << xthree << " " << ythree 
         << " " << computeArea() << endl;
}

float Triangle::computeArea() const {
    return (0.5*abs((xone * (ytwo - ythree)) - (xtwo * (yone - ythree)) + (xthree * (yone - ytwo))));
}

Shape* Triangle::clone() const {
    return (new Triangle(*this));
}