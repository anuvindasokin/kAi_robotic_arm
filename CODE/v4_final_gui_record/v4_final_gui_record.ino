/*
button 3 toggles between recording and playing
RECORDING
------------
Button1 toggles save points
Button2 saves current point to save point

PLAYING
--------
Button1 pause/start playing
Button 2 set start and end points when paused
putton 3 next*/


#include <Servo.h> 

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>// display library

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
//Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)

///////////////////////////////connect to pc public////////////////////////////////

String readString, servoA, servoB, servoC, servoD, servoE, servoF;  // Strings for 6 servos (2 manipulator servos are considered as servo6)
int posp;  // Declare servo angle variable as integer

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

Sweeper sweeper1(20);
Sweeper sweeper2(20);
Sweeper sweeper3(20);
Sweeper sweeper4(20);
Sweeper sweeper5(20);
Sweeper sweeper6(20);
Sweeper sweeper7(20);


Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

#define noofpoints 30

//define the servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

//define the buttons
const int button1 = 2;
const int button2 = 14;
const int button3 = 15;

int button1pressed = 0;

//define potentiometers
const int pot1 = A0;
const int pot2 = A1;
const int pot3 = A2;
const int pot4 = A3;
const int pot5 = A4;
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
int servo1PosSave[]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int servo2PosSave[]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int servo3PosSave[]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int servo4PosSave[]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int servo5PosSave[]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int servo6PosSave[]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

void setup() {

  display.begin();
  display.setContrast(50);
  display.clearDisplay();
  
  //define attached pins of the servos
  servo1.attach(13);
  servo2.attach(12);
  servo3.attach(11);
  servo4.attach(10);
  servo5.attach(9);
  servo6.attach(8);

  //define buttons as input units
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  Serial.begin(9600);
  
 ////////////////connecttopc/////////////////
  sweeper1.Attach(13);
  sweeper2.Attach(12);
  sweeper3.Attach(11);
  sweeper4.Attach(10);
  sweeper5.Attach(9);
  sweeper6.Attach(8);
  //sweeper7.Attach(8);

  // Call Update() and Update2() functions:
  sweeper1.Update();
  sweeper2.Update();
  sweeper3.Update();
  sweeper4.Update();
  sweeper5.Update();
  sweeper6.Update();
  //sweeper7.Update2();
 /////////////////////////////////////////// 
  
}

int menu=0;

void record(){
  delay(500);
  while(digitalRead(button3)==LOW) //exit on button 3 pressed
  {
    drawMenu1("RECORD POINT","Save Point"+(String)(button1pressed),"Save Point"+(String)(button1pressed+1),"Save Point"+(String)(button1pressed+2),1);
    

    if(digitalRead(button1)==HIGH)
    { //toggle between save points
      button1pressed++;
      button1pressed%=30;
      delay(100);
    }
  //Read and map potentiometer values  
    pot1Val = analogRead(pot1);
    pot1Angle = map (pot1Val, 0, 1023, 0, 179);
    pot2Val = analogRead(pot2);
    pot2Angle = map (pot2Val, 0, 1023, 0, 179);
    pot3Val = analogRead(pot3);
    pot3Angle = map (pot3Val, 0, 1023, 0, 179);
    pot4Val = analogRead(pot1);
    pot4Angle = map (pot1Val, 0, 1023, 0, 179);
    pot5Val = analogRead(pot2);
    pot5Angle = map (pot2Val, 0, 1023, 0, 179);
    pot6Val = analogRead(pot3);
    pot6Angle = map (pot3Val, 0, 1023, 0, 90);

    
 //servos move to mapped angles
    servo1.write(pot1Angle);
    servo2.write(pot2Angle);
    servo3.write(pot3Angle);
    servo4.write(pot1Angle);
    servo5.write(pot2Angle);
    servo6.write(pot3Angle);

    if(digitalRead(button2)==HIGH)
    {
        servo1PosSave[button1pressed] = pot1Angle;
        servo2PosSave[button1pressed] = pot2Angle;
        servo3PosSave[button1pressed] = pot3Angle;
        servo4PosSave[button1pressed] = pot4Angle;
        servo5PosSave[button1pressed] = pot5Angle;
        servo6PosSave[button1pressed] = pot6Angle;
        button1pressed++;
        button1pressed%=30;
        delay(100);
    } 

    if(digitalRead(button3)==HIGH)
      {Serial.print("exit");return;}
  }
}

void play()
  delay(500);
 int current=0; 
 int start=0;
 int finish=noofpoints;
 
  setpoints:
  while(digitalRead(button3)==LOW)  //select start
  {
    Serial.println("Select Start Point");
    if(digitalRead(button2)==HIGH){
      if(current<noofpoints){
        current++;
        delay(100);
      }
    }
    if(digitalRead(button1)==HIGH){
      if(current>0){
        current--;
        delay(100);
      }
    }
    drawMenu("START POINT","","Save point:"+(String)current,"",1);

    if(digitalRead(button3)==HIGH)
      goto stoppointselect;
  }

  stoppointselect:
  delay(100);
  while(digitalRead(button3)==LOW)  //select stop
  {
    Serial.println("Select Stop Point");
    if(digitalRead(button1)==HIGH){
      if(finish<noofpoints){
        finish++;
        delay(100);
      }
    }
    if(digitalRead(button2)==HIGH){
      if(finish>0){
        finish--;
        delay(100);
      }
    }
    drawMenu("END POINT","","Save point:"+(String)finish,"",1);

    if(digitalRead(button3)==HIGH)
      goto play;
      
  }
   
  play:
  delay(100);
  int tmp=0;
  while(digitalRead(button3)==LOW)  // play
  {
    Serial.println("Playing");
    int flag=0;
    for(int i=start; i<finish; i++){
      int j=i;
        servo1.write(servo1PosSave[i]);
        servo2.write(servo2PosSave[i]);
        servo3.write(servo3PosSave[i]);
        servo4.write(servo4PosSave[i]);
        servo5.write(servo5PosSave[i]);
        servo6.write(servo6PosSave[i]);
        

        if(digitalRead(button1)==HIGH){
          tmp++;
          tmp%=2;
          delay(200);
        }
        if(tmp==1){
          drawMenu("PLAYBACK","","PAUSED","",1);
          i=j-1;
        }
        else{
          drawMenu("PLAYBACK","",(String)i,"",1);
        }
        if(digitalRead(button3)==HIGH){  //exit
          Serial.println("Returning to MainMenu");
          return;
        }

        
        long tim=millis();
        while(millis()-tim<2000){                //delay(2000)
            if(digitalRead(button1)==HIGH){
              tmp++;
              tmp%=2;
              delay(200);
            }
            if(tmp==1){
              drawMenu("PLAYBACK","","PAUSED","",1);
              i=j-1;
            }
            else{
              drawMenu("PLAYBACK","",(String)i,"",1);
            }
            if(digitalRead(button3)==HIGH){  //exit
               Serial.println("Returning to MainMenu");
               return;
            }
        }
     }
  } 
}

void mainmenu(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK,WHITE);
  display.setCursor(15,0);
  display.print("ARM TRAINER");
  display.drawFastHLine(0,10,83,BLACK);
  display.setCursor(0,15);

    if(menu==0)
    {
      display.setTextColor(WHITE,BLACK);
    }
    else
    {
      display.setTextColor(BLACK,WHITE);
    }
    display.print(">RECORD");
    display.setCursor(0,25);

    if(menu==1)
    {
      display.setTextColor(WHITE,BLACK);
    }
    else
    {
      display.setTextColor(BLACK,WHITE);
    }
    display.print(">PLAY");
    display.setCursor(0,35);

    if(menu==2)
    {
      display.setTextColor(WHITE,BLACK);
    }
    else
    {
      display.setTextColor(BLACK,WHITE);
    }
    display.print(">CONNECT");
    display.setCursor(0,35);
    display.display();
}

void drawMenu1(String title,String item1,String item2,String item3,int menu){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK,WHITE);
  display.setCursor(0,0);
  display.print(title);
  display.drawFastHLine(0,10,83,BLACK);
  display.setCursor(0,15);

    if(menu==0)
    {
      display.setTextColor(WHITE,BLACK);
    }
    else
    {
      display.setTextColor(BLACK,WHITE);
    }
    display.print(">"+item1);
    display.setCursor(0,25);

    if(menu==1)
    {
      display.setTextColor(WHITE,BLACK);
    }
    else
    {
      display.setTextColor(BLACK,WHITE);
    }
    display.print(">"+item2);
    display.setCursor(0,35);

    if(menu==2)
    {
      display.setTextColor(WHITE,BLACK);
    }
    else
    {
      display.setTextColor(BLACK,WHITE);
    }
    display.print(">"+item3);
    display.setCursor(0,35);
    display.display();
}

void drawMenu(String title,String item1,String item2,String item3,int menu){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK,WHITE);
  display.setCursor(15,0);
  display.print(title);
  display.drawFastHLine(0,10,83,BLACK);
  display.setCursor(0,15);

    if(menu==0)
    {
      display.setTextColor(WHITE,BLACK);
    }
    else
    {
      display.setTextColor(BLACK,WHITE);
    }
    display.print(">"+item1);
    display.setCursor(0,25);

    if(menu==1)
    {
      display.setTextColor(WHITE,BLACK);
    }
    else
    {
      display.setTextColor(BLACK,WHITE);
    }
    display.print(">"+item2);
    display.setCursor(0,35);

    if(menu==2)
    {
      display.setTextColor(WHITE,BLACK);
    }
    else
    {
      display.setTextColor(BLACK,WHITE);
    }
    display.print(">"+item3);
    display.setCursor(0,35);
    display.display();
}


void startconnection(){
  while (Serial.available()>0) {  //get string from serial monitor
   delay(10);  
   if(digitalRead(button3)==HIGH)
      return;
   char c = Serial.read();
   readString += c;     
  }

  if (readString.length() >0) {  // Proceed if the string has any character
 
     servoA = readString.substring(0, 3); // Get first three characters of string
     
     servoB = readString.substring(3, 6); // Get second three characters of string

     servoC = readString.substring(6, 9); // And so on...
    
     servoD = readString.substring(9, 12);
     
     servoE = readString.substring(12, 15);

     servoF = readString.substring(15, 18);
 
 }

 char carray1[18];  // Create 18-digit array to store values of all servos
     // Convert servo1 angle string into an integer number (posp):
     servoA.toCharArray(carray1, sizeof(carray1));
     posp = atoi(carray1);
     Serial.println(posp);  // Send posp value to serial port
     sweeper1.Update();  // Update sweeper function for servo1
     
     // Proceed the same way with the other servos (for servo 6, sweeper6.Update() and sweeper7.Update2() are used):    
     char carray2[18];
     servoB.toCharArray(carray2, sizeof(carray2));
     posp = atoi(carray2);
     sweeper2.Update();
     
     char carray3[18];
     servoC.toCharArray(carray3, sizeof(carray3));
     posp = atoi(carray3);
     sweeper3.Update();
     
     char carray4[18];
     servoD.toCharArray(carray4, sizeof(carray4));
     posp = atoi(carray4);
     sweeper4.Update();
     
     char carray5[18];
     servoE.toCharArray(carray5, sizeof(carray5));
     posp = atoi(carray5);
     sweeper5.Update();

     char carray6[18];
     servoF.toCharArray(carray6, sizeof(carray6));
     posp = atoi(carray6);
     sweeper6.Update();
     //sweeper7.Update2();    

    readString="";  // Clear string variable for new input 
  
}

void connecttopc(){
  delay(500);
  while(digitalRead(button3)==LOW){ //press any button to disconnect
    if(digitalRead(button3)==HIGH)
      return;
     drawMenu("PC CONTROL","","SERIAL INPUT","",1);
     startconnection();
  }
}

void loading(){
  
}

void loop() {

  //while(digitalRead(button3)==LOW){
    if(digitalRead(button2)==HIGH){
       menu++;
      if(menu>2)
        menu=2;
        Serial.println("Select "+(String)menu);
      delay(100);
    }
    if(digitalRead(button1)==HIGH){
      menu--;
      if(menu<0)
        menu=0;
        Serial.println("Select "+(String)menu);
      delay(100);
    }
    mainmenu();
  //}
  
 if(digitalRead(button3)==HIGH){
    delay(300);
   switch(menu){
    case 0:Serial.println("a");
           record(); //record
           break;
    case 1:Serial.println("b");
           delay(100);
           play(); //play
           break;
    case 2:Serial.println("c");
           delay(100);
           connecttopc();
           break;    
   }
   delay(400);      
 }  
}
