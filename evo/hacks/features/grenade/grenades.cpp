#include "../../../inc.hpp"

__forceinline static void AngleVectors( const evo::vec3_t& angles, evo::vec3_t& forward, evo::vec3_t* right /* nullptr */, evo::vec3_t* up /* nullptr */ ) {
	const auto sp = sin( deg2rad( angles.x ) ), cp = cos( deg2rad( angles.x ) ),
		sy = sin( deg2rad( angles.y ) ), cy = cos( deg2rad( angles.y ) ),
		sr = sin( deg2rad( angles.z ) ), cr = cos( deg2rad( angles.z ) );

	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;

	if ( right ) {
		right->x = -1 * sr * sp * cy + -1 * cr * -sy;
		right->y = -1 * sr * sp * sy + -1 * cr * cy;
		right->z = -1 * sr * cp;
	}

	if ( up ) {
		up->x = cr * sp * cy + -sr * -sy;
		up->y = cr * sp * sy + -sr * cy;
		up->z = cr * cp;
	}
}


void evo::grenade_t::run( const c_entity& local_player, const c_entity& entity, int local_index, int index ) {
	/* sanity */
	if ( local_player.player_pawn.health <= 0 ) {
		return;
	}

	/* active ? */
	if ( this->m_grenades.empty( ) ) {
		return;
	}

	if ( local_player.player_pawn.weapon_type != evo::cs_weapon_type::weapon_type_grenade ) {
		return;
	}

	auto active_grenade = ( _grenade_t* ) nullptr;
	for ( auto& nade : this->m_grenades ) {
		if ( local_player.player_pawn.vec_origin.dist_to( nade.m_origin ) < 3.5f ) {
			active_grenade = &nade;
			break;
		}
	}

	if ( !active_grenade ) {
		for ( auto& nade : this->m_grenades ) {
			if ( local_player.player_pawn.vec_origin.dist_to_3d( nade.m_origin ) > 1500.f ) {
				continue;
			}
		}
	} else {
		auto angle = vec3_t( );
		AngleVectors( active_grenade->m_angles, angle, nullptr, nullptr );

		// extend
		angle *= 100.f;

		auto pos = angle + local_player.player_pawn.vec_origin + vec3_t( 0.f, 0.f, 64.f );

		if ( auto screen = vec2_t( ); _address->view.world_to_screen( pos, screen ) ) {
			/* unifnished */
		}
	}
}
