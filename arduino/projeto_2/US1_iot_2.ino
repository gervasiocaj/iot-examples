#include <SoftwareSerial.h>

String leitura;
int temperature;
SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(4800);
}

void loop() {
  if (terminalDisponivel()) {
    leitura = lerTerminal();
    escreverTerminal(leitura);
    if (leitura == "TMP") {
      escreverTerminal("enviando requisicao de temperatura...");
      escreverSecundario(leitura);
    } 
    else {
      escreverTerminal("nao entendi requisicao");
      escreverTerminal(leitura);
    }
  }

  if (secundarioDisponivel()) {
    leitura = lerSecundario();
    escreverTerminal(leitura);

    if (leitura == "TMP") {
      temperature = lerSecundario().toInt();
      /*if (temperature <= 18) {
       mySerial.print('GREEN');
       } else if(temperature >= 19 && temperature <= 22) {
       mySerial.print('YELLOW');
       } else if(temperature > 22) {
       mySerial.print('GREEN');
       } else {*/
      escreverTerminal(String(temperature));
      //}
    }
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
