
unsigned long Run;
bool state;
void Indikator(uint8_t Delay){
  unsigned long tmr = millis();
    if((tmr - Run) > Delay){ Run = tmr; state=!state;}
    digitalWrite(Ind,state);
}


void setBright(int conBright)
 
{ Disp.clear(); 
  int dataBright,dataShow;
  char out[5];
 // fType(3);
  dwCtr(16,0,"BRIGHTNESS");
  dataBright = map(conBright,10,255,0,100);
  dataShow = map(conBright,10,255,5,64);
  sprintf(out,"%d%s" ,dataBright,"%");
  Disp.drawRect(5,11,64,14);
  Disp.drawRect(5,11,dataShow,14,1,1);
  dwCtr(60,9,out);
  Serial.print(String() + "cahaya:" + out);
  Disp.swapBuffers();
}


void setClockk(){
  Disp.clear(); 
 char out[10];
 // fType(3);
  dwCtr(16,0,"SET CLOCK");

  //sprintf(out," %02d : %02d : %04d " ,now.hour(),now.minute(),now.second());
  sprintf(out," %02d : %02d : %02d " ,setHours,setMinutes,now.second());
  dwCtr(10,9,out);
  Disp.swapBuffers();
}













 
