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
  Serial.begin(9600);
  mySerial.begin(4800);
 
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
}
 
void loop() {
  if (mySerial.available()) {
    leitura = mySerial.readString();
    delay(1);
    Serial.print("Recebido: ");
    Serial.println(leitura);
    
    if (leitura == "TMP") {
      Serial.println("entendi, enviando temperatura...");
      mySerial.println(temp.getTemp());
    } else {
      Serial.print("nao entendi: ");
      Serial.println(leitura);
    }
    delay(1);
    /*
    }
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
