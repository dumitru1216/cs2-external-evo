#pragma once

namespace evo {
	namespace offsets {
		namespace c_base_entity {
			inline DWORD health = 0x32C;
			inline DWORD team_id = 0x3BF;
			inline DWORD game_scene_node = 0x310;
			inline DWORD bone_array = 0x1E0; /* xref: CSkeletonInstance_::m_modelState + CGameSceneNode_::m_vecOrigin -> if this gets outdate */
		}

		namespace c_base_player_controler {
			inline DWORD player_pawn = 0x7EC;
			inline DWORD pawn_alive = 0x7F4;
			inline DWORD player_name = 0x640;
		}

		namespace pawn {
			inline DWORD health = 0x32C;
			inline DWORD vec_old_origin = 0x1224;
			inline DWORD dormant = 0xE7;
			inline DWORD has_hemlet = 0x801;
			inline DWORD has_defuser = 0x800;
			inline DWORD ping_services = 0x1268;
			inline DWORD spotted = 0x1638 + 0xC; /* xref: m_entitySpottedState + m_bSpottedByMask  */
		}

		namespace item_services {
			inline DWORD item_services_pawn = 0x10B0;
			inline DWORD has_defuser = 0x40;
			inline DWORD has_hemlet = 0x41;
			inline DWORD has_heavy_armor = 0x42;
		}

		namespace ping_services {
			inline DWORD player_ping = 0x40;
		}

		namespace c_base_weapon {
			inline DWORD clipping_weapon = 0x12B0;
			inline DWORD wpn_data_ptr = 0x360;
			inline DWORD weapon_services = 0x10A8;
			inline DWORD active_weapon = 0x60;
			inline DWORD clip_1 = 0x1570;
			inline DWORD max_clip = 0x1FC;
			inline DWORD weapon_type = 0x240;
			inline DWORD zs_name = 0xC18;
		}

		namespace untested {
			//  constexpr std::ptrdiff_t m_iConnected = 0x63C; - CBasePlayerController 
			// constexpr std::ptrdiff_t m_iDesiredFOV = 0x6D4; - CBasePlayerController
			// constexpr std::ptrdiff_t m_iPing = 0x720; - CCSPlayerController 

			/* matchmaking stuff - CCSPlayerController
			
				constexpr std::ptrdiff_t m_iCompetitiveRanking = 0x770; // int32_t
				constexpr std::ptrdiff_t m_iCompetitiveWins = 0x774; // int32_t
				constexpr std::ptrdiff_t m_iCompetitiveRankType = 0x778; // int8_t
				constexpr std::ptrdiff_t m_iCompetitiveRankingPredicted_Win = 0x77C; // int32_t
				constexpr std::ptrdiff_t m_iCompetitiveRankingPredicted_Loss = 0x780; // int32_t
				constexpr std::ptrdiff_t m_iCompetitiveRankingPredicted_Tie = 0x784; // int32_t
			*/

			/* CCSPlayerController_InGameMoneyServices 
				 constexpr std::ptrdiff_t m_iAccount = 0x40; // int32_t
				 constexpr std::ptrdiff_t m_iStartAccount = 0x44; // int32_t
				 constexpr std::ptrdiff_t m_iTotalCashSpent = 0x48; // int32_t
				 constexpr std::ptrdiff_t m_iCashSpentThisRound = 0x4C; // int32_t
				 constexpr std::ptrdiff_t m_nPreviousAccount = 0x50; // int32_t
			*/

			// see CCSPlayer_PingServices 

			// see CCSPlayer_MovementServices
		}

		namespace glow {
			inline DWORD glow_propety = 0xB98; /* xref: player + glow_property */

			/* glow property 
				player + glow_property -> glow_address
				glow_address->glow_color/glowing
			*/
			inline DWORD glow_color = 0x8; /* xref: vector - clr[0-3] */
			inline DWORD glow_type = 0x30; /* xref: vector - clr[0-3] */
			inline DWORD glow_color_override = 0x40; /* xref: Color - clr[0-3] */
			inline DWORD glowing = 0x51; /* xref: bool */
		}

		namespace c_game_scene_mode {
			inline DWORD vec_origin = 0x80;
		}
	}

	namespace dragged_offsets {
		inline DWORD entity_list;
		inline DWORD matrix;
		inline DWORD view_angle;
		inline DWORD local_player_controller;
		inline DWORD local_player_pawn;
		inline DWORD force_jump;
		inline DWORD global_vars;
		inline DWORD inventory_services;
		inline DWORD planted_c4;
	}

	namespace signatures {
		const std::string inventory_services = "E8 ?? ?? ?? ?? 8B 45 D0 48 8B 55 D8"; // outdate
		const std::string global_vars = "48 89 0D ?? ?? ?? ?? 48 89 41"; // old?
		const std::string entity_list = "48 8B 0D ?? ?? ?? ?? 48 89 7C 24 ?? 8B FA C1 EB";
		const std::string local_player_controller = "48 8B 05 ?? ?? ?? ?? 48 85 C0 74 4F";
		const std::string view_angles = "48 8B 0D ?? ?? ?? ?? E9 ?? ?? ?? ?? CC CC CC CC 40 55";
		const std::string view_matrix = "48 8D 0D ?? ?? ?? ?? 48 C1 E0 06";
		const std::string local_player_pawn = "48 8D 05 ?? ?? ?? ?? C3 CC CC CC CC CC CC CC CC 48 83 EC ?? 8B 0D";
		const std::string force_jump = "48 8B 05 ?? ?? ?? ?? 48 8D 1D ?? ?? ?? ?? 48 89 45";
		const std::string planted_c4 = "48 8B 15 ?? ?? ?? ?? FF C0 48 8D 4C 24 40";
	}
}