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
  if (secundarioDisponivel()) {
    leitura = lerSecundario();
    delay(1);
    escreverTerminal("Recebido: ");
    escreverTerminal(leitura);
    
    if (leitura == "TMP") {
      escreverTerminal("entendi, enviando temperatura...");
      
      escreverSecundario("TMP");
      escreverSecundario(temp.getTemp());
    } else {
      escreverTerminal("nao entendi: ");
      escreverTerminal(leitura);
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

boolean terminalDisponivel() {
  return Serial.available();
}

boolean secundarioDisponivel() {
  return mySerial.available();
}

String lerTerminal() {
  return Serial.readString();
}

String lerSecundario() {
  return mySerial.readStringUntil('\r');
}

void escreverTerminal(String dados) {
  Serial.println(dados);
}

void escreverSecundario(String dados) {
  mySerial.print(dados);
}
