#pragma once
#include <config.h>
#include <render_component.h>
#include <animation_component.h>
#include <scene_controller/scene_controller.h>

class AnimationSystem {
public:
    void update(
        ComponentSet<AnimationComponent>& animation_components,
        ComponentSet<RenderComponent>& render_components
    );

};