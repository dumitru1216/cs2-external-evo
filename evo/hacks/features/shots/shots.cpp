#include "../../../inc.hpp"
#include "shots_hitsound.hpp"

void evo::shots_t::hitsound( const c_entity& entity ) {
	static int prev_total_hits;
	int total_hits;
	uintptr_t bullet_services;

	_proc_manager.read_memory( entity.player_pawn.address + 0x16B8, bullet_services );
	_proc_manager.read_memory( bullet_services + 0x40, total_hits );

	if ( total_hits != prev_total_hits ) {
		if ( total_hits == 0 && prev_total_hits != 0 ) {
			// `totalHits` changed from non-zero to zero, do not play hitsound
		} else {
			// Play the HitSound

			PlaySoundA( reinterpret_cast< char* > ( neverlose_sound ), NULL, SND_ASYNC | SND_MEMORY );
		}
	}
	prev_total_hits = total_hits;
}
