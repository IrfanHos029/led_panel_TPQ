/*************************************************************************************
JAM_DIGITAL_MODIF 64 X 16
28/02/2021
**************************************************************************************/
#include <SPI.h>
#include <DMD3asis.h>
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



char *sholatCall[] = {"IMSAK","SUBUH","TERBIT","DHUHA","DUHUR","ASHAR","MAGRIB","ISYA","JUM'AT"};               
//char *hariN[]= {"Minggu","Senin","Selasa","Rabu","Kamis","Jum'at","Sabtu"};
char *bulanN[]= {"Januari","Februari","Maret","April","Mei","Juni","Juli","Agustus","September","Oktober","November","Desember"};
int maxday[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
RTClib          RTC;
DS3231          Clock;

String text="";
/*
//Structure of Variable 
typedef struct  // loaded to EEPROM
  {
    uint8_t state;   // 1 byte  add 0
    float   L_LA;    // 4 byte  add 1
    float   L_LO;    // 4 byte  add 5
    float   L_AL;    // 4 byte  add 9
    float   L_TZ;    // 4 byte  add 13
    uint8_t MT;      // 1 byte  add 17  // value 1-masjid  2-mushollah 3-surau 4-langgar 
    uint8_t BL;      // 1 byte  add 18
    uint8_t IH;      // 1 byte  add 19
    uint8_t SO;      // 1 byte  add 20
    uint8_t JM;      // 1 byte  add 21
    uint8_t I1;      // 1 byte  add 22
    uint8_t I4;      // 1 byte  add 23
    uint8_t I5;      // 1 byte  add 24
    uint8_t I6;      // 1 byte  add 25
    uint8_t I7;      // 1 byte  add 26
    uint8_t BZ;      // 1 byte  add 27
    uint8_t SI;      // 1 byte  add 28
    uint8_t ST;      // 1 byte  add 29
    uint8_t SU;      // 1 byte  add 30
    int8_t  CH;      //20 1 byte  add 31
    int8_t  II;      //21 1 byte  add 32
    int8_t  IS;      //22 1 byte  add 33
    int8_t  IL;      //23 1 byte  add 34
    int8_t  IA;      //24 1 byte  add 35
    int8_t  IM;      //25 1 byte  add 36
  } struct_param;
*/
typedef struct  
  { 
    uint8_t   hD;
    uint8_t   hM;
    uint16_t  hY;
  } hijir_date;

   
// Variable by Structure     
//struct_param    Prm;
hijir_date      nowH;   

// Time Variable
DateTime        now;
float           floatnow   = 0;
uint8_t         daynow     = 0;
uint8_t         ty_puasa   = 0;
uint8_t         hd_puasa   = 0; 
int8_t          SholatNow  = -1;
boolean         jumat      = false;
boolean         azzan      = false;
uint8_t         reset_x    = 0;   

//Other Variable
float sholatT[8]  = {0,0,0,0,0,0,0,0};
uint8_t Iqomah[8] = {0,0,0,0,0,0,0,0};

//Blue tooth Pram Receive
char        CH_Prm[155];
int         DWidth  = Disp.width();
int         DHeight = Disp.height();
boolean     DoSwap;
int         RunSel    = 1; //
int         RunFinish = 0 ;
const byte reset = 4;
bool trigg;
unsigned long   lsTmr;
     unsigned long   lsYClock;
     int   xDate=0; 
     int   xInfo=0;  
     unsigned long lsText_1=0;
     unsigned long lsText_2=0;
      bool state1;
      int xLine ; //DWidth/2;
      int Dwidth = DWidth - 33;
      String inputString="";
      bool stringComplete = false;
      int Bright = 10;
//=======================================
//===SETUP=============================== 
//=======================================
void setup()
  { //init comunications 
    Wire.begin();
    Serial.begin(115200);
    pinMode(Ind,OUTPUT);
    pinMode(BUZZ, OUTPUT); 
    digitalWrite(Ind,HIGH);
    
    delay(1000);
    for(int i = 0; i < 2; i++)
    {
      digitalWrite(BUZZ,HIGH); 
      delay(100);
      digitalWrite(BUZZ,LOW);
      delay(100);
    }
    updateTime();
    inputString.reserve(200);
    //init P10 Led Disp & Salam
    Disp_init();
   // text= "TPQ AS-SA'ADAH Gampang-Prambon";
  }

//=======================================
//===MAIN LOOP Function =================   
//=======================================
void loop()
  {
      update_All_data();   //every time
    Indikator(500);
    cekInput();
 
  char *msgDate = DATE();
  String msgInfo = text;
  int Speed_1 = 30;
  int Speed_2 = 30;
  Disp.clear();
  
  static uint8_t    yClock;
  static uint8_t    s;
  if (reset_x !=0) { xDate=0; xInfo=0; reset_x = 0;} 
  char jam[10];
  char menit[10];
  char titik[10];
  const char Buff[50];
 
  //Serial.println(text);
  sprintf(Buff,"%-34s"," ");
  sprintf(jam,"%02d",now.hour());
  sprintf(menit,"%02d",now.minute());
  
  if((millis()-lsYClock)>100) 
    { 
      if(s==0 and yClock<9){ lsYClock=millis();    yClock++;}
      if(xLine < (Dwidth/2)){lsYClock=millis();    xLine++; }
    }
  if(xLine==Dwidth/2){s=1; lsYClock=0;}
  
   fType(1);
   int fullScrollDat = Disp.textWidth(msgDate) + DWidth  ;
   int fullScrollInf = Disp.textWidth(msgInfo) + DWidth  ;
        
   if((millis()-lsText_1)> Speed_1 && s == 1)
      { 
          if (xDate < fullScrollDat) {lsText_1=millis(); ++xDate; }
         // else {xDate = 0;return;}     
      }

   if((millis()-lsText_2)> Speed_2 && s == 1)
      {
         if (xInfo < fullScrollInf) {lsText_2=millis(); ++xInfo; }
        // else { xInfo = 0;return;}    
       }

     if((millis()-lsTmr)>500){lsTmr=millis();  state1=!state1; 
     if(state1){sprintf(titik,"%s",":");}
     else{sprintf(titik,"%s"," ");}}
     
//Serial.println(String() + "xDate:" + xDate);
//Serial.println(String() + "xInfo:" + xInfo);

  //   banding = max(xDate,xInfo);
      if(xInfo >= fullScrollInf && xDate >= fullScrollDat ){xDate = 0; xInfo = 0;return; }
    
     Disp.drawText(DWidth - xDate, 0, msgDate);
     Disp.drawText(DWidth - xInfo, 9, msgInfo);
     fType(3);
     
     Disp.drawText(0,0,Buff);
     Disp.drawText(0,yClock-9,jam);
     Disp.drawText(19,yClock-9,menit);
     Disp.drawText(13,yClock-9,titik);
     Disp.drawLine(33,8,33,8-yClock);
      Disp.drawLine(33,8,33,8+yClock);
     Disp.drawLine((Dwidth/2)+33,7,(Dwidth/2+33)+xLine,7);
     Disp.drawLine((Dwidth/2)+33,7,(Dwidth/2+33)-xLine,7);
     Disp.swapBuffers();




    if (stringComplete) 
   {
    if (inputString.substring(0,2) == "TX") 
    {
      inputString.remove(0,2);
      text = inputString;
      Serial.println(String() + "text:" + text);
      inputString = "";
      stringComplete = false;
    }
     if(inputString.substring(0,2) == "BT")
     {
      inputString.remove(0,2);
      Bright = inputString.toInt();
      setBrightness(Bright);
      Serial.println(String() + "Bright:" + Bright);
      inputString = "";
      stringComplete = false;
    }

    else if(inputString.substring(0,2) == "CK")
    {
      stringComplete = false;
    }
   }
   
    // =========================================
    // List of Display Component Block =========
    // =========================================

 //runText(DATE(),drawNama(),40,40,1);

    // =========================================
    // Display Control Block ===================
    // =========================================
 //   if(RunFinish==1) {RunSel = 1; RunFinish =0;}                      //after anim 1 set anim 2
   // if(RunFinish==2) {RunSel = 1; RunFinish =0;}                      //after anim 2 set anim 3
//    if(RunFinish==3) {RunSel = 1; RunFinish =0;}
//    if(RunFinish==4)  {RunSel = 1;  RunFinish =0;} 
  
    // =========================================
    // Swap Display if Change===================
    // =========================================
    
   // if(DoSwap){Disp.swapBuffers();} // Swap Buffer if Change
  }
// =========================================
// DMD3 P10 utility Function================
// =========================================
void Disp_init() 
  { Disp.setDoubleBuffer(true);
    Timer1.initialize(2500);
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
  
void cekInput() 
{
  if (Serial.available() > 0 ) 
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    inputString += inChar;
 
    if(inChar == '\n')
    {
      stringComplete = true;
    }
  }
   
}


void update_All_data()
  {
  uint8_t   date_cor = 0;
  updateTime();
  //sholatCal();                                                // load Sholah Time                                         // check jadwal Puasa Besok
  if(floatnow>18.00) {date_cor = 1;}                     // load Hijr Date + corection next day after Mhagrib 
  nowH = toHijri(now.year(),now.month(),now.day(),date_cor);  // load Hijir Date
  
//  if ((floatnow > (float)21) or (floatnow < (float)3.5) )    {setBrightness(15);}
//      else                                                   {setBrightness(Prm.BL);}  
  }
