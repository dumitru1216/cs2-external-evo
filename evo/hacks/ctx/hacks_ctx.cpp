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

	print_with_data_scoped( "local health " + std::to_string( local_player.player_pawn.he ) );

	/* loop between entity */
	{
		
	}
}
