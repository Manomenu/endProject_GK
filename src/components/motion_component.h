#pragma once
#include <config.h>

struct MotionComponent
{
	bool circular_move = false;
	glm::vec3 circle_center;
	float circle_radius;
};