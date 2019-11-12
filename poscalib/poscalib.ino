float sensor_volt;
float RS_gas; 
float R0;
float ratio;
float BAC;
int R2 = 10000;
 
void setup() 
{
    Serial.begin(9600);
    pinMode(A0, INPUT);
}
 
void loop() 
{
    int sensorValue = analogRead(A0);
    sensor_volt=(float)sensorValue/1024*5.0;
    RS_gas = ((5.0 * R2)/sensor_volt) + R2; 
   /*-Replace the value of R0 with the value of R0 in your test -*/
    R0 = 3400;
    ratio = RS_gas/R0;// ratio = RS/R0
    double x = 0.4*ratio;   
    BAC = pow(x,-1.431);  //BAC in mg/L
    Serial.println(sensorValue);
    Serial.print("BAC = ");
    Serial.print(BAC);  //convert to g/dL
    Serial.print(" mg/L\n\n");
    delay(200);
}
