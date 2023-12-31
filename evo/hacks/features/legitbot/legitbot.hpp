#pragma once

namespace evo {
	class legit_t {
	public:
		void run_aimbot( const c_entity& entity, vec3_t local_pos, vec3_t aim_pos );

		DWORD aim_position = bone_index::head;
	};

	inline const auto _legit = std::make_unique < legit_t >( );
}