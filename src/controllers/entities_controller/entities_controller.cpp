#include "entities_controller.h"

uint EntitiesController::get_new_id()
{
	return next_id_value++;
}