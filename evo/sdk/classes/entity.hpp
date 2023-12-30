#pragma once

namespace evo {
	struct c_utlvector {
		DWORD64 count = 0;
		DWORD64 data = 0;
	};

	enum cs_weapon_type : std::uint32_t {
		weapon_type_knife = 0,
		weapon_type_pistol = 1,
		weapon_type_submachinegun = 2,
		weapon_type_rifle = 3,
		weapon_type_shotgun = 4,
		weapon_type_sniper_rifle = 5,
		weapon_type_machinegun = 6,
		weapon_type_c4 = 7,
		weapon_type_taser = 8,
		weapon_type_grenade = 9,
		weapon_type_equipment = 10,
		weapon_type_stackable_item = 11,
		weapon_type_fists = 12,
		weapon_type_breach_charge = 13,
		weapon_type_bump_mine = 14,
		weapon_type_tablet = 15,
		weapon_type_melee = 16,
		weapon_type_shield = 17,
		weapon_type_zone_repulsor = 18,
		weapon_type_unknown = 19,
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

			if ( !_proc_manager.read_memory( this->address + offsets::c_base_player_controler::player_name, buffer, MAX_PATH ) ) {
#ifdef read_data_dbg
				print_with_data_scoped( "ccs_player_controler::_player_name -> error -> no memory" );
#endif // read_data_dbg
				return false;
			}

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
		DWORD64 address{ 0 }, spotted_by_mask{};

		/* get data in there */
		int health{}, dormant{}, clip{}, max_clip{},
			defuser{}, hemlet{}, heavy_ar{};

		cs_weapon_type weapon_type{};
		std::string weapon_name{};

		bone_t bone_data{};

		vec2_t screen_pos{};
		vec3_t pos{}, vec_origin{};
	public:
		__forceinline bool _health( ) {
			return mem::scan_memory<int>( "c_player_pawn::health", this->address, offsets::pawn::health, this->health );
		}

		__forceinline bool _pos( ) {
			return mem::scan_memory<vec3_t>( "c_player_pawn::pos", this->address, offsets::pawn::vec_old_origin, this->pos );
		}

		__forceinline bool _spotted( ) {
			return mem::scan_memory<DWORD64>( "c_player_pawn::spotted", this->address, offsets::pawn::spotted, this->spotted_by_mask );
		}

		__forceinline bool _defuser( ) {
			// item services
			// 0x10B0
			DWORD64 new_address = 0;

			if ( !_proc_manager.read_memory<DWORD64>( this->address + offsets::item_services::item_services_pawn, new_address ) ) {
#ifdef read_data_dbg
				print_with_data_scoped( "ccs_player_pawn::item_services_pawn -> error -> no memory" );
#endif // read_data_dbg
				return false;
			}

			return mem::scan_memory<int>( "c_player_pawn::has_defuser", new_address, offsets::item_services::has_defuser, this->defuser );
		}

		__forceinline bool _hemlet( ) {
			// item services
			// 0x10B0
			DWORD64 new_address = 0;

			if ( !_proc_manager.read_memory<DWORD64>( this->address + offsets::item_services::item_services_pawn, new_address ) ) {
#ifdef read_data_dbg
				print_with_data_scoped( "ccs_player_pawn::item_services_pawn -> error -> no memory" );
#endif // read_data_dbg
				return false;
			}

			return mem::scan_memory<int>( "c_player_pawn::pos", new_address, offsets::item_services::has_hemlet, this->hemlet );
		}

		__forceinline bool _heavyar( ) {
			// item services
			// 0x10B0
			DWORD64 new_address = 0;

			if ( !_proc_manager.read_memory<DWORD64>( this->address + offsets::item_services::item_services_pawn, new_address ) ) {
#ifdef read_data_dbg
				print_with_data_scoped( "ccs_player_pawn::item_services_pawn -> error -> no memory" );
#endif // read_data_dbg
				return false;
			}

			return mem::scan_memory<int>( "c_player_pawn::spotted", new_address, offsets::item_services::has_heavy_armor, this->heavy_ar );
		}

		__forceinline bool _clip( ) {
			DWORD64 clipping_weapon = 0;
			DWORD64 weapon_data = 0;

			if ( !_proc_manager.read_memory<DWORD64>( this->address + offsets::c_base_weapon::clipping_weapon, clipping_weapon ) ) {
#ifdef read_data_dbg
				print_with_data_scoped( "ccs_player_pawn::clipping_weapon -> error -> no memory" );
#endif // read_data_dbg
				return false;
			}

			return mem::scan_memory<int>( "c_player_pawn::clip", clipping_weapon, offsets::c_base_weapon::clip_1, this->clip );
		}

		__forceinline bool _weapon_name( ) {
			DWORD64 clipping_weapon = 0;
			DWORD64 weapon_data = 0;

			DWORD64 weapon_name_address = 0;
			char buffer[ 40 ]{};

			weapon_name_address = _proc_manager.trace_address( this->address + offsets::c_base_weapon::clipping_weapon, { 0x10, 0x20, 0x0 } );
			if ( weapon_name_address == 0 )
				return false;

			if ( !_proc_manager.read_memory( weapon_name_address, buffer, 40 ) )
				return false;

			this->weapon_name = std::string( buffer );
			std::size_t index = this->weapon_name.find( "_" );
			if ( index == std::string::npos || this->weapon_name.empty( ) ) {
				this->weapon_name = "Weapon_None";
			} else {
				this->weapon_name = this->weapon_name.substr( index + 1, this->weapon_name.size( ) - index - 1 );
			}


#if 0
			if ( !_proc_manager.read_memory<DWORD64>( this->address + offsets::c_base_weapon::clipping_weapon, clipping_weapon ) ) {
#ifdef read_data_dbg
				print_with_data_scoped( "ccs_player_pawn::clipping_weapon::_weapon_name -> error -> no memory" );
#endif // read_data_dbg
				return false;
			}

			if ( !_proc_manager.read_memory<DWORD64>( clipping_weapon + offsets::c_base_weapon::wpn_data_ptr, weapon_data ) ) {
#ifdef read_data_dbg
				print_with_data_scoped( "ccs_player_pawn::clipping_weapon::_weapon_name -> error -> no memory" );
#endif // read_data_dbg
				return false;
			}

			char buffer[ MAX_PATH ]{};

			if ( !_proc_manager.read_memory( weapon_data + offsets::c_base_weapon::zs_name, buffer, MAX_PATH ) ) {
#ifdef read_data_dbg
				print_with_data_scoped( "ccs_player_controler::_player_name -> error -> no memory" );
#endif // read_data_dbg
				return false;
			}

			this->weapon_name = buffer;
			if ( this->weapon_name.empty( ) )
				this->weapon_name = "no-name";
#endif
			return true;

			//return mem::scan_memory<std::string>( "c_player_pawn::sz_name", weapon_data, offsets::c_base_weapon::zs_name, this->weapon_name );
		}

		__forceinline bool _max_clip( ) {
			DWORD64 clipping_weapon = 0;
			DWORD64 weapon_data = 0;

			if ( !_proc_manager.read_memory<DWORD64>( this->address + offsets::c_base_weapon::clipping_weapon, clipping_weapon ) ) {
#ifdef read_data_dbg
				print_with_data_scoped( "ccs_player_pawn::clipping_weapon::_max_clip -> error -> no memory" );
#endif // read_data_dbg
				return false;
			}

			if ( !_proc_manager.read_memory<DWORD64>( clipping_weapon + offsets::c_base_weapon::wpn_data_ptr, weapon_data ) ) {
#ifdef read_data_dbg
				print_with_data_scoped( "ccs_player_pawn::clipping_weapon::_max_clip -> error -> no memory" );
#endif // read_data_dbg
				return false;
			}

			return mem::scan_memory<int>( "c_player_pawn::max_clip_1", weapon_data, offsets::c_base_weapon::max_clip, this->max_clip );
		}

		__forceinline bool _weapon_type( ) {
			DWORD64 clipping_weapon = 0;
			DWORD64 weapon_data = 0;

			if ( !_proc_manager.read_memory<DWORD64>( this->address + offsets::c_base_weapon::clipping_weapon, clipping_weapon ) ) {
#ifdef read_data_dbg
				print_with_data_scoped( "ccs_player_pawn::clipping_weapon::_max_clip -> error -> no memory" );
#endif // read_data_dbg
				return false;
			}

			if ( !_proc_manager.read_memory<DWORD64>( clipping_weapon + offsets::c_base_weapon::wpn_data_ptr, weapon_data ) ) {
#ifdef read_data_dbg
				print_with_data_scoped( "ccs_player_pawn::clipping_weapon::_max_clip -> error -> no memory" );
#endif // read_data_dbg
				return false;
			}

			return mem::scan_memory<cs_weapon_type>( "c_player_pawn::weapon_type", weapon_data, offsets::c_base_weapon::weapon_type, this->weapon_type );
		}

		__forceinline bool _vec_origin( ) {
			DWORD64 game_scene_node = 0;

			if ( !_proc_manager.read_memory<DWORD64>( this->address + offsets::c_base_entity::game_scene_node, game_scene_node ) ) {
#ifdef read_data_dbg
				print_with_data_scoped( "ccs_player_pawn::_dormant -> error -> no memory" );
#endif // read_data_dbg
				return false;
			}

			return mem::scan_memory<vec3_t>( "c_player_pawn::vec_origin", game_scene_node, offsets::c_game_scene_mode::vec_origin, this->vec_origin );
		}

		__forceinline bool _dormant( ) {
			DWORD64 game_scene_node = 0;

			if ( !_proc_manager.read_memory<DWORD64>( this->address + offsets::c_base_entity::game_scene_node, game_scene_node ) ) {
#ifdef read_data_dbg
				print_with_data_scoped( "ccs_player_pawn::_dormant -> error -> no memory" );
#endif // read_data_dbg
				return false;
			}

			return mem::scan_memory<int>( "c_player_pawn::_dormant", game_scene_node, offsets::pawn::dormant, this->dormant );
		}
	};

	class c_entity {
	public:
		ccs_player_controler controller;
		ccs_player_pawn player_pawn;
	public:
		__forceinline bool update_controller( const DWORD64& player_controler ) {
			if ( player_controler == 0 ) {
#if 0
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
				printf( "[evo] error controller._health\n" );
#endif 
				return false;
			}

			if ( !this->controller._team_id( ) ) {
#if 1
				/* debug */
				printf( "[evo] error controller._team_id\n" );
#endif 
				return false;
			}


			if ( !this->controller._player_name( ) ) {
#if 1
				/* debug */
				printf( "[evo] error controller._player_name\n" );
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

			if ( !this->player_pawn._health( ) ) {
#if 1
				/* debug */
				printf( "[evo] error controller._health\n" );
#endif 

				return false;
			}

			if ( !this->player_pawn._pos( ) ) {
#if 1
				/* debug */
				printf( "[evo] error controller._pos\n" );
#endif 

				return false;
			}

			if ( !this->player_pawn._dormant( ) ) {
#if 1
				/* debug */
				printf( "[evo] error controller._pos\n" );
#endif 

				return false;
			}

			if ( !this->player_pawn._spotted( ) ) {
#if 1
				/* debug */
				printf( "[evo] error controller._spotted\n" );
#endif 

				return false;
			}

			if ( !this->player_pawn._vec_origin( ) ) {
#if 1
				/* debug */
				printf( "[evo] error controller._spotted\n" );
#endif 

				return false;
			}

			if ( !this->player_pawn._clip( ) ) {
#if 1
				/* debug */
				printf( "[evo] error controller._spotted\n" );
#endif 

				return false;
			}

			if ( !this->player_pawn._max_clip( ) ) {
#if 1
				/* debug */
				printf( "[evo] error controller._spotted\n" );
#endif 

				return false;
			}

			if ( !this->player_pawn._weapon_type( ) ) {
#if 1
				/* debug */
				printf( "[evo] error controller._spotted\n" );
#endif 

				return false;
			}

			if ( !this->player_pawn._weapon_name( ) ) {
#if 1
				/* debug */
				printf( "[evo] error controller._spotted\n" );
#endif 

				return false;
			}

			if ( !this->player_pawn._defuser( ) ) {
#if 1
				/* debug */
				printf( "[evo] error controller._spotted\n" );
#endif 

				return false;
			}

			if ( !this->player_pawn.bone_data.update_bone_data( player_pawn_address ) ) {
#if 1
				/* debug */
				printf( "[evo] error bone_data.update_bone_data\n" );
#endif 
				return false;
			}

			return true;
		}

		__forceinline bone_t get_bone( ) const {
			if ( this->player_pawn.address == 0 ) {
#if 1
				/* debug */
				printf( "[evo] player address is 0\n" );
#endif 
				return bone_t{};
			}

			return this->player_pawn.bone_data;
		}

		__forceinline bool in_screen( ) {
			return evo::_address->view.world_to_screen( this->player_pawn.pos, this->player_pawn.screen_pos );
		}
	};
}