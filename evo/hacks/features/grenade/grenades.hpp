#pragma once

namespace evo {
	class grenade_t {
		enum e_throw_type : int {
			TH_FULL,
			TH_HALF,
			TH_MINIMAL
		};

	public:
		struct _grenade_t {
			vec3_t m_origin, m_angles;
			e_throw_type m_throw;
			std::string m_name, m_author;
			bool m_jump;
			std::uint16_t m_nade;

			void IndicatorThingy( );
		};

		void run( const c_entity& local_player, const c_entity& entity, int local_index, int index );

		std::vector< _grenade_t > m_grenades;
	};

	inline const auto _grenade = std::make_unique< grenade_t >( );
}