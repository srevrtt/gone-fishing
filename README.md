# Gone Fishing

## **About**

Gone Fishing is a simple fishing game made for my dad's birthday. It is also open source for anyone to play. It is written in C++ and SDL2.

## **Running**

### **Windows**

Download the latest stable release (if there is one) from the [releases](https://github.com/srevrtt/gone-fishing/releases/) page. Extract the .zip file and run the exe inside the newly extracted folder. Make sure to keep the .dll files and the res folder inside the same folder the executable is in.

### **MacOS**

Not there yet. (maybe in 1.0.0 stable)

### **Linux**

Not there yet. (maybe in 1.0.0 stable)

## **Building From Source**

Again with running, Windows is only supported right now, but in 1.0.0 stable, you can build on MacOS and Linux.

### **Windows**

You will need [Mingw](https://www.mingw-w64.org/downloads/) installed. Then, navigate to a directory where you want the game to go. After that, type in the following commands:

- `git clone https://github.com/srevrtt/gone-fishing.git`
- `cd gone-fishing`
- `make`

Inside the `bin` directory, you should see `gone_fishing.exe` file inside.

## **How to Play**

Once you enter the game, press the "Play" button. The objective is simple: _catch all of the fish before they respawn_. Once you catch all of the fish, the timer stops and you can play again or quit the game.

To catch a fish, move your mouse over to the fish and click it. Then, drag your mouse above the water and click. Now the fish is caught.

## **Version History**

### **v1.0.0-rc.1**

- The first version of Gone Fishing.

### **v1.0.0-rc.2**

- Added an auto updater.

## **Attribution**

The original game idea was based off of PolyMars's TeamSeas game.
SDL2, SDL2_image, and SDL2_ttf were used in this game.

## **License**

This repository is licensed under the MIT License. See `LICENSE` for more details.
