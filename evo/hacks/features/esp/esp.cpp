#include "../../../inc.hpp"

void evo::esp_t::render_esp( const c_entity& local_player, const c_entity& entity, ImVec4 rect, int local_index, int index ) { 
	/* dormant shit: 
		xref: entity.player_pawn.dormant

		seems to work ig
	*/

	if ( evo::_settings->bounding_box ) {
		evo::_render->add_rect(
			rect.x, rect.y, /* bb.min */
			rect.z, rect.w, /* bb.max */
			_render->to_main_color( _settings->box_color ), 0, 1.f
		);

		evo::_render->add_rect(
			rect.x - 1, rect.y - 1, /* bb.min */
			rect.z + 2, rect.w + 2, /* bb.max */
			evo::col_t( 0, 0, 0 ), 0, 1.f
		);


		evo::_render->add_rect(
			rect.x + 1, rect.y + 1, /* bb.min */
			rect.z - 2, rect.w - 2, /* bb.max */
			evo::col_t( 0, 0, 0 ), 0, 1.f
		);
	}
}

evo::macros::vec4_t evo::esp_t::get_player_bounding_box( const c_entity& entity ) {
	bone_pos head = entity.get_bone( ).bone_pos_list[ bone_index::head ];

	vec2_t size, pos;
	size.y = ( entity.player_pawn.screen_pos.y - head.screen_pos.y ) * 1.20;
	size.x = size.y * 0.6;

	// retarded 
	pos = vec2_t( entity.player_pawn.screen_pos.x - size.x / 2, head.screen_pos.y - size.y * 0.08 );

	return ImVec4{ pos.x, pos.y - 4, size.x, size.y };
}
