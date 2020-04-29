# System Design Document

## 1. Are your player, items and enemies the same class, different classes in the same family, or completely di↵erent classes?
The player, items, and enemies classes will derive from a base entity class and therefore be in the same family of classes.

## 2. What logic will you put into your Form class? What logic will you put into your Game Manager class?
We will not have a Form class.

## 3. What classes do you need to implement the dungeon? Brieﬂy explain the job of each class, list the data members it must hold, and the methods it must expose. How do the Dungeon and the TileMap communicate?


## 4. What data structure(s) do you need to hold collections of enemies and items?
Linked list and maybe std::vector

## 5. Does the dungeon need pointers to its sprites? Why or why not?
No. The TileMap will however need a pointer to it's sprites for drawing. 

## 6. Does the sprite class need a pointer to its dungeon? Why or why not?
Yes for collision detection.

## 7. What enumeration types (if any) do you need?
Entity Direction

## 8. Does the player sprite need access to the collection(s) of enemy sprites?
No. The enemy might need access to player though.

## 9. What class is responsible for creating the collections of enemies and items?
GameManager.

## 10. If you are using an FSM, what class calls the FSM methods of the sprites?
GameManager or the Sprite/Entity class itself.

## 11. At each game cycle, you need to perform collision detection between the player character and each enemy and item in the dungeon. What class or classes hold a method to compare the areas of two entities to check for collision? What is the function header of this method? What other classes are involved in the collision detection logic?


## 12. Describe the AI you are going to include.
     • Describe the behaviour
     • Describe the implementation logic
Enemies will have a finite state machine, where by default they will wander without straying too far from their original location.
They will have a state of alert where they know where the player was but not where they went (like a gunshot), they will go to that location and depending on if they see the player or not, they will either engage in combat with the player, or enter a searching state if they are unable to find the player where they thought the player would be.
In the searching state, the enemy will wander at an increased speed in search of the player. After an amount of time if they haven't found the player, they will return to their original location going back into the default state.
At any point, if the enemy is to see the player, they will immediately engage in combat.

## 13. Describe the trigonometry you are going to include
The player will be able to move their mouse on the game window in order to rotate their character in the game world, bullets shot will be fired in a line between the player's in-game entity and the mouse's point.
This will require simple sine, cosine and tangent math functions to translate from cartesian coordinates to polar coordinates in order to calculate the angles to rotate the player and bullets.

## 14. Describe in detail, the logic of your battle algorithm and computations
Battles happen in realtime, bullets will be projectiles that kill whatever it hits, this includes enemies being able to kill other enemies.

## 15. Sketch the screen layout with controls that you will use to provide feedback during battle

