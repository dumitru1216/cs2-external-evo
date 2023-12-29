#pragma once

namespace evo {
	class esp_t {
	public:
		void bounding_box( const c_entity& local_player, const c_entity& entity, ImVec4 rect, int local_index, int index );
		void render_esp( const c_entity& local_player, const c_entity& entity, ImVec4 rect,
							  int local_index, int index );

		evo::macros::vec4_t get_player_bounding_box( const c_entity& entity );

		bool spotted( const c_entity& entity, const c_entity& local_player, int local_index, int index ) {
			return ( ( entity.player_pawn.spotted_by_mask & ( DWORD64( 1 ) << local_index ) )
					 || ( local_player.player_pawn.spotted_by_mask & ( DWORD64( 1 ) << index ) ) );

		}
	};

	inline const auto _esp = std::make_unique<esp_t>( );
}