#include "../../../inc.hpp"

void evo::legit_t::run_aimbot( const c_entity& entity, vec3_t local_pos, vec3_t aim_pos ) {
	float yaw, pitch, distance, norm, lenght, target_x, target_y;
	vec3_t opp_pos;
	vec2_t angles{};
	int screen_x = 1920 / 2;
	int screen_y = 1080 / 2;

	/* fix */
	opp_pos = aim_pos - local_pos;
	distance = sqrt( pow( opp_pos.x, 2 ) + pow( opp_pos.y, 2 ) );
	lenght = sqrt( distance * distance + opp_pos.z * opp_pos.z );

	yaw = atan2f( opp_pos.y, opp_pos.x ) * 57.295779513 - entity.player_pawn.viewangle.y;
	pitch = -atan( opp_pos.z / distance ) * 57.295779513 - entity.player_pawn.viewangle.x;
	norm = sqrt( pow( yaw, 2 ) + pow( pitch, 2 ) );

	vec2_t screen_pos;
	_address->view.world_to_screen( vec3_t( aim_pos ), screen_pos );
}
