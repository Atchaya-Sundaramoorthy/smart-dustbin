#include<stdio.h>
Servo servo;
int trigpin=5;
int servopin=7;
int echopin=6;
int led=10;
long duration,dist,average;
long aver[3];
void setup(){
	Serial.begin(9600);
	servo.attach(servopin);
	pinMode(trigpin,OUTPUT);
	pinMode(echopin,INPUT);
	servo.write(0);
	delay(100);
	servo.detach();
}

void measure()
{
digitalWrite(10,HIGH);
digitalWrite(trigpin,LOW);
delayMicroSeconds(5);
digitalWrite(trigpin,HIGH);
delayMicroSeconds(15);
digitalWrite(trigpin,LOW);
pinMode(echopin,INPUT);
duration=pulseIn(echopin,HIGH);
dist=(duration/2)/29.1;
}

void loop()
{
	for(int i=0;i<=2;i++)
	{
		measure();
		aver[i]=dist;
		delay(10);
	}
	dist=aver[0]+aver[1]+aver[2];
	if(dist<50)
	{
		servo.attach(servopin);
		delay(1);
		servo.write(0);
		delay(3000);
		servo.write(150);
		delay(1000);
		servo.detach();
	}
	Serial.print(dist);
}