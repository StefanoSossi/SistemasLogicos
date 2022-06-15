
int ledModo = 2;
int ledParametro1 = 3;
int ledParametro2 = 4;
int ledParametro3 = 5;
int ledvalor1 = 6;
int ledvalor2 = 7;
int ledvalor3 = 8;

int sensorLux = A5;
int sensorViento = A4;
int sensorTemperatura = A3;

int button = 9;
int buttonState = 0; 
int time =0;
int tiempoi =0;
int tiempof =0;
int lastButtonState = 0;

String parametros[] = { "Frecuencia", "Unidades", "Nomenclatura" };
String parametro = parametros[0];
int parametroaux = 0;

String p1s[] = { "100ms", "500ms", "1s" };
String p1 = p1s[0];
String p2s[] = { "Celsius", "Kelvin", "Farenheit" };
String p2 = p2s[0];
String p3s[] = { "Grados", "Radianes", "NSEO" };
String p3 = p3s[0];
int valor1 = 0;
int valor2 = 0;
int valor3 = 0;

String modo = "Configuracion";
// Configuracion, Operacion

int valorViento = 0;
int valorTemperatura = 0;
int valorLux = 0;
int valorEnvio = 1000;

void setup()
{
  Serial.begin(9600);
  pinMode(ledModo,OUTPUT);
  pinMode(ledParametro1,OUTPUT);
  pinMode(ledParametro2,OUTPUT);
  pinMode(ledParametro3,OUTPUT);
  pinMode(ledvalor1,OUTPUT);
  pinMode(ledvalor2,OUTPUT);
  pinMode(ledvalor3,OUTPUT);
  
  pinMode(button, INPUT);
}

void loop()
{
  buttonPul();
  if(modo == "Configuracion"){
    modoLeds();
    printData();
    //printConfiguration();
    digitalWrite(ledModo, HIGH);
    delay(1000);
    digitalWrite(ledModo, LOW);
  }
  else{
    //modo = "Operacion"
    ledLightIntensity();
    lecturaTemperatura();
    lecturaViento();
    frecuenciaEnvio();
    printData();
    digitalWrite(ledModo, HIGH);
    delay(250);
    digitalWrite(ledModo, LOW);
    delay(500);
    digitalWrite(ledModo, HIGH);
    delay(250);
    digitalWrite(ledModo, LOW);
  }
  delay(valorEnvio);
}

void ledLightIntensity(){
  valorLux = analogRead(sensorLux);
  int auxLux = map(valorLux, 54, 974, 0, 6);
  switch (auxLux) {
      case 0:
        digitalWrite(ledParametro1, LOW);
        digitalWrite(ledParametro2, LOW);
        digitalWrite(ledParametro3, LOW);
        digitalWrite(ledvalor1, LOW);
        digitalWrite(ledvalor2, LOW);
        digitalWrite(ledvalor3, LOW);
        break;
      case 1:
        digitalWrite(ledParametro1, HIGH);
        digitalWrite(ledParametro2, LOW);
        digitalWrite(ledParametro3, LOW);
        digitalWrite(ledvalor1, LOW);
        digitalWrite(ledvalor2, LOW);
        digitalWrite(ledvalor3, LOW);
        break;
      case 2:
        digitalWrite(ledParametro1, HIGH);
        digitalWrite(ledParametro2, HIGH);
        digitalWrite(ledParametro3, LOW);
        digitalWrite(ledvalor1, LOW);
        digitalWrite(ledvalor2, LOW);
        digitalWrite(ledvalor3, LOW);
        break;
      case 3:
        digitalWrite(ledParametro1, HIGH);
        digitalWrite(ledParametro2, HIGH);
        digitalWrite(ledParametro3, HIGH);
        digitalWrite(ledvalor1, LOW);
        digitalWrite(ledvalor2, LOW);
        digitalWrite(ledvalor3, LOW);
        break;
      case 4:
        digitalWrite(ledParametro1, HIGH);
        digitalWrite(ledParametro2, HIGH);
        digitalWrite(ledParametro3, HIGH);
        digitalWrite(ledvalor1, HIGH);
        digitalWrite(ledvalor2, LOW);
        digitalWrite(ledvalor3, LOW);
        break;
      case 5:
        digitalWrite(ledParametro1, HIGH);
        digitalWrite(ledParametro2, HIGH);
        digitalWrite(ledParametro3, HIGH);
        digitalWrite(ledvalor1, HIGH);
        digitalWrite(ledvalor2, HIGH);
        digitalWrite(ledvalor3, LOW);
        break;
      case 6:
        digitalWrite(ledParametro1, HIGH);
        digitalWrite(ledParametro2, HIGH);
        digitalWrite(ledParametro3, HIGH);
        digitalWrite(ledvalor1, HIGH);
        digitalWrite(ledvalor2, HIGH);
        digitalWrite(ledvalor3, HIGH);
        break;
  }
}

void lecturaViento(){
  int viento = analogRead(sensorViento);
  valorViento = map(viento, 0, 1023, 0, 360);
  
  switch (valor3) {
        case 0: //Grados
            valorViento = valorViento;
            break;
          case 1: //Radianes
            valorViento = (valorViento * 3.14)/180;
            break;
          case 2: //NSEO
            valorViento = map(valorViento, 0, 360, 0, 3);
            break;
      }
}

void lecturaTemperatura(){
  int temperatura = analogRead(sensorTemperatura);
  temperatura = map(temperatura, 20, 358, -40, 125);
  
  switch (valor2) {
        case 0: //Celsius
            valorTemperatura = temperatura;
            break;
          case 1: //Kelvin
            valorTemperatura = temperatura + 273.15;
            break;
          case 2: //Farenheit
            valorTemperatura = (temperatura * 1.8) + 32;
            break;
      }
}

void frecuenciaEnvio(){
  switch (valor1) {
        case 0: //100ms
            valorEnvio = 100;
            break;
          case 1: //500ms
            valorEnvio = 500;
            break;
          case 2: //1s
            valorEnvio = 1000;
            break;
      }
}

void buttonPul(){
  buttonState = digitalRead(button);
  if (buttonState != lastButtonState) {
    updateState();
  }
  lastButtonState = buttonState;
}

void updateState() {
  if (buttonState == HIGH) {
      tiempoi = millis();
  }
  else {
    tiempof = millis();
    time = tiempof - tiempoi;
    //Serial.print(" Button time pressed");
    //Serial.println(time);
    if(time < 3000 ){
      switch (parametroaux) {
        case 0: //Frecuencia
            valor1 = (valor1 + 1) % 3;
            p1 = p1s[valor1];
            break;
          case 1: //Unidades
            valor2 = (valor2 + 1) % 3;
            p2 = p2s[valor2];
            break;
          case 2: //Nomenclatura
            valor3 = (valor3 + 1) % 3;
            p3 = p3s[valor3];
            break;
      }
    }
    if(time > 3000 && time < 5000 ){
      parametroaux = (parametroaux + 1) % 3; 
      parametro = parametros[parametroaux];
    }
    if(time > 5000){
      modo = "Operacion";
    }
    
  }
 }

void modoLeds(){
   switch (parametroaux) {
    case 0: //Frecuencia
      switch (valor1) {
        case 0:
            digitalWrite(ledParametro1, LOW);
          digitalWrite(ledParametro2, LOW);
          digitalWrite(ledParametro3, HIGH);
          digitalWrite(ledvalor1, LOW);
          digitalWrite(ledvalor2, LOW);
          digitalWrite(ledvalor3, HIGH);
            break;
          case 1:
            digitalWrite(ledParametro1, LOW);
          digitalWrite(ledParametro2, LOW);
          digitalWrite(ledParametro3, HIGH);
          digitalWrite(ledvalor1, LOW);
          digitalWrite(ledvalor2, HIGH);
          digitalWrite(ledvalor3, LOW);
            break;
          case 2:
            digitalWrite(ledParametro1, LOW);
          digitalWrite(ledParametro2, LOW);
          digitalWrite(ledParametro3, HIGH);
          digitalWrite(ledvalor1, HIGH);
          digitalWrite(ledvalor2, LOW);
          digitalWrite(ledvalor3, LOW);
            break;
      }
      break;
    case 1: //Unidades
      switch (valor2) {
        case 0:
            digitalWrite(ledParametro1, LOW);
          digitalWrite(ledParametro2, HIGH);
          digitalWrite(ledParametro3, LOW);
          digitalWrite(ledvalor1, LOW);
          digitalWrite(ledvalor2, LOW);
          digitalWrite(ledvalor3, HIGH);
            break;
          case 1:
            digitalWrite(ledParametro1, LOW);
          digitalWrite(ledParametro2, HIGH);
          digitalWrite(ledParametro3, LOW);
          digitalWrite(ledvalor1, LOW);
          digitalWrite(ledvalor2, HIGH);
          digitalWrite(ledvalor3, LOW);
            break;
          case 2:
            digitalWrite(ledParametro1, LOW);
          digitalWrite(ledParametro2, HIGH);
          digitalWrite(ledParametro3, LOW);
          digitalWrite(ledvalor1, HIGH);
          digitalWrite(ledvalor2, LOW);
          digitalWrite(ledvalor3, LOW);
            break;
      }
      break;
    case 2: //Nomenclatura
      switch (valor3) {
        case 0:
            digitalWrite(ledParametro1, HIGH);
          digitalWrite(ledParametro2, LOW);
          digitalWrite(ledParametro3, LOW);
          digitalWrite(ledvalor1, LOW);
          digitalWrite(ledvalor2, LOW);
          digitalWrite(ledvalor3, HIGH);
            break;
          case 1:
            digitalWrite(ledParametro1, HIGH);
          digitalWrite(ledParametro2, LOW);
          digitalWrite(ledParametro3, LOW);
          digitalWrite(ledvalor1, LOW);
          digitalWrite(ledvalor2, HIGH);
          digitalWrite(ledvalor3, LOW);
            break;
          case 2:
            digitalWrite(ledParametro1, HIGH);
          digitalWrite(ledParametro2, LOW);
          digitalWrite(ledParametro3, LOW);
          digitalWrite(ledvalor1, HIGH);
          digitalWrite(ledvalor2, LOW);
          digitalWrite(ledvalor3, LOW);
            break;
      }
      break;
   }
}

void printData(){
    //MODO: Operacion; P1: 100ms; P2: Celsius; P3: Grados; LUZ: 216; TEMP: 16.6; D. VIENTO: 32°
//    Serial.print(" MODO: ");
//    Serial.print(modo);
//    Serial.print("; P1: ");
//    Serial.print(p1);
//    Serial.print("; P2: ");
//    Serial.print(p2);
//    Serial.print("; P3: ");
//    Serial.print(p3);
//    Serial.print("; LUZ: ");
//    Serial.print(valorLux);
//    Serial.print("; TEMP: ");
//    Serial.print(valorTemperatura);
//    Serial.print("; D.VIENTO: ");
//    Serial.println(valorViento);

//Operacion;100ms;Celsius;Grados;216;16.6;32
    Serial.print(modo);
    Serial.print(";");
    Serial.print(p1);
    Serial.print(";");
    Serial.print(p2);
    Serial.print(";");
    Serial.print(p3);
    Serial.print(";");
    Serial.print(valorLux);
    Serial.print(";");
    Serial.print(valorTemperatura);
    Serial.print(";");
    Serial.println(valorViento);
}
  
void printConfiguration(){
  //MODO: Configuracion; Parametro: Frecuencia; P1: 100ms; P2: Celsius; P3: Grados
    Serial.print(" MODO: ");
    Serial.print(modo);
    Serial.print("; Parametro: ");
    Serial.print(parametro);
    Serial.print("; P1: ");
    Serial.print(p1);
    Serial.print("; P2: ");
    Serial.print(p2);
    Serial.print("; P3: ");
    Serial.println(p3);
}
