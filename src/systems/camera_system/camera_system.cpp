#include "camera_system.h"

void CameraSystem::initialize(ShaderManager& shader_manager, const std::vector< uint>& cameras) {

    freeCamera = cameras[0];
    followingCamera = cameras[1];
    staticCamera = cameras[2];
    currentCamera = cameras[0];
    shader_manager.use();
    viewLocation = shader_manager.get_view_location();
    viewPosLocation = shader_manager.get_uniform_location("viewPos");
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
    const std::vector<uint>& cameras, 
    ComponentSet<CameraComponent>& camera_components,
    float delta_time
) 
{
    if (platform_controller.is_pressed(Buttons::ESC))
    {
        return true;
    }

    uint camera = currentCamera;

    CameraComponent& camera_component = camera_components[camera];
    TransformComponent& transform = transform_components[camera];

    if (camera == freeCamera)
    {
        //Position
        

        if (platform_controller.is_pressed(Buttons::W))
            process_position(transform, camera_component, FORWARD, delta_time);
        if (platform_controller.is_pressed(Buttons::S))
            process_position(transform, camera_component, BACKWARD, delta_time);
        if (platform_controller.is_pressed(Buttons::A))
            process_position(transform, camera_component, LEFT, delta_time);
        if (platform_controller.is_pressed(Buttons::D))
            process_position(transform, camera_component, RIGHT, delta_time);

        //Rotation
        if (!platform_controller.is_pressed(Buttons::L_ALT))
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
    }
    else if (currentCamera == staticCamera || currentCamera == followingCamera)
    {
        if (!platform_controller.is_pressed(Buttons::L_ALT))
        {
            left_rotation_mode = true;
            if (entered_rotation_mode)
            {
                entered_rotation_mode = false;
                platform_controller.set_mouse_input_mode(InputMode::LockedMouse);
            }
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

        update_camera_vectors(camera_component);
    }

    glm::mat4 view = get_view_matrix(camera_component, transform);
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
    
    glUniform3fv(viewPosLocation, 1, glm::value_ptr(transform.position));

    return false;
}

void CameraSystem::update_camera_vectors(CameraComponent& camera_component)
{
    float pitch = camera_component.pitch;
    float yaw = camera_component.yaw;
    float roll = 0;

    if (pitch >= 90 && pitch <= 270)
    {
        roll = 180;
    }

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera_component.forwards = glm::normalize(front);
    glm::vec3 right = glm::normalize(glm::cross(camera_component.forwards, camera_component.world_up));
    glm::vec3 up = glm::normalize(glm::cross(right, camera_component.forwards));
    glm::mat4 rollMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(roll), camera_component.forwards);
    camera_component.right = glm::normalize(glm::vec3(rollMatrix * glm::vec4(right, 0.0f)));
    camera_component.up = glm::normalize(glm::vec3(rollMatrix * glm::vec4(up, 0.0f)));
}
