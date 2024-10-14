#include <radio.h>
#include "quad_remote.h"  // Header file with pin definitions and setup
#include <serLCD.h>
#include <EEPROM.h>
//serLCD lcd; //idk why but this doesn't compile. Maybe changing it to SerLCD fixes it? Removing it doesn't seem to cause any issue.

//copied from the knob example
void knobs_update();
void knob_pressed(bool);
void btn1_pressed(bool);
void btn2_pressed(bool);

void btn_up_pressed(bool down);
void btn_down_pressed(bool down);
void btn_left_pressed(bool down);
void btn_right_pressed(bool down);
void btn_center_pressed(bool down);

//data corresponding to max and min gimbal (top-bottom)
uint8_t gimbal_value_l = 0;
uint8_t gimbal_value_r = 0;
int16_t max_gimbal_l_vert = 1023;  //uint8_t only goes to 255 so I changed this data type. Also, we want a signed int - we get negative values sometimes
int16_t min_gimbal_l_vert = 0;


const int magicNumber = 57;
const int SERIAL_BAUD = 9600;
const int channel = 12;

const int BAT_SENSE_PIN = A7;

int leftupdown = 0;
int rightupdown = 0;
int leftsideways = 0;
int rightsideways = 0;
int armed=0;

//battery voltage seems to be capped at 57 using analogReference(INTERNAL);
void setup() {
  Serial.begin(SERIAL_BAUD);
  pinMode(BAT_SENSE_PIN, INPUT);
  analogReference(INTERNAL);

  quad_remote_setup();

  rfBegin(channel);  //radio stuff
  rfPrint("ATmega128RFA1 Dev Board Online!\r\n");
     

  //testing for gimbal calibration
  /* while (millis() < 1000) {
    gimbal_value_l = analogRead(A1);
    gimbal_value_r = analogRead(A3);

    if (gimbal_value_l > max_gimbal){
      int max_gimbal_l = gimbal_value_l; 
    }

    if (gimbal_value_r > max_gimbal){
      int max_gimbal_r = gimbal_value_r; 
    }
  }
*/
}

void loop() {
  // put your main code here, to run repeatedly:
  //This was very heavily inspired by the AnalogReadSerial Example
  //involves battery and gimbal control
  //int leftsideways = analogRead(A0);
  int leftupdown = analogRead(A1);
  //int rightsideways = analogRead(A2);
  //int rightupdown = analogRead(A3);
  //int BAT_SENSE_PIN = analogRead(A7);
  //part of calibration
  //btn1_pressed();

  //Serial.println(leftsideways);
  leftupdown = constrain(leftupdown, min_gimbal_l_vert, max_gimbal_l_vert);
  leftupdown = map(leftupdown, min_gimbal_l_vert, max_gimbal_l_vert, 0, 255);
  Serial.println(leftupdown);
  //Serial.println(rightsideways);
  //Serial.println(rightupdown);
  Serial.print("Battery Voltage:");
  Serial.println(BAT_SENSE_PIN);

  //float max_gimbal_l=855;
  //float min_gimbal_l=128;
  //int throttle=255*((leftupdown-min_gimbal_l)/(max_gimbal_l-min_gimbal_l));
  uint8_t a[4];
  a[0] = magicNumber;
  a[2] = leftupdown;
  //Serial.println(throttle);
  a[3] = 2;
  a[4] = 3;
  rfWrite(a, 5);
  //rfWrite('hi');
  delay(10);  // delay in between reads for stability
  update_display();
  lcd.print("Hi");

	if (is_pressed(BUTTON_UP_PIN)) {
		calibrate();
	}

  

}

void update_display() {
  lcd.clear();
  lcd.setCursor(0, 0);
}

void btn1_pressed(bool down) {
	if(down) {
		calibrate();
	}
}

void calibrate() {
  update_display();
  lcd.print("Beginning Calibration");
  delay(1000);
  update_display();
  lcd.print("Move right joystick low");
  delay(5000);
  min_gimbal_l_vert = analogRead(A1);
  update_display();
  lcd.print("Move right joystick high");
  delay(5000);
  max_gimbal_l_vert = analogRead(A1);




  /*
  leftsideways = constrain(leftsideways, min_gimbal_l,max_gimbal_l);
  leftsideways = map(leftsideways, min_gimbal_l, max_gimbal_l, 0, 255);
  pause(5000)
  leftupdown = constrain(leftupdown, min_gimbal_l, max_gimbal_l);
  leftupdown = map(leftupdown, min_gimbal_l, max_gimbal_l, 0, 255);

  rightsideways = constrain(rightsideways, min_gimbal_r,max_gimbal_r);
  rightsideways = map(rightsideways, min_gimbal_r, max_gimbal_r, 0, 255);

  rightupdown = constrain(rightupdown, min_gimbal_r, max_gimbal_r);
  rightupdown = map(rightupdown, min_gimbal_r, max_gimbal_r, 0, 255);
*/
}

