#pragma once
#include <config.h>
#include <transform_component.h>
#include <scene_controller/scene_controller.h>

class MotionSystem {
public:
    void update(
        SceneController& scene_controller, 
        ComponentSet<TransformComponent>& transform_components, 
        ComponentSet<MotionComponent>& motion_components,
        ComponentSet<CameraComponent>& camera_components,
        ComponentSet<LightComponent>& light_components,
        float delta_time
    );
    void change_running(bool should_run) { running = should_run; }

private:
    bool running = true;
};