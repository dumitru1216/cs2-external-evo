#pragma once

namespace evo {
	typedef struct _impact_info { /* thanks soufiw */
		float x, y, z;
		float time;
	}impact_info, * p_impact_info;

	typedef struct _hitmarker_info { /* thanks soufiw */
		impact_info pImpact;
		float alpha;
		int alpha2;
		int damage;
		float moved;
	}hitmarker_info, * p_hitmarker_info;

	class shots_t {
	public:
		void hitsound( const c_entity& entity );
		void hitmarker( const c_entity& entity, const c_entity& local );
	};

	inline const auto _shots = std::make_unique< shots_t >( );
}