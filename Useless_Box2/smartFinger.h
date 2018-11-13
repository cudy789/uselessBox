class smartFinger{
    public:
        smartFinger(int inRotateServo, int inActuateServo){
            rotateServo.attach(inRotateServo);
            actuateServo.attach(inActuateServo);
        }
        void turn(double angle){
            rotateServo.write(angle);
        }
        void actuate(double angle){
            actuateServo.write(angle);
        }
        
    private:
        Servo rotateServo;
        Servo actuateServo;
};