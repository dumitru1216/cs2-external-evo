#pragma once
#include "../../inc.hpp"

namespace evo {
	class c_weapon_data {
	public:
	};

	class reverse_t {
	public:
		c_weapon_data* get_wpn_data( );
	};

	inline const auto _reverse = std::make_unique< reverse_t >( );
}