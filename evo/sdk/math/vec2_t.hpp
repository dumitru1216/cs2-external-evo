#pragma once

struct vec2_t {
	/* default builders */
	vec2_t( ) : x( 0 ), y( 0 ) { }
	vec2_t( float x, float y ) : x( x ), y( y ) { }
	~vec2_t( ) { }

	/* operators */
	bool operator==( const vec2_t& src ) const {
		return ( src.x == this->x ) && ( src.y == y );
	}

	bool operator!=( const vec2_t& src ) const {
		return ( src.x != this->x ) || ( src.y != y );
	}

	float& operator[]( int i ) {
		return ( ( float* )this )[ i ];
	}

	float operator[]( int i ) const {
		return ( ( float* )this )[ i ];
	}

	/* vec - vec */
	vec2_t& operator-=( const vec2_t& v ) {
		this->x -= v.x; this->y -= v.y;
		return *this;
	}

	vec2_t& operator-=( float fl ) {
		this->x -= fl;
		this->y -= fl;

		return *this;
	}

	vec2_t& operator-( vec2_t v ) {
		vec2_t temp;
		temp.x = this->x - v.x;
		temp.y = this->y - v.y;

		return temp;
	}

	/* vec + vec */
	vec2_t& operator+=( const vec2_t& v ) {
		this->x += v.x; this->y += v.y;
		return *this;
	}

	vec2_t& operator+=( float fl ) {
		this->x += fl;
		this->y += fl;

		return *this;
	}

	vec2_t& operator+( vec2_t v ) {
		vec2_t temp;
		temp.x = this->x + v.x;
		temp.y = this->y + v.y;

		return temp;
	}

	void set( float x /*= 0.0f*/, float y /*= 0.0f */ ) {
		this->x = x;
		this->y = y;
	}

	vec2_t& operator=( const vec2_t& v ) {
		x = v.x;
		y = v.y;
		return *this;
	}

	/* > */
	bool operator<( const vec2_t& in ) const {
		return ( x < in.x && y < in.y );
	}

	bool operator>( const vec2_t& in ) const {
		return ( x > in.x && y > in.y );
	}

	/* parameters */
	float x;
	float y;
};

class vec3_t {
public:
	float x, y, z;
public:
	vec3_t( ) :x( 0.f ), y( 0.f ), z( 0.f ) { }
	vec3_t( float x_, float y_, float z_ ) :x( x_ ), y( y_ ), z( z_ ) { }
	vec3_t operator+( vec3_t Vec3_ ) {
		return { x + Vec3_.x,y + Vec3_.y,z + Vec3_.z };
	}
	vec3_t operator-( vec3_t Vec3_ ) {
		return { x - Vec3_.x,y - Vec3_.y,z - Vec3_.z };
	}
	vec3_t operator*( vec3_t Vec3_ ) {
		return { x * Vec3_.x,y * Vec3_.y,z * Vec3_.z };
	}
	vec3_t operator/( vec3_t Vec3_ ) {
		return { x / Vec3_.x,y / Vec3_.y,z / Vec3_.z };
	}
	vec3_t operator*( float n ) {
		return { x * n,y * n,z * n };
	}
	vec3_t operator/( float n ) {
		return { x / n,y / n,z / n };
	}
	bool operator==( vec3_t Vec3_ ) {
		return x == Vec3_.x && y == Vec3_.y && z == Vec3_.z;
	}
	bool operator!=( vec3_t Vec3_ ) {
		return x != Vec3_.x || y != Vec3_.y || z != Vec3_.z;
	}
	float length( ) {
		return sqrtf( powf( x, 2 ) + powf( y, 2 ) + powf( z, 2 ) );
	}
	float dist_to( const vec3_t& Pos ) {
		return sqrtf( powf( Pos.x - x, 2 ) + powf( Pos.y - y, 2 ) + powf( Pos.z - z, 2 ) );
	}
};
