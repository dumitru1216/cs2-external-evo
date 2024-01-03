#include "../../../inc.hpp"
#include "shots_hitsound.hpp"
#pragma comment(lib, "Winmm.lib")

void evo::shots_t::hitsound( const c_entity& entity ) {
	static int prev_total_hits;
	int total_hits;
	uintptr_t bullet_services;

	_proc_manager.read_memory( entity.player_pawn.address + 0x16B8, bullet_services );
	_proc_manager.read_memory( bullet_services + 0x40, total_hits );

	if ( total_hits != prev_total_hits ) {
		if ( total_hits == 0 && prev_total_hits != 0 ) { } else {
			/*xref
				    vector < const char* > hitsound = { 
						"Neverlose",
                        "Skeet",
                        "Primordial",
                        "Sound 1",
                        "Sound 2",
						"Toy duck"
								};
			*/
			switch ( _settings->hitsound_type ) {
				case 0:
				{
					PlaySoundA( reinterpret_cast< char* > ( neverlose_sound ), NULL, SND_ASYNC | SND_MEMORY );
				} break;
				case 1:
				{
					PlaySoundA( reinterpret_cast< char* > ( skeet_sound ), NULL, SND_ASYNC | SND_MEMORY );
				} break;
				case 2:
				{
					PlaySoundA( reinterpret_cast< char* > ( primordial_sound ), NULL, SND_ASYNC | SND_MEMORY );
				} break;
				case 3:
				{
					PlaySoundA( reinterpret_cast< char* > ( cock_sound ), NULL, SND_ASYNC | SND_MEMORY );
				} break;
				case 4:
				{
					PlaySoundA( reinterpret_cast< char* > ( bepis_sound ), NULL, SND_ASYNC | SND_MEMORY );
				} break;
				case 5:
				{
					PlaySoundA( reinterpret_cast< char* > ( ratamac ), NULL, SND_ASYNC | SND_MEMORY );
				} break;
			}

			
		}
	}
	prev_total_hits = total_hits;
}
