
class Robot
{
private:
    int xPosition;
    int yPosition;
    
public:
    Robot();       // constructor to auto execute in the  when robot object is called
    
    void draw();
    void erase();
    void setXPosition(int xPos);
    void setYPosition(int yPos);
    int getXPosition();
    int getYPosition();
    void moveForward(int v);
    void moveBack(int v);
    void moveLeft(int v);
    void moveRight(int v);
};
