String leitura;
int temperature;

#include <Thermistor.h>
#include <SoftwareSerial.h>

#define ledRed 2
#define ledYellow 3 
#define ledGreen 4

Thermistor temp(A0);
SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  mySerial.begin(4800);

  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
}

void loop() {
  Serial.println("to aqui oh");
  if (mySerial.available()) {
    leitura = mySerial.readString();
    Serial.println("JA RECEBI");
    if (leitura == "TMP") {
      mySerial.println(temp.getTemp());
    }/*
    else if (leitura == 'GREEN') {
      digitalWrite(ledGreen, HIGH);
      mySerial.write('OK');  
    }
    else if (leitura == 'YELLOW') {
      digitalWrite(ledYellow, HIGH);  
      mySerial.write('OK');
    } else {
      digitalWrite(ledRed, HIGH);  
      mySerial.write('OK');
    }   
*/
  }
}



