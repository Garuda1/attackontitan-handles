#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <windows.h>

#include "rs232.h"

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

#define MSG_SYNTAX "Syntax: snkapp [port] [baudrate] [mode]\nExample:\n  snkapp COM5 9600 8N1\n"
#define MSG_CONNECTIONSUCCESS "Successfully connected to %s (%s bauds, %s)\n"
#define MSG_CONNECTIONFAILURE "Failed to connect to %s (%s bauds, %s)\n"

/* Keys used in Guedin's Attack on Titan Fan Game */
#define KEY_FIRELEFTHOOK  'L'
#define KEY_FIRERIGHTHOOK 'R'
#define KEY_REELHOOKS     VK_SPACE
#define KEY_DODGE         VK_LSHIFT
#define KEY_ATTACK        'F'
#define KEY_SPECIALATTACK 'E'

//keybd_event(VkKeyScan(‘A’),0x9e,0 , 0); // ‘A’ Press
//keybd_event(VkKeyScan(‘A’),0x9e, KEYEVENTF_KEYUP,0); // ‘A’ Release

void press_key(const uint8_t key)
{
  //Keycodes can be found here: https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
  keybd_event(key, 0x9e, 0, 0);
}

void release_key(const uint8_t key)
{
  //Keycodes can be found here: https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
  keybd_event(key, 0x9e, KEYEVENTF_KEYUP, 0);
}

int main(int argc, char **argv)
{
  uint8_t port;
  uint8_t data; //Data recovered from the device

  if (argc != 4)
  {
    fprintf(stderr, MSG_SYNTAX);
    return (EXIT_FAILURE);
  }

  port = RS232_GetPortnr(argv[1]);
  if (RS232_OpenComport(port, atoi(argv[2]), argv[3]) == 1)
    printf(MSG_CONNECTIONSUCCESS, argv[1], argv[2], argv[3]);
  else
    fprintf(stderr, MSG_CONNECTIONFAILURE, argv[1], argv[2], argv[3]);

  for (;;)
  {
    while (!RS232_PollComport(port, &data, sizeof(data)));

    switch (data)
    {
      case CTRL_XAXIS_PRESSED_L:
        printf("[%s] Left handle: upper trigger pressed\n", argv[1]);
        break;
      case CTRL_ZAXIS_PRESSED_L:
        printf("[%s] Left handle: lower trigger pressed\n", argv[1]);
        break;
      case CTRL_FHOOK_PRESSED_L:
        printf("[%s] Left handle: lever pulled (hook fired)\n", argv[1]);
        press_key(VkKeyScanA(KEY_FIRELEFTHOOK));
        break;
      case CTRL_CHOOK_PRESSED_L:
        printf("[%s] Left handle: lever pulled (coiling up the wires)\n", argv[1]);
        press_key(VK_SPACE);
        break;
      case CTRL_BLADE_PRESSED_L:
        printf("[%s] Left handle: blade button pressed\n", argv[1]);
        break;
      case CTRL_XAXIS_PRESSED_R:
        printf("[%s] Right handle: upper trigger pressed\n", argv[1]);
        break;
      case CTRL_ZAXIS_PRESSED_R:
        printf("[%s] Right handle: lower trigger pressed\n", argv[1]);
        break;
      case CTRL_FHOOK_PRESSED_R:
        printf("[%s] Right handle: lever pulled (hook fired)\n", argv[1]);
        press_key(VkKeyScan(KEY_FIRERIGHTHOOK));
        break;
      case CTRL_CHOOK_PRESSED_R:
        printf("[%s] Right handle: lever pulled (coiling up the wires)\n", argv[1]);
        press_key(VK_SPACE);
        break;
      case CTRL_BLADE_PRESSED_R:
        printf("[%s] Right handle: blade button pressed\n", argv[1]);
        break;
      case CTRL_XAXIS_RELEASED_L:
        printf("[%s] Left handle: upper trigger released\n", argv[1]);
        break;
      case CTRL_ZAXIS_RELEASED_L:
        printf("[%s] Left handle: lower trigger released\n", argv[1]);
        break;
      case CTRL_FHOOK_RELEASED_L:
        printf("[%s] Left handle: lever released\n", argv[1]);
        //Do not use, you can't stop a projectile in midair
        break;
      case CTRL_CHOOK_RELEASED_L:
        printf("[%s] Left handle: lever released (detaching anchors)\n", argv[1]);
        release_key(VkKeyScanA(KEY_FIRELEFTHOOK));
        release_key(VK_SPACE);
        break;
      case CTRL_BLADE_RELEASED_L:
        printf("[%s] Left handle: blade button released\n", argv[1]);
        break;
      case CTRL_XAXIS_RELEASED_R:
        printf("[%s] Right handle: upper trigger released\n", argv[1]);
        break;
      case CTRL_ZAXIS_RELEASED_R:
        printf("[%s] Right handle: lower trigger released\n", argv[1]);
        break;
      case CTRL_FHOOK_RELEASED_R:
        printf("[%s] Right handle: lever released\n", argv[1]);
        //Do not use, you can't stop a projectile in midair
        break;
      case CTRL_CHOOK_RELEASED_R:
        printf("[%s] Right handle: lever released (detaching anchors)\n", argv[1]);
        release_key(VkKeyScanA(KEY_FIRERIGHTHOOK));
        release_key(VK_SPACE);
        break;
      case CTRL_BLADE_RELEASED_R:
        printf("[%s] Right handle: blade button released\n", argv[1]);
        break;
      default:
        break;
    }
    /* sleep for 20ms */
    Sleep(20);
  }

  return (EXIT_SUCCESS);
}
