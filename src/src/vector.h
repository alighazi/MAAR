template <class T> vec2;
template <class T> vec3;
template <class T> vec4;

template<class T>
class vec2{
public:
	int size() const {return 2;}
	
	/////////////////////////////////////////////////////
	//
	//  Constructors
	//
	/////////////////////////////////////////////////////
	
	//Default/scalar constructor
	vec2(const T &t = T())
	{
		for(int i=0; i<size(); i++)_array[i]=t;
	}
	
	//Construct from array
	vec2(const T *tp = T())
	{
		for(int i=0; i<size(); i++)_array[i]=tp[i];		
	}

	//Construct from explicit values
	vec2(const T &v0, const T &v1)
	{
		x=v0;
		y=v1;
	}

	////Explicit conversion from vec3
	//explicit vec2(const vec3<T> &v)
	//{
	//	for(int i=0; i<size(); i++)_array[i]=v._array[i];
	//}

	////Explicit conversion from vec4
	//explicit vec2(const vec4<T> &v)
	//{
	//	for(int i=0; i<size(); i++)_array[i]=v._array[i];
	//}

	//Get array
	const T* get_value() const
	{
		return _array;
	}

	//Set by array
	vec2<T> set_value(const T *rhs )
	{
		for(int i=0; i<size(); i++)_array[i]=rhs[i];
		return *this;
	}

	//Indexing operators
	T& operator [] (const int i)
	{
		return _array[i];
	}

	const T& operator [] (const int i) const
	{
		return _array[i];
	}

	union
	{
		struct
		{
			T x,y; //standard names
		};
		
		struct
		{
			T s,t; //standard names
		}

		T _array[2]; //array access
	}

};