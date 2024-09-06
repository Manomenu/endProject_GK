#pragma once
#include <config.h>
#include <camera_component.h>
#include <transform_component.h>
#include <shader_manager/shader_manager.h>
#include <camera_data.h>
#include <platform_controller/platform_controller.h>

class CameraSystem {
public:

    void initialize(ShaderManager& shader_manager, const std::vector< uint>& cameras);
    bool update(
        PlatformController& platform_controller,
        ComponentSet<TransformComponent>& transform_components,
        const std::vector<uint>& cameras, ComponentSet<CameraComponent>& camera_components, 
        float delta_time);
    uint get_current_camera() { return currentCamera; }
    uint get_camera_array_number(uint camera, const std::vector<uint>& cameras) { for (uint i = 0; i < cameras.size(); ++i) if (cameras[i] == camera) return i; }
    void change_camera(uint new_camera_array_number)
    {
        switch (new_camera_array_number)
        {
        case 0:
            currentCamera = freeCamera;
            return;
        case 1:
            currentCamera = followingCamera;
            return;
        case 2:
            currentCamera = staticCamera;
            return;
        default:
            return;
        }
    }

private:
    uint freeCamera;
    uint followingCamera;
    uint staticCamera;
    uint currentCamera;
    uint viewLocation;
    uint viewPosLocation;
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