/*
char * jamUtama()
{   //Disp.setFont(Font3);
     static char Buff[20];
   sprintf(Buff,"%02d:%02d|",now.hour(),now.minute());
   return Buff;
}

 char * masehi()
 {
  static  char  lockBuff [10];
  sprintf (lockBuff , "%02d/%02d/%04d" ,now.day(),now.month (),now.year());
  return  lockBuff ;
 }

  char * hariPasaran()
 {
  DoSwap = true;
  static  char  lockBuff [10];
  sprintf (lockBuff ,"%s %s" ,daysOfTheWeek[daynow-1],pasar[jumlahhari()%5]);
  return  lockBuff ;
 }
 */
 char*drawNama()
  {    fType(3);
      static char  out[]="TPQ AS-SA'ADAH Gampang,Prambon,Sidoarjo";
      return out;
  }
/*
 * 
char* sholatN(int number) // get sholat name from EEPROM
    {
      static char  locBuff[8];
      sprintf(locBuff,"%s" ,sholatCall[number]);
      return locBuff;
    }
 
char *  drawMode_1(){
  static char  text[]="TPQ AS-SA'ADAH Gampang-Prambon";
  static char lockBuff[150];
  // fType(5);  
  sprintf(lockBuff, "    %s         %s %s %02d-%s-%04d         %02d %s %dH\0         ", text ,daysOfTheWeek[daynow-1],pasar[jumlahhari()%5],now.day(),bulanN[now.month()-1],now.year(),nowH.hD,mounthJawa[nowH.hM-1],nowH.hY);
  return lockBuff;
}



char *  drawMode_2(){
  static char  text[]="TPQ AS-SA'ADAH Gampang-Prambon";
  static char lockBuff[150];
  // fType(5);  
  sprintf(lockBuff, "    %s      %02d %s %dH\0         ", text ,nowH.hD,mounthJawa[nowH.hM-1],nowH.hY);
  return lockBuff;
}

char *  drawMode_3(){
  static char  text[]="TPQ AS-SA'ADAH Gampang-Prambon";
  static char lockBuff[150];
   //fType(5);  
  sprintf(lockBuff, "  %s %02d-%s-%04d %02d %s %dH\0          ", text ,now.day(),bulanN[now.month()-1],now.year(),nowH.hD,mounthJawa[nowH.hM-1],nowH.hY);
  return lockBuff;
}


char *  drawHijriyah(){
  static char lockBuff[50];  
  fType(5);
  sprintf(lockBuff, "  %s %s %02d %s %dH\0     ",daysOfTheWeek[daynow-1],pasar[jumlahhari()%5],nowH.hD,mounthJawa[nowH.hM-1],nowH.hY);
  return lockBuff;
}
*/
char *  DATE(){
  static char  text[]="   TPQ AS-SA'ADAH Gampang-Prambon";
  static char lockBuff[200]; 
  sprintf(lockBuff, "%s %02d-%s-%04d  %02d-%s-%dH\0",daysOfTheWeek[daynow-1],now.day(),bulanN[now.month()-1],now.year(),nowH.hD,mounthJawa[nowH.hM-1],nowH.hY);
  return lockBuff;
}
