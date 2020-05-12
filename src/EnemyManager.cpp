#include "EnemyManager.h"

EnemyManager::EnemyManager() : EntityManager() {

}

EnemyManager::~EnemyManager() {

}

void EnemyManager::Draw(sf::RenderWindow* window, const std::vector<std::vector<bool>>& fogOfWar) {
    int i;
    for (i = 0; i < entityList.size(); i++) {
        entityList[i]->Draw(window, fogOfWar);
    }
}

void EnemyManager::Shoot(sf::RectangleShape& rect) {
    int i;
    for (i = 0; i < entityList.size(); i++) {
        if ( ((Enemy*)entityList[i])->GetState() != EnemyState::Dead ) {
            if ( ((Enemy*)entityList[i])->CheckCollision(rect, 1.0f) ) {
                ((Enemy*)entityList[i])->Die();
            }
        }
    }
}

void EnemyManager::DeleteDead() {
    int i;
    for (i = entityList.size() - 1; i >= 0; i--) {
        if ( ((Enemy*)entityList[i])->GetState() == EnemyState::Dead ) {
            entityList.erase(entityList.begin() + i);
        }
    }
}

