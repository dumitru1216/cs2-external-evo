#pragma once
#include <memory>

namespace evo {
	class hacks_t {
	public:
		evo::c_entity* get_entity( int index );
		void run( );
	};

	inline const auto _hacks = std::make_unique< hacks_t >( );
}