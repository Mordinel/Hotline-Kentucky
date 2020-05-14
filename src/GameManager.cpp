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

    levelCount = 1;
    
    // Setting up the exit of the dungeon
    sf::Vector2f exitSize(TILE_SIZE, TILE_SIZE);
    exitRect.setSize(exitSize);
    
    // Setting up the tile map
    sf::Texture tileTex;
    tileTex.loadFromFile("../assets/sprites/tiles.png");
    tileMap = new TileMap(map, TILE_SIZE, tileTex);

    evilTexture = new sf::Texture();
    evilTexture->loadFromFile("../assets/sprites/evil-chicken.png");

    mechaTexture = new sf::Texture();
    mechaTexture->loadFromFile("../assets/sprites/mecha-chicken.png");

    goodTexture = new sf::Texture();
    goodTexture->loadFromFile("../assets/sprites/good-chicken.png");

    // Setting up the player
    player = new Player(playerTex, window, sf::Vector2u(CHICKEN_ANIMATION_SIZE, CHICKEN_ANIMATIONS), ANIMATION_SWITCH_TIME, PLAYER_SPEED, &map);

    enemyManager = new EnemyManager();;

    gun = new Gun(&map, enemyManager);

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

    SpawnThings();
}

void GameManager::SpawnThings() {
    int i;
    int j;
    int chickens;

    for (i = 1; i < rooms.size() - 1; i++) {
        chickens = std::rand() % 30 + 1;
        for(j = 0; j < chickens; j++) {

            int randomVal = std::rand() % 50;

            Enemy* tmpEnemy;

            if (randomVal >= 0 && randomVal <= 15) {
                tmpEnemy = new Enemy(goodTexture, window, sf::Vector2u(8, 8), 0.125f, 2.6f, &map, EnemyType::Good);
            } else {
                tmpEnemy = new Enemy(evilTexture, window, sf::Vector2u(8, 8), 0.125f, 2.6f, &map, EnemyType::Evil);
            }

            sf::Vector2f tmpSpawn = rooms[i]->GetCenter();
            tmpSpawn *= (float)TILE_SIZE;
            tmpEnemy->SetPosition(tmpSpawn);
            enemyManager->Append(tmpEnemy);
        }
    }   
}

void GameManager::Update(float deltaTime) {
    window->setView(view); // For logic dependant on knowing where things are relative to the screen such as the mouse.

    handleWindowEvents();

    player->Update(&deltaTime);
    sf::Vector2f playerPos = player->GetPosition();

    bool increaseVision = player->GetState() == PlayerState::IncreasedVision;
    tileMap->CastLight(playerPos.x, playerPos.y, increaseVision);
    fogOfWar = tileMap->LitMaskToFogOfWar();

    //gun->SetLineCoordinates(playerPos, relativeCursorPos);
    gun->Update(&deltaTime);
    enemyManager->DeleteDead();
    enemyManager->Update(&deltaTime, player->GetPosition());
    enemyManager->CollideWithEntities();
    enemyManager->CheckCollision(*player, 0.5f);

    // Update view
    sf::Vector2f viewSize(window->getSize().x, window->getSize().y);
    view.setSize(viewSize * viewZoom);
    view.setCenter(playerPos);

    sf::RectangleShape newRect;
    newRect.setSize(exitRect.getSize());
    newRect.setPosition(exitRect.getPosition() - (exitRect.getSize() / 2.0f));
    // Has player reached the exit?
    if (player->CheckCollision(newRect, 0.0f)) {
        levelCount++;
        dungeon.NextDungeon();
        Init(); // Re-Initialize
    }
}

void GameManager::Draw() {
    window->clear(BACKGROUND_COLOR);
    window->draw(*tileMap);
    window->draw(*gun);
    enemyManager->Draw(window, fogOfWar);
    player->Draw(window);

    window->setView(window->getDefaultView());
    levelText.setPosition(TEXT_LOCATION);
    window->draw(levelText);

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
