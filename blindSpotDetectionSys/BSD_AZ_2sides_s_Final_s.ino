/***********the readME part*************

Written by: Ahmed Mohamed AboElYazeed.
For : E-RALLY.
In  : SUN, 8/4/2024.

This code is written for "Blind Spot Detection system". 'for the two sides'.

- you could change the used pins as you need (there is no special pin needed).
- you could change the "unsafeDis" definition to any reasonable number, which will 
  represent the line of detection for the sensor (must be within its limits) (   ??   ).
- This system uses 9 Arduino Pins

 So, to activate this system you must 
-> with including the "AZ_BSDsys.h".
-> write "BSDsys" in your loop function.
      (with or without ';')
-> write "BSDstup()" in your setup function.

  

***********the readME part*********end*/ 


#define LtrigPin 13        //any pin (no special feature is needed).
#define LechoPin 12        //any pin (no special feature is needed).
#define LBSDled 11
#define Lind 2             //the pin connected to the indicator switch.

#define RtrigPin 6        //any pin (no special feature is needed).
#define RechoPin 5        //any pin (no special feature is needed).
#define RBSDled 4
#define Rind 3            //the pin connected to the indicator switch.

#define buzzer 8         //we only have one buzzer.

#define unsafeDis 10    //the sensor will compare its reading to it.(in meter). 


 int LindState = 0;         // variable for reading the indicator status.
 long Lduration = 0, Ldistance = 0;
 int RindState = 0;         // variable for reading the indicator status.
 long Rduration = 0, Rdistance = 0;



#define BSDsys BSDread(); delay(10);    BSDspotR();    BSDspotL(); 
              // ^ read the current distance for BOTH sides.
                             // ^ control the led and buzzer FOR the right side in different cases.
                                          // ^ control the led and buzzer FOR the left side in different cases.

void setup() {
  BSDstup();// So, to setup this system you must write this line in your setup function.
}

void loop() 
{
  BSDsys;   // So, to activate this system you must write this line in your loop function. (with including the "BSDsys.h") (with or without ';').
}



/*************************
 * functions definitions
 *************************/

// fun 0
void BSDstup()
{
  pinMode(LtrigPin, OUTPUT);
  pinMode(LechoPin, INPUT);
  pinMode(Lind, INPUT);
  pinMode(LBSDled, OUTPUT);
  
  pinMode(RtrigPin, OUTPUT);
  pinMode(RechoPin, INPUT);
  pinMode(Rind, INPUT);
  pinMode(RBSDled, OUTPUT);
  
  pinMode(buzzer,OUTPUT);
}

// fun 1
inline void BSDread () // this fun change (duration,distance,indState) to the current reading.
{
  digitalWrite(LtrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(LtrigPin, HIGH);
  delayMicroseconds(12);              //if you had an ERROR -> TRY to change this delay TO('22' insted of '12')a much longer period to avoid any conflict.
               /****^^****/
  digitalWrite(LtrigPin, LOW);
  Lduration = pulseIn(LechoPin, HIGH); 

delayMicroseconds(20);

  digitalWrite(RtrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(RtrigPin, HIGH);
  delayMicroseconds(12);
  digitalWrite(RtrigPin, LOW);
  Rduration = pulseIn(RechoPin, HIGH);       /****<<****/
  
  Ldistance = Lduration * 0.0344 / 2;   //calculate the distance in meter. (0.0344-> CM)  (0.000344-> M)
                        // ^ speed of sound in m/us (=344 m/s).  depend on the air temperature = 331.3*(0.606*Temp).
  Rdistance = Rduration * 0.0344 / 2;   //calculate the distance in meter.
  
  LindState = digitalRead(Lind);      //read the indicator state. 
  RindState = digitalRead(Rind);      //read the indicator state.
}


// fun 2
inline void BSDspotL () // this fun spot the cars in the blind area and control the led and the buzzer.
{
 if(Ldistance < unsafeDis)
  {   //the car is "not safe", there is a car in the blind spot.
    if(LindState == 1)
      {
        /*******the blink the led & buzzer function********/  //we could apply this by PWM with a timer. (to let the MC do his other jobs).
        digitalWrite(LBSDled, HIGH);
        digitalWrite(buzzer, HIGH);
        //debug
        digitalWrite(10, HIGH);
      }
    else if(LindState == 0)
      {
        digitalWrite(LBSDled, HIGH);
        if(RindState == 0)           //to keep the buzzer working if the right BSD is active.
          {digitalWrite(buzzer, LOW);}
      } 
  }
 else if(Ldistance >= unsafeDis)
   {   //the car is "safe", no cars in the blind spot.
     digitalWrite(LBSDled, LOW);
     if(RindState == 0)           //to keep the buzzer working if the right BSD is active.
      {digitalWrite(buzzer, LOW);}
   }
}

// fun 3
inline void BSDspotR () // this fun spot the cars in the blind area and control the led and the buzzer.
{
 if(Rdistance < unsafeDis)
  {   //the car is "not safe", there is a car in the blind spot.
    if(RindState == 1)
      {
        /*******the blink the led & buzzer function********/  //we could apply this by PWM with a timer. (to let the MC do his other jobs).
        digitalWrite(RBSDled, HIGH);
        digitalWrite(buzzer, HIGH);
      }
    else if(RindState == 0)
      {
        digitalWrite(RBSDled, HIGH);
        if(LindState == 0)           //to keep the buzzer working if the right BSD is active.
          {digitalWrite(buzzer, LOW);}
      } 
  }
 else if(Rdistance >= unsafeDis)
   {   //the car is "safe", no cars in the blind spot.
     digitalWrite(RBSDled, LOW);
     if(LindState == 0)           //to keep the buzzer working if the right BSD is active.
      {digitalWrite(buzzer, LOW);}
   }
}
