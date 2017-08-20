#include <Arduino.h>
#include "controller.h"

void init_controller(t_controller *controller, const uint8_t upper_trigger, const uint8_t lower_trigger, const uint8_t lever, const uint8_t blade_button)
{
  pinMode(upper_trigger, INPUT);
  pinMode(lower_trigger, INPUT);
  pinMode(lever, INPUT);
  pinMode(blade_button, INPUT);

  controller->xaxis_pin = upper_trigger;
  controller->zaxis_pin = lower_trigger;
  controller->fhook_pin = lever;
  controller->blade_pin = blade_button;

  controller->xaxis_state = LOW;
  controller->zaxis_state = LOW;
  controller->fhook_state = LOW;
  controller->blade_state = LOW;

  controller->hook_mode = HOOKMODE_FIRE;
}
