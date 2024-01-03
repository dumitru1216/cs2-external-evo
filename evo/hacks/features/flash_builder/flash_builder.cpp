#include "../../../inc.hpp"

void evo::flash_builder::run_flash_builder( const c_entity& entity ) { 
	if ( !_settings->flash_builder )
		return;

	if ( !_settings->remove_full_flash ) {

	} else {
		// xref: m_flFlashBangTime 
		float fl = 0.f; 
		_proc_manager.write_memory<float>( entity.player_pawn.address + 0x145C, fl );
	}

	/* xref
	
	

		/* modify flash alpha 
		* 		float fl = 125.f;
				_proc_manager.write_memory<float>( local_player.player_pawn.address + 0x146C, fl );
		*

		// flashbang time - 5s max
		_proc_manager.write_memory<float>( local_player.player_pawn.address + 0x1470, fl );
	*/
}
