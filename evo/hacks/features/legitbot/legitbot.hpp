#pragma once

namespace evo {
	class legit_t {
	public:
		void run_aimbot( const c_entity& entity, const c_entity& local, vec3_t local_pos, int ent_idx, int local_idx );

		DWORD aim_position = bone_index::head;
	};

	inline const auto _legit = std::make_unique < legit_t >( );
}