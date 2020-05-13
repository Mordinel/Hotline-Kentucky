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
        delete entityList[i];
    }

    entityList.clear();
}

void EntityManager::CheckCollision(Entity& ent, float push) {
    int i;    
    for (i = 0; i < entityList.size(); i++) {
        entityList[i]->CheckCollisionCentered(ent, push);
    }
}

void EntityManager::CollideWithEntities() {
    int i;
    int j;
    for (i = 0; i < entityList.size(); i++) {
        for (j = 0; j < entityList.size(); j++) {
            if (i == j) continue;

            Entity* tmpEnt = entityList[j];
            entityList[i]->CheckCollisionCentered(*tmpEnt, 0.5f);
        }
    }
}

