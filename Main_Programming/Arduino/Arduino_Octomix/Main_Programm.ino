//////////////////////////////////////////////////////////////
//          Main Program wich needs to be run
/////////////////////////////////////////////////////////////

void loop() {
// lokale Variablen
  int i = 0;

// Main programm
  if(uploadToNextionDisplay == false){ 

  EV3_Com(EV3_STOP);
  Display_Com();

  if(isMixing == true){ // Wenn Cocktail gemixt werden soll. isMixing wird von Display_Com gesetzt.
    //wann shaken?
    shake1 = crsMix[15];
    shake2 = crsMix[16];

    Progress_Bar();

    for(i=0; i<14; i=i+2){
      valveNum = crsMix[i];
      volume = crsMix[i+1];
      
      if (valveNum != 0){
        //zum Ventil fahren
        Distance_Controll(valveDistance[(valveNum+1)/2]); // gibt den aufgerundeten halbierten wert an valveDistance weiter an distance controll um dorthin zu fahren

        Progress_Bar();  

        //richiges Ventil öffnen
        if(valveNum % 2 != 0){ //bei ungeraden Ventilen
          EV3_Com(EV3_VR_O);
        } else {
          EV3_Com(EV3_VF_O);
        }

        Progress_Bar();
        
        //Pumpe
        digitalWrite(PUMP, HIGH); // Pumpe anschalten
        Expanded_delay(volume/flowrate); // richtige Zeit warten
        digitalWrite(PUMP, LOW); //Pumpe ausschalten

        Progress_Bar();
        
        //Ventil schließen
        if(valveNum % 2 != 0){ //durch änderung im EV3 programm könnte man sich einen befehl spaaren
          EV3_Com(EV3_VR_C);
        } else {
          EV3_Com(EV3_VF_C);
        }
        Progress_Bar();

        //Shanken Wenn i/2+1=shake1 oder =shake2 dann shaken
        if(i==shake1 || i==shake2) {
          digitalWrite(SHAKER, HIGH); // shaken an
          Progress_Bar(); 
          Expanded_delay(5*1000); // watet bis i größer als die wartezeit ist. (x in sek * 1000)
          digitalWrite(SHAKER, LOW); // shaken aus
        }
      }
    }
    
    // Nachricht an Display, dass Cocktail fertig
    Display_Write_Number("Home.isMixing.val=", 0);
    isMixing = false;
  }

  } else { // Programm zum Hochladen an das Display
    upload_to_display();
  }
}