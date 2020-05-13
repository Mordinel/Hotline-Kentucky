# System Design Document

## 1. Are your player, items and enemies the same class, different classes in the same family, or completely different classes?
The player, items, and enemies classes will derive from a base entity class and therefore be in the same family of classes.

## 2. What logic will you put into your Form class? What logic will you put into your Game Manager class?
We will not have a Form class, the game manager will handle cross-platform windowing

## 3. What classes do you need to implement the dungeon? Brieﬂy explain the job of each class, list the data members it must hold, and the methods it must expose. How do the Dungeon and the TileMap communicate?
We were unsure about this at the conception of this document, but the way it has been implemented is like the following:
Dungeon class:

    private:
    - dungeon matrix that uses the TileType enum to define tile types at locations.
    - list of Room class pointer, this holds room pointers to each room generated.
    - uint roomCount, this is so new dungeons can be generated with +n amount of rooms.
    - genRooms method, takes roomCount value. Generates non-intersecting rooms.
    - roomsIntersect method, takes pointers to 2 rooms, if they intersect it returns true.
    - getBounds method gets the most extreme room's coordinates of each direction.
    - translateRooms method, translates the Rooms pointer array coordinates from 0,0 central origin to 0,0 top-left origin.

    public:
    - Dungeon constructor
    - Dungeon destructor
    - NextDungeon method, generates a new dungeon
    - GetDungeon returns the dungeon matrix
    - GetRooms returns the rooms list
    - GenMap converts Room class into a matrix of TileType based on the rooms list

TileType enum:

    enum for tiles types:
    - Void, outside room boundaries
    - Floor, the only walkable tile
    - Wall, room and pathway boundaries
    - Unlit, for fog of war, unexplored tiles, only applies to tile visibility map.
    - Stairs, the end of level target

Room class:

    public:
    - Constructor
    - GetCenter, returns the center coordinate of the room
    - X and Y for top-left position
    - Width and Height for size
    - Pointer to another Room class, contains nullptr or the room that this room branched off from.

The GenMap method parses the rooms list into a TileType matrix for the tilemap to interpret and render.

## 4. What data structure(s) do you need to hold collections of enemies and items?
Linked list and std::vector

## 5. Does the dungeon need pointers to its sprites? Why or why not?
No. The TileMap will however need a pointer to its spritesheet for drawing.

## 6. Does the sprite class need a pointer to its dungeon? Why or why not?
The Entity class gets a pointer to its dungeon's tileMap, not the dungeon itself. This makes tile-based collision much more efficient because you only need to check the tiles the sprite is near for collision.

## 7. What enumeration types (if any) do you need?
Entity Direction, Tile Type, Enemy State, Enemy Type

## 8. Does the player sprite need access to the collection(s) of enemy sprites?
No. The enemy might need access to player though. The entity class will inherit the collider class, then the enemy list can be iterated over whilst holding a player pointer so that the collider class instances work together to perform sprite to sprite collision.

## 9. What class is responsible for creating the collections of enemies and items?
GameManager.

## 10. If you are using an FSM, what class calls the FSM methods of the sprites?
GameManager or the Sprite/Entity class itself.

## 11. At each game cycle, you need to perform collision detection between the player character and each enemy and item in the dungeon. What class or classes hold a method to compare the areas of two entities to check for collision? What is the function header of this method? What other classes are involved in the collision detection logic?
All items, players and enemies descend from the Entity class, which inherits the functionality of the collider class. Then, any entity can be checked for collision with any other entity and the tilemap.
```
virtual bool CheckCollision(Collider& other, float push);
virtual bool CheckCollision(sf::RectangleShape& rect, float push);
virtual bool CheckCollisionCentered(Collider& other, float push);
virtual bool CheckCollisionCentered(sf::RectangleShape& rect, float push);
```

## 12. Describe the AI you are going to include.
     • Describe the behaviour
     • Describe the implementation logic
Enemies will have a finite state machine, where by default they will wander without straying too far from their original location.
When the player enters a certain distance from the enemy, they will enter an attack state, where they will use their own attack method based on the enemy type.

## 13. Describe the trigonometry you are going to include
The player will be able to move their mouse on the game window in order to aim their gun, bullets shot will be fired in a line between the player's in-game entity and the mouse's point, stopping when it hits an enemy or a wall.
This will require simple sine and cosine math functions to translate from cartesian coordinates to polar coordinates in order to calculate the angles to rotate the player and bullets.
The fog of war was implemented using raycasting, which requires sine and cosine to calculate the vector of each ray casted from the player, which then decides if a tile is to be lit or unlit, currently visible or seen but not visible, and enemies to be visible or invisible.
The pathfinding used for 'Evil' Enemies (see EnemyType enum) includes use of pythagoras' theorem.

## 14. Describe in detail, the logic of your battle algorithm and computations
Battles happen in realtime, bullets will be a single ray cast that kills whatever it hits, this includes enemies being able to kill other enemies.

## 15. Sketch the screen layout with controls that you will use to provide feedback during battle
Does not apply to SFML.
