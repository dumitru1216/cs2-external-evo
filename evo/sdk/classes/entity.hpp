#pragma once

namespace evo {
	struct c_utlvector {
		DWORD64 count = 0;
		DWORD64 data = 0;
	};

	class ccs_player_controler {
	public:
		DWORD64 address{ 0 };
		int health{ 0 }, alive{ 0 }, team_id{ 0 };
		DWORD pawn{ 0 };
		std::string player_name{};
	public:
		__forceinline bool _health( ) {
			return mem::scan_memory<int>( "ccs_player_controler::health", this->address,
										  offsets::c_base_entity::health, this->health );
		}

		__forceinline bool _alive( ) {
			/* we need this too whatever */
			return mem::scan_memory<int>( "ccs_player_controler::alive", this->address,
											offsets::c_base_player_controler::pawn_alive, this->alive );
		}

		__forceinline bool _team_id( ) {
			/* we need this too whatever */
			return mem::scan_memory<int>( "ccs_player_controler::team_id", this->address,
										  offsets::c_base_entity::team_id, this->team_id );
		}

		__forceinline bool _player_name( ) {
			char buffer[ MAX_PATH ]{};

			if ( !_proc_manager.read_memory( this->address + offsets::c_base_player_controler::player_name, buffer, MAX_PATH ) )
				return false;

			this->player_name = buffer;
			if ( this->player_name.empty( ) )
				this->player_name = "no-name";

			return true;
		}

		__forceinline DWORD64 get_pawn_address( ) {
			DWORD64 entity_pawn_list_entry = 0;
			DWORD64 entity_pawn_address = 0;

			if ( !mem::scan_memory<DWORD>( "ccs_player_controler::player_pawn", this->address, 
												offsets::c_base_player_controler::player_pawn, this->pawn ) ) {
				return 0;
			}

			if ( !_proc_manager.read_memory<DWORD64>( _address->get_entity_list_address( ), entity_pawn_list_entry ) ) {
#ifdef read_data_dbg 
				print_with_data_scoped( "error get_pawn_address::get_entity_list_address" );
#endif
				return 0;
			}

			if ( !_proc_manager.read_memory<DWORD64>( entity_pawn_list_entry + 0x10 + 8 * ( ( this->pawn & 0x7FFF ) >> 9 ), entity_pawn_list_entry ) ) {
#ifdef read_data_dbg 
				print_with_data_scoped( "error get_pawn_address::entity_pawn_list_entry + 0x10" );
#endif
				return 0;
			}

			if ( !_proc_manager.read_memory<DWORD64>( entity_pawn_list_entry + 0x78 * ( this->pawn & 0x1FF ), entity_pawn_address ) ) {
#ifdef read_data_dbg 
				print_with_data_scoped( "error get_pawn_address::entity_pawn_list_entry + 0x78" );
#endif
				return 0;
			}

			return entity_pawn_address;
		}
	};

	class ccs_player_pawn {
	public:
		DWORD64 address{ 0 };

		/* get data in there */
		int health{};
	public:
		__forceinline int _health( ) {
			return mem::scan_memory<int>( "c_player_pawn::health", this->address, offsets::pawn::health, this->health );
		}
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
				printf( "[evo] player controller is 0\n" );
#endif 
				return false;
			}

			this->controller.address = player_controler;

			if ( !this->controller._alive( ) ) {
#if 1
				/* debug */
				printf( "[evo] error controller._alive\n" );
#endif 
				return false;
			}

			if ( !this->controller._health( ) ) {
#if 1
				/* debug */
				printf( "[evo] error controller._alive\n" );
#endif 
				return false;
			}

			if ( !this->controller._team_id( ) ) {
#if 1
				/* debug */
				printf( "[evo] error controller._alive\n" );
#endif 
				return false;
			}


			if ( !this->controller._player_name( ) ) {
#if 1
				/* debug */
				printf( "[evo] error controller._alive\n" );
#endif 
				return false;
			}


			/* get pawn address */
			this->player_pawn.address = this->controller.get_pawn_address( );
#if 0
			/* debug */
			printf( "[evo] c_entity::update_controller ran succesfully\n" );
#endif
			return true;
		}

		__forceinline bool update_pawn( const DWORD64& player_pawn_address ) {
			if ( player_pawn_address == 0 ) {
#if 1
				/* debug */
				printf( "[evo] player controller is 0\n" );
#endif 
				return false;
			}

			/* get pawn address */
			this->player_pawn.address = player_pawn_address;

			return true;
		}
	};
}