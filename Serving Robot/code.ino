#include <SoftwareSerial.h>// import the serial library
SoftwareSerial Genotronex(3, 4); // RX, TX
int BluetoothData=0; // the data given from Computer

unsigned int x=0, lookAt, RollerTime=0;
/*
* Ultrasonic Sensor HC-SR04 interfacing with Arduino.
*/
// defining the pins
const int trigPin = 8;
const int echoPin = 9;
// defining variables
long duration;
int distance;

void setup()
{
Genotronex.begin(9600); 
pinMode(A0, OUTPUT);//ROLLER motor
pinMode(A1, OUTPUT); //pump MOTOR
pinMode(A2, OUTPUT); //Msg 1
pinMode(A3, OUTPUT);// msg 2
pinMode(A4, OUTPUT); //msg 3
pinMode(A5, OUTPUT); //msg 4
pinMode(5, OUTPUT); //Water LED
pinMode(6, INPUT);//dustbin ir
pinMode(7, INPUT);//glass ir
digitalWrite(A1,LOW); //PUMP OFF
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(10, OUTPUT); // encoder motor reverse
pinMode(11, OUTPUT); // encoder motor forward
pinMode(12, OUTPUT); // left motor forward
pinMode(13, OUTPUT); // left motor reverse
pinMode(4, INPUT);//encoder motor
Serial.begin(9600); // Starts the serial communication
}
unsigned int obstacleAt( )
{
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
return distance; 
}

void RollerOn()///////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
{
 while(digitalRead(6)!=HIGH);
  // put your main code here, to run repeatedly:
if(digitalRead(6)==HIGH)
{
  digitalWrite(A0,HIGH);
  delay(RollerTime);
}
digitalWrite(A0,LOW);
}
void ServiceWater(unsigned int wait, unsigned int dispense)///////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
{
  digitalWrite(A1,LOW);
  unsigned int waiting=0, dispensing=0;
do{
  digitalWrite(A2,HIGH);
  digitalWrite(5,HIGH);
  delay(500);
  waiting++;
  }while(waiting!=wait&&digitalRead(7)==HIGH);
  
if(waiting==wait)
{ digitalWrite(A3,HIGH); digitalWrite(A2,LOW); digitalWrite(5,LOW);}
else
{
  if(digitalRead(7)!=HIGH)
  {
    do
    {
      digitalWrite(A1,HIGH);
    dispensing++;
    delay(1);
    }while(digitalRead(7)==LOW&&dispensing!=dispense);
 digitalWrite(A3,HIGH); digitalWrite(A2,LOW); digitalWrite(A1,LOW);digitalWrite(5,LOW);  
  }
 RollerOn();
}

}

void forward(unsigned int count)//////////////////////////////////////////
///////////////////////////////////////////////////////////////////
{
  //lookAt=obstacleAt();
 do{lookAt=obstacleAt();digitalWrite(11,LOW);digitalWrite(12,LOW);}while(lookAt<50);
  // Serial.println(obstacleAt());
if((digitalRead(2)==HIGH))
{
  do
   {digitalWrite(11,HIGH); //encoder motor forward
    digitalWrite(12,HIGH);
   }while((digitalRead(2)==HIGH));
   digitalWrite(11,LOW);digitalWrite(12,LOW);
   x++;
}
else if((digitalRead(2)==LOW))
{
  do
   {digitalWrite(11,HIGH); //encoder motor forward
    digitalWrite(12,HIGH); //other motor forward
   }while((digitalRead(2)==LOW));
   digitalWrite(11,LOW);digitalWrite(12,LOW);
   x++;
}

//while(1);

if((digitalRead(2)==HIGH))
 {Serial.println("high");
  do
  {
    x++;
   digitalWrite(11,HIGH); //encoder motor forward
    digitalWrite(12,HIGH); //other motor forward
    while((digitalRead(2)==HIGH));
 
  if(x==count)
     {
      digitalWrite(11,LOW);digitalWrite(12,LOW); break;
      }
  x++;   
  while((digitalRead(2)==LOW));
    
  if(x==count)
     {
      digitalWrite(11,LOW);digitalWrite(12,LOW); break;
      }
 do{lookAt=obstacleAt();digitalWrite(11,LOW);digitalWrite(12,LOW);}while(lookAt<50); 
  }while(x<=count);
 
 }
 
else if((digitalRead(2)==LOW))
 {Serial.println("low");
   do
{
  x++;
  digitalWrite(11,HIGH); //encoder motor forward
    digitalWrite(12,HIGH); //other motor forward
    while((digitalRead(2)==LOW));
  if(x==count)
  {
    digitalWrite(11,LOW);digitalWrite(12,LOW); break;
    }
  x++; 
  while((digitalRead(2)==HIGH));
    
  if(x==count)
  {
    digitalWrite(11,LOW);digitalWrite(12,LOW); break;
    } 
 do{lookAt=obstacleAt();digitalWrite(11,LOW);digitalWrite(12,LOW);}while(lookAt<50);
 
  }while(x<=count);
 
 }
 Serial.println(x);
count=0;
x=0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void reverse(unsigned int count)//////////////////////////////////////////
///////////////////////////////////////////////////////////////////
{
  //lookAt=obstacleAt();
 do{lookAt=obstacleAt();digitalWrite(10,LOW);digitalWrite(13,LOW);}while(lookAt<50);
  // Serial.println(obstacleAt());
if((digitalRead(2)==HIGH))
{
  do
   {digitalWrite(10,HIGH); //encoder motor forward
    digitalWrite(13,HIGH);
   }while((digitalRead(2)==HIGH));
   digitalWrite(10,LOW);digitalWrite(13,LOW);
   x++;
}
else if((digitalRead(2)==LOW))
{
  do
   {digitalWrite(10,HIGH); //encoder motor forward
    digitalWrite(13,HIGH); //other motor forward
   }while((digitalRead(2)==LOW));
   digitalWrite(10,LOW);digitalWrite(13,LOW);
   x++;
}

//while(1);

if((digitalRead(2)==HIGH))
 {Serial.println("high");
  do
  {
    x++;
   digitalWrite(10,HIGH); //encoder motor forward
    digitalWrite(13,HIGH); //other motor forward
    while((digitalRead(2)==HIGH));
 
  if(x==count)
     {
      digitalWrite(10,LOW);digitalWrite(13,LOW); break;
      }
  x++;   
  while((digitalRead(2)==LOW));
    
  if(x==count)
     {
      digitalWrite(10,LOW);digitalWrite(13,LOW); break;
      }
 do{lookAt=obstacleAt();digitalWrite(10,LOW);digitalWrite(13,LOW);}while(lookAt<50); 
  }while(x<=count);
 
 }
 
else if((digitalRead(2)==LOW))
 {Serial.println("low");
   do
{
  x++;
  digitalWrite(10,HIGH); //encoder motor forward
    digitalWrite(13,HIGH); //other motor forward
    while((digitalRead(2)==LOW));
  if(x==count)
  {
    digitalWrite(10,LOW);digitalWrite(13,LOW); break;
    }
  x++; 
  while((digitalRead(2)==HIGH));
    
  if(x==count)
  {
    digitalWrite(10,LOW);digitalWrite(13,LOW); break;
    } 
 do{lookAt=obstacleAt();digitalWrite(10,LOW);digitalWrite(13,LOW);}while(lookAt<50);
 
  }while(x<=count);
 
 }
 Serial.println(x);
count=0;
x=0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TurnForward(unsigned int count)//////////////////////////////////////////
///////////////////////////////////////////////////////////////////
{
 do{lookAt=obstacleAt();digitalWrite(11,LOW);digitalWrite(13,LOW);}while(lookAt<50);
  // Serial.println(obstacleAt());
if((digitalRead(2)==HIGH))
{
  do
   {digitalWrite(11,HIGH); //encoder motor forward
    digitalWrite(13,HIGH);
   }while((digitalRead(2)==HIGH));
   digitalWrite(11,LOW);digitalWrite(13,LOW);
   x++;
}
else if((digitalRead(2)==LOW))
{
  do
   {digitalWrite(11,HIGH); //encoder motor forward
    digitalWrite(13,HIGH); //other motor forward
   }while((digitalRead(2)==LOW));
   digitalWrite(11,LOW);digitalWrite(13,LOW);
   x++;
}

//while(1);

if((digitalRead(2)==HIGH))
 {Serial.println("high");
  do
  {
    x++;
   digitalWrite(11,HIGH); //encoder motor forward
    digitalWrite(13,HIGH); //other motor forward
    while((digitalRead(2)==HIGH));
 
  if(x==count)
     {
      digitalWrite(11,LOW);digitalWrite(13,LOW); break;
      }
  x++;   
  while((digitalRead(2)==LOW));
    
  if(x==count)
     {
      digitalWrite(11,LOW);digitalWrite(13,LOW); break;
      }
 do{lookAt=obstacleAt();digitalWrite(11,LOW);digitalWrite(13,LOW);}while(lookAt<50); 
  }while(x<=count);
 
 }
 
else if((digitalRead(2)==LOW))
 {Serial.println("low");
   do
{
  x++;
  digitalWrite(11,HIGH); //encoder motor forward
    digitalWrite(13,HIGH); //other motor forward
    while((digitalRead(2)==LOW));
  if(x==count)
  {
    digitalWrite(11,LOW);digitalWrite(13,LOW); break;
    }
  x++; 
  while((digitalRead(2)==HIGH));
    
  if(x==count)
  {
    digitalWrite(11,LOW);digitalWrite(13,LOW); break;
    } 
 do{lookAt=obstacleAt();digitalWrite(11,LOW);digitalWrite(13,LOW);}while(lookAt<50);
 
  }while(x<=count);
 
 }
 Serial.println(x);
count=0;
x=0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TurnReverse(unsigned int count)//////////////////////////////////////////
///////////////////////////////////////////////////////////////////
{
    //lookAt=obstacleAt();
 do{lookAt=obstacleAt();digitalWrite(10,LOW);digitalWrite(12,LOW);}while(lookAt<50);
  // Serial.println(obstacleAt());
if((digitalRead(2)==HIGH))
{
  do
   {digitalWrite(10,HIGH); //encoder motor forward
    digitalWrite(12,HIGH);
   }while((digitalRead(2)==HIGH));
   digitalWrite(10,LOW);digitalWrite(12,LOW);
   x++;
}
else if((digitalRead(2)==LOW))
{
  do
   {digitalWrite(10,HIGH); //encoder motor forward
    digitalWrite(12,HIGH); //other motor forward
   }while((digitalRead(2)==LOW));
   digitalWrite(10,LOW);digitalWrite(12,LOW);
   x++;
}

//while(1);

if((digitalRead(2)==HIGH))
 {Serial.println("high");
  do
  {
    x++;
   digitalWrite(10,HIGH); //encoder motor forward
    digitalWrite(12,HIGH); //other motor forward
    while((digitalRead(2)==HIGH));
 
  if(x==count)
     {
      digitalWrite(10,LOW);digitalWrite(12,LOW); break;
      }
  x++;   
  while((digitalRead(2)==LOW));
    
  if(x==count)
     {
      digitalWrite(10,LOW);digitalWrite(12,LOW); break;
      }
 do{lookAt=obstacleAt();digitalWrite(10,LOW);digitalWrite(12,LOW);}while(lookAt<50); 
  }while(x<=count);
 
 }
 
else if((digitalRead(2)==LOW))
 {Serial.println("low");
   do
{
  x++;
  digitalWrite(10,HIGH); //encoder motor forward
    digitalWrite(12,HIGH); //other motor forward
    while((digitalRead(2)==LOW));
  if(x==count)
  {
    digitalWrite(10,LOW);digitalWrite(12,LOW); break;
    }
  x++; 
  while((digitalRead(2)==HIGH));
    
  if(x==count)
  {
    digitalWrite(10,LOW);digitalWrite(12,LOW); break;
    } 
 do{lookAt=obstacleAt();digitalWrite(10,LOW);digitalWrite(12,LOW);}while(lookAt<50);
 
  }while(x<=count);
 
 }
 Serial.println(x);
count=0;
x=0;
 
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////MAIN
void loop()
{
////////////////////////bluetooth///////////////////////////
  do
 {
  if (Genotronex.available())
  {
  BluetoothData=Genotronex.read();
  }
 }while(BluetoothData!='1');
 
 BluetoothData=0;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////MAIN_PROGRAM SHOULD START BELOW///////////////////////////////////////////////////////////////////////
RollerTime=3000;//millisec
forward(100);
delay(2000);
delay(2000);
forward(68);
ServiceWater(20,3000); //(sec,millisec)
reverse(100);
delay(1000);
reverse(68);










}
