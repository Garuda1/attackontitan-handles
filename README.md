#Attack on Titan - Fan made sword handles

##What is this?

In [Attack on Titan](http://i.imgur.com/i5s0Rew.jpg), the army uses a special gear called the 3DMG. Some games provide the full 3DMG experience by letting the player fight titans as a soldier. Unfortunately, while the games really capture the universe's feelings, the 3DMG controls are extremely simplified to allow everyone to easily play. This software + hardware pack exists to fix this issue.

The "stack" is divided in three parts: the devices (sword handles), the firmware (what will be used to run the sword handles) and the driver software.

##Controls

The 3DMG controls are not consistent throughout the story. As such, I had to find a reference point and work out some magic to figure out the optimal controls. I based the controls on the **No regrets OVA, part 1 and 2**.

![Controls](http://i.imgur.com/vJhAxl4.jpg)

The safety switches are unused. Typically, they block the triggers and prevent the user from mistakenly activating them.

- **Upper trigger**: Pulling it will adjust the X axis (vertical) orientation of the corresponding hook launcher.

- **Lower trigger**: Pulling it will adjust the Z axis (horizontal) orientation of the corresponding hook launcher. Pressing it on the left handle will make the left side hook launcher point left.

- **Lever**: If the corresponding (left or right) hook hasn't been fired, then pulling the lever will fire the hook and leave it attached. If the hook has been fired and is attached, pulling the trigger will coil back the wires, reeling the user towards the corresponding hook. In this case, releasing the lever will detach the hook.

- **Blade button**: Triggers the blade locking mechanism. In game, it can be interpreted as reloading the blade.

#Limitations

Currently, the best fitting game to run the program on is [Guedin's AOT Fan Game](https://www.facebook.com/guedinaot/). However, it doesn't provide the following actions:

- Reeling hooks independently

- Reloading blades

##Building

You will need:

- Working handles (see below)

- 1x Arduino Mega 2560

- The Arduino IDE

- A Windows environment (currently, the only AoT games are Windows exclusives)

- mingw-w64 (The Microsoft compiler is an outdated piece of garbage that doesn't even support C99)

###Step 1: Making the sword handles

You can download the instructions and templates on [my website](https://garuda1.github.io/). I recommend 5mm (1/5in in retarded units) wood sheets.

You will need to install a button on each action (the lever, the triggers, and the blade button). Each button will trigger an individual signal (+5V) that will need to be read by the Arduino board. Connect as follows:

![Arduino pinout](http://i.imgur.com/qPAb0tx.jpg)

###Step 2: Connect the Arduino

You will need to connect the Arduino via a serial port (virtual or physical) to your computer. Then, go to the `controllers` folder, open the corresponding `.ino` file, and send it to your Arduino device. Then, close the Arduino IDE, reconnect the Arduino, and move on to step 3.

###Step 3: Building and configuring the driver software

open `software/main.c` and edit the lines 32 to 34 to match your settings. If you haven't modified the device software (what you sent to the Arduino) then you should only edit the 32nd line to match the serial port your Arduino is connected to.

Navigate to the `software` folder, and compile the different source files using `mingw-w64`. It is important not to use the Microsoft C compiler.

##Usage

Now that everything is compiled, you can connect your Arduino with the handles attached, run the software on your computer, and play your favourite Attack on Titan game!

##Licensing

This program is licensed under the GPL v3 license. The RS232 source code (`software/rs232.c` and `software/rs232.h`) was provided [here](http://www.teuniz.net/RS-232/)
