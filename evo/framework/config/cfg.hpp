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
	};

	inline const auto _settings = std::make_unique< settings_t >( );
}