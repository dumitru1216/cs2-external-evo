#include "../../../inc.hpp"

void evo::legit_t::run_aimbot( const c_entity& entity, const c_entity& local, vec3_t local_pos, int ent_idx, int local_idx ) {
    float yaw, pitch, distance, norm, lenght;
	vec3_t opp_pos;
	vec2_t angles{};
	int screen_center_x = 1920 / 2;
	int screen_center_y = 1080 / 2;

    /* hacks_ctx.cpp */
    float distance_to_sight = 0;
    float max_aim_distance = 1500;
    vec3_t aim_pos{ 0, 0, 0 };

    /* hitbox shit */
    switch ( evo::_settings->hitbox ) {
        case 0:
        {
            _legit->aim_position = bone_index::head;
        } break;
        case 1:
        {
            _legit->aim_position = bone_index::neck_0;
        } break;
        case 2:
        {
            _legit->aim_position = bone_index::spine_1;
        } break;
        case 3:
        {
            _legit->aim_position = bone_index::pelvis;
        } break;
    }

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

    if ( norm >= _settings->fov ) {
        return; // If condition not met, exit early
    }

    float smooth_factor = ( _settings->smooth != 0.0f ) ? _settings->smooth : 1.5f;

    auto calculate_target = [ ]( int screen_pos, int screen_center, float smooth ) {
        return ( screen_pos != screen_center ) ? ( ( screen_pos > screen_center ) ? -( screen_center - screen_pos ) : ( screen_pos - screen_center ) ) / smooth : 0;
        };

    float target_x = calculate_target( screen_pos.x, screen_center_x, smooth_factor );
    float target_y = ( screen_pos.y != screen_center_y && screen_pos.y != 0 ) ? calculate_target( screen_pos.y, screen_center_y, smooth_factor ) : 0;

    if ( !_settings->smooth ) {
        mouse_event( MOUSEEVENTF_MOVE, target_x, target_y, NULL, NULL );
        return;
    }

    float distance_ratio = norm / _settings->fov;
    float speed_factor = 1.0f + ( 1.0f - distance_ratio );

    target_x = calculate_target( screen_pos.x, screen_center_x, smooth_factor ) / ( _settings->smooth * speed_factor );
    target_y = ( screen_pos.y != screen_center_y && screen_pos.y != 0 ) ? calculate_target( screen_pos.y, screen_center_y, smooth_factor ) / ( _settings->smooth * speed_factor ) : 0;

    mouse_event( MOUSEEVENTF_MOVE, target_x, target_y, NULL, NULL );

}

void evo::legit_t::draw_aimbot_fov( ) { 
    if ( !_settings->draw_fov ) {
        return;
    }

    float screen_x = GetSystemMetrics( SM_CXSCREEN ) / 2.f;
    float screen_y = GetSystemMetrics( SM_CYSCREEN ) / 2.f;

    _render->add_circle( evo::vec2_t( screen_x, screen_y ), ( _settings->fov * 10 ), evo::col_t( ) );
}
