/*************************************************************************************
JAM_DIGITAL_ABAH
28/02/2021
**************************************************************************************/
#include <SPI.h>
#include <DMD3asis.h>
//#include <SoftwareSerial.h>
//SoftwareSerial bluetooth(3,4);
#include <font/KecNumber.h>
#include <font/BigNumber.h>
#include <font/Font4x6.h>
#include <font/SystemFont5x7.h>
#include <font/Font3x5.h>
#include <font/EMSans8x16.h>
#include <font/Arab6x7.h>

#include <DS3231.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>
#include <Wire.h>
#include <MemoryFree.h>

#define BUZZ    2 
#define Ind     3

#define Font0 Font4x6
#define Font3 BigNumber
#define Font2 Font3x5
#define Font1 SystemFont5x7
#define Font4 KecNumber
#define Font5 EMSans8x16
#define Font6 Arab6x7
    
// Object Declarations
DMD3 Disp(3,1);
char *pasar[] ={"WAGE",
                "KLIWON", 
                "LEGI", 
                "PAHING", 
                "PON"}; 
                
char daysOfTheWeek[7][12] = {"MINGGU", 
                             "SENIN", 
                             "SELASA",
                             "RABU", 
                             "KAMIS",
                             "JUM'AT",
                             "SABTU"};
                             
char *mounthJawa[]= {"Muharram",
                     "Shafar",
                     "Rab.awal",
                     "Rab.akhir",
                     "Jum.awal",
                     "Jum.akhir",
                     "Rajab",
                     "Sya'ban",
                     "Ramadhan",
                     "Syawal",
                     "Dzulqa'dah",
                     "Dzulhijah"};


char *bulanN[]= {"Januari",
                 "Februari",
                 "Maret",
                 "April",
                 "Mei",
                 "Juni",
                 "Juli",
                 "Agustus",
                 "September",
                 "Oktober",
                 "November",
                 "Desember"};





                 

int maxday[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

RTClib          RTC;
DS3231          Clock;
//SoftwareSerial soft(3,4);
typedef struct  
  { 
    uint8_t   hD;
    uint8_t   hM;
    uint16_t  hY;
  } hijir_date;

   
// Variable by Structure                    
hijir_date      nowH;   

// Time Variable
DateTime        now;
float           floatnow   = 0;
uint8_t         daynow     = 0;
uint8_t         ty_puasa   = 0;
uint8_t         hd_puasa   = 0; 
int8_t          SholatNow  = -1;
//boolean         jumat      = false;
//boolean         azzan      = false;
uint8_t         reset_x    = 0;   

int         DWidth  = Disp.width();
int         DHeight = Disp.height();
boolean     DoSwap;
int         RunSel    = 1; //
int         RunFinish = 0 ;

int Speed_1;
int xLine ; //DWidth/2;
int Dwidth = DWidth - 33;
int Bright = 10;
int setHours,setMinutes;
int Screen=0;
int idxText;
int  addressCharArray = 0;
const int maxAllowedWrites = 80;
const int memBase          = 350;

unsigned long   lsYClock;

String inputString="";
bool stringComplete = false;
char text[100];
//bool on=false;


//=======================================
//===SETUP=============================== 
//=======================================
void setup()
{ //init comunications 
    
    Serial.begin(9600);
    loadMemory();
    Wire.begin();
    pinMode(Ind,OUTPUT);
    pinMode(BUZZ, OUTPUT); 
    digitalWrite(Ind,HIGH);
    //inputString.reserve(500);
    
    for(int i = 0; i < 2; i++)
    {
      digitalWrite(BUZZ,HIGH); 
      delay(100);
      digitalWrite(BUZZ,LOW);
      delay(100);
    }
    updateTime();
    Disp_init();
 
}
//=======================================
//===MAIN LOOP Function =================   
//=======================================
 void loop(){
  update_All_data();
  
if(Screen == 0)
{
  showPanel();
}



if(Screen == 1)
{
   setBright(Bright);
}

if(Screen == 2)
{
  setClockk();
}


 if (stringComplete) 
 {
   if(inputString.substring(0,2) == "S1")
   {//Serial.println(inputString);
      Disp.clear(); 
      inputString = "";
      Screen = 1;
      stringComplete = false;
   }

     else if(inputString.substring(0,2) == "S2")
    {//Serial.println(inputString);
      Disp.clear(); 
      inputString = "";
      Screen = 2;
      stringComplete = false;
    }

    else if(inputString.substring(0,2) == "EX")
    {//Serial.println(inputString);
      Disp.clear(); 
      inputString = "";
      Screen = 0;
      stringComplete = false;
    }
     else if(inputString.substring(0,2) == "TX")
     {//Serial.println(inputString);
      inputString.remove(0,2);
      delay(50);
      idxText = inputString.length();
      inputString.toCharArray(text,idxText);
      EEPROM.put(300,text);
      reset_x=1;
      inputString = "";
      stringComplete = false;
    }

    else if(inputString.substring(0,2) == "SP")
    {//Serial.println(inputString);
      inputString.remove(0,2);
      Speed_1 = inputString.toInt();
      delay(50);
      EEPROM.update(2,Speed_1); 
      //Serial.println(String() + "Speed_1:" + Speed_1 );
      reset_x=1;
      inputString = "";
      stringComplete = false;
    }
    else if(inputString.substring(0,2) == "BT")
     {//Serial.println(inputString);
      inputString.remove(0,2);
      Bright = inputString.toInt();
      delay(50);
      EEPROM.update(1,Bright);
      delay(50);
      setBrightness(Bright);
      inputString = "";
      stringComplete = false;
    }

    else if(inputString.substring(0,2) == "CK")
    {//Serial.println(inputString);
      String setJam,setMenit;
      inputString.remove(0,2);
      delay(50);
      setJam = inputString.substring(0,2);    
      setMenit = inputString.substring(3,5);
      setHours = setJam.toInt();
      setMinutes = setMenit.toInt();
      Clock.setHour(setHours);
      Clock.setMinute(setMinutes);
      inputString = "";
      stringComplete = false;
    }

    else
    {
       inputString="";
    }
}
   
    // =========================================
    // List of Display Component Block =========
    // =========================================

    // =========================================
    // Display Control Block ===================
    // =========================================
    // if(RunFinish==1) {RunSel = 1; RunFinish =0;}                      //after anim 1 set anim 2
    // if(RunFinish==2) {RunSel = 1; RunFinish =0;}                      //after anim 2 set anim 3
    // if(RunFinish==3) {RunSel = 1; RunFinish =0;}
    // if(RunFinish==4)  {RunSel = 1;  RunFinish =0;} 
  
    // =========================================
    // Swap Display if Change===================
    // =========================================
     
    //if(DoSwap){Disp.swapBuffers();} // Swap Buffer if Change
  }
// =========================================
// DMD3 P10 utility Function================
// =========================================
void Disp_init() 
  { Disp.setDoubleBuffer(true);
    Timer1.initialize(2000);
    Timer1.attachInterrupt(scan);
    setBrightness(Bright);
    fType(1);  
    Disp.clear();
    Disp.swapBuffers();
  }


void setBrightness(int bright)
  { Timer1.pwm(9,bright);}

void scan()
  { Disp.refresh();}
  
// =========================================
// Time Calculation Block===================
// =========================================
void updateTime()
  { now = RTC.now();
    floatnow = (float)now.hour() + (float)now.minute()/60 + (float)now.second()/3600;
    daynow   = Clock.getDoW();    // load day Number
  }

void serialEvent() 
{ 
    char bchar;         
           while ((bchar != '\n')and(inputString.length() < 150))
          {
          if(Serial.available())
            { 
             bchar = Serial.read();   
            inputString+=bchar;
            //Serial.println(String() + "karakter:" + bchar);
             
            }
            if(bchar == '\n'){ digitalWrite (BUZZ, LOW); stringComplete=true;  break;}
          }
    
}

void update_All_data()
{
  uint8_t   date_cor = 0;
  updateTime();                                                                                // check jadwal Puasa Besok
  if(floatnow>18.00) {date_cor = 1;}                     // load Hijr Date + corection next day after Mhagrib 
  nowH = toHijri(now.year(),now.month(),now.day(),date_cor);  // load Hijir Date
}
