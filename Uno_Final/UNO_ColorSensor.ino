#include <TimerOne.h>
#include <Wire.h>


//Color Sensor Interfaces
#define S0     6
#define S1     5
#define S2     4
#define S3     3
#define OUT    2


int   g_count = 0;    // count the frequecy
int   g_array[3];     // store the RGB value
int   g_flag = 0;     // filter of RGB queue
float g_SF[3];        // save the RGB Scale factor
  
 
// Init TSC230 and setting Frequency.
void TSC_Init(){
  pinMode(S0, OUTPUT);
  
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  
  digitalWrite(S0, LOW);  // OUTPUT FREQUENCY SCALING 2%
  digitalWrite(S1, HIGH); 
}
  
// Select the filter color 
void TSC_FilterColor(int Level01, int Level02){
  if(Level01 != 0)
    Level01 = HIGH;
  
  if(Level02 != 0)
    Level02 = HIGH;
  
  digitalWrite(S2, Level01); 
  digitalWrite(S3, Level02); 
}
  
void TSC_Count(){
  g_count ++ ;
}
  
void TSC_Callback(){
  switch(g_flag)
  {
    case 0: 
         //Serial.println("->WB Start");
         TSC_WB(LOW, LOW);              //Filter without Red
         break;
    case 1:
         //Serial.print("->Frequency R=");
         //Serial.println(g_count);
         g_array[0] = g_count;
         TSC_WB(HIGH, HIGH);            //Filter without Green
         break;
    case 2:
         //Serial.print("->Frequency G=");
         //Serial.println(g_count);
         g_array[1] = g_count;
         TSC_WB(LOW, HIGH);             //Filter without Blue
         break;
  
    case 3:
         //Serial.print("->Frequency B=");
         //Serial.println(g_count);
         //Serial.println("->WB End");
         g_array[2] = g_count;
         TSC_WB(HIGH, LOW);             //Clear(no filter)   
         break;
   default:
         g_count = 0;
         break;
  }
}
  
void TSC_WB(int Level0, int Level1){      //White Balance{
    g_count = 0;
    g_flag ++;
    TSC_FilterColor(Level0, Level1);
    Timer1.setPeriod(1000000);             // set 1s period
}
  
void ColorSensorSetup(){
    Wire.begin();
    TSC_Init();
    Serial.begin(9600);
    Timer1.initialize();             // defaulte is 1s
    Timer1.attachInterrupt(TSC_Callback);  
    attachInterrupt(0, TSC_Count, RISING);  
    
    delay(4000);
    // for(int i=0; i<3; i++)
    // //Serial.println(g_array);
    g_SF[0] = 255.0/ g_array[0];     //R Scale factor
    g_SF[1] = 255.0/ g_array[1] ;    //G Scale factor
    g_SF[2] = 255.0/ g_array[2] ;    //B Scale factor
  
    // Serial.println(g_SF[0]);
    //Serial.println(g_SF[1]);
    // Serial.println(g_SF[2]);
}
  
void ColorSensorLoop(){
    g_flag = 0;

    //Serial Output Section
    Serial.print("[");
    for(int i=0; i<2; i++){
        Serial.print(int(g_array[i] * g_SF[i]));
        Serial.print(",");
    }
    Serial.print(int(g_array[2] * g_SF[2]));
    Serial.println("]");
    delay(4000);

    //Color Judgement Procedure
    int red = g_array[0] * g_SF[0];
    int green = g_array[1] * g_SF[1];
    int blue = g_array[2] * g_SF[2];

    int val = 0;

    if(red <= 50 && green <= 50 && blue <= 50){         //BLACK
        val = 1;
    }
    else if(red >= 200 && green >= 200 && blue >= 200){ //WHITE
        val = 2;
    }
    else if(red>=green&&red>=blue){                     //RED
        val=3;
    }
    else if(green>=red&&green>=blue){                   //GREEN
        val=4;       
    }
    else if(blue>=red&&blue>=green){
        val=5;                                          //blue
    }

    //I2C Communication
    Wire.beginTransmission(4);
    Wire.write(int(val));
    Wire.endTransmission();
}