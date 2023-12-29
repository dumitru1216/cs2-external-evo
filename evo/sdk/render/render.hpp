#pragma once

namespace evo {
	enum fonts_t {
		_default
	};

	enum font_flags_t {
		none,
		dropshadow,
		outline
	};

	enum text_animation_t {
		left_to_right,
		middle_pulse,
		tiny_color
	};

	class render_t {
	public:
		void initialize_font_system( );

		void add_text( int x, int y, col_t c, int font, const char* text, int /* or font_flags_t */ flag = font_flags_t::none );
		void add_rect_filled( int x, int y, int w, int h, evo::col_t col, int round );
		void add_rect( int x, int y, int w, int h, evo::col_t col, int round, int tickness );
		evo::col_t to_main_color( float color[ 4 ] );
		void add_filled_circle( evo::vec2_t center, float radius, evo::col_t c );
		void add_gradient_circle_filled( evo::vec2_t c, int radius, evo::col_t inner_color, evo::col_t outer_color );
		void add_gradient_vertical( int x, int y, int w, int h, evo::col_t c1, evo::col_t c2 );
		void add_gradient_horizontal( int x, int y, int w, int h, evo::col_t c1, evo::col_t c2 );
		void add_drop_shadow( int x, int y, int w, int h );
		void add_image( int x, int y, int w, int h, evo::macros::texture_id user_texture_id, evo::col_t c );

		void bind_animation( int id, std::string text, evo::col_t color, int font, int x, int y, text_animation_t animation_type );

		void clip_rect( float x, float y, float w, float h, std::function<void( )> function );

		evo::vec2_t text_size( const char* text, int font );
		std::vector<ImFont*> fonts{};
	};

	inline const auto _render = std::make_unique<render_t>( );
}