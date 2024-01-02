#pragma once
#include <memory>

namespace evo {
	class hacks_t {
	public:
		void run( );
	};

	inline const auto _hacks = std::make_unique< hacks_t >( );
}