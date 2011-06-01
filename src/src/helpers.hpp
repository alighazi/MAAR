#define DEG2RAD(x) ((x)/(57.295778f))
#define EPSILON 0.001f
#define GL_ERR_CHECK GLenum error = glGetError();\
	if(error  != GL_NO_ERROR)\
		{fprintf(stderr,"GL Error at line: %i code: 0x%X\n",__LINE__,error); assert(false);}
const GLfloat PI=3.1415926535f;

float randrage(float a, float b)
{
	if(a>=b)
		return a;
	float r=rand()%1001;
	r/=1000.f;
	r*=b-a;
	return r+a;
}
struct polarVector3
{
	//radius
	float ro;
	//angle between vector and y axis
	float fi;
	//angle between vector and x axis
	float theta;
};
struct f3//can be point, color, vector, anything.
{
	float x,y,z;
	float length() const
	{
		return sqrtf(x*x+y*y+z*z);
	}
	f3 unit() const
	{
		float len=length();
		f3 r={x/len, y/len, z/len};
		return r;
	}
	polarVector3 toPolar() const
	{
		polarVector3 p;
		p.ro=length();
		p.fi=acosf(y/p.ro);
		p.theta=atan2f(z,x);
		return p;
	}	
	f3 operator*(float left)
	{
		f3 r=*this;
		r.x*=left;
		r.y*=left;
		r.z*=left;
		return r;
	}
};
struct f4//can be point, color, vector, anything.
{
	float x,y,z,w;
};

void f3CrossProduct(f3 *u, f3 *v, f3* out)
{
	out->x	= u->y*v->z - u->z*v->y;
	out->y	= u->z*v->x - u->x*v->z;
	out->z	= u->x*v->y - u->y*v->x;
}

float f3DotProduct(f3 *u, f3 *v)
{
	return u->x*v->x + u->y*v->y + u->z*v->z;
}


struct Matrix4
{
	float elements[16];
	f4 GetColumn4(int c)
	{
		f4 r;
		r.x=elements[c*4+0];
		r.y=elements[c*4+1];
		r.z=elements[c*4+2];
		r.w=elements[c*4+3];
		return r;
	}
	f3 GetColumn3(int c)
	{
		f3 r;
		r.x=elements[c*4+0];
		r.y=elements[c*4+1];
		r.z=elements[c*4+2];
		return r;
	}
	f4 GetRow4(int r)
	{
		f4 ret;
		ret.x=elements[r];
		ret.y=elements[4+r];
		ret.z=elements[8+r];
		ret.w=elements[12+r];
		return ret;
	}
	f3 GetRow3(int r)
	{
		f3 ret;
		ret.x=elements[r];
		ret.y=elements[4+r];
		ret.z=elements[8+r];
		return ret;
	}
	inline float operator[](int index)
	{
		return elements[index];
	}
	inline operator float*()//cast to float* operator
	{
		return elements;
	}
}; 