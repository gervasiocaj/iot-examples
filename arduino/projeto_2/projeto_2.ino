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
    } else {
      escreverTerminal("nao entendi requisicao");
      escreverTerminal(leitura);
    }
  }

  if (secundarioDisponivel()) {
    leitura = lerSecundario();
   
    escreverTerminal("___________");
    escreverTerminal(leitura);
    escreverTerminal("___________");

    if (leitura == "TMP") {
    
      temperature = lerSecundario().toInt();
      escreverSecundario("TMP_LED");
      if (temperature <= 18) {
        escreverSecundario("GREEN");
      } else if (temperature >= 19 && temperature <= 22) {
        escreverSecundario("YELLOW");
      } else if(temperature > 22) {
        escreverSecundario("RED");
      }
        
    } else if (leitura == "TMP_DONE") {
      escreverTerminal(String(temperature) + "°C");
      escreverTerminal(String(32 + (temperature * 1.8)) + "°F");
      escreverTerminal(String(temperature + 273.15) + "°K");
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
  String a = mySerial.readStringUntil('\r');
  a.trim();
  return a;
}

void escreverTerminal(String dados) {
  Serial.println(dados);
}

void escreverSecundario(String dados) {
  mySerial.println(dados);
}
