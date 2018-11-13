// #include "event.h"
// #include "smartFinger.h"
// #include "smartSwitch.h"
#include "dumbBox.h"
#include <vector>

dumbBox* myBox;

void setup() {
    vector<double> myAngles;
    // CHANGE THESE TO TUNE YOUR USELESS BOX! //
    // Switch angles go CCW starting with D2 //
    myAngles.push_back(67); //D2's angle
    myAngles.push_back(113); //D3's angle
    myAngles.push_back(163); //D4's angle
    myBox = new dumbBox("myBox", 3, myAngles); // boxName, number of switches, vector of switch position angles
}

void loop() {
    myBox->run();
}