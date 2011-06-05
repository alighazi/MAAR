#include "GameCell.h"
namespace MAAR
{
	GameCell::GameCell(){}
	
	void GameCell::SetContentColor(Content c, unsigned char r,unsigned char g, unsigned char b)
	{
		colors[(int)c][0]=r;
		colors[(int)c][1]=g;
		colors[(int)c][2]=b;
	}

	unsigned char* GameCell::GetContentColor(Content c)
	{
		return colors[(int)c];
	}

	unsigned char* GameCell::GetColor()
	{

		unsigned char ret[3];
		if(content==Kerm)
			switch(maar->type)
			{
			case MaarCell::Head:
				ret[0]= 0xff;
				ret[1]= 0xff;
				ret[2]= 0;
				return ret;
			case MaarCell::Tail:
				ret[0]=0xff;
				ret[1]=0;
				ret[2]=0xff;
				return ret;
			}
		return colors[(int)content];
	}

vec2f GameCell::dimensions;
unsigned char GameCell::colors[4][3]={{32,32,32},{255,255,0},{255,0,255},{100,20,0}};
}