// =========================================
// Drawing Content Block====================    
// =========================================
 /* 
void mode_1(int Speed,int DrawAdd)
{
     // check RunSelector
    static uint16_t   x; 
    if(!dwDo(DrawAdd)) return;
    if (reset_x !=0) { x=0;reset_x = 0;}  
       char *msg =  drawMode_1();
       static uint16_t   lsRn;
       static uint16_t   rScn;
        uint16_t          Tmr = millis();
  char jam[20];
  char menit[20];
  int detik = now.second();
  char titik[20];
  const char Buff[50];
  sprintf(Buff,"%-34s"," ");
  sprintf(jam,"%02d",now.hour());
  sprintf(menit,"%02d",now.minute());
  if(detik % 2){sprintf(titik,"%s",":");}
  else{sprintf(titik,"%s"," ");}
       fType(5);
          int fullScroll = Disp.textWidth(msg) + DWidth; 
      
       if((Tmr-lsRn)> Speed)
        { lsRn=Tmr;
          if (x < fullScroll) {++x;}
          else {  dwDone(DrawAdd); 
                x = 0;return;}
    
    
     Disp.drawText(DWidth - x, 0, msg);
     Disp.drawRect(32,0,33,16);
     fType(3);
    
     Disp.drawText(0,0,Buff);
     Disp.drawText(0,0,jam);
     Disp.drawText(19,0,menit);
      Disp.drawText(13,0,titik);
    
     DoSwap = true;
        }
}
void mode_2(int Speed,int DrawAdd)
{
      // check RunSelector
    static uint16_t   x; 
    if(!dwDo(DrawAdd)) return;
    if (reset_x !=0) { x=0;reset_x = 0;} 
    char *msg =  drawMode_2();
  char jam[20];
  char menit[20];
  int detik = now.second();
  char titik[10];
  const char Buff[50];
  sprintf(Buff,"%-34s"," ");
  sprintf(jam,"%02d",now.hour());
  sprintf(menit,"%02d",now.minute());
  if(detik % 2){sprintf(titik,"%s",":");}
  else{sprintf(titik,"%s"," ");}
       static uint16_t   lsRn;
        uint16_t          Tmr = millis();
        int batas = Disp.textWidth(Buff);
        fType(1);
        int fullScroll = Disp.textWidth(msg) + DWidth  ;
      
       if((Tmr-lsRn)> Speed)
        { lsRn=Tmr;
          if (x < fullScroll) {++x;}
          else {  dwDone(DrawAdd); 
                x = 0;return;}
    
     Disp.drawText(DWidth - x, 9, msg);
     Disp.drawText(35,0,masehi());
     fType(3);
     Disp.drawText(0,0,Buff);
     Disp.drawText(0,0,jam);
     Disp.drawText(19,0,menit);
     Disp.drawText(13,0,titik);
     Disp.drawRect(33,0,33,17);
     DoSwap = true;
        } 
}


void mode_3(int Speed,int DrawAdd)
{
    static uint16_t   x; 
     static uint16_t   s;
    static int   y = -9;
    static uint16_t   con;
    static uint8_t   conH;
    if(!dwDo(DrawAdd)) return;
    if (reset_x !=0) { x=0;reset_x = 0;} 
    char *msg =  drawMode_3();
            char jam[20];
  char menit[20];
  int detik = now.second();
  char titik[10];
  const char Buff[50];
  sprintf(Buff,"%-34s"," ");
  sprintf(jam,"%02d",now.hour());
  sprintf(menit,"%02d",now.minute());
  if(detik % 2){sprintf(titik,"%s",":");}
  else{sprintf(titik,"%s"," ");}
        static uint16_t   lsRn;
        static uint16_t   rHP;
        uint16_t          Tmr = millis();
      
        int batas = Disp.textWidth(Buff);
        fType(1);
        int fullScroll = Disp.textWidth(msg) + DWidth ; 
     
       if((Tmr-lsRn)> Speed)
        { lsRn=Tmr;
          if (x < fullScroll) {++x;}
          else {  dwDone(DrawAdd); 
                x = 0;return;}
     if(s==0 and con<9){con++; y++;}
        if(s==1 and con>0){con--;y--;}
     Disp.drawText(DWidth - x, 9, msg);
     if((Tmr-rHP)>3000 and con ==  9){rHP=Tmr; s=1;}

    if (con == 0 and s==1) {conH++; s=0;}
if(conH==0){ Disp.drawText(50,y,daysOfTheWeek[daynow-1]);}
if(conH==1){ Disp.drawText(50,y,pasar[jumlahhari()%5]);}
if(conH==2){ conH=0;}

     
     fType(3);
     Disp.drawText(0,0,Buff);
      Disp.drawText(0,0,jam);
     Disp.drawText(19,0,menit);
     Disp.drawText(13,0,titik);
     Disp.drawLine(33,0,33,16);
     //Disp.drawLine(35,7,93,7);
     DoSwap = true;
     
        }
     
}

void effekMode_4(int Speed,int y,int yLine)
{
    static uint16_t   x; 
    if (reset_x !=0) { x=0;reset_x = 0;} 
    char *msg =  drawHijriyah();
              char jam[20];
  char menit[20];
  int detik = now.second();
  char titik[10];
  const char Buff[50];
  sprintf(Buff,"%-34s"," ");
  sprintf(jam,"%02d",now.hour());
  sprintf(menit,"%02d",now.minute());
  if(detik % 2){sprintf(titik,"%s",":");}
  else{sprintf(titik,"%s"," ");}
       static uint16_t   lsRn;
        uint16_t          Tmr = millis();
        
        fType(1);
       int fullScroll = Disp.textWidth(msg) +DWidth ;
     
       if((Tmr-lsRn)> Speed )
        { lsRn=Tmr;
      if(yLine==17){
          if ( x < fullScroll) {++x; trigg=0;}
          else { trigg=1; x = 0;return;}
      }
     Disp.drawText(DWidth - x, 9, msg);
     Disp.drawText(36,y,masehi());
     fType(3);
     Disp.drawText(0,y,Buff);
      Disp.drawText(0,y,jam);
     Disp.drawText(19,y,menit);
     Disp.drawText(13,y,titik);
     Disp.drawLine(33,0,33,yLine-1);
     Serial.println(String() + "yLine:" + yLine);
     DoSwap = true;
        } 
}
int state;
void mode_4(int Speed,int DrawAdd)
  {
    // check RunSelector
    if(!dwDo(DrawAdd)) return; 
    static uint8_t    x;
    static uint8_t    y;
    static uint8_t    s=state; // 0=in, 1=out              
    static uint16_t   lsRn;
    uint16_t          Tmr = millis();
    
    if((Tmr-lsRn)>100) 
      { 
        if(s==0 and y<17){lsRn=Tmr;y++;}
        if(s==1 and y>0){lsRn=Tmr;y--;}
      }
    if(trigg == 1 and y ==17) {s=1; }
    if (y == 0 and s==1) {trigg=0;    RunSel = 10; s=0;}
     effekMode_4(40, 17-y,y );    
    
    }
  
void runText(int Speed,int DrawAdd)
   {
     
    static uint16_t   x;   
   if(!dwDo(DrawAdd)) return;
    if (reset_x !=0) { x=0;reset_x = 0;} 
    char *msg =  drawNama();
       char  Buff[30];
       static uint16_t   lsRn; 
        uint16_t          Tmr = millis();
   fType(5);
       int fullScroll = Disp.textWidth(msg) + DWidth ; 
      
       if((Tmr-lsRn)> Speed)
        { lsRn=Tmr;
          if (x < fullScroll) {++x;}
          else {  dwDone(DrawAdd); RunSel = 1;
                x = 0;return;}
Disp.drawText(DWidth - x, 0, msg);
DoSwap = true;
        }
        
}
*/
//     unsigned long   lsTmr;
//     unsigned long   lsYClock;
//     int   xDate=0; 
//     int   xInfo=0;  
//     unsigned long lsText_1=0;
//     unsigned long lsText_2=0;
/*void runText(char *msgDate,char *msgInfo,int Speed_1,int Speed_2,int DrawAdd)
{
     // check RunSelector
     if(!dwDo(DrawAdd)) return;   
    static uint8_t    banding;
    static uint8_t    yClock;
    static uint8_t    s;
    if (reset_x !=0) { xDate=0; xInfo=0; reset_x = 0;} 
   char jam[10];
   char menit[10];
   char titik[10];
   const char Buff[50];
   static bool state1;
  
  sprintf(Buff,"%-34s"," ");
  sprintf(jam,"%02d",now.hour());
  sprintf(menit,"%02d",now.minute());
  
       if((millis()-lsYClock)>100) 
      { 
        if(s==0 and yClock<9){ lsYClock=millis();    yClock++;}
      }
      if(yClock==9){s=1; lsYClock=0;}
  
        fType(1);
        int fullScrollDat = Disp.textWidth(msgDate) + DWidth  ;
        int fullScrollInf = Disp.textWidth(msgInfo) + DWidth  ;
        
       if((millis()-lsText_1)> Speed_1 && s == 1)
        { 
          if (xDate < fullScrollDat) {lsText_1=millis(); ++xDate; }
          else {xDate = 0;return;}
           
        }

        if((millis()-lsText_2)> Speed_2 && s == 1)
        {
          if (xInfo < fullScrollInf) {lsText_2=millis(); ++xInfo; }
        else { xInfo = 0;return;}
          
        }


  //   banding = max(xDate,xInfo);
    // if(xInfo >= fullScrollInf && xDate >= fullScrollDat ){dwDone(DrawAdd); xDate = 0; xInfo = 0;return; }
    //  DoSwap = true;
    
     Disp.drawText(DWidth - xDate, 0, msgDate);
     Disp.drawText(DWidth - xInfo, 9, msgInfo);
     fType(3);
      if((millis()-lsTmr)>500){lsTmr=millis();  state1=!state1; 
     if(state1){sprintf(titik,"%s",":");}
     else{sprintf(titik,"%s"," ");}}
     Disp.drawText(0,0,Buff);
     Disp.drawText(0,yClock-9,jam);
     Disp.drawText(19,yClock-9,menit);
     Disp.drawText(13,yClock-9,titik);
     Disp.drawLine(33,0,33,17);
     Disp.drawLine(33,7,93,7);
     Disp.swapBuffers();
   
       
}
*/

// =========================================
// Drawing Tools============================
// =========================================
boolean dwDo(int DrawAdd)
  { if (RunSel== DrawAdd) {return true;}
    else return false;}
  
void dwDone(int DrawAdd)
  { RunFinish = DrawAdd;
    RunSel = 0;}
    
void dwCtr(int x, int y,const char* Msg)
  { int   tw = Disp.textWidth(Msg);
    int   th = Disp.textHeight();
    int   c = int((DWidth-x-tw)/2);
    Disp.drawFilledRect(x+c-1,y,x+tw+c,y+th,0);
    Disp.drawText(x+c,y,Msg); DoSwap = true; }

void Buzzer(uint8_t state)
  {
    if(state ==1)
      {digitalWrite(BUZZ,HIGH);}
    else 
      {digitalWrite(BUZZ,LOW);}
  }
  
void fType(int x)
  {
    if(x==0) Disp.setFont(Font0);
    else if(x==1) Disp.setFont(Font1); 
    else if(x==2) Disp.setFont(Font2);
    else if(x==3) Disp.setFont(Font3);
    else if(x==4) Disp.setFont(Font4);
    else if(x==5) Disp.setFont(Font5);  
    else if(x==6) Disp.setFont(Font6);  
  }

// digunakan untuk menghitung hari pasaran
  int jumlahhari(){ 
  DateTime  now = RTC.now(); 
  int d= now.day();
  int m= now.month();
  int y= now.year();
  int hb[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
  int ht = (y - 1970) * 365 - 1;
  int hs = hb[m - 1] + d;
  int kab = 0;
  int i;
  if(y % 4 == 0) {
    if(m > 2) {
    hs++;
    }
  }
  for(i = 1970; i < y; i++) {
    if(i % 4 == 0) {
    kab++;
    }
  }
  return (ht + hs + kab); 
}
