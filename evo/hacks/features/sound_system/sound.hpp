#pragma once

namespace evo {
	struct sound_info_t {
		vec3_t player_origin;
		bool has_changed;
	};

	class sound_info {
	public:

	};

	inline const auto _sound = std::make_unique< sound_info >( );
}