#include "hacks_ctx.hpp"
#include "../../inc.hpp"

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

		if ( _settings->aimbot ) {
			switch ( _settings->a_activationz_type ) {
				case 0: /* hold */
				{
					if ( GetAsyncKeyState( _input_key->get_bind_id( _settings->a_triggerkey ) ) ) {
						_legit->run_aimbot( entity, local_player, local_player.player_pawn.camera_pos, i, local_player_index );
					}
				} break;
				case 1: /* toggle */
				{
					if ( GetKeyState( _input_key->get_bind_id( _settings->a_triggerkey ) ) ) {
						_legit->run_aimbot( entity, local_player, local_player.player_pawn.camera_pos, i, local_player_index );
					}
				} break;
				case 2: /* always on */
				{
					_legit->run_aimbot( entity, local_player, local_player.player_pawn.camera_pos, i, local_player_index );
				} break;
			}
		}

		_rage->run_aimbot( entity, local_player, local_player.player_pawn.camera_pos, i, local_player_index );

		ImVec4 rect = evo::_esp->get_player_bounding_box( entity );
		evo::_esp->render_esp( local_player, entity, rect, local_player_index, i );
	}

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
