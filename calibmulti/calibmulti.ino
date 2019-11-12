
#define         MQ3                 3


         //define the load resistance connected to the gas sensor on the board, in kilo ohms
     //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO, which is extracted from the graph in datasheet

#define         RL_VALUE_MQ3                  10   
#define         RO_CLEAN_AIR_FACTOR_MQ3       60.314



   //define which analog input channel you are going to use
#define         MQ3PIN                       (A0)


#define         CALIBARAION_SAMPLE_TIMES     (50)    //define how many samples you are going to take in the calibration phase
#define         CALIBRATION_SAMPLE_INTERVAL  (50)     //define the time interal(in milisecond) between each samples in the cablibration phase

float               Ro = 0;                    //Ro is initialized to 0 kilo ohms
float               RL_VALUE, RO_CLEAN_AIR_FACTOR;

void setup() {
  Serial.begin(9600);                                   //UART setup, baudrate = 9600bps
  
                                                        //Calibrating the sensor. Please make sure the sensor is in clean air
                                                        //when you perform the calibration
  int Ro3 = MQCalibration(MQ3PIN,MQ3);

}

void loop() {
                     //Calibrating the sensor. Please make sure the sensor is in clean air
                                                        //when you perform the calibration
  int Ro3 = MQCalibration(MQ3PIN,MQ3);

}

  /****************** MQResistanceCalculation ****************************************
  Input:   raw_adc - raw value read from adc, which represents the voltage
  Output:  the calculated sensor resistance
  Remarks: The sensor and the load resistor forms a voltage divider. Given the voltage
         across the load resistor and its resistance, the resistance of the sensor
         could be derived.
************************************************************************************/
float MQResistanceCalculation(int raw_adc)
{
  return ( ((float)RL_VALUE * (1023 - raw_adc) / raw_adc));
  
}

/***************************** MQCalibration ****************************************
  Input:   mq_pin - analog channel
  Output:  Ro of the sensor
  Remarks: This function assumes that the sensor is in clean air. It uses
         MQResistanceCalculation to calculates the sensor resistance in clean air
         and then divides it with RO_CLEAN_AIR_FACTOR. RO_CLEAN_AIR_FACTOR is about
         9.577 for MQ2 sensor and differs slightly between different sensors.
************************************************************************************/
float MQCalibration(int mq_pin, int type)
{
  int i;
  float RS_AIR_val = 0, r0;

 switch (type) {

    case MQ3:
      { RL_VALUE = RL_VALUE_MQ3;
        RO_CLEAN_AIR_FACTOR = RO_CLEAN_AIR_FACTOR_MQ3;
      }
      break;
  }
  
  Serial.println("Calibrating MQ sensor...");
  
  for (i = 0; i < CALIBARAION_SAMPLE_TIMES; i++) {              //take multiple samples
    RS_AIR_val += MQResistanceCalculation(analogRead(mq_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  
  RS_AIR_val = RS_AIR_val / CALIBARAION_SAMPLE_TIMES;           //calculate the average value

  r0 = RS_AIR_val / RO_CLEAN_AIR_FACTOR;                        //RS_AIR_val divided by RO_CLEAN_AIR_FACTOR yields the Ro
                                                                //according to the chart in the datasheet
  Serial.println("Calibration is done");
  Serial.print("Ro value for MQ");
  Serial.print(type);
  Serial.print(" sensor is ");  
  Serial.print(r0);
  Serial.println("kohm\n");
  //Serial.print(F("r0 value"));
  //Serial.println(r0);

  return r0;
}
