#include<LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

//botoes
#define bt1 A1
#define bt2 A2
#define bt3 A3

//variaveis
int index = 0;
int buttonState = 0;

int result = 0;
long sumLevels = 0;      
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
  pinMode(bt3, INPUT_PULLUP);
    
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
  
}

void loop()
{
  main_menu();
}


void main_menu(){
  //lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(">");
  lcd.setCursor(1, 0);
  lcd.print(" Iniciar teste");
  Serial.print("BT1: ");
  Serial.print(analogRead(bt1));
  Serial.print("  BT2: ");
  Serial.print(analogRead(bt2));
  Serial.print("  BT3: ");
  Serial.println(analogRead(bt3));
  
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
        sumLevels += analogRead(A0);
        quantityLoops += 1;
        //Serial.println(millis() - startTime);
      }
      result = sumLevels / quantityLoops;
      //flag = 0x01;
      Serial.println(result);
      if(result > 650){
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Bloqueado!");
        lcd.setCursor(3, 1);
        lcd.print("Nivel: ");
        lcd.print(result);
        //acende led
        while(true){}
      }else{
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Resultado: ");
        lcd.print(result);
        delay(2000);
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Salvando...");
        delay(2000);
        index = 0;
        lcd.clear();
      }
    }
  }
}
