#pragma once

namespace evo {
	class grenade_t {
	public:
		void run( const c_entity& local_player, const c_entity& entity, int local_index, int index );
	};

	inline const auto _grenade = std::make_unique< grenade_t >( );
}