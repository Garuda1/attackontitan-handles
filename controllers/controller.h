#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>

/* Those bytes describe what action has been performed by the controller.
 * They are sent through a serial port and decoded by the computer. */
#define CTRL_NOTHING          0x00 //Do nothing
#define CTRL_XAXIS_PRESSED_L  0x01 //Aim left with the left hook
#define CTRL_ZAXIS_PRESSED_L  0x02 //Aim up with the left hook
#define CTRL_FHOOK_PRESSED_L  0x03 //Fire the left hook
#define CTRL_CHOOK_PRESSED_L  0x04 //Start coiling up the left hook
#define CTRL_BLADE_PRESSED_L  0x05 //Reload the left blade (DO NOT USE. This action should only be performed with CTRL_BLADE_RELEASED_L)
#define CTRL_XAXIS_PRESSED_R  0x06 //Aim right with the right hook
#define CTRL_ZAXIS_PRESSED_R  0x07 //Aim up with the right hook
#define CTRL_FHOOK_PRESSED_R  0x08 //Fire the right hook
#define CTRL_CHOOK_PRESSED_R  0x09 //Start coiling up the right hook
#define CTRL_BLADE_PRESSED_R  0x0A //Reload the right blade (DO NOT USE. This action should only be performed with CTRL_BLADE_RELEASED_R)
#define CTRL_XAXIS_RELEASED_L 0x0B //Stop aiming left with the left hook
#define CTRL_ZAXIS_RELEASED_L 0x0C //Stop aiming up with the left hook
#define CTRL_FHOOK_RELEASED_L 0x0D //Stop firing the left hook (Does nothing, we can't stop a projectile in midair)
#define CTRL_CHOOK_RELEASED_L 0x0E //Stop coiling up the left hook
#define CTRL_BLADE_RELEASED_L 0x0F //Reload the left blade
#define CTRL_XAXIS_RELEASED_R 0x10 //Stop aiming right with the right hook
#define CTRL_ZAXIS_RELEASED_R 0x11 //Stop aiming up with the right hook
#define CTRL_FHOOK_RELEASED_R 0x12 //Stop firing the right hook (Does nothing, we can't stop a projectile in midair)
#define CTRL_CHOOK_RELEASED_R 0x13 //Stop coiling up the right hook
#define CTRL_BLADE_RELEASED_R 0x14 //Reload the right blade

#define HOOKMODE_FIRE 0x01 //Next time the lever is pulled, fire the hook
#define HOOKMODE_COIL 0x02 //Next time the lever is puller, coil up the wire

typedef struct s_controller t_controller;
struct s_controller
{
  uint8_t xaxis_pin;
  uint8_t zaxis_pin;
  uint8_t fhook_pin;
  uint8_t blade_pin;
  
  //Signal states (high or low) during the last loop
  uint8_t xaxis_state;
  uint8_t zaxis_state;
  uint8_t fhook_state;
  uint8_t blade_state;

  uint8_t hook_mode; //Will pulling the lever retract or fire the hook?
};

void init_controller(t_controller *controller, const uint8_t upper_trigger, const uint8_t lower_trigger, const uint8_t lever, const uint8_t blade_button);

#endif
