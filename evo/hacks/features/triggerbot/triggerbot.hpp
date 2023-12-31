#pragma once

namespace evo {
	class trigger_t {
	public:
		void release_mouse_event( );
		void run_trigger( const c_entity& local_entity );
	};

	inline const auto _triggerbot = std::make_unique< trigger_t >( );
}