
int bulb_on =12;
int bulb_off =12;

void setup()
{
  pinMode(bulb_on, OUTPUT);
  pinMode(bulb_off, OUTPUT);
}

 
void loop()
{
  if(bulb_on <13 && bulb_on >7){
    digitalWrite(bulb_on,HIGH);
    delay(1000);
    bulb_on = bulb_on - 1;
  }
  
  else if(bulb_off <13 &&  bulb_off >7){
    digitalWrite(bulb_off,LOW);
    delay(1000);
    bulb_off = bulb_off - 1;
  }
  
  else {
  	bulb_on = 12;
    bulb_off =12;
  }
}
