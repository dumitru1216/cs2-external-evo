#include "../../../inc.hpp"

void evo::trigger_t::release_mouse_event( ) { 
	/* we can now shot so lets do it */
	std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) ); /* add a custom delay and more */
	mouse_event( MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 ); /* release shot event */
}

void evo::trigger_t::run_trigger( const evo::c_entity& local_entity ) { 
	/* read memory of ent index */
	if ( !_proc_manager.read_memory<DWORD>( local_entity.player_pawn.address + ) )
}
