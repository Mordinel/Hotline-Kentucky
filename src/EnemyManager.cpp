EnemyManager::EnemyManager() {

}

EnemyManager::~EnemyManager() {

}

void EntityManager::Draw(sf::RenderWindow* window, const std::vector<std::vector<bool>>& fogOfWar) {
    int i;
    for (i = 0; i < entityList.size(); i++) {
        entityList[i]->Draw(window, fogOfWar);
    }
}

void EntityManager::Shoot(sf::RectangleShape& rect) {
    int i;
    for (i = 0; i < entityList.size(); i++) {
        if ( ((Enemy*)entityList[i])->GetState() != EnemyState::Dead ) {
            if ( ((Enemy*)entityList[i])->CheckCollision(rect, 1.0f) ) {
                ((Enemy*)entityList[i])->Die();
            }
        }
    }
}

void DeleteDead() {
    int i;
    for (i = entityList.size() - 1; i >= 0; i--) {
        if ( ((Enemy*)entityList[i]) == EnemyState::Dead ) {
            entityList.erase(begin() + i);
        }
    }
}

