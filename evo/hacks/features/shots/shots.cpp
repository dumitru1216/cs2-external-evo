#include "../../../inc.hpp"
#include "shots_hitsound.hpp"
#pragma comment(lib, "Winmm.lib")

void evo::shots_t::hitsound( const c_entity& entity ) {
	if ( !_settings->hitsound )
		return;

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
						"Toy duck",
						"Bell 1",
						"Bell 2",
						"Button",
						"Pop",
						"Wow"
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
				case 6:
				{
					PlaySoundA( reinterpret_cast< char* > ( bell1 ), NULL, SND_ASYNC | SND_MEMORY );
				} break;
				case 7:
				{
					PlaySoundA( reinterpret_cast< char* > ( bell2 ), NULL, SND_ASYNC | SND_MEMORY );
				} break;
				case 8:
				{
					PlaySoundA( reinterpret_cast< char* > ( button_snd ), NULL, SND_ASYNC | SND_MEMORY );
				} break;
				case 9:
				{
					PlaySoundA( reinterpret_cast< char* > ( popsnd ), NULL, SND_ASYNC | SND_MEMORY );
				} break;
				case 10:
				{
					PlaySoundA( reinterpret_cast< char* > ( wowsnd ), NULL, SND_ASYNC | SND_MEMORY );
				} break;
			}

			
		}
	}
	prev_total_hits = total_hits;
}

/* xref:
	https://github.com/aiuka/neverlose-cs2/Cheat/Visuals/Hitmarkers.cpp#L20
*/
void evo::shots_t::hitmarker( const c_entity& entity, const c_entity& local ) {
	if ( local.player_pawn.health <= 0 ) { /* clear these mothercukers */
		if ( !this->impacts.empty( ) ) {
			this->impacts.clear( );
		}

		if ( !this->hitmarkers.empty( ) ) {
			this->hitmarkers.clear( );
		}

		/* do not run multiple times */
		return;
	}

	/* xref:
		https://github.com/aiuka/neverlose-cs2/Cheat/Visuals/Hitmarkers.cpp#L25
	*/
	std::vector<hitmarker_info>::iterator p_iterator;
	for ( p_iterator = this->hitmarkers.begin( ); p_iterator != this->hitmarkers.end( ); ) {
		static auto line_size = 6;

		/* xref:
			https://github.com/aiuka/neverlose-cs2/Cheat/Visuals/Hitmarkers.cpp#L28

			lazyness globalvar-frametime = 0.015
		*/

		const auto step = 255.f / 1.f * 0.015;
		const auto step_move = 30.f / 1.5f * 0.015;
		const auto multiplicator = 0.3f;

		if ( p_iterator->pImpact.time + 0.5f <= 0.015 /* curtime */ && p_iterator->alpha > 0.0f )
			p_iterator->alpha -= step;

		p_iterator->moved -= step_move;

		if ( p_iterator->pImpact.time + 0.5f <= 0.015 /* curtime */ && p_iterator->alpha2 > 0 )
			p_iterator->alpha2 -= 5;

		if ( p_iterator->alpha <= 0 && p_iterator->alpha2 <= 0 ) {
			p_iterator = hitmarkers.erase( p_iterator );
			continue;
		}

		/* xref:
			https://github.com/aiuka/neverlose-cs2/Cheat/Visuals/Hitmarkers.cpp#L125
		*/
		++p_iterator;
	}
}
