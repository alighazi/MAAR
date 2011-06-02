#include "vector.h"

typedef  MAAR::vec2<float> vec2f;
typedef  MAAR::vec3<float> vec3f;
typedef  MAAR::vec4<float> vec4f;
typedef  MAAR::vec2<int> vec2i;
typedef  MAAR::vec3<int> vec3i;
typedef  MAAR::vec4<int> vec4i;


#define DEG2RAD(x) ((x)/(57.295778f))
#define EPSILON 0.001f
#define GL_ERR_CHECK GLenum error = glGetError();\
	if(error  != GL_NO_ERROR)\
		{fprintf(stderr,"GL Error at line: %i code: 0x%X\n",__LINE__,error); assert(true);}
const GLfloat PI=3.1415926535f;

float randrange(float a, float b)
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
