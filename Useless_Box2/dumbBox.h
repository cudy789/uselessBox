#include "smartSwitch.h"
#include "smartFinger.h"
#include "event.h"
#include <vector>
#include <queue>
using namespace std;

// CHANGE THE FOLLOWING TO TUNE YOUR USELESS BOX! //

double ARMED_ANGLE = 120;
double ATTACK_ANGLE = 40;
double ACTUATE_REST_ANGLE = 175;
double TURN_REST_ANGLE = 100;
int TURNING_DELAY = 220;

class dumbBox{
    public:
        dumbBox(char inName[200], int inTotalSwitches, vector<double> inSwitchAngles){
            switchAngles = inSwitchAngles;
            myFinger = new smartFinger(0,1); // Rotate servo angle, actuate servo angle
            sprintf(name, "%s", inName);
            totalSwitches = inTotalSwitches;
            for (int i(2); i<totalSwitches+2; ++i){ // assign switches to pins 
                switches.push_back(smartSwitch(switchAngles[i-2], i));
            }
            myFinger = new smartFinger(0, 1);
            SYSTEM_MODE(SEMI_AUTOMATIC);
            pinMode(D5, INPUT_PULLDOWN); // setup rocker switch to input
            lastRockerState != digitalRead(D5);
            setNetwork();
        }
        
        void run(){
            setConfig();
            addToQueue();
            while (!events.empty()){
                myFinger->turn((double)switches[events.front().switchNum-2].getAngle());
                char publish_string[40];
                delay(TURNING_DELAY);
                myFinger->actuate(ATTACK_ANGLE);
                while (switches[events.front().switchNum-2].isOn()){}
                events.pop();
                if (events.size() >=1){
                    myFinger->actuate(ARMED_ANGLE);
                }
                else{
                    addToQueue();
                    if (events.size() >=1){
                        myFinger->actuate(ARMED_ANGLE);
                    }
                    else{
                        myFinger->actuate(ACTUATE_REST_ANGLE);
                        myFinger->turn(TURN_REST_ANGLE);
                    }
                }
            }
        }
    
    private:
        void addToQueue(){
            for (int i(0); i<totalSwitches; ++i){
                if (switches[i].isOn()){
                    events.push(event(i+2, 1));
                }
            }
        }
        void setConfig(){
            if (digitalRead(D5) == true && lastRockerState == false){
                setNetwork();
            }
            else if (digitalRead(D5) == false && lastRockerState == true){
                setLocal();
            }
        }
        void setLocal(){
            WiFi.off();
            lastRockerState=false;
        }
        void setNetwork(){
            SYSTEM_MODE(AUTOMATIC);
            WiFi.on();
            WiFi.connect();
            lastRockerState=true;
            delay(1000);
            Particle.publish(name, "is in network mode!");

        }
        
        vector<smartSwitch> switches; // FRONT - D2, D3, D4 - BACK
        vector<double> switchAngles; // FRONT - D2, D3, D4 - BACK
        smartFinger* myFinger;
        int totalSwitches;
        
        queue<event> events;
        char name[200];
        bool lastRockerState;
        
};