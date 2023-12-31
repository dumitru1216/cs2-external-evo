#include "../../../inc.hpp"

void evo::legit_t::run_aimbot( const c_entity& entity, const c_entity& local, vec3_t local_pos, int ent_idx, int local_idx ) {
	float yaw, pitch, distance, norm, lenght, target_x, target_y;
	vec3_t opp_pos;
	vec2_t angles{};
	int screen_center_x = 1920 / 2;
	int screen_center_y = 1080 / 2;

    /* hacks_ctx.cpp */
    float distance_to_sight = 0;
    float max_aim_distance = 1500;
    vec3_t aim_pos{ 0, 0, 0 };

    distance_to_sight = entity.get_bone( ).bone_pos_list[ bone_index::head ].screen_pos.dist_to( { ( 1920 / 2 ), ( 1080 / 2 ) } );
    if ( distance_to_sight < max_aim_distance ) {
        max_aim_distance = distance_to_sight;

        if ( !_settings->visible_check || entity.player_pawn.spotted_by_mask & ( DWORD64( 1 ) << ( local_idx ) ) || local.player_pawn.spotted_by_mask & ( DWORD64( 1 ) << ( ent_idx ) ) ) {
            aim_pos = entity.get_bone( ).bone_pos_list[ _legit->aim_position ].pos;
            if ( _legit->aim_position == bone_index::head )
                aim_pos.z -= 1.f;
        }
    }

    /* paste fix */
    if ( aim_pos == vec3_t( 0, 0, 0 ) ) {
        return;
    }

    if ( framework::m_b_open ) {
        return;
    }

    if ( entity.player_pawn.health <= 0 ) {
        return;
    }

	/* fix */
	opp_pos = aim_pos - local_pos;
	distance = sqrt( pow( opp_pos.x, 2 ) + pow( opp_pos.y, 2 ) );
	lenght = sqrt( distance * distance + opp_pos.z * opp_pos.z );

	yaw = atan2f( opp_pos.y, opp_pos.x ) * 57.295779513 - local.player_pawn.viewangle.y;
	pitch = -atan( opp_pos.z / distance ) * 57.295779513 - local.player_pawn.viewangle.x;
	norm = sqrt( pow( yaw, 2 ) + pow( pitch, 2 ) );

	vec2_t screen_pos;
	_address->view.world_to_screen( vec3_t( aim_pos ), screen_pos );

    if ( norm < _settings->fov ) {
        // Shake Fixed by @Sweely
        if ( screen_pos.x != screen_center_x ) {
            target_x = ( screen_pos.x > screen_center_x ) ? -( screen_center_x - screen_pos.x ) : screen_pos.x - screen_center_x;
            target_x /= _settings->smooth != 0.0f ? _settings->smooth : 1.5f;
            target_x = ( target_x + screen_center_x > screen_center_x * 2 || target_x + screen_center_x < 0 ) ? 0 : target_x;
        }

        if ( screen_pos.y != 0 ) {
            if ( screen_pos.y != screen_center_y ) {
                target_y = ( screen_pos.y > screen_center_y ) ? -( screen_center_y - screen_pos.y ) : screen_pos.y - screen_center_y;
                target_y /= _settings->smooth != 0.0f ? _settings->smooth : 1.5f;
                target_y = ( target_y + screen_center_y > screen_center_y * 2 || target_y + screen_center_y < 0 ) ? 0 : target_y;
            }
        }

        if ( !_settings->smooth ) {
            mouse_event( MOUSEEVENTF_MOVE, ( DWORD )( target_x ), ( DWORD )( target_y ), NULL, NULL );
            return;
        }

        float distance_ratio = norm / _settings->fov;
        float speed_factor = 1.0f + ( 1.0f - distance_ratio ); 
        target_x /= ( _settings->smooth * speed_factor );
        target_y /= ( _settings->smooth * speed_factor );

        if ( screen_pos.x != screen_center_x ) {
            target_x = ( screen_pos.x > screen_center_x ) ? -( screen_center_x - screen_pos.x ) : screen_pos.x - screen_center_x;
            target_x /= _settings->smooth != 0.0f ? _settings->smooth : 1.5f;
            target_x = ( target_x + screen_center_x > screen_center_x * 2 || target_x + screen_center_x < 0 ) ? 0 : target_x;
        }

        if ( screen_pos.y != 0 ) {
            if ( screen_pos.y != screen_center_y ) {
                target_y = ( screen_pos.y > screen_center_y ) ? -( screen_center_y - screen_pos.y ) : screen_pos.y - screen_center_y;
                target_y /= _settings->smooth != 0.0f ? _settings->smooth : 1.5f;
                target_y = ( target_y + screen_center_y > screen_center_y * 2 || target_y + screen_center_y < 0 ) ? 0 : target_y;
            }
        }
        mouse_event( MOUSEEVENTF_MOVE, target_x, target_y, NULL, NULL );
    }

}
