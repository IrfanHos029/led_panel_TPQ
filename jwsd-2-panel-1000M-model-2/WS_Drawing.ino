// =========================================
// Drawing Content Block====================    
// =========================================
void showJam(int DrawAdd){
 // if(!dwDo(DrawAdd)) return;
  char jam[20];
  char menit[20];
  int detik =now.second();
  char buff[20];
  sprintf(jam,"%02d",now.hour());
  sprintf(menit,"%02d",now.minute());
  if(detik % 2){sprintf(buff,"%s",":");}
  else{sprintf(buff,"%s"," ");}
  Disp.drawText(0,0,jam);
  Disp.drawText(19,0,menit);
  Disp.drawText(13,0,buff);
  //dwCtr(0,0,Buff);
 //  DoSwap = true;
   
}

void drawAzzan(int DrawAdd)
  {
    // check RunSelector
    if(!dwDo(DrawAdd)) return;
    uint8_t           ct_limit =40;  //harus angka genap
    static uint8_t    ct;
    static uint16_t   lsRn;
    uint16_t          Tmr = millis();

    if((Tmr-lsRn) > 500 and ct <= ct_limit)
      {
        lsRn = Tmr;
        if((ct%2) == 0)
          { //Disp.drawRect(1,2,62,13);
            fType(0);
            dwCtr(0,0,"ADZAN");
            fType(1);
            if(jumat) {dwCtr(0,8,sholatN(8));}
            else      {dwCtr(0,8,sholatN(SholatNow));}
            Buzzer(1);
          }
        else 
          { Buzzer(0);}
        DoSwap = true; 
        ct++;
      }
    if ((Tmr-lsRn)>2000 and (ct > ct_limit))
      {dwDone(DrawAdd);
       ct = 0;
       Buzzer(0);}
  }

void drawIqomah(int DrawAdd)  // Countdown Iqomah (9 menit)
  {  
    // check RunSelector
    if(!dwDo(DrawAdd)) return;

    static uint16_t   lsRn;
    uint16_t          Tmr = millis();
    static int        ct;
    int               mnt, scd,cn_l ;
    char              locBuff[6];           
    
    cn_l  = (Iqomah[SholatNow]*60);
    //Disp.drawRect(1,2,62,13);
    if((Tmr-lsRn) > 1000 and ct <=cn_l)
      {
          lsRn = Tmr;        
          mnt = floor((cn_l-ct)/60); 
          scd = (cn_l-ct)%60;
          if(mnt>0) {sprintf(locBuff,"%02d:%02d",mnt,scd);}
            else    {sprintf(locBuff,"%02d",scd);}
          if((ct%2) == 0){
          fType(0); //font iqomah
          dwCtr(0,-1,"IQOMAH");}          
          fType(0);
          dwCtr(0,8,locBuff);
          if (ct> (cn_l-10)) Buzzer(1);   // Buzzer on 2 seccon before Iqomah
          ct++;
          DoSwap = true;
             
      }
    if (ct > cn_l)
      {
       dwDone(DrawAdd);
       ct = 0;
       Buzzer(0);
      }    
  }

void drawHari(int DrawAdd)
  {
    // check RunSelector
//    int DrawAdd = 0b0000000000000100;
    if(!dwDo(DrawAdd)) return; 

    static uint8_t    x;
    static uint8_t    s; // 0=in, 1=out
    static uint8_t    sNum =1; 
    static uint16_t   lsRn;
    uint16_t          Tmr = millis();
    uint8_t           c=0;
    uint8_t    first_sNum = 0; 
    int               DrawWd=DWidth - c;    

    if((Tmr-lsRn)>10) 
      {
        if(s==0 and x<(DrawWd/2)){x++;lsRn=Tmr;}
        if(s==1 and x>0){x--;lsRn=Tmr;}
      }
      
    if((Tmr-lsRn)>2000 and x ==(DrawWd/2)) {s=1;}
    if (x == 0 and s==1) 
      { 
        if (sNum <1){sNum++;}
        else 
          { 
           dwDone(DrawAdd);
           sNum=1;
          } 
        s=0;
      }

    if(Prm.SI==0) {first_sNum =1;}
    else {first_sNum =0;}
    if(Prm.SI==0 and sNum == 0) {sNum=1;}
   // if(Prm.ST==0 and sNum == 2) {sNum=3;}
   // if(Prm.SU==0 and sNum == 3) {sNum=4;}

 
    if(  (((sNum == first_sNum) and s ==0) or 
          ((sNum == 1)and s == 1)) 
          and x <=20) {//drawSmallTS(int(x/2));
          } 
    else {//drawSmallTS(10);
    }
    drawSholat_S(sNum, c);

    Disp.drawFilledRect(c,0,c+DrawWd/2-x,15,0);
    Disp.drawFilledRect(DrawWd/2+x+c,0,63,15,0);
  }


void drawSholat_S(int sNum,int c) 
  {
    ///////////////jam gedhe///////////
uint16_t y;
     char  BuffJ[6];
    char  BuffM[6];
    char  BuffD[6];
    sprintf(BuffJ,"%02d",now.hour());
    sprintf(BuffM,"%02d",now.minute());
  //  sprintf(BuffD,"%02d",now.second());
    fType(3);
    Disp.drawText(0,y,BuffJ);  //tampilkan jam
    Disp.drawText(19,y,BuffM);  //tampilkan menit
  //  fType(3);
  //  Disp.drawText(19,y,BuffD);  //tampilkan detik
    Disp.drawRect(15,y+3,16,y+5,1);
    Disp.drawRect(15,y+10,16,y+12,1);
    DoSwap = true; 


    ////////////
    char  BuffTime[10];
    char  BuffShol[7];
    float   stime   = sholatT[sNum];
    uint8_t shour   = floor(stime);
    uint8_t sminute = floor((stime-(float)shour)*60);
    uint8_t ssecond = floor((stime-(float)shour-(float)sminute/60)*3600);
    sprintf(BuffTime,"%02d:%02d",shour,sminute);
   // Disp.drawRect(c+1,2,62,13);
    fType(1); dwCtr(33,0,sholatN(sNum)); //tulisan waktu sholat
    fType(1); dwCtr(33,9,BuffTime);   //jadwal sholatnya
    DoSwap = true;          
  }
  
void drawGreg_DS(uint16_t y)   //Draw Date
  { 
    char  Buff[20];
    sprintf(Buff,"%02d/%02d/%02d",now.day(),now.month(),now.year()-2000);
    dwCtr(0,y-2,Buff);
    DoSwap = true;
  }

void drawSmallTS(int x) //jam kecil  ketika sholat
  {
    char BuffH[3];
    char BuffM[3];
    static uint16_t   lsRn;
    uint16_t          Tmr = millis();
    sprintf(BuffH,"%02d",now.hour());
    sprintf(BuffM,"%02d",now.minute());
    fType(0);
    Disp.drawText((x-10)+1,-1,BuffH);
    Disp.drawText((x-10)+1,8,BuffM);
   // if(Tmr-lsRn<500)Disp.drawLine((x-10)+1,7,(x-10)+9,7,1);
   // if(Tmr-lsRn>1000) lsRn = Tmr;
    DoSwap = true;
  }  

void drawGreg_TS(uint16_t y)   // Draw Time
  {
    char  Buff[20];
    //sprintf(Buff,"%02d:%02d:%02d",now.hour(),now.minute(),now.second());
    sprintf(Buff,"%02d:%02d",now.hour(),now.minute());
    dwCtr(0,y,Buff);
    DoSwap = true; 
  }

  void jamKecil()   // Draw Time
  {
    char  Buff[20];
    //sprintf(Buff,"%02d:%02d:%02d",now.hour(),now.minute(),now.second());
    sprintf(Buff,"%02d:%02d",now.hour(),now.minute());
    return Buff;
   // dwCtr(0,y,Buff);
//DoSwap = true; 
  }
void drawGreg_cil(uint16_t y)   // Draw Time
  {
    char  Buff[20];
    sprintf(Buff,"%02d:%02d:%02d",now.hour(),now.minute(),now.second());    
    dwCtr(0,y,Buff);
    DoSwap = true;  
  }
void Jam_GD(uint16_t y)   // Draw Time Depan  jam besar di depan
  {
    char  BuffJ[6];
    char  BuffM[6];
    char  BuffD[6];
    sprintf(BuffJ,"%02d",now.hour());
    sprintf(BuffM,"%02d",now.minute());
    sprintf(BuffD,"%02d",now.second());
    fType(3);
    Disp.drawText(1,y,BuffJ);  //tampilkan jam
    Disp.drawText(32,y,BuffM);  //tampilkan menit
  //  fType(3);
    Disp.drawText(64,y,BuffD);  //tampilkan detik
//    Disp.drawRect(20,y+3,18,y+5,1);
//    Disp.drawRect(20,y+10,18,y+12,1);
//
//      Disp.drawRect(85,y+3,43,y+5,1);
//    Disp.drawRect(85,y+10,43,y+12,1);
    DoSwap = true; 
  }

void anim_DT(int DrawAdd)
  {
    // check RunSelector
    if(!dwDo(DrawAdd)) return; 
    
    static uint8_t    y;
    static uint8_t    s; // 0=in, 1=out              
    static uint16_t   lsRn;
    uint16_t          Tmr = millis();

    if((Tmr-lsRn)>100) 
      { 
        if(s==0 and y<17){lsRn=Tmr;y++;}
        if(s==1 and y>0){lsRn=Tmr;y--;}
      }
    if((Tmr-lsRn)>10000 and y ==17) {s=1;}
    if (y==7)
      {
       // Disp.drawRect(1,2,62,13);
      }
    if (y == 0 and s==1) {dwDone(DrawAdd); s=0;}
    fType(4);                           ////////////////////////////jam kuru dowoooooo
    drawGreg_cil(y-16);
  //  fType(2);
 //   drawGreg_DS(16-y);      
    }
 
void anim_JG(int DrawAdd)
  {
    // check RunSelector
    if(!dwDo(DrawAdd)) return; 
    
    static uint8_t    y;
    static uint8_t    s; // 0=in, 1=out              
    static uint16_t   lsRn;
    uint16_t          Tmr = millis();

    if((Tmr-lsRn)>100) 
      { 
        if(s==0 and y<17){lsRn=Tmr;y++;}
        if(s==1 and y>0){lsRn=Tmr;y--;}
      }
    if((Tmr-lsRn)>10000 and y ==17) {s=1;}
    if (y==7)
      {
       // Disp.drawRect(1,2,62,13);
      }
    if (y == 0 and s==1) {dwDone(DrawAdd); s=0;}
    fType(1);
    drawGreg_TS(y-8);
    
    }
void dwMrq(const char* msg, int Speed, int dDT, int DrawAdd) //running teks ada jam nya
  { 
    // check RunSelector
    static uint16_t   x; 
    if(!dwDo(DrawAdd)) return;
    if (reset_x !=0) { x=0;reset_x = 0;}      

       
    static uint16_t   lsRn;
    int fullScroll = Disp.textWidth(msg) + DWidth;    
    uint16_t          Tmr = millis();
    if((Tmr-lsRn)> Speed)
      { lsRn=Tmr;
        if (x < fullScroll) {++x;}
        else {  dwDone(DrawAdd); 
                x = 0;return;}
     if(dDT==1)
        {
        fType(1);  //Marquee    jam yang tampil di bawah
        Disp.drawText(DWidth - x, 0, msg); //runing teks diatas
       // fType(1);
        if (x<=6)                     { drawGreg_TS(16-x);}
        else if (x>=(fullScroll-6))   { drawGreg_TS(16-(fullScroll-x));}
        else                          { 
          //Disp.drawRect(1,8,30,8);//garis tengah
                                        drawGreg_TS(9);}//posisi jamnya yang bawah
        }
     else if(dDT==2) //jam yang diatas
        {    
      //  fType(1);
        if (x<=6)                     { drawGreg_TS(x-6);}
        else if (x>=(fullScroll-6))   { drawGreg_TS((fullScroll-x)-6);}
        else                          { 
          //Disp.drawRect(1,7,30,7);//garis tengah
                                        drawGreg_TS(0);}  //posisi jam nya yang diatas
        fType(1); //Marquee  running teks dibawah
        Disp.drawText(DWidth - x, 9 , msg);//runinng teks dibawah
        }
     else
        {
       // fType(1);
    //    Disp.drawLine(1,2,62,2);  nampilkan garis
     //   Disp.drawLine(1,13,62,13); //nampilkan garis
     //   Disp.drawText(DWidth - x, 4, msg);
        }
        DoSwap = true; 
      }          
  }
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

void runTEXT(int Speed,int DrawAdd)
   {
     
    static uint16_t   x;   
   if(!dwDo(DrawAdd)) return;
    if (reset_x !=0) { x=0;reset_x = 0;} 
   
    static char  text[]="TPQ AS-SA'ADAH Gampang-Prambon";
  static char lockBuff[200]; 
  sprintf(lockBuff, "%s | %s %s | %02d-%s-%04d | %02d-%s-%dH\0          ", text ,daysOfTheWeek[daynow-1],pasar[jumlahhari()%5],now.day(),bulanN[now.month()-1],now.year(),nowH.hD,mounthJawa[nowH.hM-1],nowH.hY);
   
       static uint16_t   lsRn; 
        uint32_t          Tmr = millis();
        fType(5);
       int fullScroll = Disp.textWidth(lockBuff) + DWidth ; 
      
       if((Tmr-lsRn)> Speed)
        { lsRn=Tmr;
          if (x < fullScroll) {++x;}
          else {  dwDone(DrawAdd); 
                x = 0;return;}
Disp.drawText(DWidth - x, 0, lockBuff);
DoSwap = true;
Serial.println(String() + "fulllscroll:" + fullScroll);
Serial.println(String() + "x:" + x);
        }
   }
*/
void mode_5(int Speed,int DrawAdd)
{
      // check RunSelector
    static uint16_t   xDate; 
    static uint16_t   xInfo;  if(!dwDo(DrawAdd)) return;
    if (reset_x !=0) { xDate=0; xInfo=0; reset_x = 0;} 
     static uint32_t   lsTmr;
        uint16_t          Tmr1 = millis();
    char *msgDate =  DATE();
    char *msgInfo = drawNama();
  char jam[20];
  char menit[20];
  char titik[10];
  const char Buff[50];
  static bool state1;
  sprintf(Buff,"%-34s"," ");
  sprintf(jam,"%02d",now.hour());
  sprintf(menit,"%02d",now.minute());
  if((Tmr1-lsTmr)>500){lsTmr=Tmr1;  state1=!state1; }
  if(state1){sprintf(titik,"%s",":");}
  else{sprintf(titik,"%s"," ");}
       
        int batas = Disp.textWidth(Buff);
        fType(1);
        int fullScrollD = Disp.textWidth(msgDate) + DWidth  ;
        int fullScrollI = Disp.textWidth(msgInfo) + DWidth  ;
        static uint32_t   lsRn;
        static uint32_t   lsRn1;
        uint16_t          Tmr = millis();
       if((Tmr-lsRn)> Speed)
        { lsRn=Tmr;
          if (xDate < fullScrollD) {++xDate;}
          else {  dwDone(DrawAdd); 
                xDate = 0;return;}
         if (xInfo < fullScrollI) {++xInfo;}
          else {  dwDone(DrawAdd); 
                xInfo = 0;return;}
    
      Disp.drawText(DWidth - xDate, 0, msgDate);
     Disp.drawText(DWidth - xInfo, 9, msgInfo);
    // Disp.drawText(35,0,masehi());
     fType(3);
     Disp.drawText(0,0,Buff);
     Disp.drawText(0,0,jam);
     Disp.drawText(19,0,menit);
     Disp.drawText(13,0,titik);
     Disp.drawLine(33,0,33,17);
     Disp.drawLine(33,7,93,7);
     DoSwap = true;
        } 
       
}
/*
void mode_6(int Speed,int DrawAdd)
{
      // check RunSelector
    static uint16_t   xDate; 
    static uint16_t   xInfo; 
   if(!dwDo(DrawAdd)) return;
    if (reset_x !=0) { xDate=0; xInfo=0; reset_x = 0;} 
     static uint32_t   lsTmr;
        uint16_t          Tmr1 = millis();
    char *msgDate =  DATE();
    char *msgInfo = drawNama();
  char jam[20];
  char menit[20];
  char titik[10];
  const char Buff[50];
  static bool state1;
  sprintf(Buff,"%-34s"," ");
  sprintf(jam,"%02d",now.hour());
  sprintf(menit,"%02d",now.minute());
  if((Tmr1-lsTmr)>500){lsTmr=Tmr1;  state1=!state1; }
  if(state1){sprintf(titik,"%s",":");}
  else{sprintf(titik,"%s"," ");}
       static uint32_t   lsRn;
        static uint32_t   lsRn1;
        uint16_t          Tmr = millis();
        int batas = Disp.textWidth(Buff);
        fType(1);
        int fullScrollD = Disp.textWidth(msgDate) + DWidth  ;
        int fullScrollI = Disp.textWidth(msgInfo) + DWidth  ;
      /* if((Tmr-lsRn)> Speed)
        { lsRn=Tmr;
          if (xDate < fullScrollD) {++xDate;}
          else {  //dwDone(DrawAdd); 
                xDate = 0;return;}
         if (xInfo < fullScrollI) {++xInfo;}
          else {  //dwDone(DrawAdd); 
                xInfo = 0;return;}
    
   //   Disp.drawText(DWidth - xDate, 0, msgDate);
     Disp.drawText(DWidth - xInfo, 9, msgInfo);
    // Disp.drawText(35,0,masehi());
     fType(3);
     Disp.drawText(0,0,Buff);
     Disp.drawText(0,0,jam);
     Disp.drawText(19,0,menit);
     Disp.drawText(13,0,titik);
     Disp.drawLine(33,0,33,17);
     Disp.drawLine(33,7,93,7);
     DoSwap = true;
        } 

         if((Tmr-lsRn1)> 30)
        { lsRn1=Tmr;
          if (xDate < fullScrollD) {++xDate;}
          else {  //dwDone(DrawAdd); 
                xDate = 0;return;}
//         if (xInfo < fullScrollI) {++xInfo;}
//          else {  //dwDone(DrawAdd); 
//                xInfo = 0;return;}
    
      Disp.drawText(DWidth - xDate, 0, msgDate);
    // Disp.drawText(DWidth - xInfo, 9, msgInfo);
    // Disp.drawText(35,0,masehi());
     fType(3);
     Disp.drawText(0,0,Buff);
     Disp.drawText(0,0,jam);
     Disp.drawText(19,0,menit);
     Disp.drawText(13,0,titik);
     Disp.drawLine(33,0,33,17);
     Disp.drawLine(33,7,93,7);
     DoSwap = true;
        } 
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
    if(state ==1 and Prm.BZ == 1)
      {tone(BUZZ, 500, 400);}
    else 
      {noTone(BUZZ);}
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
