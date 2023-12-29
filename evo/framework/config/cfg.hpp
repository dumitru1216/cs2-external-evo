#pragma once

namespace evo {
	class settings_t {
	public:
		bool save( std::string file_name );
		bool load( std::string file_name );

		/* variables */
		bool bounding_box = false;
	};

	inline const auto _settings = std::make_unique< settings_t >( );
}