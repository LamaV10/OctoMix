float EV3_Distance(){
  const int numMeasurements = 50; // Anzahl an Messungen für den US-Sensor
  float duration[numMeasurements]; // Laufzeit der Schallwelle der jeweilligen Messung
  float sum, mean, distance; // Umrechnung Laufzeit in Abstand
  int validCount; // Anzahl an Messungen im Rahmen der Tolleranz

do {
    Display_Com(); //Dass immer auf das Display zugegriffen werden kann
    
    sum = 0;
    for(i=0; i<numMeasurements; i++) { //Misst so oft wie numMeasurements vorgibt
      digitalWrite(USONIC_TRIG, HIGH);
      delayMicroseconds(10);
      digitalWrite(USONIC_TRIG, LOW);

      duration[i] = pulseIn(USONIC_ECHO, HIGH); 
      sum += duration[i];
    }
    mean = sum / numMeasurements;

// Erstellung eines Durchschnittes ohne werten mit großer Abweichung vom Ursprünglichen durchschnittes   
    sum = 0;
    validCount = 0;
    for (int i = 0; i < numMeasurements; i++) { 
      if (abs(duration[i] - mean) <= 0.05 * mean) { // Werte innerhalb 5% Abweichung
        sum += duration[i];
        validCount++;
      }
    }

    mean = sum / validCount;
    distance = (mean * 0.0343) / 2; // Distanz berechnen

} while(distance != distance); //Wenn distance NaN ist dann ist die abfrage true

return distance;
}