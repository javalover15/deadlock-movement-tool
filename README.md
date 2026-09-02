# deadlock-movement-tool
A simple tool I made to practice C++ and help me learn Deadlock movement and routes.

The tool allows you to save and teleport to positions in-game. You can also create and save lists of positions to load and use later with the built-in position loader and saver.

## Installation
1. Add `-condebug` to your Deadlock launch options.
2. Copy the `autoexec.cfg` file into `../Deadlock/game/citadel/cfg/`
3. Launch the `.exe`.
4. When prompted paste your Deadlock game path: `../Deadlock/`

## Menu
- Press `INSERT` on your keyboard to show/hide the menu.
- You won't be able to interact with the desktop/background while the menu is open.
- The menu can be opened while in-game even if its in fullscreen

## Binds
- Press `J` to save your current position.
- Press `K` to teleport to your last saved position.

## Positions
1. Open the menu and enter a name for the position you want to save.
2. Click the **add new position** button to save your current position to the list.
3. To teleport to a specific position in your saved list, select the position and click the **set current position** button.
