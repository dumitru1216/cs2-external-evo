#include "../../inc.hpp"
#include "../animation_system/animation_system.hpp"

void evo::render_t::initialize_font_system( ) {
	ImGuiIO& io = ImGui::GetIO( ); /* get imgui io */

	/* create a new cfg for each type of font */
	ImFontConfig* cfg = new ImFontConfig( );

	/* ranges */
	static const ImWchar ranges[ ] =
	{
	   0x0020, 0x00FF,
	   0x0400, 0x052F,
	   0x2DE0, 0x2DFF,
	   0xA640, 0xA69F,
	   0x3131, 0x3163,
	   0xAC00, 0xD79D,
	   0,
	};

	/* tupe the fonts */
	std::tuple<const char*, float, const ImWchar*> render_fonts[ ] =
	{
	   std::make_tuple( xorstr_( "verdana.ttf" ), 12.0f, ranges ),
	};

	/* init fonts */
	for ( auto font : render_fonts ) {
		std::string path = std::string( xorstr_( "C:\\Windows\\Fonts\\" ) );
		path += std::get<0>( font );

		cfg = new ImFontConfig( );
		cfg->PixelSnapH = true;
		cfg->OversampleH = cfg->OversampleV = 1;

		auto im_font = io.Fonts->AddFontFromFileTTF( path.c_str( ), std::get<1>( font ), cfg, std::get<2>( font ) );
		io.Fonts->Fonts.push_back( im_font );

		printf( "Loaded font: %s, Size: %.1f\n", std::get<0>( font ), std::get<1>( font ) );
	}

	/* freetype build */
	ImGuiFreeType::BuildFontAtlas( io.Fonts, ImGuiFreeTypeBuilderFlags_Monochrome | ImGuiFreeTypeBuilderFlags_MonoHinting );
}

void evo::render_t::add_text( int x, int y, col_t c, int font, const char* text, int flag ) {
	ImGuiIO& io = ImGui::GetIO( );
	ImGui::PushFont( io.Fonts->Fonts[ 0 ] );

	if ( flag == font_flags_t::dropshadow ) {
		ext_draw_list->AddText( evo::macros::vec_t( x + 1.f, y + 1.f ), col_t( 5, 5, 5 ).modify_alpha( c.a ).convert( ), text );
	}

	if ( flag == font_flags_t::outline ) {
		ext_draw_list->AddText( evo::macros::vec_t( x + 1, y - 1 ), col_t( 5, 5, 5 ).modify_alpha( c.a ).convert( ), text );
		ext_draw_list->AddText( evo::macros::vec_t( x - 1, y + 1 ), col_t( 5, 5, 5 ).modify_alpha( c.a ).convert( ), text );
		ext_draw_list->AddText( evo::macros::vec_t( x - 1, y - 1 ), col_t( 5, 5, 5 ).modify_alpha( c.a ).convert( ), text );
		ext_draw_list->AddText( evo::macros::vec_t( x + 1, y + 1 ), col_t( 5, 5, 5 ).modify_alpha( c.a ).convert( ), text );

		ext_draw_list->AddText( evo::macros::vec_t( x, y + 1 ), col_t( 5, 5, 5 ).modify_alpha( c.a ).convert( ), text );
		ext_draw_list->AddText( evo::macros::vec_t( x, y - 1 ), col_t( 5, 5, 5 ).modify_alpha( c.a ).convert( ), text );
		ext_draw_list->AddText( evo::macros::vec_t( x + 1, y ), col_t( 5, 5, 5 ).modify_alpha( c.a ).convert( ), text );
		ext_draw_list->AddText( evo::macros::vec_t( x - 1, y ), col_t( 5, 5, 5 ).modify_alpha( c.a ).convert( ), text );
	}

	/* text */
	ext_draw_list->AddText( evo::macros::vec_t( x, y ), c.convert( ), text );

	ImGui::PopFont( );
}

evo::vec2_t evo::render_t::text_size( const char* text, int font ) {
	ImGuiIO& io = ImGui::GetIO( );

	return {
		io.Fonts->Fonts[ font ]->CalcTextSizeA( io.Fonts->Fonts[ font ]->FontSize, FLT_MAX, -1.0f, text ).x,
		io.Fonts->Fonts[ font ]->CalcTextSizeA( io.Fonts->Fonts[ font ]->FontSize, FLT_MAX, -1.0f, text ).y
	};
}

void evo::render_t::add_rect_filled( int x, int y, int w, int h, evo::col_t col, int round ) {
	ext_draw_list->AddRectFilled( evo::macros::vec_t( x, y ), evo::macros::vec_t( x + w, y + h ), col.convert( ), round );
}

void evo::render_t::add_rect( int x, int y, int w, int h, evo::col_t col, int round, int tickness ) {
	ext_draw_list->AddRect( evo::macros::vec_t( x, y ), evo::macros::vec_t( x + w, y + h ), col.convert( ), round, 0, tickness );
}

void evo::render_t::add_filled_circle( evo::vec2_t center, float radius, evo::col_t c ) {
	ext_draw_list->AddCircleFilled( evo::macros::vec_t( center.x, center.y ), radius, c.convert( ) );
}

evo::macros::u32_t lerp_color( evo::macros::u32_t col1, evo::macros::u32_t col2, float t ) {
	evo::macros::vec4_t c1 = ImGui::ColorConvertU32ToFloat4( col1 );
	evo::macros::vec4_t c2 = ImGui::ColorConvertU32ToFloat4( col2 );
	evo::macros::vec4_t lerped = evo::macros::vec4_t( c1.x + t * ( c2.x - c1.x ),
													  c1.y + t * ( c2.y - c1.y ),
													  c1.z + t * ( c2.z - c1.z ),
													  c1.w + t * ( c2.w - c1.w ) );
	return ImGui::ColorConvertFloat4ToU32( lerped );
}

void evo::render_t::add_gradient_circle_filled( evo::vec2_t c, int radius, evo::col_t inner_color, evo::col_t outer_color ) {
	for ( int i = 0; i <= radius; ++i ) {
		float t = static_cast< float >( i ) / radius;
		ImU32 color = ImGui::GetColorU32( lerp_color( inner_color.convert( ), outer_color.convert( ), t ) );
		ext_draw_list->AddCircleFilled( evo::macros::vec_t( c.x, c.y ), static_cast< float >( i ), color );
	}
}

void evo::render_t::add_gradient_vertical( int x, int y, int w, int h, evo::col_t c1, evo::col_t c2 ) {
	ext_draw_list->AddRectFilledMultiColor( evo::macros::vec_t( x, y ), evo::macros::vec_t( x + w, y + h ), c1.convert( ), c2.convert( ), c2.convert( ), c1.convert( ) );
}

void evo::render_t::add_gradient_horizontal( int x, int y, int w, int h, evo::col_t c1, evo::col_t c2 ) {
	ext_draw_list->AddRectFilledMultiColor( evo::macros::vec_t( x, y ), evo::macros::vec_t( x + w, y + h ), c1.convert( ), c1.convert( ), c2.convert( ), c2.convert( ) );
}

void evo::render_t::add_drop_shadow( int x, int y, int w, int h ) {
	this->add_gradient_horizontal( x, y - 5, w, 5, evo::col_t( 12, 26, 36, 0 ), evo::col_t( 12, 26, 36, 100 ) );
	this->add_gradient_horizontal( x, y + h, w, 5, evo::col_t( 12, 26, 36, 100 ), evo::col_t( 12, 26, 36, 0 ) );

	this->add_gradient_vertical( x - 5, y, 5, h, evo::col_t( 12, 26, 36, 0 ), evo::col_t( 12, 26, 36, 100 ) );
	this->add_gradient_vertical( x + w, y, 5, h, evo::col_t( 12, 26, 36, 100 ), evo::col_t( 12, 26, 36, 0 ) );
}

void evo::render_t::add_image( int x, int y, int w, int h, evo::macros::texture_id user_texture_id, evo::col_t c ) {
	ext_draw_list->AddImage( user_texture_id, evo::macros::vec_t( x, y ), evo::macros::vec_t( x + w, y + h ), ImVec2( 0, 0 ), ImVec2( 1, 1 ), c.convert( ) );
}

void evo::render_t::bind_animation( int id, std::string text, evo::col_t color, int font, int x, int y, text_animation_t animation_type ) {
	static int animation_[ 1000 ]; /* iterate */

	int w_of_text = this->text_size( text.c_str( ), font ).x;
	int h_of_text = this->text_size( text.c_str( ), font ).y;

	switch ( animation_type ) {
		case text_animation_t::left_to_right:
		{
			auto animation = animation_controller.get( text + std::to_string( id ) + animation_controller.current_child );
			animation.adjust( animation.value + 3.f * animation_controller.get_min_deltatime( 0.025f ) * ( ( animation_[ id ] < w_of_text ) ? 1.f : -1.f ) );

			if ( animation.value >= 0.99f ) {
				animation_[ id ] = w_of_text;
			} else if ( animation.value <= 0.f ) {
				animation_[ id ] = 0;
			}

			this->clip_rect( x, y, w_of_text * animation.value, h_of_text, [ & ]( ) {
				this->add_text( x, y, color, font, text.c_str( ) );
							 } );
		} break;
		case text_animation_t::middle_pulse:
		{
			auto animation = animation_controller.get( text + std::to_string( id ) + animation_controller.current_child );
			animation.adjust( animation.value + 3.f * animation_controller.get_min_deltatime( 0.025f ) * ( ( animation_[ id ] < w_of_text ) ? 1.f : -1.f ) );

			if ( animation.value >= 0.99f ) {
				animation_[ id ] = w_of_text;
			} else if ( animation.value <= 0.f ) {
				animation_[ id ] = 0;
			}

			this->clip_rect( x + ( w_of_text / 2 ) - ( ( ( w_of_text * 2 ) / 2 ) * ( animation.value / 2 ) ), y,
							 ( ( w_of_text * 2 ) / 2 ) * animation.value, h_of_text, [ & ]( ) {
								 this->add_text( x, y, color, font, text.c_str( ) );
							 } );
		} break;
		case text_animation_t::tiny_color:
		{
			auto animation = animation_controller.get( text + std::to_string( id ) + animation_controller.current_child );
			animation.adjust( animation.value + 3.f * animation_controller.get_min_deltatime( 0.025f ) * ( ( animation_[ id ] < w_of_text ) ? 1.f : -1.f ) );

			if ( animation.value >= 0.99f ) {
				animation_[ id ] = w_of_text;
			} else if ( animation.value <= 0.f ) {
				animation_[ id ] = 0;
			}

			this->clip_rect( ( x - 15 ) + ( w_of_text * animation.value ), y, 45, h_of_text, [ & ]( ) {
				this->add_text( x, y, color, font, text.c_str( ) );
							 } );
		} break;
	}
}

void evo::render_t::clip_rect( float x, float y, float w, float h, std::function< void( ) > function ) {
	ext_draw_list->PushClipRect( { x, y }, { x + w, y + h }, true );

	function( );

	ext_draw_list->PopClipRect( );
}