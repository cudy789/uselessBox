class smartSwitch{
    
    public:
        smartSwitch(double inAngle, int inPinNum = D0){
            angle = inAngle;
            pinNum = inPinNum;
            pinMode(pinNum, INPUT_PULLDOWN);
        }
        bool isOn(){
            state = digitalRead(pinNum);
            return state;
        }
        double getAngle(){
            return angle;
        }
        
        
    private:
        double angle;
        int pinNum;
        bool state = 0;
};