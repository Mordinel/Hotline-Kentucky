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

void EnemyList::Shoot(sf::RectangleShape& rect) {
    Entity* node;

    if (head == nullptr) {
        return;
    }

    for (node = head; node != nullptr; node = node->Next) {
        if ( ((Enemy*)node)->GetState() != EnemyState::Dead ) {
            if ( ((Enemy*)node)->CheckCollision(rect, 1.0f) ) {
                ((Enemy*)node)->Die();
            }
        }
    }
}

void EnemyList::DeleteDead() {
    Entity* node;
    Entity* deleteNode;

    if (head == nullptr) {
        return;
    }

    for (node = head; (node->Next != nullptr) && (((Enemy*)node->Next)->GetState() == EnemyState::Dead); node = node->Next) {
        deleteNode = node->Next;
        node->Next = node->Next->Next;
        delete deleteNode;
    }
}
