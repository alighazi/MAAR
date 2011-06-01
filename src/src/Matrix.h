//
// Template math library for common 3D functionality
//
// Matrix.h - template matrix code
//


#ifndef MATRIX_H
#define MATRIX_H

template <class T> class vec2;
template <class T> class vec3;
template <class T> class vec4;

////////////////////////////////////////////////////////////////////////////////
//
//  Matrix
//
////////////////////////////////////////////////////////////////////////////////

template<class T>

class	matrix4
{
public:
	matrix4(){make_identity();}

	matrix4( T t ) 
    { set_value(t); }

	matrix4( const T* m )
    { set_value(m); }

	matrix4( T a00, T a01, T a02, T a03,
        T a10, T a11, T a12, T a13,
        T a20, T a21, T a22, T a23,
        T a30, T a31, T a32, T a33 ) :
    _11(a00), _12(a01), _13(a02), _14(a03),
    _21(a10), _22(a11), _23(a12), _24(a13),
    _31(a20), _32(a21), _33(a22), _34(a23),
    _41(a30), _42(a31), _43(a32), _44(a33)
    {}

	void get_value( T * mp ) const {
        int c = 0;
        for(int j=0; j < 4; j++)
            for(int i=0; i < 4; i++)
                mp[c++] = element(i,j);
    }

	const T * get_value() const {
        return _array;
    }

	void set_value( T * mp) {
        int c = 0;
        for(int j=0; j < 4; j++)
            for(int i=0; i < 4; i++)
                element(i,j) = mp[c++];
    }

	void set_value( T r ) {
        for(int i=0; i < 4; i++)
            for(int j=0; j < 4; j++)
                element(i,j) = r;
    }

	void make_identity() {
        element(0,0) = 1.0;
        element(0,1) = 0.0;
        element(0,2) = 0.0; 
        element(0,3) = 0.0;

        element(1,0) = 0.0;
        element(1,1) = 1.0; 
        element(1,2) = 0.0;
        element(1,3) = 0.0;

        element(2,0) = 0.0;
        element(2,1) = 0.0;
        element(2,2) = 1.0;
        element(2,3) = 0.0;

        element(3,0) = 0.0; 
        element(3,1) = 0.0; 
        element(3,2) = 0.0;
        element(3,3) = 1.0;
    }

	// set a uniform scale
    void set_scale( T s ) {
        element(0,0) = s;
        element(1,1) = s;
        element(2,2) = s;
    }

	void set_scale( const vec3<T> & s ) {
        for (int i = 0; i < 3; i++) element(i,i) = s[i];
    }

	void set_translate( const vec3<T> & t ) {
        for (int i = 0; i < 3; i++) element(i,3) = t[i];
    }

	void set_row(int r, const vec4<T> & t) {
        for (int i = 0; i < 4; i++) element(r,i) = t[i];
    }

	void set_column(int c, const vec4<T> & t) {
        for (int i = 0; i < 4; i++) element(i,c) = t[i];
    }

	vec4<T> get_row(int r) const {
        vec4<T> v;
        for (int i = 0; i < 4; i++) v[i] = element(r,i);
        return v;
    }

	vec4<T> get_column(int c) const {
        vec4<T> v;
        for (int i = 0; i < 4; i++) v[i] = element(i,r);
        return v;
    }

}