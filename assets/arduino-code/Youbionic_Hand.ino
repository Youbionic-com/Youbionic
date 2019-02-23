#define pinMusSen A1

int position = 1;
int contractionlimitvalue= 150;
int instantreading = 0;
int savedreading = 0;
int maxcontractionset = 0;
int mincontractionset= 1023;
int minmaxdifferenceset = 0 ;

int maxcontraction = 0;
int mincontraction= 1023;
int deltavalue = 0;
int maxmindifference = 0 ;
int contractiontype = 1;

// A = Index
// B = Middle
// C = Ring
// D = Pinky
// E = Thumb
// F = Thumb rotation

int pinDirA = 2;
int pinPwmA = 3;
int pinDirB = 7;
int pinPwmB = 5;
int pinDirC = 8;
int pinPwmC = 6;
int pinDirD = 12;
int pinPwmD = 9;
int pinDirE = 13;
int pinPwmE = 10;
int pinDirF = 1;
int pinPwmF = 11;

int pinModeHigh = 4;

void setup() {

Serial.begin(9600);

pinMode ( pinDirA, OUTPUT );
pinMode ( pinPwmA, OUTPUT );

pinMode ( pinDirB, OUTPUT );
pinMode ( pinPwmB, OUTPUT );

pinMode ( pinDirC, OUTPUT );
pinMode ( pinPwmC, OUTPUT );

pinMode ( pinDirD, OUTPUT );
pinMode ( pinPwmD, OUTPUT );

pinMode ( pinDirE, OUTPUT );
pinMode ( pinPwmE, OUTPUT );

pinMode ( pinDirF, OUTPUT );
pinMode ( pinPwmF, OUTPUT );

pinMode ( pinModeHigh, OUTPUT );


digitalWrite( pinModeHigh,HIGH );

//Open the Hand
 digitalWrite( pinDirE,LOW );
 analogWrite( pinPwmE,255 );
 delay(200);
 digitalWrite( pinDirA,LOW );
 analogWrite( pinPwmA,255 );
 digitalWrite( pinDirB,LOW );
 analogWrite( pinPwmB,255 );
 digitalWrite( pinDirC,LOW );
 analogWrite( pinPwmC,255 );
 digitalWrite( pinDirD,LOW );
 analogWrite( pinPwmD,255 );
 digitalWrite( pinDirF,LOW );
 analogWrite( pinPwmF,255 );

delay(2000);

//Close the Hand
digitalWrite( pinDirD,HIGH );
analogWrite( pinPwmD,255 );
digitalWrite( pinDirC,HIGH );
analogWrite( pinPwmC,255 );
digitalWrite( pinDirB,HIGH );
analogWrite( pinPwmB,255 );
digitalWrite( pinDirA,HIGH );
analogWrite( pinPwmA,255 );
digitalWrite( pinDirE,HIGH );
analogWrite( pinPwmE,200 );

delay(2000);

//Open the Hand
 digitalWrite( pinDirE,LOW );
 analogWrite( pinPwmE,255 );
 delay(200);
 digitalWrite( pinDirA,LOW );
 analogWrite( pinPwmA,255 );
 digitalWrite( pinDirB,LOW );
 analogWrite( pinPwmB,255 );
 digitalWrite( pinDirC,LOW );
 analogWrite( pinPwmC,255 );
 digitalWrite( pinDirD,LOW );
 analogWrite( pinPwmD,255 );
 digitalWrite( pinDirF,LOW );
 analogWrite( pinPwmF,255 );

//Muscle Contraction Calibration Phase
delay(1000);     // Time to let the signal stabilize
instantreading = analogRead( pinMusSen );   //read the value of the contraction
savedreading = instantreading ;   //write into savedreading a number already read, different from zero
delay(25);
for (int i=0; i <= 400; i++)  // 10 seconds to perform accurate calibration
{
instantreading = analogRead( pinMusSen );
  if (instantreading > savedreading  &&  instantreading > maxcontractionset )
{
maxcontractionset = instantreading ;
}
  if (instantreading < savedreading  &&  instantreading < mincontractionset)
{
mincontractionset= instantreading ;
}
savedreading = instantreading;
Serial.print  ("Lettura Istantanea: ");
Serial.println( instantreading );
delay(25);
}

contractionlimitvalue= (( ( maxcontractionset - mincontractionset) / 2 ) + mincontractionset) * 0.8 ;

Serial.print  ("Maximum Contraction Set: ");
Serial.println(maxcontractionset);

Serial.print  ("Minimum Contrast Set: ");
Serial.println(mincontractionset);

// Stop Calibration Signed 
 digitalWrite( pinDirF,HIGH );
 analogWrite( pinPwmF,255 );

delay(500);

 digitalWrite( pinDirF,LOW );
 analogWrite( pinPwmF,255 );

delay(500);

 digitalWrite( pinDirF,LOW );
 analogWrite( pinPwmF,0 );

}



void loop() 
{
out:
instantreading = analogRead( pinMusSen );
if ( instantreading > contractionlimitvalue)
{
         savedreading = instantreading ;    //save savedreading different from zero
        maxcontraction = instantreading ;     //save maxcontraction different from zero
         mincontraction= instantreading ;         //save mincontraction different from zero
delay(25);
  for (int i=0; i <= 20; i++)   //   1/2 second to run the command
{
instantreading = analogRead( pinMusSen );
    if (instantreading > savedreading  &&  instantreading > maxcontraction )
  {
  maxcontraction = instantreading ;
  }
    if (instantreading < savedreading  &&  instantreading < mincontraction)
  {
  mincontraction= instantreading ;
  }
savedreading = instantreading;
Serial.print  ("Instant reading : ");
Serial.println( instantreading );
delay(25);
}
deltavalue = analogRead( pinMusSen );
maxmindifference = maxcontraction - mincontraction;
minmaxdifferenceset = maxcontractionset - mincontractionset;



if ( deltavalue < (contractionlimitvalue* 0.9) &&  mincontraction< (contractionlimitvalue* 0.8)  )
{
  contractiontype = 1 ;  //Contraction Pulse
  }
if ( deltavalue > (contractionlimitvalue* 0.9) &&  mincontraction> (contractionlimitvalue* 0.8)  )
{
  contractiontype = 2 ;  //Contraction Durable
  }
if ( deltavalue > (contractionlimitvalue* 0.9) &&  mincontraction< (contractionlimitvalue* 0.8)  )
{
  contractiontype = 3 ;
  }





if ( contractiontype == 2 && position == 1 ) 
  {
//Run to fist
fist:
digitalWrite( pinDirD,HIGH );
analogWrite( pinPwmD,255 );
digitalWrite( pinDirC,HIGH );
analogWrite( pinPwmC,255 );
digitalWrite( pinDirB,HIGH );
analogWrite( pinPwmB,255 );
digitalWrite( pinDirA,HIGH );
analogWrite( pinPwmA,255 );
digitalWrite( pinDirE,HIGH );
analogWrite( pinPwmE,200 );

delay(100);

instantreading = analogRead( pinMusSen );
if ( instantreading > contractionlimitvalue)
{
//than continue to Run to fist
goto fist ;
}

delay(100);

instantreading = analogRead( pinMusSen );
if ( instantreading > contractionlimitvalue)
{
//than continue to Run to fist
goto fist ;
}

delay(100);

instantreading = analogRead( pinMusSen );
if ( instantreading > contractionlimitvalue)
{
//than continue to Run to fist
goto fist ;
}

//otherwise stop the motors
digitalWrite( pinDirD,HIGH );
analogWrite( pinPwmD,0 );
digitalWrite( pinDirC,HIGH );
analogWrite( pinPwmC,0 );
digitalWrite( pinDirB,HIGH );
analogWrite( pinPwmB,0 );
digitalWrite( pinDirA,HIGH );
analogWrite( pinPwmA,0 );
digitalWrite( pinDirE,HIGH );
analogWrite( pinPwmE,0 );

delay(150);

Serial.print  ("Contraction type : ");
Serial.println( contractiontype );

Serial.println  ("Close Hand ");

position = 2 ;
contractiontype = 0;
goto out ;

}

if ( contractiontype == 2 && position == 2 ) 
  {
//Run to fist
fist2:
digitalWrite( pinDirD,HIGH );
analogWrite( pinPwmD,255 );
digitalWrite( pinDirC,HIGH );
analogWrite( pinPwmC,255 );
digitalWrite( pinDirB,HIGH );
analogWrite( pinPwmB,255 );
digitalWrite( pinDirA,HIGH );
analogWrite( pinPwmA,255 );
digitalWrite( pinDirE,HIGH );
analogWrite( pinPwmE,200 );

delay(100);

instantreading = analogRead( pinMusSen );
if ( instantreading > contractionlimitvalue)
{
//than continue to Run to fist
goto fist2 ;
}

delay(100);

instantreading = analogRead( pinMusSen );
if ( instantreading > contractionlimitvalue)
{
//than continue to Run to fist
goto fist2 ;
}

delay(100);

instantreading = analogRead( pinMusSen );
if ( instantreading > contractionlimitvalue)
{
//than continue to Run to fist
goto fist2 ;
}

//otherwise stop the motors
digitalWrite( pinDirD,HIGH );
analogWrite( pinPwmD,0 );
digitalWrite( pinDirC,HIGH );
analogWrite( pinPwmC,0 );
digitalWrite( pinDirB,HIGH );
analogWrite( pinPwmB,0 );
digitalWrite( pinDirA,HIGH );
analogWrite( pinPwmA,0 );
digitalWrite( pinDirE,HIGH );
analogWrite( pinPwmE,0 );

delay(150);

Serial.print  ("Contraction type : ");
Serial.println( contractiontype );

Serial.println  ("Close Hand ");

position = 2 ;
contractiontype = 0;
goto out ;

}

if ( contractiontype == 1 && position == 2 )
  {
// Open the Hand
 digitalWrite( pinDirE,LOW );
 analogWrite( pinPwmE,255 );
 delay(200);
 digitalWrite( pinDirA,LOW );
 analogWrite( pinPwmA,255 );
 digitalWrite( pinDirB,LOW );
 analogWrite( pinPwmB,255 );
 digitalWrite( pinDirC,LOW );
 analogWrite( pinPwmC,255 );
 digitalWrite( pinDirD,LOW );
 analogWrite( pinPwmD,255 );
 digitalWrite( pinDirF,LOW );
 analogWrite( pinPwmF,255 );

Serial.print  ("Contraction type : ");
Serial.println( contractiontype );

Serial.println  ("Open Hand ");


delay(1200);

position = 1 ;
contractiontype = 0;
goto out ;


}

if ( contractiontype == 1 && position == 1 )
  {
// get the 3 Fingers position (Position 3)
digitalWrite( pinDirB,HIGH );
analogWrite( pinPwmB,0 );
digitalWrite( pinDirA,HIGH );
analogWrite( pinPwmA,0 );
digitalWrite( pinDirE,HIGH );
analogWrite( pinPwmE,0 );
digitalWrite( pinDirF,HIGH );
analogWrite( pinPwmF,0 );

digitalWrite( pinDirD,HIGH );
analogWrite( pinPwmD,255 );
digitalWrite( pinDirC,HIGH );
analogWrite( pinPwmC,255 );

position = 3 ;
contractiontype = 0;
goto out ;

}

if ( contractiontype == 2 && position == 3 ) 
  {
//Run to 3 Fingers closed
TFC:  // 3 Fingers Closed

digitalWrite( pinDirB,HIGH );
analogWrite( pinPwmB,255 );
digitalWrite( pinDirA,HIGH );
analogWrite( pinPwmA,255 );
digitalWrite( pinDirE,HIGH );
analogWrite( pinPwmE,255 );

delay(100);

instantreading = analogRead( pinMusSen );
if ( instantreading > contractionlimitvalue)
{
//than continue to 3 Fingers closed
goto TFC ;
}

delay(100);

instantreading = analogRead( pinMusSen );
if ( instantreading > contractionlimitvalue)
{
//than continue to 3 Fingers closed
goto TFC ;
}

delay(100);

instantreading = analogRead( pinMusSen );
if ( instantreading > contractionlimitvalue)
{
//than continue to 3 Fingers closed
goto TFC ;
}

//otherwise stop the motors
digitalWrite( pinDirD,HIGH );
analogWrite( pinPwmD,0 );
digitalWrite( pinDirC,HIGH );
analogWrite( pinPwmC,0 );
digitalWrite( pinDirB,HIGH );
analogWrite( pinPwmB,0 );
digitalWrite( pinDirA,HIGH );
analogWrite( pinPwmA,0 );
digitalWrite( pinDirE,HIGH );
analogWrite( pinPwmE,0 );

delay(150);

position = 4 ;
contractiontype = 0;
goto out ;

}

if ( contractiontype == 2 && position == 4 ) 
  {
//Run to 3 Fingers closed
TFCC:  // 3 Fingers Closed

digitalWrite( pinDirB,HIGH );
analogWrite( pinPwmB,255 );
digitalWrite( pinDirA,HIGH );
analogWrite( pinPwmA,255 );
digitalWrite( pinDirE,HIGH );
analogWrite( pinPwmE,235 );

delay(100);

instantreading = analogRead( pinMusSen );
if ( instantreading > contractionlimitvalue)
{
//than continue to 3 Fingers closed
goto TFCC ;
}

delay(100);

instantreading = analogRead( pinMusSen );
if ( instantreading > contractionlimitvalue)
{
//than continue to 3 Fingers closed
goto TFCC ;
}

delay(100);

instantreading = analogRead( pinMusSen );
if ( instantreading > contractionlimitvalue)
{
//than continue to 3 Fingers closed
goto TFCC ;
}

//otherwise stop the motors
digitalWrite( pinDirD,HIGH );
analogWrite( pinPwmD,0 );
digitalWrite( pinDirC,HIGH );
analogWrite( pinPwmC,0 );
digitalWrite( pinDirB,HIGH );
analogWrite( pinPwmB,0 );
digitalWrite( pinDirA,HIGH );
analogWrite( pinPwmA,0 );
digitalWrite( pinDirE,HIGH );
analogWrite( pinPwmE,0 );

delay(150);

position = 4 ;
contractiontype = 0;
goto out ;

}

if ( contractiontype == 1 && position == 4 )
  {
// Open the Hand
 digitalWrite( pinDirE,LOW );
 analogWrite( pinPwmE,255 );
 delay(200);
 digitalWrite( pinDirA,LOW );
 analogWrite( pinPwmA,255 );
 digitalWrite( pinDirB,LOW );
 analogWrite( pinPwmB,255 );
 digitalWrite( pinDirC,LOW );
 analogWrite( pinPwmC,255 );
 digitalWrite( pinDirD,LOW );
 analogWrite( pinPwmD,255 );
 digitalWrite( pinDirF,LOW );
 analogWrite( pinPwmF,255 );

Serial.print  ("Contraction type : ");
Serial.println( contractiontype );

Serial.println  ("Open Hand ");


delay(1200);

position = 1 ;
contractiontype = 0;
goto out ;


}

if ( contractiontype == 1 && position == 3 )
  {
// get the 1 Fingers position (Position 5)

digitalWrite( pinDirA,HIGH );
analogWrite( pinPwmA,0 );
digitalWrite( pinDirE,HIGH );
analogWrite( pinPwmE,0 );
digitalWrite( pinDirF,HIGH );
analogWrite( pinPwmF,0 );
digitalWrite( pinDirD,HIGH );
analogWrite( pinPwmD,0 );
digitalWrite( pinDirC,HIGH );
analogWrite( pinPwmC,0 );

digitalWrite( pinDirB,HIGH );
analogWrite( pinPwmB,255 );

position = 5 ;
contractiontype = 0;
goto out ;

}

if ( contractiontype == 2 && position == 5 ) 
  {
//Run to 1 Finger closed
OFC:  // One Fingers Closed

digitalWrite( pinDirA,HIGH );
analogWrite( pinPwmA,255 );
digitalWrite( pinDirE,HIGH );
analogWrite( pinPwmE,235 );

delay(100);

instantreading = analogRead( pinMusSen );
if ( instantreading > contractionlimitvalue)
{
//than continue to 1 Finger closed
goto OFC ;
}

delay(100);

instantreading = analogRead( pinMusSen );
if ( instantreading > contractionlimitvalue)
{
//than continue to 1 Finger closed
goto OFC ;
}

delay(100);

instantreading = analogRead( pinMusSen );
if ( instantreading > contractionlimitvalue)
{
//than continue to 1 Finger closed
goto OFC ;
}

//otherwise stop the motors
digitalWrite( pinDirD,HIGH );
analogWrite( pinPwmD,0 );
digitalWrite( pinDirC,HIGH );
analogWrite( pinPwmC,0 );
digitalWrite( pinDirB,HIGH );
analogWrite( pinPwmB,0 );
digitalWrite( pinDirA,HIGH );
analogWrite( pinPwmA,0 );
digitalWrite( pinDirE,HIGH );
analogWrite( pinPwmE,0 );

delay(150);

position = 6 ;
contractiontype = 0;
goto out ;

}

if ( contractiontype == 2 && position == 6 ) 
  {
//Run to 1 Finger closed
OFCC:  // One Fingers Closed

digitalWrite( pinDirA,HIGH );
analogWrite( pinPwmA,255 );
digitalWrite( pinDirE,HIGH );
analogWrite( pinPwmE,235 );

delay(100);

instantreading = analogRead( pinMusSen );
if ( instantreading > contractionlimitvalue)
{
//than continue to 1 Finger closed
goto OFCC ;
}

delay(100);

instantreading = analogRead( pinMusSen );
if ( instantreading > contractionlimitvalue)
{
//than continue to 1 Finger closed
goto OFCC ;
}

delay(100);

instantreading = analogRead( pinMusSen );
if ( instantreading > contractionlimitvalue)
{
//than continue to 1 Finger closed
goto OFCC ;
}

//otherwise stop the motors
digitalWrite( pinDirD,HIGH );
analogWrite( pinPwmD,0 );
digitalWrite( pinDirC,HIGH );
analogWrite( pinPwmC,0 );
digitalWrite( pinDirB,HIGH );
analogWrite( pinPwmB,0 );
digitalWrite( pinDirA,HIGH );
analogWrite( pinPwmA,0 );
digitalWrite( pinDirE,HIGH );
analogWrite( pinPwmE,0 );

delay(150);

position = 6 ;
contractiontype = 0;
goto out ;

}

if ( contractiontype == 1 && position == 6 )
  {
// Open the Hand
 digitalWrite( pinDirE,LOW );
 analogWrite( pinPwmE,255 );
 delay(200);
 digitalWrite( pinDirA,LOW );
 analogWrite( pinPwmA,255 );
 digitalWrite( pinDirB,LOW );
 analogWrite( pinPwmB,255 );
 digitalWrite( pinDirC,LOW );
 analogWrite( pinPwmC,255 );
 digitalWrite( pinDirD,LOW );
 analogWrite( pinPwmD,255 );
 digitalWrite( pinDirF,LOW );
 analogWrite( pinPwmF,255 );

Serial.print  ("Contraction type : ");
Serial.println( contractiontype );

Serial.println  ("Open Hand ");


delay(1200);

position = 1 ;
contractiontype = 0;
goto out ;


}

if ( contractiontype == 1 && position == 5 )
  {
// Open the Hand
 digitalWrite( pinDirE,LOW );
 analogWrite( pinPwmE,255 );
 delay(200);
 digitalWrite( pinDirA,LOW );
 analogWrite( pinPwmA,255 );
 digitalWrite( pinDirB,LOW );
 analogWrite( pinPwmB,255 );
 digitalWrite( pinDirC,LOW );
 analogWrite( pinPwmC,255 );
 digitalWrite( pinDirD,LOW );
 analogWrite( pinPwmD,255 );
 digitalWrite( pinDirF,LOW );
 analogWrite( pinPwmF,255 );

Serial.print  ("Contraction type : ");
Serial.println( contractiontype );

Serial.println  ("Open Hand ");


delay(1200);

position = 1 ;
contractiontype = 0;
goto out ;


}

}

}

