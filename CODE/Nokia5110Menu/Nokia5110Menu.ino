#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

boolean backlight = true;
int contrast=50;

int menuitem = 1;
int page = 1;

volatile boolean up = false;
volatile boolean down = false;
volatile boolean middle = false;

volatile boolean axis1=false;
volatile boolean axis2=false;
volatile boolean axis3=false;
volatile boolean axis4=false;
volatile boolean axis5=false;
volatile boolean axis6=false;


int downButtonState = 0;
int upButtonState = 0;  
int selectButtonState = 0;          
int lastDownButtonState = 0;
int lastSelectButtonState = 0;
int lastUpButtonState = 0;

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

void setup() {

  pinMode(2,INPUT);
  pinMode(14,INPUT);
  pinMode(15,INPUT);
  pinMode(11,OUTPUT);

  digitalWrite(7,LOW); //Turn Backlight ON
  
  Serial.begin(9600);
  
  display.begin();      
  display.setContrast(contrast); //Set contrast to 50
  display.clearDisplay(); 
  display.display();   
}

void loop() {
  
  drawMenu();

  downButtonState = digitalRead(8);
  selectButtonState = digitalRead(9);
  upButtonState =   digitalRead(10);
 
  checkIfDownButtonIsPressed();
  checkIfUpButtonIsPressed();
  checkIfSelectButtonIsPressed();

  if (up && page == 1 ) {
    up = false;
    menuitem--;
    if (menuitem==0)
    {
      menuitem=3;
    }      
  }else if (up && page == 2 ) {
    up = false;
    contrast--;
    setContrast();
  }

  else if (up && page == 3 ) //axis2
  {
    up = false;
    contrast--;
    setContrast();
  }



  if (down && page == 1) {
    down = false;
    menuitem++;
    if (menuitem==4) 
    {
      menuitem=1;
    }      
  }else if (down && page == 2 ) {
    down = false;
    contrast++;
    setContrast();
  }


  if (middle) {
    middle = false;
    
    if (page == 1 && menuitem==2) 
    {
      if (backlight) 
      {
        backlight = false;
        turnBacklightOff();
        }
      else 
      {
        backlight = true; 
        turnBacklightOn();
       }
    }

    if(page == 1 && menuitem ==3)
    {
      resetDefaults();
    }


else if (page == 1 && menuitem==1) {
      page=2;
     }
else if (page == 2) {
      page=3;
     }
   }
   
  }

  void checkIfDownButtonIsPressed()
  {
    if (downButtonState != lastDownButtonState) 
  {
    if (downButtonState == 0) 
    {
      down=true;
    }
    delay(50);
  }
   lastDownButtonState = downButtonState;
  }

void checkIfUpButtonIsPressed()
{
  if (upButtonState != lastUpButtonState) 
  {
    if (upButtonState == 0) {
      up=true;
    }
    delay(50);
  }
   lastUpButtonState = upButtonState;
}

void checkIfSelectButtonIsPressed()
{
   if (selectButtonState != lastSelectButtonState) 
  {
    if (selectButtonState == 0) {
      middle=true;
    }
    delay(50);
  }
   lastSelectButtonState = selectButtonState;
}

  
  void drawMenu()
  {
    
  if (page==1) 
  {    
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("ARM TRAINER");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(0, 15);
   
    if (menuitem==1) 
    { 
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print(">RECORD");
    display.setCursor(0, 25);
   
    if (menuitem==2) 
    {
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }    
    display.print(">PLAY");
    
   
    display.display();
    
    if (menuitem==3) 
    { 
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }  
    display.setCursor(0, 35);
    display.print(">RESET");
    display.display();
  }
    
 
  else if (page==2) 
  {
    
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("RECORD");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(5, 15);
    display.print("Value");
    display.setTextSize(2);
    display.setCursor(5, 25);
    display.print(contrast);
 
    display.setTextSize(2);
    display.display();
  }
  
  }

  void resetDefaults()
  {
    contrast = 50;
    setContrast();
    backlight = true;
    turnBacklightOn();
  }

  void setContrast()
  {
    display.setContrast(contrast);
    display.display();
  }

  void turnBacklightOn()
  {
    digitalWrite(7,LOW);
  }

    void turnBacklightOff()
  {
    digitalWrite(7,HIGH);
  }
