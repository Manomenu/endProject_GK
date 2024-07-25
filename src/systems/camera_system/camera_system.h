#pragma once
#include <config.h>
#include <camera_component.h>
#include <transform_component.h>
#include <shader_manager/shader_manager.h>
#include <camera_data.h>
#include <platform_controller/platform_controller.h>

class CameraSystem {
public:

    void initialize(ShaderManager& shader_manager);

    bool update(
        PlatformController& platform_controller,
        ComponentSet<TransformComponent>& transform_components,
        uint camera, CameraComponent& camera_component, float delta_time);

private:
    uint viewLocation;
    glm::vec3 global_up = { 0.0f, 0.0f, 1.0f };
    float last_x, last_y;
    bool first_rotation = true, entered_rotation_mode = false, left_rotation_mode = false;

    void update_camera_vectors(CameraComponent& camera_component);
    glm::mat4 get_view_matrix(CameraComponent& camera_component, TransformComponent& transform_component);
    void process_position(
        TransformComponent& transform_component, CameraComponent& camera_component, 
        Camera_Movement direction, float delta_time);
    void process_rotation(
        TransformComponent& transform_component, CameraComponent& camera_component,
        float offset_x, float offset_y);
    void process_zoom(CameraComponent& camera_component, float offset_y);
};