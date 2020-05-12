#include "EntityManager.h"

EntityManager::EntityManager() {

}

EntityManager::~EntityManager() {
    DeleteAll();
}

void EntityManager::Append(Entity* entity) {
    entityList.push_back(entity);
}

void EntityManager::Delete(Entity* entity) {
    int i;
    for (i = 0; i < entityList.size(); i++) {
        if (entityList[i] == entity) {
            entityList.erase(entityList.begin() + i);
            return;
        }
    }
}

void EntityManager::Update(float* deltaTime) {
    int i;
    for (i = 0; i < entityList.size(); i++) {
        entityList[i]->Update(deltaTime);
    }
}

void EntityManager::Draw(sf::RenderWindow* window) {
    int i;
    for (i = 0; i < entityList.size(); i++) {
        entityList[i]->Draw(window);
    }
}

void EntityManager::DeleteAll() {
    int i;
    for (i = 0; i < entityList.size(); i++) {
        entityList.erase(entityList.end() - i);
    }
}

void EntityManager::CheckCollision(Entity& ent, float push) {
    int i;    
    for (i = 0; i < entityList.size(); i++) {
        entityList[i]->CheckCollsion(ent, push);
    }
}

