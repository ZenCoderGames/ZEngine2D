#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "./BoxCollider.h"
#include <vector>
#include <map>
#include <functional>
#include <iostream>
#include <algorithm>

class CollisionManager {
    private:
        std::vector<BoxCollider*> boxColliderList;
        std::map<Entity*, std::function<void(Entity*)>> entityEventMap;
    public:
        void RegisterBoxCollider(BoxCollider* boxCollider) {
            boxColliderList.emplace_back(boxCollider);
        }

        void RegisterForCollision(Entity* entity, std::function<void(Entity*)> callback) {
            entityEventMap.insert(std::pair<Entity*, std::function<void(Entity*)>>(entity, callback));
        }

        void UnregisterBoxCollider(BoxCollider* boxCollider) {
            boxColliderList.erase(std::remove(boxColliderList.begin(), boxColliderList.end(), boxCollider), boxColliderList.end());
        }

        void Update() {
            if(boxColliderList.size()>0) {
                for(int i=0; i<boxColliderList.size()-1; ++i) {
                    for(int j=i+1; j<boxColliderList.size(); ++j) {
                        if(boxColliderList[i]->IsColliding(boxColliderList[j]->rect)) {
                            if(entityEventMap.count(boxColliderList[i]->parentEntity)>0) {
                                entityEventMap[boxColliderList[i]->parentEntity](boxColliderList[j]->parentEntity);
                            }
                        }
                    }
                }
            }
        }
};

#endif