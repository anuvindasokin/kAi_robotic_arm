#include <Servo.h> 
//define servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

//define buttons
const int button1 = 2;
const int button2 = 14;

//define variable for values of the button
int button1Pressed = 0;
boolean button2Pressed = false;

//define potentiometers
const int pot1 = A0;
const int pot2 = A1;
const int pot3 = A2;
const int pot4 = A3;
const int pot5= A4;
const int pot6 = A5;

//define variable for values of the potentiometers
int pot1Val;
int pot2Val;
int pot3Val;
int pot4Val;
int pot5Val;
int pot6Val;

//define variable for angles of the potentiometer
int pot1Angle;
int pot2Angle;
int pot3Angle;
int pot4Angle;
int pot5Angle;
int pot6Angle;

//define variable for saved position of the servos
int servo1PosSave[]={1,1,1,1,1};
int servo2PosSave[]={1,1,1,1,1};
int servo3PosSave[]={1,1,1,1,1};
int servo4PosSave[]={1,1,1,1,1};
int servo5PosSave[]={1,1,1,1,1};
int servo6PosSave[]={1,1,1,1,1};

void setup() {
  //define attached pins of the servos
  servo1.attach(13);
  servo2.attach(12);
  servo3.attach(11);
  servo1.attach(10);
  servo2.attach(9);
  servo3.attach(8);
  //define buttons as input units
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);

  //initialize serial communication for saved position
  Serial.begin(9600);
}

void loop() {
  //read the potentiometer values and map the values
  pot1Val = analogRead(pot1);
  pot1Angle = map (pot1Val, 0, 1023, 0, 179);
  pot2Val = analogRead(pot2);
  pot2Angle = map (pot2Val, 0, 1023, 0, 179);
  pot3Val = analogRead(pot3);
  pot3Angle = map (pot3Val, 0, 1023, 0, 90);
   pot4Val = analogRead(pot4);
  pot4Angle = map (pot4Val, 0, 1023, 0, 179);
  pot5Val = analogRead(pot5);
  pot5Angle = map (pot5Val, 0, 1023, 0, 179);
  pot6Val = analogRead(pot6);
  pot6Angle = map (pot6Val, 0, 1023, 0, 90);

  //servos move to mapped angles
  servo1.write(pot1Angle);
  servo2.write(pot2Angle);
  servo3.write(pot3Angle);
  servo1.write(pot4Angle);
  servo2.write(pot5Angle);
  servo3.write(pot6Angle);

  //if button1 is pressed (HIGH), save the potentiometers position
  //as long as button1 is pressed
  if(digitalRead(button1) == HIGH){
    button1Pressed++;
    switch(button1Pressed){
      case 1:
        servo1PosSave[0] = pot1Angle;
        servo2PosSave[0] = pot2Angle;
        servo3PosSave[0] = pot3Angle;
        servo4PosSave[0] = pot4Angle;
        servo5PosSave[0] = pot5Angle;
        servo6PosSave[0] = pot6Angle;
        
        Serial.println("Position #1 Saved");
       break;
       case 2:
        servo1PosSave[1] = pot1Angle;
        servo2PosSave[1] = pot2Angle;
        servo3PosSave[1] = pot3Angle;
        servo4PosSave[1] = pot4Angle;
        servo5PosSave[1] = pot5Angle;
        servo6PosSave[1] = pot6Angle;
        Serial.println("Position #2 Saved");
       break;
       case 3:
        servo1PosSave[2] = pot1Angle;
        servo2PosSave[2] = pot2Angle;
        servo3PosSave[2] = pot3Angle;
        servo4PosSave[2] = pot4Angle;
        servo5PosSave[2] = pot5Angle;
        servo6PosSave[2] = pot6Angle;
        Serial.println("Position #3 Saved");
       break;
       case 4:
        servo1PosSave[3] = pot1Angle;
        servo2PosSave[3] = pot2Angle;
        servo3PosSave[3] = pot3Angle;
        servo4PosSave[3] = pot4Angle;
        servo5PosSave[3] = pot5Angle;
        servo6PosSave[3] = pot6Angle;
        Serial.println("Position #4 Saved");
       break;
       case 5:
        servo1PosSave[4] = pot1Angle;
        servo2PosSave[4] = pot2Angle;
        servo3PosSave[4] = pot3Angle;
        servo4PosSave[4] = pot4Angle;
        servo5PosSave[4] = pot5Angle;
        servo6PosSave[4] = pot6Angle;
        Serial.println("Position #5 Saved");
       break;
    }
  }
  //if button2 pressed (HIGH), the servos move saved position
  if(digitalRead(button2) == HIGH){
    button2Pressed = true;
  }
  if(button2Pressed){
    for(int i=0; i<5; i++){
      servo1.write(servo1PosSave[i]);
      servo2.write(servo2PosSave[i]);
      servo3.write(servo3PosSave[i]);
      servo4.write(servo4PosSave[i]);
      servo5.write(servo5PosSave[i]);
      servo6.write(servo6PosSave[i]);
      delay(2000);
    }
  }
  delay(500);
}
