#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include "./Entity.h"
#include "../../../lib/lua/sol.hpp"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/SpriteAnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/TextComponent.h"
#include "../Components/TileComponent.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
/// Helper class that creates all components
//////////////////////////////////////////////////////////////////////////////////////////////////
class ComponentManager {
    public:
        static Component* GetComponent(Entity* newEntity, sol::table componentTable) {
            Component* newComponent = nullptr;
            std::string type = componentTable["type"];
            if(type=="transform") {
                newComponent = TransformComponent::Generate(componentTable["params"]);
            }
            else if(type=="sprite") {
                newComponent = SpriteComponent::Generate(componentTable["params"]);
            }
            else if(type=="spriteAnimation") {
                newComponent = SpriteAnimationComponent::Generate(componentTable["params"]);
            }
            else if(type=="boxCollider") {
                newComponent = BoxColliderComponent::Generate(componentTable["params"]);
            }
            else if(type=="projectile") {
                newComponent = ProjectileComponent::Generate(componentTable["params"]);
            }
            else if(type=="text") {
                newComponent = TextComponent::Generate(componentTable["params"]);
            }
            else if(type=="tile") {
                newComponent = TileComponent::Generate(componentTable["params"]);
            }

            return newComponent;
        }
};

#endif