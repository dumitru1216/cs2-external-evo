#include "../../../inc.hpp"

/* handlers and stuff */
DWORD ent_handler = 0;
DWORD64 list_avaible_entries = 0;
DWORD64 entry_pawn_address = 0;
evo::c_entity entity;
bool allow_shot = false;
/* handlers and stuff */

void evo::trigger_t::release_mouse_event( ) { 
	/* we can now shot so lets do it */
	std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) ); /* add a custom delay and more */
	mouse_event( MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 ); /* release shot event */
}

void evo::trigger_t::run_trigger( const evo::c_entity& local_entity ) { 
	/* read memory of ent index */
	if ( !_proc_manager.read_memory<DWORD>( local_entity.player_pawn.address + offsets::pawn::ent_index, ent_handler ) ) {
#ifdef read_data_dbg
		print_with_data_scoped( "trigger_t::run_trigger -> error -> no memory [ 0 ]" );
#endif // read_data_dbg
		return;
	}

	if ( ent_handler == -1 ) {
#ifdef read_data_dbg
		print_with_data_scoped( "trigger_t::run_trigger -> error -> idx -1 ( invalid ) [ 1 ]" );
#endif // read_data_dbg
		return;
	}
}
