#pragma once

namespace evo {
	namespace offets {
		namespace c_base_entity {
			constexpr std::ptrdiff_t health = 0x32C;
		}

		namespace c_base_player_controler {
			constexpr std::ptrdiff_t player_pawn = 0x7EC;
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