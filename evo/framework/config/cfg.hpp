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


		bool change_by_visibility = false;
	};

	inline const auto _settings = std::make_unique< settings_t >( );
}