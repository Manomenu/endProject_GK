#include "mesh.h"

void mesh_management::merge_meshes(Mesh& destination_mesh, Mesh& merged_mesh)
{
	auto& dst_vert = destination_mesh.get_vertices();
	auto& mrg_vert = merged_mesh.get_vertices();
	dst_vert.insert(dst_vert.end(), mrg_vert.begin(), mrg_vert.end());

	auto& dst_ind = destination_mesh.get_indices();
	auto& mrg_ind = merged_mesh.get_indices();
	dst_ind.insert(dst_ind.end(), mrg_ind.begin(), mrg_ind.end());

	auto& dst_tex = destination_mesh.get_textures();
	auto& mrg_tex = merged_mesh.get_textures();
	dst_tex.insert(dst_tex.end(), mrg_tex.begin(), mrg_tex.end());
}