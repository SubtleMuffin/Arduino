// #include <Wire.h>

// void setup()
// {
//   Wire.begin(2);                // join i2c bus with address #2
//   Wire.onRequest(requestEvent); // register event
// }

// void loop()
// {
//   delay(100);
// }

// // function that executes whenever data is requested by master
// // this function is registered as an event, see setup()
// void requestEvent()
// {
//   Wire.write("hello "); // respond with message of 6 bytes
//                        // as expected by master
// }
//

// #include <Wire.h>


// void setup()
// {
//   Wire.begin();

//   Serial.begin(9600);
//   Serial.println("\nI2C Scanner");
// }


// void loop()
// {
//   byte error, address;
//   int nDevices;

//   Serial.println("Scanning...");

//   nDevices = 0;
//   for(address = 1; address < 127; address++ ) 
//   {
//     // The i2c_scanner uses the return value of
//     // the Write.endTransmisstion to see if
//     // a device did acknowledge to the address.
//     Wire.beginTransmission(address);
//     error = Wire.endTransmission();

//     if (error == 0)
//     {
//       Serial.print("I2C device found at address 0x");
//       if (address<16) 
//         Serial.print("0");
//       Serial.print(address,HEX);
//       Serial.println("  !");

//       nDevices++;
//     }
//     else if (error==4) 
//     {
//       Serial.print("Unknow error at address 0x");
//       if (address<16) 
//         Serial.print("0");
//       Serial.println(address,HEX);
//     }    
//   }
//   if (nDevices == 0)
//     Serial.println("No I2C devices found\n");
//   else
//     Serial.println("done\n");

//   delay(5000);           // wait 5 seconds for next scan
// }


// #include <Servo.h>

// void setup(){
// 	//MegaCommSetup();
// }

// void loop(){
// 	//MegaCommLoop();

// }


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created
Servo myservo1; 
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo1.attach(10);
} 
 
 
void loop() 
{ 
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
                           // waits 15ms for the servo to reach the position 
  	myservo1.write(-pos);
  	delay(15);
  } 
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
                           // waits 15ms for the servo to reach the position 
    myservo1.write(-pos);
    delay(15); 
  } 
}