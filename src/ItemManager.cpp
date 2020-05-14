#include "ItemManager.h"

ItemManager::ItemManager() : EntityManager() {}
ItemManager::~ItemManager() {}

void ItemManager::Draw(sf::RenderWindow* window, const std::vector<std::vector<bool>>& fogOfWar) {
    for (int i = 0; i < entityList.size(); i++) {
        entityList[i]->Draw(window, fogOfWar);
    }
}

void ItemManager::DeleteConsumed() {
    for (int i = 0; i < entityList.size(); i++) {
        if (((Item*)entityList[i])->GetConsumed() == true) {
            entityList.erase(entityList.begin() + i);
        }
    }
}

void ItemManager::Update(float* deltaTime) {
    for (int i = 0; i < entityList.size(); i++) {
        entityList[i]->Update(deltaTime);
    }
}

ItemType ItemManager::CheckCollisionPlayer(Entity& ent) {
    for (int i = 0; i < entityList.size(); i++) {
        if (entityList[i]->CheckCollisionCentered(ent, 0.0f)) {
            ((Item*)entityList[i])->SetConsumed(true);
            return ((Item*)entityList[i])->GetItemType();
        }
    }

    return ItemType::None;
}

void ItemManager::PrintItems() {
    for (int i = 0; i < entityList.size(); i++) {
        switch(((Item*)entityList[i])->GetItemType()) {
            case ItemType::Coin:
                std::cout << "Coin" << std::endl;
                break;
            case ItemType::Speed:
                std::cout << "Speed" << std::endl;
                break;
            case ItemType::Vision:
                std::cout << "Vison" << std::endl;
        }
    }
}