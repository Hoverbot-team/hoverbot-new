#include "movement/movement.hpp"
#include <iostream>
using namespace std;
movement::movement(int speedPinLeft, int dirPinLeft, int speedPinRight, int dirPinRight) : eng_L(speedPinLeft, dirPinLeft), eng_R(speedPinRight, dirPinRight)
{
    // Any additional initialization code here
}

movement::~movement() {
    eng_L.stop();
    eng_R.stop();
}

void movement::safe(){
    while(abs(movement::gyro.read_gaccel_X()) < 60){
        
    }
    eng_L.stop();
    eng_R.stop();
    cout<<"automatic shutdown event occured"<<endl;
    exit(0);
    
}
void movement::stop(){
    eng_L.stop();
    eng_R.stop();
    cout << "Engines stopped." << endl;
}