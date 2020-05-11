#include "EnemyList.h"

EnemyList::EnemyList() : EntityList(){

}

EnemyList::~EnemyList() {

}

void EnemyList::Draw(sf::RenderWindow* window, const std::vector<std::vector<bool>>& fogOfWar) {
    Entity* node;

    if (head == nullptr) {
        return;
    }

    for (node = head; node != nullptr; node = node->Next) {
        node->Draw(window, fogOfWar);         
    }
}
