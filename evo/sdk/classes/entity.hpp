#pragma once

namespace evo {
	struct c_utlvector {
		DWORD64 count = 0;
		DWORD64 data = 0;
	};

	class ccs_player_controler {
	public:
		DWORD64 address{ 0 };
		DWORD pawn{ 0 };

		int health{ 0 }, alive{ 0 }, team_id{ 0 };
		std::string player_name{};
	public:
		__forceinline int _health( ) {
			health = mem::scan_memory<int>( "ccs_player_controler::health", this->address, 
												 offets::c_base_entity::health, this->health );
		}

		__forceinline bool _alive( ) {
			/* we can do this shit rlly easy */
			return ( this->_health( ) > 0 );
		}

		__forceinline DWORD64 get_pawn_address( ) {
			DWORD64 entity_pawn_list_entry = 0;
			DWORD64 entity_pawn_address = 0;

			if ( !mem::scan_memory<DWORD>( "ccs_player_controler::player_pawn", this->address, 
												offets::c_base_player_controler::player_pawn, this->pawn ) ) {
				return 0;
			}

			if ( !_proc_manager.read_memory<DWORD64>( _address->get_entity_list_address( ), entity_pawn_list_entry ) ) {
				//print_with_data( "sa" );
				return 0;
			}

			if ( !_proc_manager.read_memory<DWORD64>( entity_pawn_list_entry + 0x10 + 8 * ( ( this->pawn & 0x7FFF ) >> 9 ), entity_pawn_list_entry ) ) {

				return 0;
			}

			if ( !_proc_manager.read_memory<DWORD64>( entity_pawn_list_entry + 0x78 * ( this->pawn & 0x1FF ), entity_pawn_address ) ) {

				return 0;
			}
		}
	};

	class ccs_player_pawn {
	public:
		DWORD64 address{ 0 };
	public:

	};

	class c_entity {
	public:
		ccs_player_controler controller;
		ccs_player_pawn player_pawn;
	public:
		__forceinline bool update_controller( const DWORD64& player_controler ) {
			if ( player_controler == 0 ) {
#if 1
				/* debug */
				printf( "[evo] player controller is 0" );
#endif 
				return false;
			}

			this->controller.address = player_controler;

#if 0
			/* debug */
			printf( "[evo] c_entity::update_controller ran succesfully" );
#endif
			return true;
		}

		__forceinline bool update_pawn( const DWORD64& player_pawn_address ) {

		}
	};
}