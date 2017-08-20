#include "controller.h"

/* Pins used by the controllers */
#define XAXIS_L 30 //Upper trigger (sets the vertical inclination) (left controller)
#define ZAXIS_L 31 //Lower trigger (sets the horizontal inclination (left controller)
#define FHOOK_L 32 //Hook action (fire or retract the hook) (left controller)
#define BLADE_L 33 //Blade action (reloads the blades) (left controller)
#define XAXIS_R 40 //Upper trigger (sets the vertical inclination) (right controller)
#define ZAXIS_R 41 //Lower trigger (sets the horizontal inclination (right controller)
#define FHOOK_R 42 //Hook action (fire or retract the hook) (right controller)
#define BLADE_R 43 //Blade action (reloads the blades) (right controller)

#define SERIAL_BITRATE 115200 //The serial baudrate used. Must match that of the computer's program.

#define MSG_BOOTING "Device booting...\n"
#define MSG_LCTINIT "Initializing the left controller...\n"
#define MSG_RCTINIT "Initializing the right controller...\n"
#define MSG_DONE    "Done.\n"

/* The controller structures */
static t_controller l_controller;
static t_controller r_controller;

static void toggle_state(uint8_t *control)
{
  if (*control == LOW)
    *control = HIGH;
  else
    *control = LOW;
}

void setup(void)
{
  Serial.begin(SERIAL_BITRATE);
  Serial.print(MSG_BOOTING MSG_LCTINIT);
  init_controller(&l_controller, XAXIS_L, ZAXIS_L, FHOOK_L, BLADE_L);
  Serial.print(MSG_DONE MSG_RCTINIT);
  init_controller(&r_controller, XAXIS_R, ZAXIS_R, FHOOK_R, BLADE_R);
  Serial.print(MSG_DONE);
}

void loop(void)
{
  static uint32_t start_time;

  start_time = millis();
  
  //Left controller, upper trigger
  if (l_controller.xaxis_state != digitalRead(l_controller.xaxis_pin))
  {
    if (l_controller.xaxis_state == LOW) //If we pressed the button
      Serial.write(CTRL_XAXIS_PRESSED_L);
    else
      Serial.write(CTRL_XAXIS_RELEASED_L);
    toggle_state(&(l_controller.xaxis_state));
  }

  //Left controller, lower trigger
  if (l_controller.zaxis_state != digitalRead(l_controller.zaxis_pin))
  {
    if (l_controller.zaxis_state == LOW) //If we pressed the button
      Serial.write(CTRL_ZAXIS_PRESSED_L);
    else
      Serial.write(CTRL_ZAXIS_RELEASED_L);
    toggle_state(&(l_controller.zaxis_state));
  }

  //Left controller, blade button
  if (l_controller.blade_state != digitalRead(l_controller.blade_pin))
  {
    if (l_controller.blade_state == LOW) //If we pressed the button
      Serial.write(CTRL_BLADE_PRESSED_L);
    else
      Serial.write(CTRL_BLADE_RELEASED_L);
    toggle_state(&(l_controller.blade_state));
  }

  //Left controller, lever
  if (l_controller.fhook_state != digitalRead(l_controller.fhook_pin))
  {
    if (l_controller.fhook_state == LOW) //If we pressed the button
    {
      if (l_controller.hook_mode == HOOKMODE_FIRE)
        Serial.write(CTRL_FHOOK_PRESSED_L);
      else
        Serial.write(CTRL_CHOOK_PRESSED_L);
    }
    else
    {
      if (l_controller.hook_mode == HOOKMODE_FIRE)
      {
        Serial.write(CTRL_FHOOK_RELEASED_L);
        l_controller.hook_mode = HOOKMODE_COIL;
      }
      else
      {
        Serial.write(CTRL_CHOOK_RELEASED_L);
        l_controller.hook_mode = HOOKMODE_FIRE;
      }
    }
    toggle_state(&(l_controller.fhook_state));
  }

  //Right controller, upper trigger
  if (r_controller.xaxis_state != digitalRead(r_controller.xaxis_pin))
  {
    if (r_controller.xaxis_state == LOW) //If we pressed the button
      Serial.write(CTRL_XAXIS_PRESSED_R);
    else
      Serial.write(CTRL_XAXIS_RELEASED_R);
    toggle_state(&(r_controller.xaxis_state));
  }

  //Right controller, lower trigger
  if (r_controller.zaxis_state != digitalRead(r_controller.zaxis_pin))
  {
    if (r_controller.zaxis_state == LOW) //If we pressed the button
      Serial.write(CTRL_ZAXIS_PRESSED_R);
    else
      Serial.write(CTRL_ZAXIS_RELEASED_R);
    toggle_state(&(r_controller.zaxis_state));
  }

  //Left controller, blade button
  if (r_controller.blade_state != digitalRead(r_controller.blade_pin))
  {
    if (r_controller.blade_state == LOW) //If we pressed the button
      Serial.write(CTRL_BLADE_PRESSED_R);
    else
      Serial.write(CTRL_BLADE_RELEASED_R);
    toggle_state(&(r_controller.blade_state));
  }

  //Right controller, lever
  if (r_controller.fhook_state != digitalRead(r_controller.fhook_pin))
  {
    if (r_controller.fhook_state == LOW) //If we pressed the button
    {
      if (r_controller.hook_mode == HOOKMODE_FIRE)
        Serial.write(CTRL_FHOOK_PRESSED_R);
      else
        Serial.write(CTRL_CHOOK_PRESSED_R);
    }
    else
    {
      if (l_controller.hook_mode == HOOKMODE_FIRE)
      {
        Serial.write(CTRL_FHOOK_RELEASED_R);
        r_controller.hook_mode = HOOKMODE_COIL;
      }
      else
      {
        Serial.write(CTRL_CHOOK_RELEASED_R);
        r_controller.hook_mode = HOOKMODE_FIRE;
      }
    }
    toggle_state(&(r_controller.fhook_state));
  }
  /*
  Serial.print("Loop time: ");
  Serial.print(millis()-start_time);
  Serial.print("ms\n");
  */
}

