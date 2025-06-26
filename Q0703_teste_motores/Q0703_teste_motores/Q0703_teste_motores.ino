/*
     CÓDIGO:	  Q0703
     AUTOR:		  BrincandoComIdeias
     ACOMPANHE:	https://www.youtube.com/brincandocomideias ; https://www.instagram.com/canalbrincandocomideias/
     APRENDA:	  https://cursodearduino.net/ ; https://cursoderobotica.net
     COMPRE:	  https://www.arducore.com.br/
     SKETCH:    Teste da ligação dos motores
     DATA:		  25/09/2021
*/

// DEFINIÇÕES DE PINOS
#define dirFrente 5
#define dirTras   3

#define esqFrente 9
#define esqTras   6

void setup() {
  Serial.begin(9600);

  Serial.println("Configurando pinMode");

  pinMode(dirFrente, OUTPUT);
  pinMode(dirTras,   OUTPUT);
  pinMode(esqFrente, OUTPUT);
  pinMode(esqTras,   OUTPUT);

  digitalWrite(dirFrente, LOW);
  digitalWrite(dirTras,   LOW);
  digitalWrite(esqFrente, LOW);
  digitalWrite(esqTras,   LOW);

  Serial.println("Setup concluido \n Iniciando teste em 3 segundos");
  delay(3000);
}

void loop() {
  Serial.println("M. Esquerdo = Frente");
  digitalWrite(esqFrente,   HIGH);
  digitalWrite(esqTras,     LOW);
  Serial.println("M. Direito = Frente");
  digitalWrite(dirFrente,   HIGH);
  digitalWrite(dirTras,     LOW);
  
  delay(2000);
  
  Serial.println("M. Esquerdo = Parado");
  digitalWrite(esqFrente,   LOW);
  digitalWrite(esqTras,     LOW);
  Serial.println("M. Direito = Parado");
  digitalWrite(dirFrente,   LOW);
  digitalWrite(dirTras,     LOW);

  delay(2000);

  Serial.println("M. Esquerdo = Tras");
  digitalWrite(esqFrente,   LOW);
  digitalWrite(esqTras,     HIGH);
  Serial.println("M. Direito = Tras");
  digitalWrite(dirFrente,   LOW);
  digitalWrite(dirTras,     HIGH);

  delay(2000);

  Serial.println("M. Esquerdo = Parado");
  digitalWrite(esqFrente,   LOW);
  digitalWrite(esqTras,     LOW);
  Serial.println("M. Direito = Parado");
  digitalWrite(dirFrente,   LOW);
  digitalWrite(dirTras,     LOW);

  delay(2000);
}
