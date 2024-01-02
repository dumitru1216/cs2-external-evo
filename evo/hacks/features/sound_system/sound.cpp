#include "../../../inc.hpp"
#include "../../../sdk/animation_system/animation_system.hpp"

void render_filled_3d_circle( const evo::vec3_t& origin, float radius, evo::col_t color ) {
	static constexpr float pi = 3.14159265358979323846f;

	static constexpr float Step = pi * 2.0f / 60;
	std::vector<ImVec2> points;
	for ( float lat = 0.f; lat <= pi * 2.0f; lat += Step ) {
		const auto& point3d = evo::vec3_t( sin( lat ), cos( lat ), 0.f ) * radius;
		evo::vec2_t point2d;
		if ( evo::_address->view.world_to_screen( origin + point3d, point2d ) )
			points.push_back( ImVec2( point2d.x, point2d.y ) );
	}
	ImGui::GetBackgroundDrawList( )->AddConvexPolyFilled( points.data( ), points.size( ), color.convert( ) );
}

void render_3d_circle( const evo::vec3_t& origin, float radius, evo::col_t color ) {
	static constexpr float pi = 3.14159265358979323846f;
	static constexpr float Step = pi * 2.0f / 60;

	std::vector<ImVec2> points;
	for ( float lat = 0.f; lat <= pi * 2.0f; lat += Step ) {
		const auto& point3d = evo::vec3_t( sin( lat ), cos( lat ), 0.f ) * radius;
		evo::vec2_t point2d;
		if ( evo::_address->view.world_to_screen( origin + point3d, point2d ) )
			points.push_back( ImVec2( point2d.x, point2d.y ) );
	}

	if ( !points.empty( ) ) {
		points.push_back( points.front( ) );
		ImGui::GetBackgroundDrawList( )->AddPolyline( points.data( ), points.size( ), color.convert( ), false, 1.0f );
	}
}

void evo::sound_info::push_sound( const c_entity& entity ) {
	// game::m_flEmitSoundTime
	float smth3; // will we need to iterate?
	_proc_manager.read_memory<float>( entity.player_pawn.address + 0x1404, smth3 );

	static float main = smth3;
	
	if ( main != smth3 ) {
#if 0
		printf( "mem[0]\n" );
#endif
		/* should pushback */
		this->s_info.push_back( sound_info_t{ entity.player_pawn.vec_origin, true } );

		/* reupdate */
		main = smth3;
	}

	/* draw */
	for ( int i = 0; i < this->s_info.size( ); i++ ) {
		auto animation = animation_controller.get( "soundinfo" + std::to_string( i ) + animation_controller.current_child );
		animation.adjust( animation.value + 3.f * animation_controller.get_min_deltatime( 0.1f ) * ( this->s_info[i].has_changed ? 1.f : -1.f ) );

		if ( animation.value >= 0.99f )
			this->s_info[ i ].has_changed = false;

		render_3d_circle( this->s_info[ i ].player_origin, 35 * animation.value, evo::col_t( ) );

		if ( i >= 60 ) {
#if 0
			printf( "mem[1]" );
#endif
			this->s_info.erase( this->s_info.begin( ), this->s_info.begin( ) + 51 );

#if 0
			print_with_data_scoped( "size: " + std::to_string( this->s_info.size( ) ) )
#endif
		}
	}
}

void evo::sound_info::push_sound2( const c_entity& entity, int idx ) { /* use that for enemy */

	// game::m_flEmitSoundTime
	float smth3; // will we need to iterate?
	_proc_manager.read_memory<float>( entity.player_pawn.address + 0x1404, smth3 );

	static float main[ 64 ]{smth3};

	if ( main[idx] != smth3) {
#if 0
		printf( "mem[0]\n" );
#endif
		/* should pushback */
		this->s_info.push_back( sound_info_t{ entity.player_pawn.vec_origin, true } );

		/* reupdate */
		main[idx] = smth3;
	}

	/* draw */
	for ( int i = 0; i < this->s_info.size( ); i++ ) {
		auto animation = animation_controller.get( "soundinfo" + std::to_string( i ) + animation_controller.current_child );
		animation.adjust( animation.value + 3.f * animation_controller.get_min_deltatime( 0.1f ) * ( this->s_info[ i ].has_changed ? 1.f : -1.f ) );

		if ( animation.value >= 0.99f )
			this->s_info[ i ].has_changed = false;

		render_3d_circle( this->s_info[ i ].player_origin, 35 * animation.value, evo::col_t( ) );

		if ( i >= 60 ) {
#if 0
			printf( "mem[1]" );
#endif
			this->s_info.erase( this->s_info.begin( ), this->s_info.begin( ) + 51 );

#if 0
			print_with_data_scoped( "size: " + std::to_string( this->s_info.size( ) ) )
#endif
		}
	}
}
