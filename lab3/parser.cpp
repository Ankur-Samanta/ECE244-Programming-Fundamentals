//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented 
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
enum commandCode {maxShapesIO, createIO, moveIO, rotateIO, drawIO, deleteIO};
commandCode passCode(string input) {
    if (input == "maxShapes") return maxShapesIO;
    if (input == "create") return createIO;
    if (input == "move") return moveIO;
    if (input == "rotate") return rotateIO;
    if (input == "draw") return drawIO;
    if (input == "delete") return deleteIO;
}

string tempName, tempType; int tempXLoc, tempYLoc, tempXSize, tempYSize, tempRotation;
int errorPriority = 0;
int c1, c2, c3, c4, c5, c6, c7;
bool invalidCommand, invalidArgument, invalidName, nameAlreadyExists, nameNotFound, invalidType, invalidValue, tooManyArguments, tooFewArguments, shapeArrayIsFull;

//ERROR CASE 1: INVALID COMMAND
void invalidCommandErrorCase(string input) {
    for (int i = 0; i < 7; ++i) {
        if (keyWordsList[i] == input) {c1 += 1; invalidCommand = false;} //if the command is valid (within key words list), increment counter
    }
    if (c1 == 0) {
        invalidCommand = true; //if the command doesn't match with any of the key words, then it is invalid
        if ((errorPriority == 0) || (errorPriority >= 1)) {errorPriority = 1;} //if error priority is 0 or greater than or equal to 1, set to 1
    }
    if ((input == " ") || input == "") {
        if ((errorPriority == 0) || (errorPriority >= 1)) {errorPriority = 1;}
    }
    c1 = 0; //reset counter
}

//ERROR CASE 2: INVALID ARGUMENT
bool invalidArgumentErrorCase;

//ERROR CASE 3: INVALID NAME //note that this is an initiation error
void invalidNameErrorCase(string input) {
    c3 = 0;
    for (int i = 0; i < 7; ++i) {
        if (keyWordsList[i] == input) {c3 += 1; invalidName = false;}
    } //check if tempName is a keyword
    if (c3 != 0) {
        invalidName = true; 
        if (errorPriority >= 3) {errorPriority = 3;}
    } //if tempName matches with a keyword, then it is an invalid name, and if error priority is not lower than 3, set it to 3
    for (int i = 0; i < 4; ++i) {
        if (shapeTypesList[i] == input) {c3 += 1; invalidName = false;}
    } //check if tempName is a shape type
    if (c3 != 0) {
        invalidName = true; 
        if ((errorPriority == 0) || (errorPriority >= 3)) {errorPriority = 3;};
    } //if tempName matches with a shape type, then it is an invalid name, and if error priority is not lower than 3, set it to 3
    c3 = 0; //reset counter
}

//ERROR CASE 4: NAME ALREADY EXISTS //note that this is an initiation error
bool nameAlreadyExistsErrorCase(string input) {
    for (int i = 0; i < max_shapes; ++i) {
        if (shapesArray[i] != NULL) {
            if (shapesArray[i]->getName() == input) {return true;} //check if a shape of the given name exists in the system
        }
    }
    return false;
}

//ERROR CASE 5: NAME NOT FOUND //this returns true or false and is a command error
bool nameNotFoundErrorCase(string input) {
    for (int i = 0; i < max_shapes; ++i) {
        if (shapesArray[i] != NULL) {
            if (shapesArray[i]->getName() == input) {return false;} //check if a shape of the given name exists in the system
        }
    }
    return true;
}

//ERROR CASE 6: INVALID TYPE
void invalidTypeErrorCase(string input) {
    c6 = 0;
    for (int i = 0; i < 4; ++i) {
        if (shapeTypesList[i] == input) {c6 += 1; invalidType = false;}
    } //check if tempType is a valid shape type
    if (c6 == 0) {
        invalidType = true; 
        if ((errorPriority == 0) || (errorPriority >= 6)) {errorPriority = 6;}
    } //if tempName does not match any valid shape types, then it is an invalid type, and if error priority is not lower than 6, set it to 6
    c6 = 0; //reset counter
}

//ERROR CASE 7: INVALID VALUE
void invalidValueErrorCase(int tempxloc, int tempyloc, int tempxsize, int tempysize, int temprotation) {
    c7 = 0;
    if ((tempxloc < 0) || (tempyloc < 0)) {c7 += 1;} //if the location values for x or y are less than 0, value is invalid
    if (tempType == "circle") {
        if (tempxsize != tempysize) {c7 += 1;} //if the type is circle and the x and y sizes aren't equal, value is invalid
    }
    if ((tempxsize < 0) || (tempysize < 0)) {c7 += 1;}
    if ((temprotation < 0) || (temprotation > 360)) {c7 += 1;} //if the rotation value is not between 0 and 360, value is invalid

    if (c7 == 0) {invalidValue = false;} //if the counter hasn't been incremented, there is no invalid value so return false
    else if (c7 > 0) {
        if ((errorPriority == 0) || (errorPriority >= 7)) {errorPriority = 7;} //set error priority to 7 if it isnt lower than that already
        invalidValue = true;
    } //if the counter has been incremented (>0), there is an invalid value so return true
    c7 = 0; //reset counter
}
void invalidxLoc(int tempxloc) {
    if ((tempxloc < 0)) {
        invalidValue = true;
        if ((errorPriority == 0) || (errorPriority >= 7)) {errorPriority = 7;}
    }
    else {invalidValue = false;}
}
void invalidyLoc(int tempyloc) {
    if ((tempyloc < 0)) {
        invalidValue = true;
        if ((errorPriority == 0) || (errorPriority >= 7)) {errorPriority = 7;}
    }
    else {invalidValue = false;}
}
void invalidxSize(int tempxsize) {
    if ((tempxsize < 0)) {
        invalidValue = true;
        if ((errorPriority == 0) || (errorPriority >= 7)) {errorPriority = 7;}
    }
    else {invalidValue = false;}
}
void invalidySize(int tempysize) {
    if ((tempysize < 0)) {
        invalidValue = true;
        if ((errorPriority == 0) || (errorPriority >= 7)) {errorPriority = 7;}
    }
    else {invalidValue = false;}
}
void invalidSize(int tempxsize, int tempysize) {
    if ((tempType == "circle")) {
        if (tempxsize != tempysize) {
            invalidValue = true;
            if ((errorPriority == 0) || (errorPriority >= 7)) {errorPriority = 7;}
        } //if the type is circle and the x and y sizes aren't equal, value is invalid
    }
    else {invalidValue = false;}
}
void invalidRotation(int temprotation) {
    if ((temprotation < 0) || (temprotation > 360)) {
        invalidValue = true;
        if ((errorPriority == 0) || (errorPriority >= 7)) {errorPriority = 7;}
    }
    else {invalidValue = false;}
}

//ERROR CASE 8: TOO MANY ARGUMENTS
void tooManyArgumentsErrorCase(std::stringstream &lineStream) {
    if (lineStream.peek() == EOF) {
        tooManyArguments = false; //if the next character (found by peeking) in the stringstream results in EOF, then there aren't too many arguments
    }
    else {
        tooManyArguments = true; //if peek does not return EOF, that means there were too many arguments passed in, so retrurn true
        if ((errorPriority == 0) || (errorPriority >= 8)) {errorPriority = 8;} //set error priority
    }
}

//ERROR CASE 9: TOO FEW ARGUMENTS
void tooFewArgumentsErrorCase(std::stringstream &lineStream) {
    if (lineStream.peek() == EOF) {
        tooFewArguments = true; //if the next character (found by peeking) in the stringstream results in EOF, then there are too few arguments
        if ((errorPriority == 0) || (errorPriority >= 9)) {errorPriority = 9;} //set error priority
    }
    else {tooFewArguments = false;} //if peek doesn't EOF, that means there aren't too few arguments at the point of calling
    
}

//ERROR CASE 10: SHAPE ARRAY IS FULL
void shapeArrayIsFullErrorCase() {
   if (shapeCount >= max_shapes) {
       shapeArrayIsFull = true;
       if ((errorPriority == 0) || (errorPriority >= 10)) {errorPriority = 10;}
   }
   else {shapeArrayIsFull = false;}
}

void printError(int errorPriority) {
    switch (errorPriority) {
        case 1: 
            cout << "Error: invalid command" << endl;
            cin.clear();
            break;
        case 2: 
            cout << "Error: invalid argument" << endl;
            cin.clear();
            break;
        case 3:
            cout << "Error: invalid shape name" << endl;
            cin.clear();
            break;
        case 4:
            cout << "Error: shape " << tempName << " exists" << endl;
            cin.clear();
            break;
        case 5:
            cout << "Error: shape " << tempName << " not found" << endl;
            cin.clear();
            break;
        case 6:
            cout << "Error: invalid shape type" << endl;
            cin.clear();
            break;
        case 7:
            cout << "Error: invalid value" << endl;
            cin.clear();
            break;
        case 8:
            cout << "Error: too many arguments" << endl;
            cin.clear();
            break;
        case 9:
            cout << "Error: too few arguments" << endl;
            cin.clear();
            break;
        case 10:
            cout << "Error: shape array is full" << endl;
            cin.clear();
            break;
        default:
            errorPriority = 0;
            break;
    }
    return;
}

int main() {

    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while (( !cin.eof () )) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);

        //Reset all boolean flags
        invalidCommand = false; invalidArgument = false; invalidName = false; nameAlreadyExists = false; nameNotFound = false; 
        invalidType = false; invalidValue = false; tooManyArguments = false; tooFewArguments = false; shapeArrayIsFull = false;
        errorPriority = 0;
        
        //if ((lineStream.peek() == ' ') || (lineStream.peek() == EOF)) {errorPriority = 1;}  
        printError(errorPriority); // if (errorPriority != 0) {int s = 2;}
        if (errorPriority != 0) {lineStream.ignore(1000, '/n');}

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        //ERROR CASE 1: INVALID COMMAND
        invalidCommandErrorCase(command);
        if ((command == " ") || command.empty()) {errorPriority = 1;}
        tooFewArgumentsErrorCase(lineStream);
        printError(errorPriority); //if (errorPriority != 0) {break;}
        
        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here

        if (!lineStream.eof()) {
            if (!invalidCommand) {
                switch (passCode(command)) {
                    case maxShapesIO:
                        lineStream >> max_shapes;
                        if (lineStream.fail() && !lineStream.eof()) {invalidArgument = true; errorPriority = 2; lineStream.clear();}
                        tooManyArgumentsErrorCase(lineStream);
                        printError(errorPriority); if (errorPriority != 0) {break;}
                        
                        for(int i=0; i<shapeCount; i++){ 
			                if(shapesArray[i]){
				                delete shapesArray[i];
				                shapesArray[i] = nullptr;
			                }
		                }
                        delete [] shapesArray;
		                shapesArray = nullptr;
		                shapeCount = 0;

                        shapesArray = new Shape*[max_shapes]; //dynamically allocate and initialize new array
                        for (int i = 0; i < max_shapes; ++i) {
                            shapesArray[i] = NULL; //initialize all elements to NULL
                        }
                        cout << "New database: max shapes is " << max_shapes << endl;
                        break;

                    case createIO:
                        
                        lineStream >> tempName;
                        if (lineStream.fail() && !lineStream.eof()) {invalidArgument = true; errorPriority = 2; lineStream.clear();}
                        invalidNameErrorCase(tempName); //ERROR CASE 3: INVALID NAME
                        if (nameAlreadyExistsErrorCase(tempName)) {
                            if ((errorPriority == 0) || (errorPriority >= 4)) {errorPriority = 4;}
                        }; //ERROR CASE 4: NAME ALREADY EXISTS
                        tooFewArgumentsErrorCase(lineStream); //ERROR CASE 9: TOO FEW ARGUMENTS
                        printError(errorPriority); if (errorPriority != 0) {break;} 
                        
                        lineStream >> tempType;
                        if (lineStream.fail() && !lineStream.eof()) {invalidArgument = true; errorPriority = 2; lineStream.clear();}
                        invalidTypeErrorCase(tempType); //ERROR CASE 6: INVALID TYPE
                        tooFewArgumentsErrorCase(lineStream);
                        printError(errorPriority); if (errorPriority != 0) {break;} 

                        lineStream >> tempXLoc;
                        if (lineStream.fail() && !lineStream.eof()) {invalidArgument = true; errorPriority = 2; lineStream.clear();}
                        invalidxLoc(tempXLoc);
                        tooFewArgumentsErrorCase(lineStream); //ERROR CASE 9: TOO FEW ARGUMENTS
                        printError(errorPriority); if (errorPriority != 0) {break;}

                        lineStream >> tempYLoc;
                        if (lineStream.fail() && !lineStream.eof()) {invalidArgument = true; errorPriority = 2; lineStream.clear();}
                        invalidyLoc(tempYLoc);
                        tooFewArgumentsErrorCase(lineStream); //ERROR CASE 9: TOO FEW ARGUMENTS
                        printError(errorPriority); if (errorPriority != 0) {break;}

                        lineStream >> tempXSize;
                        if (lineStream.fail() && !lineStream.eof()) {invalidArgument = true; errorPriority = 2; lineStream.clear();}
                        invalidxSize(tempXSize);
                        tooFewArgumentsErrorCase(lineStream); //ERROR CASE 9: TOO FEW ARGUMENTS
                        printError(errorPriority); if (errorPriority != 0) {break;}

                        lineStream >> tempYSize;
                        if (lineStream.fail() && !lineStream.eof()) {invalidArgument = true; errorPriority = 2; lineStream.clear();}
                        invalidySize(tempYSize);
                        invalidSize(tempXSize, tempYSize);
                        tooManyArgumentsErrorCase(lineStream); //ERROR CASE 10: TOO MANY ARGUMENTS
                        printError(errorPriority); if (errorPriority != 0) {break;}

                        invalidValueErrorCase(tempXLoc, tempYLoc, tempXSize, tempYSize, 0); //ERROR CASE 7: INVALID VALUE
                        shapeArrayIsFullErrorCase();
                        printError(errorPriority); if (errorPriority != 0) {break;}
                        
                        if (errorPriority == 0) {
                            shapesArray[shapeCount] = new Shape(tempName, tempType, tempXLoc, tempXSize, tempYLoc, tempYSize);
                            //shapeCount += 1; //once a shape has been created in the database, increment the counter by 1
                            cout << "Created " << shapesArray[shapeCount]->getName() << ": " << shapesArray[shapeCount]->getType() << " " << shapesArray[shapeCount]->getXlocation() << " " << shapesArray[shapeCount]->getYlocation() << " " << shapesArray[shapeCount]->getXsize() << " " << shapesArray[shapeCount]->getYsize() << endl;
                            shapeCount += 1;
                        }
                        break;

                    case moveIO:
                        lineStream >> tempName;
                        if (lineStream.fail() && !lineStream.eof()) {invalidArgument = true; errorPriority = 2; lineStream.clear();}
                        invalidNameErrorCase(tempName); //ERROR CASE 3: INVALID NAME
                        if (nameNotFoundErrorCase(tempName)) {
                            if ((errorPriority == 0) || (errorPriority >= 5)) {errorPriority = 5;}
                        } //ERROR CASE 5: NAME NOT FOUND
                        tooFewArgumentsErrorCase(lineStream); //ERROR CASE 9: TOO FEW ARGUMENTS
                        printError(errorPriority); if (errorPriority != 0) {break;}

                        lineStream >> tempXLoc;
                        if (lineStream.fail() && !lineStream.eof()) {invalidArgument = true; errorPriority = 2; lineStream.clear();}
                        tooFewArgumentsErrorCase(lineStream); //ERROR CASE 9: TOO FEW ARGUMENTS
                        printError(errorPriority); if (errorPriority != 0) {break;}

                        lineStream >> tempYLoc;
                        if (lineStream.fail() && !lineStream.eof()) {invalidArgument = true; errorPriority = 2; lineStream.clear();}

                        for (int i = 0; i < max_shapes; ++i) {
                            if (shapesArray[i] != NULL) {
                                if (shapesArray[i]->getName() == tempName) {
                                    invalidValueErrorCase(tempXLoc, tempYLoc, shapesArray[i]->getXsize(), shapesArray[i]->getYsize(), 0);
                                }
                            }
                        }
                        tooManyArgumentsErrorCase(lineStream); //ERROR CASE 10: TOO MANY ARGUMENTS
                        printError(errorPriority); if (errorPriority != 0) {break;}

                        if (errorPriority == 0) {
                            for (int i = 0; i < max_shapes; ++i) {
                                if (shapesArray[i] != NULL) {
                                    if (shapesArray[i]->getName() == tempName) {
                                        shapesArray[i]->setXlocation(tempXLoc);
                                        shapesArray[i]->setYlocation(tempYLoc);
                                        cout << "Moved " << shapesArray[i]->getName() << " to " << shapesArray[i]->getXlocation() << " " << shapesArray[i]->getYlocation() << endl;
                                    }
                                }
                            }
                            
                        }
                        break;

                    case rotateIO:
                        lineStream >> tempName;
                        if (lineStream.fail() && !lineStream.eof()) {invalidArgument = true; errorPriority = 2; lineStream.clear();}
                        if (nameNotFoundErrorCase(tempName)) {
                            if ((errorPriority == 0) || (errorPriority >= 5)) {errorPriority = 5;}
                        } //ERROR CASE 5: NAME NOT FOUND
                        invalidNameErrorCase(tempName); //ERROR CASE 3: INVALID NAME
                        tooFewArgumentsErrorCase(lineStream); //ERROR CASE 9: TOO FEW ARGUMENTS
                        printError(errorPriority); if (errorPriority != 0) {break;}

                        lineStream >> tempRotation;
                        if (lineStream.fail() && !lineStream.eof()) {invalidArgument = true; errorPriority = 2; lineStream.clear();}
                        for (int i = 0; i < max_shapes; ++i) {
                            if (shapesArray[i]) {
                                if (shapesArray[i]->getName() == tempName) {
                                    invalidValueErrorCase(shapesArray[i]->getXlocation(), shapesArray[i]->getYlocation(), shapesArray[i]->getXsize(), shapesArray[i]->getYsize(), tempRotation);
                                }
                            }
                        }
                        tooManyArgumentsErrorCase(lineStream); //ERROR CASE 10: TOO MANY ARGUMENTS
                        printError(errorPriority); if (errorPriority != 0) {break;}

                        if (errorPriority == 0) {
                            for (int i = 0; i < max_shapes; ++i) {
                                if (shapesArray[i]) {
                                    if (shapesArray[i]->getName() == tempName) {
                                        shapesArray[i]->setRotate(tempRotation);
                                        cout << "Rotated " << shapesArray[i]->getName() << " by " << tempRotation << " degrees" << endl;
                                    }
                                }
                            }
                        }
                        break;

                    case drawIO:
                        lineStream >> tempName;
                        if (lineStream.fail() && !lineStream.eof()) {invalidArgument = true; errorPriority = 2;}
                        if (tempName != "all") {
                            invalidNameErrorCase(tempName); //ERROR CASE 3: INVALID NAME
                        }
                        if ((tempName != "all") && nameNotFoundErrorCase(tempName)) {
                            if ((errorPriority == 0) || (errorPriority >= 5)) {errorPriority = 5;}
                        } //ERROR CASE 5: NAME NOT FOUND
                        tooManyArgumentsErrorCase(lineStream); //ERROR CASE 10: TOO MANY ARGUMENTS
                        printError(errorPriority); if (errorPriority != 0) {break;}

                        if (errorPriority == 0) {
                            if (tempName == "all") {
                                cout << "Drew all shapes" << endl;
                                for (int i = 0; i < max_shapes; ++i) {
                                    if (shapesArray[i]) {
                                        shapesArray[i]->draw();
                                    }
                                }
                            }
                            else {
                                cout << "Drew ";
                                for (int i = 0; i < max_shapes; ++i) {
                                    if (shapesArray[i]) {
                                        if (shapesArray[i]->getName() == tempName) {
                                            shapesArray[i]->draw();
                                        }
                                    }
                                }
                            }
                        }
                        break;

                    case deleteIO:
                        lineStream >> tempName;
                        if (lineStream.fail() && !lineStream.eof()) {invalidArgument = true; errorPriority = 2; lineStream.clear();}
                        if (tempName != "all") {
                            invalidNameErrorCase(tempName); //ERROR CASE 3: INVALID NAME
                        }
                        if ((tempName != "all") && nameNotFoundErrorCase(tempName)) {
                            if ((errorPriority == 0) || (errorPriority >= 5)) {errorPriority = 5;}
                        } //ERROR CASE 5: NAME NOT FOUND
                        tooManyArgumentsErrorCase(lineStream); //ERROR CASE 10: TOO MANY ARGUMENTS
                        printError(errorPriority); if (errorPriority != 0) {break;}

                        if (errorPriority == 0) {
                            if (tempName == "all") {
                                for (int i = 0; i < max_shapes; ++i) {
                                    if (shapesArray[i]) {
                                        delete shapesArray[i];
                                    }
                                    shapesArray[i] = nullptr;
                                }
                                delete [] shapesArray;
                                cout << "Deleted: all shapes" << endl;
                            }
                            else {
                                for (int i = 0; i < max_shapes; ++i) {
                                    if (shapesArray[i]) {
                                        if ((shapesArray[i]->getName()) == tempName) {
                                            cout << "Deleted shape " << shapesArray[i]->getName() << endl;
                                            delete shapesArray[i];
                                            shapesArray[i] = nullptr;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                }
            }
        }        
        
        cin.clear();
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}

