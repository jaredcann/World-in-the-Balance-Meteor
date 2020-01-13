#include "mbed.h"
#include "MMA8452.h"
#include "uLCD_4DGL.h"
#include "PinDetect.h"
#include "Speaker.h"
#include "Robot.h"
#include <time.h>

#define ASTEROID_HEIGHT 12
#define ASTEROID_WIDTH 15
#define SPRITE_MAX 15
#define EARTH_WIDTH 10
#define EARTH_HEIGHT 10
#define EXPLOSION1_WIDTH 20
#define SCREEN_MAX 125
#define SCREEN_MIN 1
#define NUM_ASTEROIDS 4
#define Q 0x808000 //OLIVE
#define O 0x008000 //GREEN
#define S 0xC0C0C0 //SILVER
#define C 0x17202A //UFO GLASS
#define D 0x797D7F //DARK GREY
#define L 0x00FF00 //LIME
#define P 0xFF00FF //PINK
#define R 0xF1C40F //YELLOW
#define I 0xF39C12 //ORANGE
#define G 0xAAB7B8 //GREY
#define _ 0x000000 //BLACK
#define X 0xFFFFFF //WHITE
#define B 0x0000FF //BLUE
#define r 0xFF0000 //RED
using namespace std;
int asteroid_sprite_1[ASTEROID_HEIGHT * ASTEROID_WIDTH] = {
    _,_,_,_,X,P,P,P,P,P,P,P,_,_,_,
    _,_,_,P,_,_,_,_,_,_,_,_,P,_,_,
    _,_,P,_,_,_,_,_,_,_,_,_,P,_,_,
    _,P,_,_,_,_,_,_,_,_,_,_,P,_,_,
    P,P,P,P,_,_,_,_,_,_,_,_,_,P,_,
    _,_,_,P,_,_,_,_,_,_,_,_,_,P,_,
    _,_,P,_,_,_,_,_,_,_,_,_,_,P,_,
    _,P,_,_,_,_,_,P,_,_,_,_,_,P,_,
    P,_,_,_,_,_,P,P,_,_,_,_,P,_,_,
    _,P,_,_,_,P,_,P,_,_,_,_,P,_,_,
    _,_,P,_,P,_,_,P,_,_,_,P,_,_,_,
    _,_,_,P,_,_,_,P,P,P,P,_,_,_,_

};

int asteroid_sprite_2[ASTEROID_HEIGHT * ASTEROID_WIDTH] = {
    _,_,_,_,_,X,X,X,X,X,X,X,_,_,_,
    _,_,_,_,_,X,_,_,_,_,X,_,_,_,_,
    _,_,_,_,_,X,_,_,_,_,X,_,_,_,_,
    _,_,_,_,_,X,_,_,_,_,X,_,_,_,_,
    _,_,_,_,_,X,_,_,_,_,X,X,X,X,_,
    _,_,_,X,_,_,_,_,_,_,_,_,_,X,_,
    _,_,X,_,_,_,_,_,_,_,_,_,_,X,_,
    _,X,_,_,_,_,_,X,_,_,_,_,_,X,_,
    X,_,_,_,_,_,X,X,_,_,_,_,X,_,_,
    _,X,_,_,_,X,_,X,_,_,_,_,X,_,_,
    _,_,X,_,X,_,_,X,_,_,_,X,_,_,_,
    _,_,_,X,_,_,_,X,X,X,X,_,_,_,_

};
int asteroid_sprite_3[ASTEROID_HEIGHT * ASTEROID_WIDTH] = {
    _,_,_,_,X,X,X,X,X,_,_,_,_,_,_,
    _,_,_,X,_,_,_,_,_,X,_,_,_,_,_,
    _,_,X,_,_,_,_,_,_,X,_,_,_,_,_,
    _,X,_,_,_,_,_,_,_,X,_,_,X,_,_,
    X,_,_,_,_,_,_,_,_,_,X,X,X,X,_,
    _,X,_,_,_,_,_,_,_,_,_,_,_,X,_,
    X,_,_,_,_,_,X,X,X,_,_,_,_,X,_,
    _,X,_,_,_,_,X,_,_,X,_,_,_,X,_,
    X,_,_,_,_,_,X,_,_,X,_,_,X,_,_,
    _,X,_,_,_,X,_,_,_,X,_,_,X,_,_,
    _,_,X,_,X,_,_,_,_,X,_,X,_,_,_,
    _,_,_,X,_,_,_,_,_,X,X,_,_,_,_

};
int asteroid_sprite_4[ASTEROID_HEIGHT * ASTEROID_WIDTH] = {
    _,_,_,_,X,X,X,X,X,X,X,X,_,_,_,
    _,_,_,X,_,_,_,_,_,_,_,_,X,_,_,
    _,_,X,_,_,_,_,_,_,_,_,_,X,_,_,
    _,X,_,_,_,_,_,_,_,_,_,_,X,_,_,
    X,_,_,_,_,_,_,_,_,_,_,_,_,X,_,
    _,X,_,_,_,_,_,_,_,_,_,_,_,X,_,
    _,X,_,_,_,_,_,_,_,_,_,_,_,X,_,
    _,X,_,_,_,_,_,_,_,_,_,_,_,X,_,
    X,_,_,_,_,_,_,_,_,_,_,_,X,_,_,
    _,X,_,_,_,_,_,_,_,_,_,_,X,_,_,
    _,_,X,_,_,_,_,_,_,_,_,X,_,_,_,
    _,_,_,X,X,X,X,X,X,X,X,_,_,_,_

};

int spaceship_earth1[EARTH_WIDTH *EARTH_HEIGHT] = {
    _,_,S,S,S,S,S,S,_,_,
    _,S,I,I,I,I,I,I,S,_,
    S,I,I,I,I,I,I,I,I,S,
    S,I,I,I,I,I,I,I,I,S,
    S,I,I,I,I,I,I,I,I,S,
    S,I,I,I,I,I,I,I,I,S,
    S,I,I,I,I,I,I,I,I,S,
    S,I,I,I,I,I,I,I,I,S,
    S,I,I,I,I,I,I,I,S,_,
    _,S,S,S,S,S,S,S,_,_,
};


int asteroid_sprite_5[ASTEROID_HEIGHT * ASTEROID_WIDTH] = {
    R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,
    R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,
    R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,
    R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,
    R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,
    R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,
    R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,
    R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,
    R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,
    R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,
    R,R,R,R,R,R,R,R,R,R,R,R,R,R,R,
    R,R,R,R,R,R,R,R,R,R,R,R,R,R,R

};

uLCD_4DGL uLCD(p28, p27, p29); // create a global uLCD object
Serial pc(USBTX,USBRX); //not used in this program
Speaker mySpeaker(p21);
PinDetect pb1(p16);
//PinDetect pb2(p17);
DigitalIn pb2(p17);

bool BombUsed = true;





class ScreenObject
{
protected:
    int x_pos;

    int y_pos;

public:
    //virtual ScreenObject(); // possible constructor

    virtual void draw()=0;    //=0 needed to make a pure vitual function
    virtual void update()=0;
    int getY() {
        return y_pos;
    }
    int getX() {
        return x_pos;
    }
    void explode(){
        uLCD.filled_rectangle(x_pos-4, y_pos-4, x_pos+16, y_pos+14, BLACK);
        uLCD.BLIT(x_pos, y_pos, ASTEROID_WIDTH, ASTEROID_HEIGHT, asteroid_sprite_5);
        wait(0.04);
        uLCD.filled_rectangle(x_pos-4, y_pos-4, x_pos+16, y_pos+14, BLACK);
        }



};

class SpaceShipEarth: public ScreenObject
{
public:
    void draw() {
        x_pos= 60;
        y_pos= 60;
        
        uLCD.BLIT(x_pos, y_pos, EARTH_WIDTH, EARTH_HEIGHT, spaceship_earth1);
    }
    void update() {
        uLCD.filled_rectangle(x_pos-3, y_pos-3, x_pos+12, y_pos+12, BLACK);
        uLCD.BLIT(x_pos, y_pos, EARTH_WIDTH, EARTH_HEIGHT, spaceship_earth1);
    }
    void moveForward(int v) {
        y_pos += v;   //future use neeed geetter
    }
    void moveBack(int v) {
        y_pos -= v;
    }
    void moveLeft(int v) {
        x_pos -= v;
    }

    void moveRight(int v) {
        x_pos += v;
    }
     void explode(){
        uLCD.filled_rectangle(x_pos-4, y_pos-4, x_pos+16, y_pos+14, BLACK);
        uLCD.BLIT(x_pos, y_pos, ASTEROID_WIDTH, ASTEROID_HEIGHT, asteroid_sprite_5);
        }
};

class AbstractAstroid: public ScreenObject
{
protected:
    int deltaX;
    int deltaY;
    
public:
    
    void explode()
    {
        uLCD.filled_rectangle(x_pos-4, y_pos-4, x_pos+16, y_pos+14, BLACK);
        uLCD.BLIT(x_pos, y_pos, ASTEROID_WIDTH, ASTEROID_HEIGHT, asteroid_sprite_5);
        }

};

class ConcreteAstroid1: public AbstractAstroid
{
public:

    void draw() {
        
        x_pos = rand()% 95 + 15;    //random number between 15 and 110
        y_pos = rand()% 5 + 15; //random number between 15 and 20
        deltaX = (rand() % 3+1) - 2;
        deltaY =  (rand() % 3+1) - 2;
        //deltaX = 3;
        //deltaY = 3;
       
        uLCD.BLIT(x_pos, y_pos, ASTEROID_WIDTH, ASTEROID_HEIGHT, asteroid_sprite_1); // draw the astroid
    }
    void update() {
        x_pos +=deltaX;
        y_pos += deltaY;
        uLCD.filled_rectangle(x_pos-4, y_pos-4, x_pos+16, y_pos+14, BLACK);
        if ((x_pos < 110 && x_pos > 15) && (y_pos < 110 && y_pos > 15)) {

            uLCD.BLIT(x_pos, y_pos, ASTEROID_WIDTH, ASTEROID_HEIGHT, asteroid_sprite_1);

        }else {
            x_pos = rand()% 95 + 15;    //random number between 15 and 110
            //y_pos = rand()% 15 + 90;
            y_pos = rand()% 5 + 15;     //random number between 15 and 20
            deltaX = (rand() % 4+1) - 2;
            deltaY =  (rand() % 3+1);
        }
    } // end update function
    
     void explode(){
        uLCD.filled_rectangle(x_pos-4, y_pos-4, x_pos+16, y_pos+14, BLACK);
        uLCD.BLIT(x_pos, y_pos, ASTEROID_WIDTH, ASTEROID_HEIGHT, asteroid_sprite_5);
        }
    
};
class ConcreteAstroid2: public AbstractAstroid
{
public:
    void draw() {
        
        x_pos = rand()% 95 + 15;    //random number between 15 and 110
        y_pos = rand()% 5 + 15; //random number between 15 and 20
            deltaX = (rand() % 4+1) - 2;
            deltaY =  (rand() % 3+1);

    
        uLCD.BLIT(x_pos, y_pos, ASTEROID_WIDTH, ASTEROID_HEIGHT,
                  asteroid_sprite_2);
    }
    void update() {
        x_pos +=deltaX;
        y_pos += deltaY;
        uLCD.filled_rectangle(x_pos-4, y_pos-4, x_pos+16, y_pos+14, BLACK);
        if ((x_pos < 110 && x_pos > 15) && (y_pos < 110 && y_pos > 15)) {

            uLCD.BLIT(x_pos, y_pos, ASTEROID_WIDTH, ASTEROID_HEIGHT, asteroid_sprite_2);
    

        } else {
            x_pos = rand()% 95 + 15;    //random number between 15 and 110
            y_pos = rand()% 5 + 15;     //random number between 15 and 20
            deltaX = (rand() % 3+1) - 1;
            deltaY =  (rand() % 3+1);
        }
    }
};
class ConcreteAstroid3: public AbstractAstroid
{
public:
    void draw() {
        
        x_pos = rand()% 95 + 15;    //random number between 15 and 110
        y_pos = rand()% 5 + 15; //random number between 15 and 20
        deltaX = (rand() % 5+1) - 3;
        deltaY =  (rand() % 4+1);
        uLCD.BLIT(x_pos, y_pos, ASTEROID_WIDTH, ASTEROID_HEIGHT, asteroid_sprite_3); // draw the astroid
    }
    void update() {
        x_pos +=deltaX;
        y_pos += deltaY;
        uLCD.filled_rectangle(x_pos-4, y_pos-4, x_pos+17, y_pos+14, BLACK);
        if ((x_pos < 110 && x_pos > 15) && (y_pos < 110 && y_pos > 15)) {

            uLCD.BLIT(x_pos, y_pos, ASTEROID_WIDTH, ASTEROID_HEIGHT, asteroid_sprite_3);

   
        } else {
            x_pos = rand()% 95 + 15;    //random number between 15 and 110
            y_pos = rand()% 5 + 10;     //random number between 15 and 20
            deltaX = (rand() % 4+1) - 2;
            deltaY =  (rand() % 3+1);
        }
    }
};
class ConcreteAstroid4: public AbstractAstroid
{
public:
    void draw() {
        x_pos = rand()% 15 + 15;    //random number between 15 and 110
        y_pos = rand()% 5 + 15; //random number between 15 and 20
        deltaX = (rand() % 3+1) - 2;
        deltaY =  (rand() % 3+1);
   
        uLCD.BLIT(x_pos, y_pos, ASTEROID_WIDTH, ASTEROID_HEIGHT, asteroid_sprite_4); // draw the astroid
    }
    void update() {
        x_pos +=deltaX;
        y_pos += deltaY;
        uLCD.filled_rectangle(x_pos-3, y_pos-3, x_pos+17, y_pos+14, BLACK);
        if ((x_pos < 110 && x_pos > 15) && (y_pos < 110 && y_pos > 15)) {

            uLCD.BLIT(x_pos, y_pos, ASTEROID_WIDTH, ASTEROID_HEIGHT, asteroid_sprite_4);

  
        } else {
            x_pos = rand()% 95 + 15;    //random number between 15 and 110
            y_pos = rand()% 5 + 15;     //random number between 15 and 20
            deltaX = (rand() % 4+1) - 2;
            deltaY =  (rand() % 3+1);
        }
    }
};


bool overlap(ScreenObject & objectA, ScreenObject & objectB)
{
    int EX = objectA.getX();
    int EY = objectA.getY();
    int AX = objectB.getX();
    int AY = objectB.getY();

    int LCX = EX - ASTEROID_WIDTH+5;
    int LCY = EY - ASTEROID_HEIGHT+5;
    int RCX = AX + EARTH_WIDTH-4;
    int RCY = AY + EARTH_HEIGHT-4;

    if ((AX > LCX) && (AX < RCX) && (AY > LCY) && (AY < RCY))
        return true;

    else
        return false;
}


int main()
{
    Timer timer1;       // timer object built in function
    double length;
    double lengthh;
    timer1.start();     // start timer object

    uLCD.filled_rectangle(1,1, 125,9, GREEN); // timing bar first instance
 
 
    uLCD.baudrate(300000); // refresh rate of LCD screen
    wait(0.2);
    srand(time(0));
    ScreenObject * ActiveAsteroids[NUM_ASTEROIDS];  // creates an array of pointers
    ActiveAsteroids[0] = new ConcreteAstroid1;
    ActiveAsteroids[1] = new ConcreteAstroid2;
    ActiveAsteroids[2] = new ConcreteAstroid3;
    ActiveAsteroids[3] = new ConcreteAstroid4;

    SpaceShipEarth earth;

    // you can play around with the parameters to see the response
    double factor = 50;
    double music_factor = 200;
    bool MusicOn = false;
    //set the push buttons that control sounds
    pb1.mode(PullUp);
    pb2.mode(PullUp);
    //I will not use interupts like in jazzy tunes
    double x = 0, y = 0, z = 0;
    MMA8452 acc(p9, p10, 40000);  //instantiate an acc object!
    //set parameters -- use these and don't change
    acc.setBitDepth(MMA8452::BIT_DEPTH_12);
    acc.setDynamicRange(MMA8452::DYNAMIC_RANGE_4G);
    acc.setDataRate(MMA8452::RATE_100);

    earth.draw();                // draw the original earth
    ActiveAsteroids[0]->draw();  // draw first astroid
    wait(0.2);
    ActiveAsteroids[1]->draw();
    wait(0.2);
    ActiveAsteroids[2]->draw();
    wait(0.2);
    ActiveAsteroids[3]->draw();
    wait(0.2);
    bool overlapp1;
    bool overlapp2;
    bool overlapp3;
    bool overlapp4;

    while(1) {
        wait(0.05);
        earth.update();
        ActiveAsteroids[0]->update();
        ActiveAsteroids[1]->update();
        ActiveAsteroids[2]->update();
        ActiveAsteroids[3]->update();
        
        length = timer1.read_ms(); // length of time class
        lengthh = .015*length;
        uLCD.filled_rectangle(1,1, lengthh, 9, BLACK); //time class destructing bar
        if(lengthh > 124) 
           break;
            
     overlapp1 = overlap(earth , (*ActiveAsteroids[0]));
     overlapp2 = overlap(earth , (*ActiveAsteroids[1]));
     overlapp3 = overlap(earth , (*ActiveAsteroids[2]));
     overlapp4 = overlap(earth , (*ActiveAsteroids[3]));
     
        if(overlapp1 || overlapp2 || overlapp3 || overlapp4)
            break;
        
            if(!acc.isXYZReady()) {
                wait(0.01);
            } else {

                acc.readXYZGravity(&x,&y,&z); //notice this is passed by reference use pointers
                if(x>0.3) {
                    earth.moveRight(2);
                } else if(x<-0.3) {
                    earth.moveLeft(2);
                } else if(y>0.3) {
                    earth.moveForward(2);
                } else if(y<-0.3) {
                    earth.moveBack(2);
                }


                

                if (pb1 == false)
                    MusicOn = true;

                if ((pb2 == false) && BombUsed){
                    
                    BombUsed = false;
                    
                    //uLCD.cls();
                   
                    ActiveAsteroids[0]->explode();
                    wait(0.04);
                    ActiveAsteroids[1]->explode();
                    wait(0.04);
                    ActiveAsteroids[2]->explode();
                    wait(0.04);
                    ActiveAsteroids[3]->explode();
                    wait(0.04);
                  
                    ActiveAsteroids[0]->draw();
                    ActiveAsteroids[1]->draw();
                    ActiveAsteroids[2]->draw();
                    ActiveAsteroids[3]->draw();
                    
                    mySpeaker.PlayNote(160.0+x*music_factor,.4+0.2*y,0.05);
                    wait(0.04);
                    mySpeaker.PlayNote(200.0+x*music_factor,.3+0.2*y,0.05);
                    wait(0.04);
                    mySpeaker.PlayNote(260.0+x*music_factor,.5+0.2*y,0.05);
                    
                    
                    
                    wait(0.9);}
                     
                   
//                 if (!BombUsed){
//                    mySpeaker.PlayNote(160.0+x*music_factor,.4+0.2*y,0.05);
//                    wait(0.04);
//                    mySpeaker.PlayNote(200.0+x*music_factor,.3+0.2*y,0.05);
//                    wait(0.04);
//                    mySpeaker.PlayNote(260.0+x*music_factor,.5+0.2*y,0.05); 
//                }
                 // } //end if bomb used
                       

                // You can uncomment this line to see the values coming off the MMA8452
                //uLCD.printf("\n(%.2f,%.2f,%.2f)  \n", x,y,z);
            }                                                                 //end acc Gravity else

    } //end infinite while loop
    
    //uLCD.cls();
    if(overlapp1 || overlapp2 || overlapp3 || overlapp4)
    {
        earth.explode();
        
        uLCD.printf("\n\n\n\n\n\n\n\n\n You lose ", x,y,z);
                    mySpeaker.PlayNote(80.0+x*music_factor,.5+0.2*y,0.05);
                    mySpeaker.PlayNote(50.0+x*music_factor,.4+0.2*y,0.05);
                    wait(0.04);
                    mySpeaker.PlayNote(30.0+x*music_factor,.7+0.2*y,0.05);
        }
        else{
        uLCD.printf("\n\n\n\n\n\n\n\n\n You Win ", x,y,z);
             }  
   



} // end main