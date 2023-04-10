
unsigned long Run;
bool state;
void Indikator(uint8_t Delay){
  unsigned long tmr = millis();
    if((tmr - Run) > Delay){ Run = tmr; state=!state;}
    digitalWrite(Ind,state);
}


void setActive()
{
  
}














 
