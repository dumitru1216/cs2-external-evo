#include "../../../inc.hpp"

void evo::esp_t::setup_alpha( const c_entity& local_player, const c_entity& entity, int local_index, int index ) { 
	float frame_time = 0.015;
	float delta_time = ( 1.0f / 0.3f ) * frame_time * 0.10f;

	bool alive_player = entity.player_pawn.health > 0; /* health > 0 */
	/* grab distance from local to player */
	float distance = local_player.player_pawn.vec_origin.dist_to( entity.player_pawn.vec_origin );

	/* allowed distance */
	static const float run_dormancy = 750.f;

	if ( alive_player && !( ( distance > run_dormancy ) && !this->spotted( entity, local_player, local_index, index ) ) ) {
		this->esp_alpha[ index ] += 255.f / 0.68f * frame_time;
		this->esp_alpha[ index ] = std::clamp( this->esp_alpha[ index ], 0.f, 255.f );
	} else if ( !alive_player ) {
		this->esp_alpha[ index ] -= 255.f / 0.68f * frame_time;
		this->esp_alpha[ index ] = std::clamp( this->esp_alpha[ index ], 0.f, 255.f );
	}
	else if ( alive_player && ( distance > run_dormancy ) && evo::_settings->dormancy ) {
		if ( esp_alpha[ index ] < 150.f ) {
			this->esp_alpha[ index ] -= 255.f / 16.f * frame_time;
			this->esp_alpha[ index ] = std::clamp( this->esp_alpha[ index ], 0.f, 160.f );
		} else {
			this->esp_alpha[ index ] -= 255.f / 1.f * frame_time;
		}
	}
}

void evo::esp_t::bounding_box( const c_entity& local_player, const c_entity& entity, ImVec4 rect, int local_index, int index ) {
	evo::col_t box_color{ };
	if ( evo::_settings->change_by_visibility ) {
		box_color = this->spotted( entity, local_player, local_index, index ) ? _render->to_main_color( _settings->box_color ).modify_alpha( this->esp_alpha[ index ] ) : _render->to_main_color( _settings->box_color_inv ).modify_alpha( this->esp_alpha[ index ] );
	}  else {
		box_color = _render->to_main_color( _settings->box_color ).modify_alpha( this->esp_alpha[ index ] );
	}

	evo::_render->add_rect(
		rect.x, rect.y, /* bb.min */
		rect.z, rect.w, /* bb.max */
		box_color, 0, 1.f
	);

	evo::_render->add_rect(
		rect.x - 1, rect.y - 1, /* bb.min */
		rect.z + 2, rect.w + 2, /* bb.max */
		evo::col_t( 0, 0, 0 ).modify_alpha( this->esp_alpha[ index ] ), 0, 1.f
	);


	evo::_render->add_rect(
		rect.x + 1, rect.y + 1, /* bb.min */
		rect.z - 2, rect.w - 2, /* bb.max */
		evo::col_t( 0, 0, 0 ).modify_alpha( this->esp_alpha[ index ] ), 0, 1.f
	);
}

void evo::esp_t::render_name( const c_entity& local_player, const c_entity& entity, ImVec4 rect, int local_index, int index ) { 
	evo::col_t name_color{ };
	if ( evo::_settings->change_by_visibility ) {
		name_color = this->spotted( entity, local_player, local_index, index ) ? _render->to_main_color( _settings->name_color ).modify_alpha( this->esp_alpha[ index ] ) : _render->to_main_color( _settings->name_color_inv ).modify_alpha( this->esp_alpha[ index ] );
	} else {
		name_color = _render->to_main_color( _settings->name_color ).modify_alpha( this->esp_alpha[ index ] );
	}

	/* player name */
	std::string player_name = entity.controller.player_name;

	/* text sizes */
	int text_width = evo::_render->text_size( player_name.c_str( ), evo::fonts_t::_default ).x;
	int text_height = evo::_render->text_size( player_name.c_str( ), evo::fonts_t::_default ).y;

	evo::_render->add_text(
		rect.x + ( rect.z  * 0.5f ) - ( text_width * 0.5f ), rect.y - text_height - 2, name_color, evo::fonts_t::_default,
		player_name.c_str( ), evo::font_flags_t::dropshadow
	);

	if ( evo::_settings->name_animation	) {
		evo::_render->bind_animation( index, player_name.c_str( ), _render->to_main_color( _settings->name_color_a ).modify_alpha( this->esp_alpha[ index ] ),
									  evo::fonts_t::_default, rect.x + ( rect.z * 0.5f ) - ( text_width * 0.5f ), rect.y - text_height - 2, (evo::text_animation_t)evo::_settings->name_at, 0.1 );
	}
}

void evo::esp_t::health_bar( const c_entity& local_player, const c_entity& entity, ImVec4 rect, int local_index, int index ) { 
	int player_hp = entity.player_pawn.health;
	int max_hp = 100;

	static float prev_player_hp[ 64 ];
	constexpr float speed_freq = 255 / 1.0f;

	if ( prev_player_hp[ index ] > player_hp )
		prev_player_hp[ index ] -= speed_freq * 0.015;
	else
		prev_player_hp[ index ] = player_hp;

	/* calc hp color */
	int r = std::fmin( ( 510 * ( 100 - player_hp ) ) / 100, 255 );
	int g = std::fmin( ( 510 * player_hp ) / 100, 255 );

	int h = rect.w - 2;
	int fill = ( int )std::round( prev_player_hp[ index ] * h / 100.f );

	/* health color */
	evo::col_t health_color{ };
	if ( evo::_settings->change_by_visibility && evo::_settings->customhealthbar ) {
		health_color = this->spotted( entity, local_player, local_index, index ) ? _render->to_main_color( _settings->healthbar ).modify_alpha( this->esp_alpha[ index ] ) : _render->to_main_color( _settings->healthbari ).modify_alpha( this->esp_alpha[ index ] );
	} else if ( evo::_settings->customhealthbar ) { 
		health_color = _render->to_main_color( _settings->healthbar ).modify_alpha( this->esp_alpha[ index ] );
	} else {
		health_color = evo::col_t( r, g, 0 ).modify_alpha( this->esp_alpha[ index ] );
	}

	/* backround */
	evo::_render->add_rect_filled( rect.x - 6, rect.y + 1, 4, rect.w - 2, evo::col_t( 0, 0, 0, this->esp_alpha[ index ] * 0.5 ), 0 );
	evo::_render->add_rect_filled( rect.x - 5, rect.y + 2 + ( h - fill ), 2, fill - 2, health_color, 0 );

	if ( player_hp < 98 ) {
		evo::_render->add_text( rect.x - ( ( player_hp > 10 ) ? 8 : 7 ),
								rect.y + 1 + ( ( h - fill ) - 7 ), evo::col_t().modify_alpha( this->esp_alpha[ index ] ), evo::fonts_t::_default_2, std::to_string( player_hp ).c_str(), evo::font_flags_t::outline );
	}
}

void evo::esp_t::ammo_bar( const c_entity& local_player, const c_entity& entity, ImVec4 rect, int local_index, int index ) { 
	int bullets = entity.player_pawn.clip;

	evo::col_t health_color = evo::col_t( 20, 20, 200 );


}

void evo::esp_t::render_esp( const c_entity& local_player, const c_entity& entity, ImVec4 rect, int local_index, int index ) { 
	/* 
		dormant shit: 
			xref: entity.player_pawn.dormant

		spotted shit:
			xref: this->spotted( entity, local_player, local_index, index )
	*/

	print_with_data_scoped( "b: " + std::to_string( local_player.player_pawn.clip ) + ", m: " + std::to_string( local_player.player_pawn.max_clip ) )

	/* setup dormancy */
	this->setup_alpha( local_player, entity, local_index, index ); 

	if ( evo::_settings->bounding_box ) {
		this->bounding_box( local_player, entity, rect, local_index, index );
	}

	if ( evo::_settings->name_esp ) {
		this->render_name( local_player, entity, rect, local_index, index );
	}

	if ( evo::_settings->health_bar ) {
		this->health_bar( local_player, entity, rect, local_index, index );
	}
}

evo::macros::vec4_t evo::esp_t::get_player_bounding_box( const c_entity& entity ) {
	bone_pos head = entity.get_bone( ).bone_pos_list[ bone_index::head ];

	vec2_t size, pos;
	size.y = ( entity.player_pawn.screen_pos.y - head.screen_pos.y ) * 1.26;
	size.x = size.y * 0.6;

	// retarded 
	pos = vec2_t( entity.player_pawn.screen_pos.x - size.x / 2, head.screen_pos.y - size.y * 0.08 );

	return ImVec4{ pos.x + 2, pos.y - 5, size.x - 4, size.y };
}