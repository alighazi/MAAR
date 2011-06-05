#ifndef GAMECELL_H
#define GAMECELL_H

#include "MaarCell.h"
#include "helpers.h"

namespace MAAR
{
class GameCell
{
private:
	static unsigned char colors[4][3];
public:
	enum Content{Empty=0, Kerm=1, Fruit=2, Wall=3};
	static vec2f dimensions;
	Content content;
	MaarCell *maar;
	GameCell();	
	static void SetContentColor(Content c, unsigned char r,unsigned char g, unsigned char b);
	static unsigned char* GetContentColor(Content c);
	unsigned char* GetColor();
};
}
#endif