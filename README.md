# Computer Graphics 3D Game
---
![alt text](https://github.com/marprok/computer_graphics_project/blob/master/Assets/MarkdownImages/1.png)

## Introduction
The goal of the project is to create a tower defence game using OpenGL. The objective of the game is to prevent enemies from stealing the treasure by placing defence towers along the path that leads to the treasure chests. 

![alt text](https://github.com/marprok/computer_graphics_project/blob/master/Assets/MarkdownImages/2.png)

![alt text](https://github.com/marprok/computer_graphics_project/blob/master/Assets/MarkdownImages/3.png)

## Gameplay
The goal is to prevent the enemies (Pirates) from reaching the treasure chests by placing defence towers along the path that leads to the treasure. Upon reaching the treasure chests, pirates will steal coins from them and in order for the player to win, the player should prevent the enemies from stealing all the coins. If all the coins are gone before the completion of the level, then the player loses. New waves of enemies are be more resilient to your salvo.
Pirates will spawn in waves from the start of the path. They will follow the designated route and upon reaching the treasure, will remove 10 coins from the chest. The chest is placed at the end of the path and will hold 100 coins. After reaching level 10 the map changes and the player received an addittional of 100 coins as a reward. When the chest becomes empty, it is removed from the map and the the player is defeated. The seconds until the player's defeat is the highscore which is displayed in the console.
         
To defend the chests, the player can place defence towers along the path, that will shoot and eliminate pirates. There are two types of towers. The 'blue' type offers faster shooting but can also miss the target. It also causes less damage than the 'red' tower. The red tower launches rockets that follow pirates without missing. They also cause much more damage. However their shooting frequensy is lower. A new 'blue' tower can be placed every 30 seconds. A new 'red' tower can be placed every 60 seconds. Defence towers can also be rearranged. By removing 3 towers, the player can place a tower of the same kind in any available position without the need to wait for the timer of 30 or 60 seconds as described above.

![alt text](https://github.com/marprok/computer_graphics_project/blob/master/Assets/MarkdownImages/4.png)

![alt text](https://github.com/marprok/computer_graphics_project/blob/master/Assets/MarkdownImages/5.png)


## Controls

| Key | Function |
| ------ | ----------- |
| w | Move camera forwards |
| s | Move camera backwards |
| a| Move camera to the left|
| d| Move camera to the right|
| t| Place a tower|
| y| Use the red tower mode|
| h| Use the blue tower mode|
| m| Try it out if you are a fan of Michael Jackson|
| z| pause|
| Esc| Exit the game|
