#pragma once

namespace evo {
	class shots_t {
	public:

		void hitsound( const c_entity& entity );

	};

	inline const auto _shots = std::make_unique< shots_t >( );
}