#pragma once
#include <config.h>

struct EntitiesController
{
public:
	uint get_new_id();

private:
	uint next_id_value = 0;
	std::vector<uint> freed_entity_ids;


};