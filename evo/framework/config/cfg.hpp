#pragma once

namespace evo {
	class settings_t {
	public:
		bool save( std::string file_name );
		bool load( std::string file_name );

		/* variables */
		bool bounding_box = false;
		float box_color[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float box_color_inv[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };

		bool dormancy = false;
		bool name_esp = false;
		float name_color[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float name_color_a[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float name_color_inv[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };
		int name_at = 0;
		bool name_animation = false;

		bool health_bar = false;
		bool customhealthbar = false;
		float healthbar[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float healthbari[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };

		bool ammobar = false;
		float ammobar_color[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float ammobar_color_inv[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };

		bool eap = false;
		float eap_color[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float eap_color_inv[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };

		bool bones_h = false;
		bool bones = false;
		float bone_color[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float bone_color_inv[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };

		bool flags = false;

		bool show_competivie_wins = false;
		bool show_dmg_dealt = false;

		bool change_by_visibility = false;


		/* triggerbot */
		bool triggerbot = false;
		int activationz_type = 0; // hold - toggle - always on
		int triggerkey = 1;

		int reaction_time = 0;
		int shot_delay = 0;

		bool aimbot = false;
		float fov = 0;
		float smooth = 0;
		int aim_distance_max = 200;
		bool visible_check = true; // autowall
		int hitbox = 0;
		bool draw_fov = false;
		float fov_color[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };

		/* other shit for legitbot */
		bool legitbot_stuff[ 50 ];
		int legitbot_stuff_int[ 50 ];
		float legitbot_stuff_float[ 50 ];

		int a_activationz_type = 0; // hold - toggle - always on
		int a_triggerkey = 29;

		bool rage = false;
		int rage_fov = 10;
		bool ignore_wall = true;
		int rage_hitbox = 0;

		bool change_smoke = false;
		float smoke_coloringol[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };

		bool remove_smoke = false;


		int ragebot_spot_type;
		bool ignore_if_Distance_tO_high;
		int distance_to_rage;

		bool ragebot_stuff[ 50 ];
		int ragebot_stuff2[ 50 ];
		float ragebot_stuff3[ 50 ];
	};

	inline const auto _settings = std::make_unique< settings_t >( );
}