#include "GameManager.h"

GameManager::GameManager(sf::RenderWindow* startWindow, sf::View startView, sf::Texture* playerTex, sf::Font startFont) {
    window = startWindow;
    
    view = startView;
    viewZoom = ZOOM_DEFAULT;

    // Set up dungeon and rooms
    map = dungeon.GenMap();
    rooms = dungeon.GetRooms();

    font = startFont;

    levelText.setFont(font);
    levelText.setFillColor(sf::Color::White);
    levelText.setCharacterSize(TEXT_SIZE);

    scoreText.setFont(font);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setCharacterSize(TEXT_SIZE);

    powerupText.setFont(font);
    powerupText.setFillColor(sf::Color::White);
    powerupText.setCharacterSize(TEXT_SIZE);

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

    Init();
}

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

void GameManager::spawnEnemies() {
    int i;
    int j;
    int chickens;

    for (i = 1; i < rooms.size() - 1; i++) {
        chickens = std::rand() % 40 + 1;
        for(j = 0; j < chickens; j++) {

            int randomVal = std::rand() % 50;

            Enemy* tmpEnemy;

            if (randomVal >= 2 && randomVal <= 10) {
                tmpEnemy = new Enemy(goodTexture, window, sf::Vector2u(8, 8), 0.2f, 1.4f, &map, EnemyType::Good);
            } else if (randomVal >= 0 && randomVal < 2) {
                tmpEnemy = new Enemy(mechaTexture, window, sf::Vector2u(8, 8), 0.3f, 5.0f, &map, EnemyType::Mecha);
            } else {
                tmpEnemy = new Enemy(evilTexture, window, sf::Vector2u(8, 8), 0.2f, 1.4f, &map, EnemyType::Evil);
            }

            sf::Vector2f spawnLocation = getRandomLocationInRoom(rooms[i]);
            tmpEnemy->SetPosition(spawnLocation);
            enemyManager->Append(tmpEnemy);
        }
    }   
}

void GameManager::spawnItems() {
    // Spawn Power Ups
    for (int i = 0; i < rooms.size(); i++) {
        if (std::rand() % ITEM_SPAWN_CHANCE == 0) {
            Item* tmpItem;

            if (std::rand() % 2 == 0) {
                tmpItem = new Item(speedTexture, window, sf::Vector2u(1, 1), 0.2f, 0.0f, &map, ItemType::Speed);
            } else {
                tmpItem = new Item(visibilityTexture, window, sf::Vector2u(1, 1), 0.2f, 0.0f, &map, ItemType::Vision);
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
            Item* tmpItem = new Item(coinTexture, window, sf::Vector2u(4, 1), 0.2f, 0.0f, &map, ItemType::Coin);

            int xPos, yPos;

            xPos = ((std::rand() % (rooms[i]->Width - 2)) + rooms[i]->X + 2) * TILE_SIZE;
            yPos = ((std::rand() % (rooms[i]->Height - 2)) + rooms[i]->Y + 2) * TILE_SIZE;

            sf::Vector2f spawnLocation = getRandomLocationInRoom(rooms[i]);
            tmpItem->SetPosition(spawnLocation);

            itemManager->Append(tmpItem);
        }
    }
}

sf::Vector2f GameManager::getRandomLocationInRoom(Room* room) {
    int xPos, yPos;

    xPos = ((std::rand() % (room->Width - 2)) + room->X + 2) * TILE_SIZE;
    yPos = ((std::rand() % (room->Height - 2)) + room->Y + 2) * TILE_SIZE;

    return sf::Vector2f(xPos, yPos);
}

void GameManager::Update(float deltaTime) {
    int i;
    bool newGame = false;

    window->setView(view); // For logic dependant on knowing where things are relative to the screen such as the mouse.

    handleWindowEvents();

    player->Update(&deltaTime);
    sf::Vector2f playerPos = player->GetPosition();

    bool increaseVision = player->GetState() == PlayerState::IncreasedVision;
    tileMap->CastLight(playerPos.x, playerPos.y, increaseVision);
    fogOfWar = tileMap->LitMaskToFogOfWar();

    gun->Update(&deltaTime);

    std::vector<Enemy*>* dead = enemyManager->GetDead();

    for (i = 0; i < dead->size(); i++) {
        switch ((*dead)[i]->GetType()) {
            case EnemyType::Good:
                score -= 500;
                break;
            case EnemyType::Evil:
                score += 50;
                break;
            case EnemyType::Mecha:
                score += 150;
                break;
        }
    }

    delete dead;

    enemyManager->DeleteDead();
    enemyManager->Update(&deltaTime, player->GetPosition());
    enemyManager->CollideWithEntities();
    newGame = enemyManager->CheckCollisionPlayer(*player, 0.4f);

    itemManager->DeleteConsumed();
    itemManager->Update(&deltaTime);
    ItemType pickedUpItem = itemManager->CheckCollisionPlayer(*player);
    switch (pickedUpItem) {
        case ItemType::Coin:
            score += 100;
            break;
        case ItemType::Speed:
            player->GiveSpeed();
            break;
        case ItemType::Vision:
            player->GiveVisibility();
            break;
    }

    scoreString = "Score: " + std::to_string(score);
    scoreText.setString(scoreString);

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
    // Has player reached the exit or died?
    if (player->CheckCollision(newRect, 0.0f) || newGame) {

        if (newGame) {
            levelCount = 1;
            score = 0;
        } else {
            levelCount++;
        }

        dungeon.NextDungeon(newGame);
        Init(); // Re-Initialize
    }
}

void GameManager::Draw() {
    window->clear(BACKGROUND_COLOR);
    window->draw(*tileMap);
    window->draw(*gun);
    enemyManager->Draw(window, fogOfWar);
    itemManager->Draw(window, fogOfWar);
    player->Draw(window);

    window->setView(window->getDefaultView());

    levelText.setPosition(TEXT_LOCATION);
    scoreText.setPosition(TEXT_LOCATION + TEXT_SIZE);
    powerupText.setPosition(TEXT_LOCATION + (TEXT_SIZE * 2));

    window->draw(levelText);
    window->draw(scoreText);
    window->draw(powerupText);

    window->display();
}

void GameManager::handleWindowEvents() {
    sf::Event evnt;

    while (window->pollEvent(evnt)) {
        switch(evnt.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::MouseWheelMoved:
                setViewZoom(evnt.mouseWheel.delta);
                break;
            case sf::Event::MouseButtonPressed:
                sf::Vector2i cursorPos = sf::Mouse::getPosition(*window); 
                sf::Vector2f relativeCursorPos = window->mapPixelToCoords(cursorPos);
                sf::Vector2f playerPos = player->GetPosition();
                gun->SetLineCoordinates(player->GetPosition(), relativeCursorPos);
                gun->Fire(playerPos, relativeCursorPos, window);
                break;

        }
    } 
}

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
