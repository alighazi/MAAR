#ifndef MAARCELL_H
#define MAARCELL_H
namespace MAAR
{
enum Direction
{
	DIR_Up=0,
	DIR_Left,
	DIR_Down,
	DIR_Right
};


class MaarCell
{
	public:
	enum Type
	{
		Head=0,
		Body,
		Tail,
		Empty
	};
	Direction dir;
	int x,y;
	Type type;
	MaarCell();
};
}
#endif