#include<LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

//sensor//
#define pinoSensor A0

/* CALIBRAÇÃO */
#define numLoopsCalibrar 50
#define intervaloCalibrar 5

/* LEITURA */
#define numLoopsLeitura 100
#define intervaloLeitura 50


#define constanteArLimpo 60

/* GLOBAIS */
const int R2 = 10;
float resLocal = 0.0f;
float resGas = 0.0f;
float ratio = 0.0f;
float bac;


//botoes
#define bt1 A1
#define bt2 A2

//variaveis
int index = 0;
int buttonState = 0;

float result = 0;
float sumLevels = 0;      
unsigned long quantityLoops = 0;
unsigned long startTime = 0;
unsigned long interval = 0; // seconds

boolean flag = 0x00;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(bt1, INPUT_PULLUP);
  pinMode(bt2, INPUT_PULLUP);

  for(int i = 0; i < 1; i++){
    lcd.setCursor(3, 0);
    lcd.print("BAFOMETRO!");
    lcd.setCursor(3, 1);          
    lcd.print("Loading");
    delay(100);
    lcd.setCursor(3, 1);
    lcd.print("Loading.");
    delay(100);
    lcd.setCursor(3, 1);
    lcd.print("Loading..");
    delay(150);
    lcd.setCursor(3, 1);
    lcd.print("Loading...");
    delay(150);
    lcd.clear();
  }

  while(resLocal < 1.40){
      calibrarSensor();
    }
    lcd.clear();
  
}

void loop()
{
  main_menu();
  //Serial.println(realizaLeitura());
}


void main_menu(){
  //lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(">");
  lcd.setCursor(1, 0);
  lcd.print(" Iniciar teste");
  /*Serial.print("BT1: ");
  Serial.print(analogRead(bt1));
  Serial.print("  BT2: ");
  Serial.print(analogRead(bt2));
  Serial.print("  BT3: ");
  Serial.println(analogRead(bt3));
  */
  if(analogRead(bt1) <= 350) 
  {
    index += 1;
    delay(1000);
    }
  //else index = 0;
  
  //Serial.println(millis());
  //Serial.println(buttonState);
  //Serial.println(analogRead(A5));
  
  while(index == 1){
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Aguardando");
    delay(100);
    lcd.setCursor(1, 0);
    lcd.print("Aguardando.");
    delay(100);
    lcd.setCursor(1, 0);
    lcd.print("Aguardando..");
    delay(100);
    lcd.setCursor(1, 0);
    lcd.print("Aguardando...");
    delay(100);
    lcd.clear();
    
    if(analogRead(bt1) <= 350) index += 1;
    if(analogRead(bt2) <= 350) index = 0;
    if(analogRead(bt1) <= 350 && index == 2){
      for(int i = 3; i > 0; i--){
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Assopre em ");
        lcd.print(i);
        lcd.print("s");
        delay(1000);
      }
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Medindo...");
      
      result = 0;
      sumLevels = 0;
      quantityLoops = 0;
      startTime = millis();
      interval = 500UL; // seconds
      
      while(millis() - startTime < interval){
        sumLevels += realizaLeitura();
        quantityLoops += 1;
        //Serial.println(millis() - startTime);
      }
      result = sumLevels / quantityLoops;
      //flag = 0x01;
      //Serial.println(result, 2);

       lcd.clear();
       lcd.setCursor(1, 0);
       lcd.print("Salvando...");
       //manda pro app
       Serial.print(result);
       delay(2000);
       index = 0;
       lcd.clear();
      
      if(result > 0.06){
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Bloqueado!");
        lcd.setCursor(3, 1);
        lcd.print("Nivel: ");
        lcd.print(result, 2);
        //acende led
        while(true){
          if(Serial.available() > 0){
            if(Serial.read() == 42){
              //Serial.println(Serial.read());
              break;
            }
          }
         }
      }else{
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Resultado: ");
        lcd.setCursor(2, 1);
        lcd.print(result, 2);
        lcd.print(" mg/L");
        delay(4000);
      }
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Aguarde...");
      while(realizaLeitura() > 0.02){
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Aguarde");
        delay(100);
        lcd.setCursor(1, 0);
        lcd.print("Aguarde.");
        delay(100);
        lcd.setCursor(1, 0);
        lcd.print("Aguarde..");
        delay(100);
        lcd.setCursor(1, 0);
        lcd.print("Aguarde...");
        delay(200);
        lcd.clear();
        }
    }
  }
}

float calcResistenciaLocal() // cálculo do R0
{
  float resistenciaGas = 0.0f;
  float resistenciaLocal = 0.0f; 
  
  int leituraSensor = analogRead(pinoSensor);
  float tensaoSensor = (float) leituraSensor / 1024 * 5.0;  
  resistenciaGas = ((5.0 * R2) / tensaoSensor) + R2;
  resistenciaLocal = resistenciaGas / constanteArLimpo;

  return resistenciaLocal;
  }


void calibrarSensor()
{
  //Serial.print("\nCalibrando...");
  float valorResistencia = 0.0f;
  float somaRes = 0.0f;
  float mediaResistenciaAr = 0.0f; 

  for(int i = 0; i < numLoopsCalibrar; i++)
  {
    valorResistencia = calcResistenciaLocal();
    somaRes = somaRes + valorResistencia;
    delay(intervaloCalibrar);
    }
    
  mediaResistenciaAr = somaRes / numLoopsCalibrar;
  //Serial.print("\nSensor calibrado!  R0:  ");
  //Serial.print(mediaResistenciaAr);
  //Serial.print(" Ohms\n");
  lcd.setCursor(2, 0);
  lcd.print("Calibrando...");
  lcd.setCursor(2, 1);
  lcd.print("R0: ");
  lcd.print(mediaResistenciaAr);
  lcd.print("Ohms");
  delay(50);
  //lcd.clear();

  resLocal = mediaResistenciaAr;
  //return mediaResistenciaAr;  
  }

float calcBac() // Cálculo de concentração de álcool no sangue / BAC
{
  float bacLocal = 0.0f;
  int leituraSensor = analogRead(pinoSensor);
  float tensaoSensor = (float) leituraSensor / 1024 * 5.0;
  resGas = ((5.0 * R2) / tensaoSensor) + R2;
  ratio = resGas / resLocal;
  double x = 0.4 * ratio;
  bacLocal = pow(x, -1.431); // mg/L
  return bacLocal;
  }

float realizaLeitura()
{
  float valorBac = 0.0f;
  float somaBac = 0.0f;
  float mediaBac = 0.0f;
  for(int i = 0; i < numLoopsLeitura; i++)
  {
    valorBac = calcBac();
    somaBac = somaBac + valorBac;
    //Serial.println(somaBac);   
    }
  mediaBac = somaBac / numLoopsLeitura;
  
  return mediaBac;
  }
