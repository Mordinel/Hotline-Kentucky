#include "GameManager.h"

GameManager::GameManager(sf::RenderWindow* startWindow, sf::View startView, sf::Texture* playerTex) {
    window = startWindow;
    
    view = startView;
    viewZoom = ZOOM_DEFAULT;

    // Set up dungeon and rooms
    map = dungeon.GenMap();
    rooms = dungeon.GetRooms();
    
    // Setting up the exit of the dungeon
    sf::Vector2f exitLocation = dungeon.GetExitLocation();
    sf::Vector2f exitSize(TILE_SIZE, TILE_SIZE);
    exitRect.setPosition(exitLocation * (float)TILE_SIZE);
    exitRect.setSize(exitSize);
    
    // Setting up the tile map
    sf::Texture tileTex;
    tileTex.loadFromFile("../assets/sprites/tiles.png");
    tileMap = new TileMap(map, TILE_SIZE, tileTex);

    // Setting up the player
    player = new Player(playerTex, window, sf::Vector2u(CHICKEN_ANIMATION_SIZE, CHICKEN_ANIMATIONS), ANIMATION_SWITCH_TIME, PLAYER_SPEED, &map);
    sf::Vector2f spawnLocation = rooms[0]->GetCenter() * (float)TILE_SIZE; // Set players location to center of first room
    player->SetPosition(spawnLocation);

}

GameManager::~GameManager() {
    delete tileMap;
    delete player;
}

void GameManager::Update(float deltaTime) {
    handleWindowEvents();

    player->Update(&deltaTime);
    sf::Vector2f playerPos = player->GetPosition();

    tileMap->CastLight(playerPos.x, playerPos.y);
    fogOfWar = tileMap->LitMaskToFogOfWar();

    // Update view
    sf::Vector2f viewSize(window->getSize().x, window->getSize().y);
    view.setSize(viewSize * viewZoom);
    view.setCenter(playerPos);
    window->setView(view);
}

void GameManager::Draw() {
    window->clear(BACKGROUND_COLOR);
    window->draw(*tileMap);
    player->Draw(window);
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