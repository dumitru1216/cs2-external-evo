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
	DWORD local_player_adr, local_pawn_adr;
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
}
