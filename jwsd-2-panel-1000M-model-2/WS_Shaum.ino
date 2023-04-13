
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
  dwCtr(2,0,"BRIGHTNESS");
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
  setHours = now.hour();
  setMinutes = now.minute();
  fType(1);
  dwCtr(2,0,"SET CLOCK");
  sprintf(out," %02d : %02d : %02d " ,setHours,setMinutes,now.second());
  dwCtr(5,9,out);
  Disp.swapBuffers();
}

void showPanel()
{
  Disp.clear();
  char *msgDate = DATE();
  static uint8_t    yClock;
  static uint8_t    s;
  static uint16_t    xScl;
  uint32_t tmr = millis();
  int speedd[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55};
  if (reset_x !=0) { xScl=0; reset_x = 0;} 
  char jam[10];
  char menit[10];
  char titik[10];
  const char Buff[50];
  int detikk = now.second();
  sprintf(Buff,"%-34s"," ");
  sprintf(jam,"%02d",now.hour());
  sprintf(menit,"%02d",now.minute());
  fType(1);
  if((millis()-lsYClock)>100) 
    { 
      if(s==0 and yClock<9){ lsYClock=millis();    yClock++;}
      if(xLine < (Dwidth/2)){lsYClock=millis();    xLine++; }
    }
  if(xLine==Dwidth/2){s=1; lsYClock=0;}
 
  
     int fullScrollDat = Disp.textWidth(msgDate) + DWidth;
     int fullScrollInf = Disp.textWidth(text) + DWidth;
     int Max = max(fullScrollDat,fullScrollInf);
     if(xScl <= Max && s == 1)
     {
      ++xScl;
      Disp.drawText(DWidth - xScl, 9, text); 
      Disp.drawText(DWidth - xScl, 0, msgDate);
      delay(speedd[Speed_1]);
       
      }
      if(xScl > Max ){ xScl = 0; return; }

     fType(3);
     if(detikk % 2 == 0){sprintf(titik,"%s",":");}
     else{sprintf(titik,"%s"," ");}
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








 
