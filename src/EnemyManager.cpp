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

bool EnemyManager::Shoot(sf::RectangleShape& rect) {
    int i;
    for (i = 0; i < entityList.size(); i++) {
        if ( ((Enemy*)entityList[i])->GetState() != EnemyState::Dead ) {
            if ( ((Enemy*)entityList[i])->CheckCollisionCentered(rect, 1.0f) ) {
                ((Enemy*)entityList[i])->Die();
                return true;
            }
        }
    }

    return false;
}

void EnemyManager::DeleteDead() {
    int i;
    for (i = entityList.size() - 1; i >= 0; i--) {
        if ( ((Enemy*)entityList[i])->GetState() == EnemyState::Dead ) {
            delete entityList[i];
            entityList.erase(entityList.begin() + i);
        }
    }
}

void EnemyManager::Update(float* deltaTime, sf::Vector2f playerPos) {
    int i;
    for (i = 0; i < entityList.size(); i++) {
        ((Enemy*)entityList[i])->Update(deltaTime, playerPos);
    }
}

bool EnemyManager::CheckCollisionPlayer(Entity& ent, float push) {
    int i;
    bool collided = false;

    for (i = 0; i < entityList.size(); i++) {

        collided = entityList[i]->CheckCollisionCentered(ent, push);

        if ( ((Enemy*)entityList[i])->GetType() == EnemyType::Evil || ((Enemy*)entityList[i])->GetType() == EnemyType::Mecha ) {
            if (collided) return collided;
        }

    }

    return collided;
}

