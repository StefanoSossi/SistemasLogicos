int sensorEste = A0;
int sensorSud = A1;
int sensorOeste = A2;
int sensorNorte = A3;

int potenciometro = A4;

int media = 0;
int referencia = 80;

int lecturaEste = 0;
int lecturaSud = 0;
int lecturaOeste = 0;
int lecturaNorte = 0;


int ledNorteRojo = 2;
int ledEsteRojo = 3;
int ledOesteRojo = 4;
int ledSudRojo = 5;

int ledNorteAzul = 6;
int ledEsteAzul = 7;
int ledOesteAzul = 8;
int ledSudAzul = 9;

int ledVerde = 10;

int button = 11;
int buttonState = 0;  

String modo = "Maxima intensidad de luz";
int state = 0;

void setup() {
  
  Serial.begin(9600);
  pinMode(ledNorteRojo,OUTPUT);
  pinMode(ledEsteRojo,OUTPUT);
  pinMode(ledOesteRojo,OUTPUT);
  pinMode(ledSudRojo,OUTPUT);
  pinMode(ledNorteAzul,OUTPUT);
  pinMode(ledEsteAzul,OUTPUT);
  pinMode(ledOesteAzul,OUTPUT);
  pinMode(ledSudAzul,OUTPUT);
  pinMode(ledVerde,OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  
  buttonState = digitalRead(button);
  lecturaEste = analogRead(sensorEste);
  lecturaSud = analogRead(sensorSud);
  lecturaOeste = analogRead(sensorOeste);
  lecturaNorte = analogRead(sensorNorte);
  media = (lecturaEste + lecturaSud + lecturaOeste + lecturaNorte)/4;
  
  int potencia = analogRead(potenciometro);
  referencia = map(potencia, 0, 1023, 80, 450);
  
  switch(state){
    case 0:
      modoSensorLux();
        if (buttonState == HIGH) {
        modo = "Intensidad Luminica";
            state = 1;
      }
    break;
    case 1:
      modoIntensidadLux();
      if (buttonState == HIGH) {
        modo = "Alarma";
            state = 2;
      }
    break;
    default:
      modoAlarma();
      if (buttonState == HIGH) {
        modo = "Maxima intensidad de luz";
            state = 0;
      }
  }
  delay(500);
}

void logSystem(String result){
  
    Serial.print(" MODO: ");
    Serial.print(modo);
    Serial.print("; SENSORES: ");
    Serial.print(lecturaEste);
    Serial.print(", ");
    Serial.print(lecturaSud);
    Serial.print(", ");
    Serial.print(lecturaEste);
    Serial.print(", ");
    Serial.print(lecturaOeste);
    Serial.print(", ");
    Serial.print(lecturaNorte);
    Serial.print("; MEDIA: ");
    Serial.print(media);
    Serial.print("; LUX_REF: ");
    Serial.print(referencia);
    Serial.print("; RESULT: ");
    Serial.println(result);
}

void modoSensorLux(){
  
  if(lecturaEste == lecturaSud && 
     lecturaSud == lecturaOeste &&
     lecturaOeste == lecturaNorte){
    digitalWrite(ledVerde, HIGH);
    logSystem("ENCONTRADO"); 
  }
  else {
    digitalWrite(ledVerde, LOW);
    logSystem("BUSCANDO");
    directionLight(lecturaEste, ledEsteRojo, ledEsteAzul );
    directionLight(lecturaSud, ledSudRojo, ledSudAzul );
    directionLight(lecturaOeste, ledOesteRojo, ledOesteAzul );
    directionLight(lecturaNorte, ledNorteRojo, ledNorteAzul );
  }
}

void directionLight(int lectura, int ledRojo, int ledAzul){
  
  digitalWrite(ledAzul, HIGH);
  delay(100);
  digitalWrite(ledAzul, LOW);
  
  if(lectura > 400) {
    digitalWrite(ledRojo, HIGH);
    delay(100);
    digitalWrite(ledRojo, LOW);
  }
}

void modoIntensidadLux(){
  
  logSystem("NINGUNO");
  int valor = map(media, 54, 974, 0, 5);
  
  switch (valor) {
  case 0:
    digitalWrite(ledEsteRojo, LOW);
    digitalWrite(ledEsteAzul, LOW);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledOesteAzul, LOW);
    digitalWrite(ledOesteRojo, LOW);
    break;
  case 1:
    digitalWrite(ledEsteRojo, HIGH);
    digitalWrite(ledEsteAzul, LOW);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledOesteAzul, LOW);
    digitalWrite(ledOesteRojo, LOW);
    break;
  case 2:
    digitalWrite(ledEsteRojo, HIGH);
    digitalWrite(ledEsteAzul, HIGH);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledOesteAzul, LOW);
    digitalWrite(ledOesteRojo, LOW);
    break;
  case 3:
    digitalWrite(ledEsteRojo, HIGH);
    digitalWrite(ledEsteAzul, HIGH);
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledOesteAzul, LOW);
    digitalWrite(ledOesteRojo, LOW);
    break;
  case 4:
    digitalWrite(ledEsteRojo, HIGH);
    digitalWrite(ledEsteAzul, HIGH);
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledOesteAzul, HIGH);
    digitalWrite(ledOesteRojo, LOW);
    break;
  default:
    digitalWrite(ledEsteRojo, HIGH);
    digitalWrite(ledEsteAzul, HIGH);
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledOesteAzul, HIGH);
    digitalWrite(ledOesteRojo, HIGH);
  }
  
  delay(100);
  digitalWrite(ledEsteRojo, LOW);
  digitalWrite(ledEsteAzul, LOW);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledOesteAzul, LOW);
  digitalWrite(ledOesteRojo, LOW);
}

void modoAlarma(){
  if(media > referencia){
    
    logSystem("ALARMA ON");
    digitalWrite(ledEsteRojo, HIGH);
    digitalWrite(ledEsteAzul, HIGH);
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledOesteAzul, HIGH);
    digitalWrite(ledOesteRojo, HIGH);
    digitalWrite(ledSudRojo, HIGH);
    digitalWrite(ledSudAzul, HIGH);
    digitalWrite(ledNorteRojo, HIGH);
    digitalWrite(ledNorteAzul, HIGH);
    
  } else {
    logSystem("ALARMA OFF");
  }
  
  delay(100);
  digitalWrite(ledEsteRojo, LOW);
  digitalWrite(ledEsteAzul, LOW);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledOesteAzul, LOW);
  digitalWrite(ledOesteRojo, LOW);
  digitalWrite(ledSudRojo, LOW);
  digitalWrite(ledSudAzul, LOW);
  digitalWrite(ledNorteRojo, LOW);
  digitalWrite(ledNorteAzul, LOW);
}
