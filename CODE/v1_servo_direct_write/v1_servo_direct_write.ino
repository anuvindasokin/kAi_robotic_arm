#include <Servo.h>//Servo Library
// Define Potentiometers
int pot1=A0;
int pot2=A1;
int pot3=A2;
int pot4=A3;
int pot5=A4;
int pot6=A5;

//define variable for values of the potentiometers
int val1=0;
int val2=0;
int val3=0;
int val4=0;
int val5=0;
int val6=0;

//define the servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

void setup{
 //define attached pins of the servos
    servo1.attach(3);
    servo2.attach(4);
    servo3.attach(5);
    servo4.attach(6);
    servo5.attach(7);
    servo6.attach(8);
    
}
void loop{
   //read the potentiometer values
  val1=analogRead(pot1);
  val2=analogRead(pot2);
  val3=analogRead(pot3);
  val4=analogRead(pot4);
  val5=analogRead(pot5);
  val6=analogRead(pot6);

  //Map potentiometer values  
  val1=map(val1,0,1023,0,180);
  val2=map(val2,0,1023,0,180);
  val3=map(val3,0,1023,0,180);
  val4=map(val4,0,1023,0,180);
  val5=map(val5,0,1023,0,180);
  val6=map(val6,0,1023,0,180);
  
  //servos move to mapped angles
  servo1.write(val1);
  servo2.write(val2);
  servo3.write(val3);
  servo4.write(val4);
  servo5.write(val5);
  servo6.write(val6);
}
