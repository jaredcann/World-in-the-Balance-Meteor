#include "Robot.h"
#include "uLCD_4DGL.h"
extern uLCD_4DGL uLCD;


Robot::Robot() {
    xPosition = 63;
    yPosition = 63;
    
    }
    
void Robot:: draw() {
    uLCD.filled_circle(xPosition, yPosition, 15, GREEN);
    uLCD.filled_rectangle(xPosition-17, yPosition-4,xPosition+17, yPosition+4, RED);
    uLCD.filled_rectangle(xPosition-6, yPosition-2,xPosition-4, yPosition+2, BLACK);
    uLCD.filled_rectangle(xPosition+4, yPosition-2,xPosition+6, yPosition+2, BLACK);
    uLCD.filled_rectangle(xPosition-5, yPosition-12,xPosition+5, yPosition-9, WHITE);
    uLCD.line(xPosition-5, yPosition-10 , xPosition+5, yPosition-10, BLACK);   
    }    
void Robot::erase() {
    uLCD.filled_circle(xPosition, yPosition, 30, BLACK);
    
    }

void Robot::setXPosition(int xPos)              // update the x axis location
{
    xPosition = xPos;
}
void Robot::setYPosition(int yPos){    // update the y axis location values for robot based on last command
    yPosition = yPos;
}

int Robot:: getXPosition(){             // returns current location of robot
    return xPosition;
}
int Robot:: getYPosition(){
    return yPosition;
}

void Robot:: moveForward(int v)
{
    setYPosition(yPosition+v);   //future use neeed geetter

}
void Robot::moveBack(int v){
    setYPosition(yPosition-v);
    
    
}
void Robot::moveLeft(int v){
    setXPosition(xPosition-v);
    
}

void Robot::moveRight(int v){
    setXPosition(xPosition+v);
    
}
