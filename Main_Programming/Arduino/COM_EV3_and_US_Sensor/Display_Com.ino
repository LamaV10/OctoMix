int Display_Com() {

char m='"';
String out="";
int got=0;


// display Command 100: Cocktail ID incoming
// display Command 101: crs_Mix incoming

got = display_read();

  if(got>99){
    Serial.print("recived Signal: ");
    Serial.println(got);
    if (got == 100) { // for receving a Cocktial ID and sending an Cocktail recipe
      
      do{
        ID = display_read();
      }while(ID<=0); //geht raus wenn falsch. Wenn über 0 dann geht weiter weil 1<=0 falsch ist
 
      Serial.print("ID: ");
      Serial.println(ID);

      out=crs[ID-1];
      
      displaySerial.print("CRS.txt="); //schreibt Variable CRS mit dem Cocktialrezept
      displaySerial.print(m);
      displaySerial.print(out);
      displaySerial.print(m);
        displaySerial.write(0X0ff);
        displaySerial.write(0X0ff);
        displaySerial.write(0X0ff);

      Serial.println("setting tm0 to 1");
      displaySerial.print("tm0.en=1");//triggert das programm zum auflisten
        displaySerial.write(0X0ff);
        displaySerial.write(0X0ff);
        displaySerial.write(0X0ff);
    }

    if (got==101) {
      Serial.println("CRS empfangen: ");
      delay(100);

      for(i=0; i<sizeof(crsMix); i++){
        do{
          crsMix[i] = display_read();
        }while(crsMix[i]<0);
      }

      for(i=0; i<sizeof(crsMix); i++){
        Serial.println(crsMix[1]);
      }
      
      Serial.println(" ");
    }
    got = 0;
  }
}

char display_read(){
  int index = 0;
  char buffer[4]; //4 weil 1x zeichen und 3x OxFF

  if(displaySerial.available()){
    while(index < sizeof(buffer)) {
      buffer[index] = displaySerial.read();
      index++;
    }
  }

return buffer[0];
}