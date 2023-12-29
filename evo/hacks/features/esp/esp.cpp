#include "../../../inc.hpp"

void evo::esp_t::render_esp( const c_entity& local_player, const c_entity& entity, ImVec4 rect, int local_index, int index ) { 
	if ( evo::_settings->bounding_box ) {
		/*  xref eexomi
			Render::Get( )->AddRect( bbox.min, bbox.max, color, 0.0f, -1, 1.0f );
			Render::Get( )->AddRect( bbox.min - Vector2D( 1.0f, 1.0f ), bbox.max + Vector2D( 1.0f, 1.0f ), outline, 0.0f, -1, 1.0f );
			Render::Get( )->AddRect( bbox.min + Vector2D( 1.0f, 1.0f ), bbox.max - Vector2D( 1.0f, 1.0f ), outline, 0.0f, -1, 1.0f );
		*/

		evo::_render->add_rect(
			rect.x, rect.y, /* bb.min */
			rect.w, rect.z, /* bb.max */
			evo::col_t( ), 0, 1.f
		);
	}
}

evo::vec4 evo::esp_t::get_player_bounding_box( const c_entity& entity ) {
	
}
