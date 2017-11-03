#include <Time.h>
#include <TimeLib.h>
#include <Adafruit_RGBLCDShield.h>
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
#include <Wire.h>
#include <utility/Adafruit_MCP23017.h>
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7
#define idle 0
#define mainMenu 1
#define setTheTime 2
#define setTheSecond 3
#define setTheMinute 4
#define setTheHour 5
#define setAlarm 6
#define alarmSecond 7
#define alarmMinute 8
#define alarmHour 9
#define alarmStatus 10
#define showAlarm 11
#define alarmSnooze 12
#define alarmFlash 13


int state = idle;
int xsec = 05;
int xmin = 18;
int xhour = 22;
int alarmSeconds = 0;
int alarmMinutes = 0;
int alarmHours = 0;
int alarmState = 1;
int currentHour = 0;
int currentMin = 0;
int currentSec = 0;


///set up initla time and idle screen//
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  setTime(xhour, xmin, xsec, 22, 02, 2016);
  
  
}

///loop with all the cases which will be affected by input of pins//

void loop() {
  switch (state) {
    case idle:
      lcd.setBacklight(WHITE);
      digitalClockDisplay();
      checkForAlarm();
      delay(500);
      break;
    case mainMenu:
      break;
    case setTheTime:
      break;
    case setTheSecond:
      break;
    case setTheMinute:
      break;
    case setTheHour:
      break;
    case alarmStatus:
      break;
    case showAlarm:
      break;
    case alarmSnooze:
      break;
    case alarmFlash:
      break;
//    case showTime:
      digitalClockDisplay();
      delay(500);
      break;
  }
  
  uint8_t buttons = lcd.readButtons();

   // first state called when select pin is pressed to take to main menu//////////////////////////////////////////////////////
    if (state == idle) {
        if(alarmHour== hour() && alarmMinute == minute() && alarmSecond ==second() ) {
          state = alarmHour;
     }
      if (buttons & BUTTON_SELECT) {
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Main Menu");
        lcd.setCursor(4,1);
        lcd.print("USE PINS -->");
        state = mainMenu;
      }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// main menu state
    else if (state == mainMenu) {
      if (buttons & BUTTON_RIGHT) {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Set Time");
        lcd.setCursor(0, 1);
        lcd.print("<--          -->");
        state = setTheTime;
      }
      else if (buttons & BUTTON_LEFT) {
        lcd.clear();
        state = idle;
      }
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///menu option of setting time left and right pin can be used to navigate ////////////////////////////////////////////////////////////////////////////////////
  else if (state == setTheTime) {
      if (buttons & BUTTON_SELECT) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Set Time Hour");
        state = setTheHour;
        lcd.setCursor(0,1);
        lcd.print(xhour);
      }
      if (buttons & BUTTON_RIGHT) {
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Set Alarm");
        lcd.setCursor(0, 1);
        lcd.print("<--          -->");
        state = setAlarm;
      }
       if (buttons & BUTTON_LEFT) {
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Main Menu");
        lcd.setCursor(4,1);
        lcd.print("USE PINS -->");
        state = mainMenu;
      }
    }


    else if (state == setTheSecond) {
      if (buttons & BUTTON_UP){
        xsec=(xsec+1)%60;
         lcd.clear();
         lcd.print("Set Time Second");
         lcd.setCursor(0,1);
         lcd.print(xsec);         
      }
     else if (buttons & BUTTON_DOWN){
      if(xsec!=0){
        xsec=(xsec-1)%60;
         lcd.clear();
         lcd.print("Set Time Second");
         lcd.setCursor(0,1);
         lcd.print(xsec);              
      }     
      }
       else if (buttons & BUTTON_SELECT) {
        setTime(xhour, xmin, xsec, 22, 02, 2016);
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Main Menu");
        lcd.setCursor(4,1);
        lcd.print("USE PINS -->");
        state = mainMenu;
        
      }
    }


   else if (state == setTheMinute) {
    if (buttons & BUTTON_UP){
        xmin=(xmin+1)%60;
         lcd.clear();
         lcd.print("Set Time Minute");
         lcd.setCursor(0,1);
         lcd.print(xmin);
         
      }
     else if (buttons & BUTTON_DOWN){
      if(xmin!=0){
        xmin=(xmin-1)%60;
         lcd.clear();
         lcd.print("Set Time Minute");
         lcd.setCursor(0,1);
         lcd.print(xmin);
      }     
      }
      else if (buttons & BUTTON_SELECT) {
        state = setTheSecond;
        lcd.clear();
        lcd.print("Set Time Second");
        lcd.setCursor(0,1);
        lcd.print(xsec);
      }
    }
    
   else if (state == setTheHour) {
      if (buttons & BUTTON_UP){
        xhour=(xhour+1)%24;
         lcd.clear();
         lcd.print("Set Time Hour");
         lcd.setCursor(0,1);
         lcd.print(xhour);
         
      }
     else if (buttons & BUTTON_DOWN){
      if(xhour!=0){
        xhour=(xhour-1)%24;
         lcd.clear();
         lcd.print("Set Time Hour");
         lcd.setCursor(0,1);
         lcd.print(xhour);
      }      
      }
      
     else if (buttons & BUTTON_SELECT) {
        state = setTheMinute;
        lcd.clear();
        lcd.print("Set Time Minute");        
        lcd.setCursor(0,1);
        lcd.print(xmin);
      }
   }
 
   else if (state == setAlarm) {
      if (buttons & BUTTON_SELECT) {
        lcd.clear();
        lcd.print("Set Alarm Hours");
        state = alarmHour;
        alarmState = 2;
      }
      if (buttons & BUTTON_RIGHT) {
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Alarm Status");
        lcd.setCursor(0, 1);
        lcd.print("<--          -->");
        
        alarmStateShow();
        state = alarmStatus;
      }
       if (buttons & BUTTON_LEFT) {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Set Time");
        lcd.setCursor(0, 1);
        lcd.print("<--          -->");
        state = setTheTime;
      }
    }


   else if (state == alarmSecond) {
    lcd.setCursor(0,1);
    lcd.print(alarmSeconds);  
    if (buttons & BUTTON_UP){
        alarmSeconds=(alarmSeconds+1)%60;
         lcd.clear();
         lcd.print("Set Alarm Seconds");
         lcd.setCursor(0,1);
         lcd.print(alarmSeconds);       
      }
      else if (buttons & BUTTON_DOWN){
      if(alarmSeconds!=0){
        alarmSeconds=(alarmSeconds-1)%60;
         lcd.clear();
         lcd.print("Set Alarm Seconds");
         lcd.setCursor(0,1);
         lcd.print(alarmSeconds);
      }
      }
    else if (buttons & BUTTON_SELECT) {
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Main Menu");
        lcd.setCursor(4,1);
        lcd.print("USE PINS -->");
        state = mainMenu;
      }
    }

   else if (state == alarmMinute) {
    lcd.setCursor(0,1);
    lcd.print(alarmMinutes);  
    if (buttons & BUTTON_UP){
        alarmMinutes=(alarmMinutes+1)%60;
         lcd.clear();
         lcd.print("Set Alarm Minutes");
         lcd.setCursor(0,1);
         lcd.print(alarmMinutes);       
      }
      else if (buttons & BUTTON_DOWN){
      if(alarmMinutes!=0){
        alarmMinutes=(alarmMinutes-1)%60;
         lcd.clear();
         lcd.print("Set Alarm Minutes");
         lcd.setCursor(0,1);
         lcd.print(alarmMinutes);
      }
      }    
     else if (buttons & BUTTON_SELECT) {
        lcd.clear();
        lcd.print("Set Alarm Second");
        state = alarmSecond;
      }
    }


   else if (state == alarmHour) {
    lcd.setCursor(0,1);
    lcd.print(alarmHours);
    if (buttons & BUTTON_UP){
        alarmHours=(alarmHours+1)%24;
         lcd.clear();
         lcd.print("Set Alarm Hours");
         lcd.setCursor(0,1);
         lcd.print(alarmHours);       
      }
      else if (buttons & BUTTON_DOWN){
      if(alarmHours!=0){
        alarmHours=(alarmHours-1)%24;
         lcd.clear();
         lcd.print("Set Alarm Hours");
         lcd.setCursor(0,1);
         lcd.print(alarmHours);
      }
      } 
       if (buttons & BUTTON_SELECT) {
        lcd.clear();
        lcd.print("Set Alarm Minute");
        state = alarmMinute;
      } 
    }

   else if (state == alarmStatus) {
      if (buttons & BUTTON_RIGHT) {
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Show Alarm");
        lcd.setCursor(3, 1);
        lcd.print("<--          ");
        lcd.setCursor(7, 1);
        lcd.print(alarmHours);
        lcd.setCursor(9, 1);
        lcd.print(":");
        lcd.setCursor(10, 1);
        lcd.print(alarmMinutes);
        lcd.setCursor(12, 1);
        lcd.print(":");
        lcd.setCursor(13, 1);
        lcd.print(alarmSeconds);
        state = showAlarm;
      }
       if (buttons & BUTTON_LEFT) {
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Set Alarm");
        lcd.setCursor(0, 1);
        lcd.print("<--          -->");
        
        state = setAlarm;
      }

       if (buttons & BUTTON_UP) {
        
        alarmState=2;
        alarmStateShow();
        
       }

         if (buttons & BUTTON_DOWN) {
        alarmState=1;
        alarmStateShow();
        
       }
    }

   else if (state == showAlarm) {
      if (buttons & BUTTON_RIGHT) {
        state = idle;
      }
       if (buttons & BUTTON_LEFT) {
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Alarm Status");
        lcd.setCursor(0, 1);
        lcd.print("<--          -->");
        alarmStateShow();
        state = alarmStatus;
      }
   }

   else if (state==alarmFlash){
    lcd.clear();
    
    lcd.setCursor(0,0);
    lcd.print( "SELECT = OFF");
    lcd.setCursor(0,1);
    lcd.print( "UP = SNOOZE");

     if (buttons & BUTTON_SELECT) {
        alarmState=1;
        state=idle;
        
       }

     if (buttons & BUTTON_UP) {
        alarmSeconds=second();
        alarmMinutes=minute();
        alarmHours=hour();
        if((alarmSeconds+30)%60<alarmSeconds){
          alarmSeconds=(alarmSeconds+30)%60;
          alarmMinutes=alarmMinutes+1;
        }
        else if ((alarmSeconds+30)%60>alarmSeconds) {
          alarmSeconds=alarmSeconds+30;
        }
        state=idle;
       }
       lcd.setBacklight(RED);
       delay(500);
       lcd.setBacklight(BLUE);
   }

      
  
    delay(200);
}



void digitalClockDisplay() {
  lcd.clear();
  lcd.noBlink();
  lcd.setCursor(4, 1);
  lcd.print(hour());
  currentHour=hour();
  printDigits(minute());
  currentMin=minute();
  printDigits(second());
  currentSec=second();
   
  lcd.setCursor(1, 0);
  lcd.print("SELECT = MENU");
}



void printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon and leading 0
  lcd.print(":");
  if (digits < 10)
    lcd.print('0');
  lcd.print(digits);
}

void alarmStateShow(){
  if (alarmState == 1){
    lcd.setCursor(8,1);
    lcd.print("OFF");
  }
  else if (alarmState == 2){
    lcd.setCursor(8,1);
    lcd.print("ON ");
    
  }
}

void checkForAlarm(){
  if(alarmState==2){
    if(alarmHours== currentHour && alarmMinutes == currentMin && alarmSeconds ==currentSec ){
      state=alarmFlash;
   }
  }
}
 
 








