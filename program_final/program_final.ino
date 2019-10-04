#define pinoSensor A0

/* CALIBRAÇÃO */
#define numLoopsCalibrar 50
#define intervaloCalibrar 5

/* LEITURA */
#define numLoopsLeitura 100
#define intervaloLeitura 50


#define constanteArLimpo 60

/* GLOBAIS */
const int R2 = 2000;

float resLocal = 0.0f;
float resGas = 0.0f;
float ratio = 0.0f;
float bac;

 
void setup() 
{
    Serial.begin(9600);
    calibrarSensor();
}
 
void loop() 
{
  bac = realizaLeitura();
  Serial.print("BAC = ");
  Serial.print(bac);  //convert to g/dL
  Serial.print(" mg/L\n\n");
  delay(200);
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
  Serial.print("\nCalibrando...");
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
  Serial.print("\nSensor calibrado!  R0:  ");
  Serial.print(mediaResistenciaAr);
  Serial.print(" Ohms\n");

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
  
