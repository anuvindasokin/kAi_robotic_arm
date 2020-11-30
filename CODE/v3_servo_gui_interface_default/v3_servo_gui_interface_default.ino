
#include <Servo.h>  // Include Servo library  

// Declare potentiometers analog pins:
int potpin1 = 0;
int potpin2 = 1;
int potpin3 = 2;
int potpin4 = 3;
int potpin5 = 4;
int potpin6 = 5;

int posp;  // Declare servo angle variable as integer

String readString, servo1, servo2, servo3, servo4, servo5, servo6;  // Strings for 6 servos 
int jumpto;  // Jumpto variable (this will be used to switch between serial and control box control).


class Sweeper  // Needed for millis() function

{
  Servo servo;  // Servo object
  int pos;  // Declare second servo angle variable as integer
  int increment;  // Declare increment variable (needed for millis() function)
  int  updateInterval;  // Needed for millis() function
  unsigned long lastUpdate; // Needed for millis() function

// SERVO CONTROL WITH millis() FUNCTION:

public: 
  Sweeper(int interval)
  {
    updateInterval = interval;
    increment = 1;  // Change this value to modify the servo speed
  }
  
  void Attach(int pin)
  {
    servo.attach(pin);
  }
  
  void Detach()
  {
    servo.detach();
  }

// Motion of servos 1 to 5:  
  void Update()
  {
 if ((posp >= pos)){
    if((millis() - lastUpdate) > updateInterval) 
    {
      lastUpdate = millis();
      pos += increment;
      servo.write(pos);
      Serial.println(pos);
    }
    }
    
 else{
    if((millis() - lastUpdate) > updateInterval)  
    {
      lastUpdate = millis();
      pos -= increment;
      servo.write(pos);
      Serial.println(pos);
    }
    }
  }

// Motion of servo 6 (two manipulator servos, moving in opposite directions):
  void Update2()
  {
 if ((posp < pos)){
    if((millis() - lastUpdate) > updateInterval) 
    {
      lastUpdate = millis();
      pos -= increment;
      servo.write(90-pos);
      Serial.println(pos);
    }
    }
    
 else{
    if((millis() - lastUpdate) > updateInterval) 
    {
      lastUpdate = millis();
      pos += increment;
      servo.write(90-pos);
      Serial.println(pos);
    }
    }
  } 
};
 
// Define sweeper function for every servo:
Sweeper sweeper1(20);
Sweeper sweeper2(20);
Sweeper sweeper3(20);
Sweeper sweeper4(20);
Sweeper sweeper5(20);
Sweeper sweeper6(20);
Sweeper sweeper7(20);

void setup() 
{ 
  Serial.begin(9600);  // Open serial port and set data rate to 9600 bps
  
  // Define servos digital pins:
  sweeper1.Attach(2);
  sweeper2.Attach(3);
  sweeper3.Attach(4);
  sweeper4.Attach(5);
  sweeper5.Attach(6);
  sweeper6.Attach(7);
  sweeper7.Attach(8);

  // Call Update() and Update2() functions:
  sweeper1.Update();
  sweeper2.Update();
  sweeper3.Update();
  sweeper4.Update();
  sweeper5.Update();
  sweeper6.Update();
  sweeper7.Update2();

  while(Serial.available()==0 && millis()<4000);  // Wait for up to 4 sec. if no data is received

  if(Serial.available()>0)  // Proceed if there’s data received:
  {
    jumpto = 1; // Set jumpto variable to 1 
  }
} 
 
 
void loop() 
{ 
  if(jumpto==1){  // If jumpto was set to 1, the robot arm will be controlled through the serial port: 
  
 while (Serial.available()>0) {  // Proceed only when there is data received
   delay(10);  

     char c = Serial.read();  // Get one byte from the serial buffer
     readString += c;  // Read characters from serial buffer into a string
     
  }

if (readString.length() >0) {  // Proceed if the string has any character
 
     servo1 = readString.substring(0, 3); // Get first three characters of string
     
     servo2 = readString.substring(3, 6); // Get second three characters of string

     servo3 = readString.substring(6, 9); // And so on...
    
     servo4 = readString.substring(9, 12);
     
     servo5 = readString.substring(12, 15);

     servo6 = readString.substring(15, 18);
 
 }
     char carray1[18];  // Create 18-digit array to store values of all servos
     // Convert servo1 angle string into an integer number (posp):
     servo1.toCharArray(carray1, sizeof(carray1));
     posp = atoi(carray1);
     Serial.println(posp);  // Send posp value to serial port
     sweeper1.Update();  // Update sweeper function for servo1
     
     // Proceed the same way with the other servos (for servo 6, sweeper6.Update() and sweeper7.Update2() are used):    
     char carray2[18];
     servo2.toCharArray(carray2, sizeof(carray2));
     posp = atoi(carray2);
     sweeper2.Update();
     
     char carray3[18];
     servo3.toCharArray(carray3, sizeof(carray3));
     posp = atoi(carray3);
     sweeper3.Update();
     
     char carray4[18];
     servo4.toCharArray(carray4, sizeof(carray4));
     posp = atoi(carray4);
     sweeper4.Update();
     
     char carray5[18];
     servo5.toCharArray(carray5, sizeof(carray5));
     posp = atoi(carray5);
     sweeper5.Update();

     char carray6[18];
     servo6.toCharArray(carray6, sizeof(carray6));
     posp = atoi(carray6);
     sweeper6.Update();
     sweeper7.Update2();    

    readString="";  // Clear string variable for new input    

  } 

 else{  // If jumpto was NOT set to 1, the robot arm will be controlled manually with the control box:

  posp = analogRead(potpin1);  // Read analog input from potentiometer 
  posp = map(posp, 10, 1023, 0, 170);  // Map down the potentiometer input from its original range (0 to 1024) to 0 to 180 deg.

  sweeper1.Update();  // Update sweeper function for servo1
  
  // Proceed the same way with the other servos:  
  posp = analogRead(potpin2);  
  posp = map(posp, 0, 1023, 0, 180);
  
  sweeper2.Update();

  posp = analogRead(potpin3);  
  posp = map(posp, 0, 1023, 0, 180);
  
  sweeper3.Update();  
  
  posp = analogRead(potpin4);  
  posp = map(posp, 0, 1023, 0, 180);
  
  sweeper4.Update();  
  
  posp = analogRead(potpin5);  
  posp = map(posp, 0, 1023, 0, 180);
  
  sweeper5.Update();  
  
  posp = analogRead(potpin6);  
  posp = map(posp, 0, 1023, 30, 60);
  
  sweeper6.Update();  
  sweeper7.Update2();
   
  }
}
 
