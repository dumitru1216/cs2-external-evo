#pragma once

namespace evo {
	class legit_t {
	public:
		void run_aimbot( const c_entity& entity, vec3_t local_pos, vec3_t aim_pos );
	};

	inline const auto _legit = std::make_unique < legit_t >( );
}