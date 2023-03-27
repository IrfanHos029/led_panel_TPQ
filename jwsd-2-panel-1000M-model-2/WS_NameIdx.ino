

char* sholatN(int number) // get sholat name from EEPROM
    {
      static char  locBuff[8];
      sprintf(locBuff,"%s" ,sholatCall[number]);
      return locBuff;
    }

char * DayName(int number)  // get Day Name from EEPROM
    {
      static char  locBuff[7];
      sprintf(locBuff,"s" ,hariN[number]);
      return locBuff;
    }

char * MonthName(int number)  // get  Month Name from EEPROM
    {
      static char  locBuff[4];
      sprintf(locBuff,"s" ,bulanN[number]);
      return locBuff;
    }

char * drawDayDate()
  {
      char  locBuff[20];
      static char  out[45];
      
      sprintf(out,"%s %s,%02d-%02d-%04d   %02d %s %dH\0",DayName(daynow),pasar[jumlahhari()%5],now.day(),now.month(),now.year(),nowH.hD,locBuff,nowH.hY);
      return out;
  }


//    char *  drawMasjidName()
//  {
//      char  bufMN[]="test";
//      static char  out[150];
//      char  locBuff[45];
//     // int   locLen = (Prm.MT-1)*10;
//     // memccpy_P(locBuff,MT_Name_E+locLen  ,0,10);
//     // EEPROM.get(55,bufMN);
//      sprintf(out,"%s",locBuff,bufMN);
//      return out;
//  }
  
 
char *  drawNama()
  {
      static char  out[150]="Suhartono.Khusnul.Irfan.Alfin.Alfian";
      return out;
  }
