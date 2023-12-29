#pragma once

namespace evo {
	class esp_t {
		void render_esp( const c_entity& local_player, const c_entity& entity, ImVec4 rect, 
							  int local_index, int index );

		evo::vec4 get_player_bounding_box( const c_entity& entity );
	};

	inline const auto _esp = std::make_unique<esp_t>( );
}