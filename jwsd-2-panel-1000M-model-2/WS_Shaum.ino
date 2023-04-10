
unsigned long Run;
bool state;
void Indikator(uint8_t Delay)
{
   unsigned long tmr = millis();
    if((tmr - Run) > Delay){ Run = tmr; state=!state;}
    digitalWrite(Ind,state);
}


void setBright(int conBright)
{ 
  Disp.clear(); 
  int dataBright,dataShow;
  char out[5];
  fType(1);
  dwCtr(16,0,"BRIGHTNESS");
  dataBright = map(conBright,10,255,0,100);
  dataShow = map(conBright,10,255,5,64);
  sprintf(out,"%d%s" ,dataBright,"%");
  Disp.drawRect(5,11,64,14);
  Disp.drawRect(5,11,dataShow,14,1,1);
  dwCtr(60,9,out);
  Disp.swapBuffers();
}


void setClockk()
{
  Disp.clear(); 
  char out[10];
  fType(1);
  dwCtr(16,0,"SET CLOCK");
  sprintf(out," %02d : %02d : %02d " ,setHours,setMinutes,now.second());
  dwCtr(10,9,out);
  Disp.swapBuffers();
}

void showPanel(int stateShow)
{
  char *msgDate = DATE();
  char *msgInfo = text;
  int Speed_1 = 30;
  int Speed_2 = 30;
  static uint8_t    yClock;
  static uint8_t    s;
  if (reset_x !=0) { xDate=0; xInfo=0; reset_x = 0;} 
  char jam[10];
  char menit[10];
  char titik[10];
  const char Buff[50];
  int detikk = now.second();
  
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
        Serial.println(msgInfo);
   if((millis()-lsText_1)> Speed_1 && s == 1)
      { 
          if (xDate < fullScrollDat) {lsText_1=millis(); ++xDate; }    
      }

   if((millis()-lsText_2)> Speed_2 && s == 1)
      {
         if (xInfo < fullScrollInf) {lsText_2=millis(); ++xInfo; } 
       }

   if(stateShow)
   {   
     Disp.clear();
     if(detikk % 2 == 0){sprintf(titik,"%s",":");}
     else{sprintf(titik,"%s"," ");}
//Serial.println(String() + "xDate:" + xDate);
//Serial.println(String() + "xInfo:" + xInfo);
  
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
    }
    else{
      return;
    }
}











 
