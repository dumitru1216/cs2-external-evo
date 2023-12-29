#pragma once

namespace evo {
	class settings_t {
	public:
		bool save( std::string file_name );
		bool load( std::string file_name );

		/* variables */
		bool bounding_box = false;
		float box_color[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

	inline const auto _settings = std::make_unique< settings_t >( );
}