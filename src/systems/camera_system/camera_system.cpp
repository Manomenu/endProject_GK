#include "camera_system.h"

void CameraSystem::initialize(ShaderManager& shader_manager) {

    shader_manager.use();
    viewLocation = shader_manager.get_view_location();
}

glm::mat4 CameraSystem::get_view_matrix(CameraComponent& camera_component, TransformComponent& transform_component)
{
    return glm::lookAt(
        transform_component.position,
        transform_component.position + camera_component.forwards,
        camera_component.up
    );
}

void CameraSystem::process_position(TransformComponent& transform_component, CameraComponent& camera_component, Camera_Movement direction, float delta_time)
{
    float velocity = camera_component.movement_speed * delta_time;
    
    switch (direction)
    {
    case FORWARD:
        transform_component.position += camera_component.forwards * velocity;
        break;
    case BACKWARD:
        transform_component.position -= camera_component.forwards * velocity;
        break;
    case LEFT:
        transform_component.position -= camera_component.right * velocity;
        break;
    case RIGHT:
        transform_component.position += camera_component.right * velocity;
        break;
    default:
        PROJECT_ERROR("Invalid Camera_Movement enum value");
    }
}

void CameraSystem::process_rotation(TransformComponent& transform_component, CameraComponent& camera_component, float offset_x, float offset_y)
{
    offset_x *= camera_component.mouse_sensitivity;
    offset_y *= camera_component.mouse_sensitivity;

    camera_component.yaw += offset_x;
    camera_component.pitch += offset_y;
    camera_component.pitch = glm::clamp(camera_component.pitch, -89.0f, 89.0f);

    update_camera_vectors(camera_component);
}

void CameraSystem::process_zoom(CameraComponent& camera_component, float offset_y)
{
    camera_component.zoom -= offset_y;
    camera_component.zoom = glm::clamp(camera_component.zoom, 1.0f, 45.0f);
}

bool CameraSystem::update(
    PlatformController& platform_controller,
    ComponentSet<TransformComponent>& transform_components,
    uint camera, CameraComponent& camera_component, 
    float delta_time
) 
{
    if (platform_controller.is_pressed(Buttons::ESC))
    {
        return true;
    }

    //Position
    TransformComponent& transform = transform_components[camera];
    
    if (platform_controller.is_pressed(Buttons::W))
        process_position(transform, camera_component, FORWARD, delta_time);
    if (platform_controller.is_pressed(Buttons::S))
        process_position(transform, camera_component, BACKWARD, delta_time);
    if (platform_controller.is_pressed(Buttons::A))
        process_position(transform, camera_component, LEFT, delta_time);
    if (platform_controller.is_pressed(Buttons::D))
        process_position(transform, camera_component, RIGHT, delta_time);

    //Rotation
    if (!platform_controller.is_pressed(Buttons::L_CTRL))
    {
        left_rotation_mode = true;
        if (entered_rotation_mode)
        {
            entered_rotation_mode = false;
            platform_controller.set_mouse_input_mode(InputMode::LockedMouse);
        }

        glm::vec2 cursor_position = platform_controller.get_cursor_position();
        

        if (first_rotation)
        {
            last_x = cursor_position.x;
            last_y = cursor_position.y;
            first_rotation = false;
        }
        float offset_x = cursor_position.x - last_x;
        float offset_y = last_y - cursor_position.y;
        last_x = cursor_position.x;
        last_y = cursor_position.y;
        // todo camera does not work!

        process_rotation(transform, camera_component, offset_x, offset_y);

        //platform_controller.center_cursor();
    }
    else
    {
        entered_rotation_mode = true;
        if (left_rotation_mode)
        {
            left_rotation_mode = false;
            platform_controller.set_mouse_input_mode(InputMode::FreeMouse);
        }
    }


    glm::mat4 view = get_view_matrix(camera_component, transform);
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

    return false;
}

void CameraSystem::update_camera_vectors(CameraComponent& camera_component)
{
    float yaw = camera_component.yaw;
    float pitch = camera_component.pitch;

    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera_component.forwards = glm::normalize(front);
    // also re-calculate the Right and Up vector
    camera_component.right = glm::normalize(
        glm::cross(camera_component.forwards, camera_component.world_up)
    );  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    camera_component.up = glm::normalize(glm::cross(camera_component.right, camera_component.forwards));
}
