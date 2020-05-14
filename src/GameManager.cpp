/******************************************************************************
 * Filename: GameManager.cpp
 * FileType: C++ Source File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 12/05/2020
 * Description: Handles game flow, ties all classes together.
 *****************************************************************************/

#include "GameManager.h"

/*
 * GameManager Constructor
 *
 * Parameters:
 *      startWindow - Window to draw all graphics to.
 *      startView - view to follow player
 *      playerTex - player texture map
 *      startFont - text font.
 */
GameManager::GameManager(sf::RenderWindow* startWindow, sf::View startView, sf::Texture* playerTex, sf::Font startFont) {
    window = startWindow;
    
    view = startView;
    viewZoom = ZOOM_DEFAULT;

    // Set up dungeon and rooms
    map = dungeon.GenMap();
    rooms = dungeon.GetRooms();

    font = startFont;

    // set text fonts
    levelText.setFont(font);
    levelText.setFillColor(sf::Color::White);
    levelText.setCharacterSize(TEXT_SIZE);

    scoreText.setFont(font);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setCharacterSize(TEXT_SIZE);

    powerupText.setFont(font);
    powerupText.setFillColor(sf::Color::White);
    powerupText.setCharacterSize(TEXT_SIZE);

    lossText.setFont(font);
    lossText.setFillColor(sf::Color::White);
    lossText.setCharacterSize(TEXT_SIZE);
    lossString = "You died! Press SPACEBAR to restart.";
    lossText.setString(lossString);
    int lossTextXPos = (window->getSize().x / 2) - (lossText.getLocalBounds().width / 2);
    int lossTextYPos = (window->getSize().y / 2) - (TEXT_SIZE  / 2);
    lossText.setPosition(lossTextXPos, lossTextYPos);

    levelCount = 1;
    
    // Setting up the exit of the dungeon
    sf::Vector2f exitSize(TILE_SIZE, TILE_SIZE);
    exitRect.setSize(exitSize);
    
    // Setting up the tile map
    sf::Texture tileTex;
    tileTex.loadFromFile("../assets/sprites/tiles.png");
    tileMap = new TileMap(map, TILE_SIZE, tileTex);

    // Load enemy textures
    evilTexture = new sf::Texture();
    evilTexture->loadFromFile("../assets/sprites/evil-chicken.png");

    mechaTexture = new sf::Texture();
    mechaTexture->loadFromFile("../assets/sprites/mecha-chicken.png");

    goodTexture = new sf::Texture();
    goodTexture->loadFromFile("../assets/sprites/good-chicken.png");

    // Load item textures
    coinTexture = new sf::Texture();
    coinTexture->loadFromFile("../assets/sprites/coin.png");

    speedTexture = new sf::Texture();
    speedTexture->loadFromFile("../assets/sprites/speed-potion.png");

    visibilityTexture = new sf::Texture();
    visibilityTexture->loadFromFile("../assets/sprites/visibility-potion.png");

    // Setting up the player
    player = new Player(playerTex, window, sf::Vector2u(CHICKEN_ANIMATION_SIZE, CHICKEN_ANIMATIONS), ANIMATION_SWITCH_TIME, PLAYER_SPEED, &map);

    enemyManager = new EnemyManager();
    itemManager = new ItemManager();

    gun = new Gun(&map, enemyManager);

    score = 0;

    gameState = GameState::Running;

    Init();
}

/*
 * Gamemanager destructor
 *
 * Destroys all heap pointers owned by this class.
 */
GameManager::~GameManager() {
    delete tileMap;
    delete player;
    delete enemyManager;
    delete evilTexture;
    delete mechaTexture;
    delete goodTexture;
    delete gun;
    delete coinTexture;
    delete speedTexture;
    delete visibilityTexture;
    delete itemManager;
}

/*
 * Called on initialization of each new dungeon
 * Sets player to starting room, spawns enemies and items.
 */
void GameManager::Init() {
    map = dungeon.GenMap();
    rooms = dungeon.GetRooms();

    tileMap->SetTiles(map);

    fogOfWar = tileMap->LitMaskToFogOfWar();

    sf::Vector2f exitLocation = dungeon.GetExitLocation();
    exitRect.setPosition(exitLocation * (float)TILE_SIZE);

    sf::Vector2f spawnLocation = rooms[0]->GetCenter() * (float)TILE_SIZE; // Set players location to center of first room
    player->SetPosition(spawnLocation);

    levelString = "Level: " + std::to_string(levelCount);
    levelText.setString(levelString);
    
    enemyManager->DeleteAll();
    itemManager->DeleteAll();

    spawnEnemies();
    spawnItems();
}

/*
 * Spawns enemies in the current dungeon.
 */
void GameManager::spawnEnemies() {
    int i;
    int j;
    int chickens;

    // for each room
    for (i = 1; i < rooms.size() - 1; i++) {
        // add chickens up to 40 per room
        chickens = std::rand() % MAX_CHICKEN_PER_ROOM + 1;
        for(j = 0; j < chickens; j++) {

            int randomVal = std::rand() % CHICKEN_DENOM;

            Enemy* tmpEnemy;

            // 8 / 50 will be good
            if (randomVal >= GOOD_MIN && randomVal <= GOOD_MAX) {
                tmpEnemy = new Enemy(goodTexture, window, sf::Vector2u(ENEMY_FRAMES), GOOD_FRAMESPEED, GOOD_SPEED, &map, EnemyType::Good);
            // 2 / 50 will be mecha
            } else if (randomVal >= MECHA_MIN && randomVal < MECHA_MAX) {
                tmpEnemy = new Enemy(mechaTexture, window, sf::Vector2u(ENEMY_FRAMES), MECHA_FRAMESPEED, MECHA_SPEED, &map, EnemyType::Mecha);
            // the rest will be evil (normal enemies)
            } else {
                tmpEnemy = new Enemy(evilTexture, window, sf::Vector2u(ENEMY_FRAMES), EVIL_FRAMESPEED, EVIL_SPEED, &map, EnemyType::Evil);
            }

            // place it within the room
            sf::Vector2f spawnLocation = getRandomLocationInRoom(rooms[i]);
            tmpEnemy->SetPosition(spawnLocation);

            // add it to the EnemyManager
            enemyManager->Append(tmpEnemy);
        }
    }   
}

/*
 * Spawns powerups and coins in the rooms
 */
void GameManager::spawnItems() {
    // Spawn Power Ups
    for (int i = 0; i < rooms.size(); i++) {
        if (std::rand() % ITEM_SPAWN_CHANCE == 0) {
            Item* tmpItem;

            if (std::rand() % 2 == 0) {
                tmpItem = new Item(speedTexture, window, sf::Vector2u(1, 1), ITEM_FRAMESPEED, 0.0f, &map, ItemType::Speed);
            } else {
                tmpItem = new Item(visibilityTexture, window, sf::Vector2u(1, 1), ITEM_FRAMESPEED, 0.0f, &map, ItemType::Vision);
            }

            sf::Vector2f spawnLocation = getRandomLocationInRoom(rooms[i]);
            tmpItem->SetPosition(spawnLocation);

            itemManager->Append(tmpItem);
        }
    }

    // Spawn Coins
    for (int i = 0; i < rooms.size(); i++) {
        int coinCount = std::rand() % ROOM_COIN_COUNT;

        for (int i = 0; i < coinCount; i++) {
            Item* tmpItem = new Item(coinTexture, window, sf::Vector2u(COIN_FRAMES), ITEM_FRAMESPEED, 0.0f, &map, ItemType::Coin);

            int xPos, yPos;

            xPos = ((std::rand() % (rooms[i]->Width - 2)) + rooms[i]->X + 2) * TILE_SIZE;
            yPos = ((std::rand() % (rooms[i]->Height - 2)) + rooms[i]->Y + 2) * TILE_SIZE;

            sf::Vector2f spawnLocation = getRandomLocationInRoom(rooms[i]);
            tmpItem->SetPosition(spawnLocation);

            itemManager->Append(tmpItem);
        }
    }
}

/*
 * Gets random location in a room
 *
 * Parameters:
 *      room - pointer to room to get location within
 *
 * Returns:
 *      position inside the room
 */
sf::Vector2f GameManager::getRandomLocationInRoom(Room* room) {
    int xPos, yPos;

    xPos = ((std::rand() % (room->Width - 2)) + room->X + 2) * TILE_SIZE;
    yPos = ((std::rand() % (room->Height - 2)) + room->Y + 2) * TILE_SIZE;

    return sf::Vector2f(xPos, yPos);
}

/*
 * Updates game entities, lighting, handles window events, computes scores, ends rounds and starts new games.
 *
 * Parameters:
 *      deltaTime - passed into update functions for animation speed and movement speed regulation.
 */
void GameManager::Update(float deltaTime) {
    int i;
    bool newGame = false;

    window->setView(view); // For logic dependant on knowing where things are relative to the screen such as the mouse.

    handleWindowEvents();

    if (gameState == GameState::Running) {
        player->Update(&deltaTime);
    }
    
    sf::Vector2f playerPos = player->GetPosition();

    bool increaseVision = player->GetState() == PlayerState::IncreasedVision;
    tileMap->CastLight(playerPos.x, playerPos.y, increaseVision);
    fogOfWar = tileMap->LitMaskToFogOfWar();

    if (gameState == GameState::Running) {
        gun->Update(&deltaTime);
    }

    // change the score based on dead enemies
    std::vector<Enemy*>* dead = enemyManager->GetDead();
    for (i = 0; i < dead->size(); i++) {
        switch ((*dead)[i]->GetType()) {
            case EnemyType::Good:
                score -= GOOD_POINTS;
                break;
            case EnemyType::Evil:
                score += EVIL_POINTS;
                break;
            case EnemyType::Mecha:
                score += MECHA_POINTS;
                break;
        }
    }
    delete dead;

    // call enemyManager functions
    enemyManager->DeleteDead();
    enemyManager->Update(&deltaTime, player->GetPosition());
    enemyManager->CollideWithEntities();
    if (gameState == GameState::Running) {
        newGame = enemyManager->CheckCollisionPlayer(*player, PLAYER_ENEMY_PUSH);
    }
    // call itemManager functions
    itemManager->DeleteConsumed();
    itemManager->Update(&deltaTime);
    ItemType pickedUpItem = itemManager->CheckCollisionPlayer(*player);

    // score or apply perks based on the item picked up.
    switch (pickedUpItem) {
        case ItemType::Coin:
            score += COIN_POINTS;
            break;
        case ItemType::Speed:
            player->GiveSpeed();
            break;
        case ItemType::Vision:
            player->GiveVisibility();
            break;
    }

    // sets the score string
    scoreString = "Score: " + std::to_string(score);
    scoreText.setString(scoreString);

    // sets the perk string based on the current active perk
    switch (player->GetState()) {
        case PlayerState::IncreasedVision:
            powerupString = "Increased Vision";
            break;
        case PlayerState::IncreasedSpeed:
            powerupString = "Increased Speed";
            break;
        default:
            powerupString = "";
            break;
    }
    powerupText.setString(powerupString);

    // Update view
    sf::Vector2f viewSize(window->getSize().x, window->getSize().y);
    view.setSize(viewSize * viewZoom);
    view.setCenter(playerPos);

    sf::RectangleShape newRect;
    newRect.setSize(exitRect.getSize());
    newRect.setPosition(exitRect.getPosition() - (exitRect.getSize() / 2.0f));

    // Has player died?
    if (newGame) {
        gameState = GameState::Over;
    }
    // Has player reached the exit or died?
    if (player->CheckCollision(newRect, 0.0f)) {
        levelCount++;

        dungeon.NextDungeon(false);
        Init(); // Re-Initialize
    }
}

/*
 * Calls drawing functions of game objects and other things needed to be drawn.
 */
void GameManager::Draw() {
    // clear the window and draw the tilemap
    window->clear(BACKGROUND_COLOR);
    window->draw(*tileMap);
    window->draw(*gun);

    // draw enemies and items based on the fog of war
    enemyManager->Draw(window, fogOfWar);
    itemManager->Draw(window, fogOfWar);

    if (gameState == GameState::Running) {
        player->Draw(window);
    }
    

    // set the window view
    window->setView(window->getDefaultView());

    // set the location of and draw the text to the window
    levelText.setPosition(TEXT_LOCATION);
    scoreText.setPosition(TEXT_LOCATION + TEXT_SIZE);
    powerupText.setPosition(TEXT_LOCATION + (TEXT_SIZE * 2));

    window->draw(levelText);
    window->draw(scoreText);
    window->draw(powerupText);

    if (gameState == GameState::Over) {
        window->draw(lossText);
    }

    // display all changes made
    window->display();
}

/*
 * Handles window input events
 */
void GameManager::handleWindowEvents() {
    sf::Event evnt;

    while (window->pollEvent(evnt)) {
        switch(evnt.type) {
            case sf::Event::Closed:                 // window closed (alt + f4, click the X in the corner etc)
                window->close();
                break;
            case sf::Event::MouseWheelMoved:        // mouse wheel scroll
                setViewZoom(evnt.mouseWheel.delta);
                break;
            case sf::Event::MouseButtonPressed:     // mousebutton clicks
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && gameState == GameState::Running) {
                    sf::Vector2i cursorPos = sf::Mouse::getPosition(*window); 
                    sf::Vector2f relativeCursorPos = window->mapPixelToCoords(cursorPos);
                    sf::Vector2f playerPos = player->GetPosition();
                    gun->SetLineCoordinates(player->GetPosition(), relativeCursorPos);
                    gun->Fire(playerPos, relativeCursorPos, window);
                }
                break;
            case sf::Event::KeyPressed:
                if (evnt.key.code == sf::Keyboard::Space && gameState == GameState::Over) {
                    gameState = GameState::Running;
                    score = 0;
                    levelCount = 0;
                    dungeon.NextDungeon(false);
                    Init();
                }

        }
    } 
}

/*
 * sets the view resolution, limiting the zoom in the process.
 *
 * Parameters:
 *      mouseDelta - the direction of the mouse scroll wheel.
 */
void GameManager::setViewZoom(int mouseDelta) {
    if (mouseDelta < 0) {
        viewZoom += ZOOM_INCREMENTS;
    } else if (mouseDelta > 0) {
        viewZoom -= ZOOM_INCREMENTS;
    }

    if (viewZoom < ZOOM_MIN) {
        viewZoom = ZOOM_MIN;
    } else if (viewZoom > ZOOM_MAX) {
        viewZoom = ZOOM_MAX;
    }
}
