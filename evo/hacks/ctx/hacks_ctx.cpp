#include "hacks_ctx.hpp"
#include "../../inc.hpp"
#include "../../sdk/animation_system/animation_system.hpp"

// this is just a test

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

evo::c_entity* get_entity( int index ) { // just leave it like that
	evo::c_entity* ent = ( evo::c_entity* )( evo::_address->get_entity_list_entry() + 0x78 * ( index + 1 ) );
	return ent;
}

void evo::hacks_t::run( ) { 
	/* update matrix */
	if ( !_proc_manager.read_memory( evo::_address->get_matrix_address( ), evo::_address->view.matrix, 64 ) ) {
#ifdef read_data_dbg
		print_with_data_scoped( "hacks_t::run -> error -> read_memory::get_matrix_address" );
#endif // read_data_dbg
		return;
	}

	/* update entity list entry */
	evo::_address->update_entity_list_entry( );

	/* local player stuff */
	DWORD64 local_player_adr = 0;
	DWORD64 local_pawn_adr = 0;
	if ( !_proc_manager.read_memory( evo::_address->get_local_controller_address( ), local_player_adr ) ) {
#ifdef read_data_dbg
		print_with_data_scoped( "hacks_t::run -> error -> read_memory::get_local_controller_address" );
#endif // read_data_dbg
		return;
	}

	if ( !_proc_manager.read_memory( evo::_address->get_local_pawn_address( ), local_pawn_adr ) ) {
#ifdef read_data_dbg
		print_with_data_scoped( "hacks_t::run -> error -> read_memory::get_local_pawn_address" );
#endif // read_data_dbg
		return;
	}

	evo::c_entity local_player;
	static int local_player_index = 1;

	if ( !local_player.update_controller( local_player_adr ) ) {
#ifdef read_data_dbg
		print_with_data_scoped( "hacks_t::run -> error -> update_controller::local_player_adr" );
#endif // read_data_dbg
		return;
	}

	if ( !local_player.update_pawn( local_pawn_adr ) ) {
#ifdef read_data_dbg
		print_with_data_scoped( "hacks_t::run -> error -> update_pawn::local_pawn_adr" );
#endif // read_data_dbg
		return;
	}


	/* loop between entity */
	for ( int i = 0; i < 64; i++ ) {
		c_entity entity;
		DWORD64 entity_address = 0;

		if ( !_proc_manager.read_memory<DWORD64>( evo::_address->get_entity_list_entry( ) + ( i + 1 ) * 0x78, entity_address ) ) {
#ifdef read_data_dbg1
			print_with_data_scoped( "hacks_t::run -> error -> loop::get_entity_list_entry" );
#endif // read_data_dbg
			continue;
		}

		if ( entity_address == local_player.controller.address ) {
			local_player_index = i;
			continue;
		}

		if ( !entity.update_controller( entity_address ) ) {
#ifdef read_data_dbg1
			print_with_data_scoped( "hacks_t::run -> error -> update_controller::entity_address" );
#endif // read_data_dbg
			continue;
		}

		if ( !entity.update_pawn( entity.player_pawn.address ) ) {
#ifdef read_data_dbg
			print_with_data_scoped( "hacks_t::run -> error -> update_pawn::entity.player_pawn.address" );
#endif // read_data_dbg
			continue;
		}

		if ( entity.controller.team_id == local_player.controller.team_id ) {
			continue;
		}

		if ( !entity.in_screen( ) ) {
			continue;
		}

		_legit->run_aimbot( entity, local_player, local_player.player_pawn.camera_pos, i, local_player_index );
		_rage->run_aimbot( entity, local_player, local_player.player_pawn.camera_pos, i, local_player_index );

		ImVec4 rect = evo::_esp->get_player_bounding_box( entity );
		evo::_esp->render_esp( local_player, entity, rect, local_player_index, i );
	}

	/* loop between other entity */
	for ( int i_smoke = 64; i_smoke < 1024; i_smoke++ ) {
		uintptr_t ent = ( uintptr_t )get_entity( i_smoke );

		if ( ent == 0 ) {
#ifdef read_data_dbg
			print_with_data_scoped( "hacks_t::run2 -> error -> loop::continue - 1024 [ 0 ]" );
#endif // read_data_dbg
			continue;
		}

		evo::_esp->change_smoke_color( ent );
		evo::_esp->remove_smoke( ent );
	}

	_legit->draw_aimbot_fov( );

	/*
		scoped: _proc_manager.read_memory<bool>( local_player.player_pawn.address + 0x13A8, smth );
		defusing: _proc_manager.read_memory<bool>( local_player.player_pawn.address + 0x13B0, smth );
		grabbing_hostage: _proc_manager.read_memory<bool>( local_player.player_pawn.address + 0x13B1, smth );
		gungame_imunity: _proc_manager.read_memory<bool>( local_player.player_pawn.address + 0x13C4, smth );
	*/


	bool is = true;
	bool smth;
	float smth3;
	DWORD64 smth2;
	_proc_manager.read_memory<float>( local_player.player_pawn.address + 0x1404, smth3 );

	static float sound = smth3;
	static bool diff = false;

	if ( smth3 != sound ) {
		printf( "diff \n" );
		sound = smth3;

		diff = true;
	}

	/* run animation */
	auto animation = animation_controller.get( "animation_fov" + std::to_string( 0 ) + animation_controller.current_child );
	animation.adjust( animation.value + 3.f * animation_controller.get_min_deltatime( 0.3f ) * ( diff ? 1.f : -1.f ) );

	if ( animation.value >= 0.99 )
		diff = false;

	//_render->add_circle( evo::vec2_t( 1920 / 2, 1080 / 2 ), ( ( 20 * animation.value ) * 10 ), _render->to_main_color( _settings->fov_color ) );
	render_filled_3d_circle( local_player.player_pawn.vec_origin, 20 * animation.value, evo::col_t( ) );

	if ( GetAsyncKeyState( VK_F2 ) )
		print_with_data_scoped( "s: " + std::to_string( smth3 )  )

	//if ( smth ) {
	//	printf( "yes\n" );
	//} else {
	//	printf( "no\n" );
	//}
	
	/* trigger bot */
	if ( _settings->triggerbot ) {
		switch ( _settings->activationz_type ) {
			case 0: /* hold */
			{
				if ( GetAsyncKeyState( _input_key->get_bind_id( _settings->triggerkey ) ) ) {
					_triggerbot->run_trigger( local_player );
				}
			} break;
			case 1: /* toggle */
			{
				if ( GetKeyState( _input_key->get_bind_id( _settings->triggerkey ) ) ) {
					_triggerbot->run_trigger( local_player );
				}
			} break;
			case 2: /* always on */
			{
				_triggerbot->run_trigger( local_player );
			} break;
		}
	}
}
