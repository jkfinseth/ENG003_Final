/* Code to turn on a light if it is night and motion is detected, and turn off the light if atleast one of the desire atributes is not detected*/
/* Definitions for main pins*/
#define echoPin 9
#define trigPin 10
#define LDR A0
#define LIGHT 8

/* global variable to contain measurements*/
long duration;
long distance;
float R0;
float RLDR;
float num0;
float V0;
float DV0;
long distComp;

void setup() {
  // put your setup code here, to run once:
/* Set up the serial monitor */
  Serial.begin(9600);
  /*Set up the motion detector*/
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  /*Set up the light control*/
  pinMode(LIGHT, OUTPUT);
  /* Set up the distance difference*/
  distComp = 0.00;
}

void loop() {
  /* Check reading from LDR pin*/
  R0 = analogRead (LDR);
  /* Change value into a voltage*/
  V0 = R0 * (5.0/1023.0);
  /* Find the drop across the LDR*/
  DV0 = 5 - V0;
  /* Determine the resistance of the LDR*/
  RLDR = (DV0*10000)/V0;
  /* Determine if it is dark outside*/
  if (RLDR>7000)
  {
    /* Reset the motion detector*/
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    /* Send out a ping*/
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite (trigPin, LOW);
    /* Store the duration it took to return*/
    duration = pulseIn(echoPin, HIGH);
    /* Calculate a distance in CM*/
    distance = duration/58.2;
    /* Check to see if this is first iteration*/
    Serial.println("Distance:");
    Serial.println(distance);
    Serial.println("Comparison:");
    Serial.println(distComp);
    if (distComp == 0.00)
    {
      /* Set up dist2*/
      distComp = distance;
    }
    /* Check for a change in distance*/
    else if (distComp+1 >= distance&&distComp-1 <=distance)
    {
      /*Turn light off*/
      digitalWrite(LIGHT, LOW);
    }
    else
    {
      /* Turn light on and wait for 30 sec*/
      digitalWrite(LIGHT, HIGH);
      distComp = distance;
      delay (500);
    }
  }
  else
  {
    /* turn the light off*/
    digitalWrite(LIGHT, LOW);
  }
}
