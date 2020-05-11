#include "EntityList.h"

// construct empty linked list
EntityList::EntityList() {
    head = nullptr;
    tail = nullptr;
}

EntityList::~EntityList() {
    DeleteAll();
}

// count the items in the linked list
int EntityList::EntityCount() {
    int count = 0;
    Entity* node;

    for (node = head; node != nullptr; node = (count++,node->Next))
        ;

    return count;
}

// Append an entity to the linked list
void EntityList::Append(Entity* entity) {
    if (tail == nullptr) {
        head = entity;
        tail = entity;
    } else {
        tail->Next = entity;
        tail = tail->Next;
    }
}

// delete and entity from the linked list
void EntityList::Delete(Entity* entity) {
    Entity* node;

    if (head == nullptr) {
        return;
    }

    for (node = head; (node->Next != nullptr) && (node->Next != entity); node = node->Next)
        ;
    
    if (node->Next == nullptr) {
        return;
    }

    node->Next = entity->Next;
    delete entity;
}

// call the Update() function of each entity
void EntityList::Update(float* deltaTime) {
    Entity* node;

    if (head == nullptr) {
        return;
    }

    for (node = head; node != nullptr; node = node->Next) {
        node->Update(deltaTime);
    }
}

// call the Draw() function of each entity
void EntityList::Draw(sf::RenderWindow* window) {
    Entity* node;

    if (head == nullptr) {
        return;
    }

    for (node = head; node != nullptr; node = node->Next) {
        node->Draw(window);
    }
}

// delete each entity
void EntityList::DeleteAll() {
    Entity* node;
    Entity* nextNode;

    if (head == nullptr) {
        return;
    }

    for (node = head; node != nullptr; node = nextNode) {
        nextNode = node->Next;
        delete node;
    }

    head = nullptr;
    tail = nullptr;
}

void EntityList::CheckCollision(Entity& ent, float push) {
    Entity* node;

    if (head == nullptr) {
        return;
    }

    for (node = head; node != nullptr; node = node->Next) {
        node->CheckCollision(ent, push);
    }
}
