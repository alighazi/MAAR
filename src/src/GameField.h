#ifndef GAMEFIELD_H
#define GAMEFIELD_H
#include<vector>
using std::vector;
#include"GameCell.h"
namespace MAAR
{
//Kind of manager class for GameCell
class GameField
{
private:
	vector<GameCell> cells;
public:
	const int WIDTH,HEIGHT;	
	unsigned char BackGroundColor[3];
	GameField(int Width, int Height);

	//calculates the rectangle dedicated to this cell based on the gamefield size
	RECTf GetRect(int x, int y);
	inline GameCell* GetCell(int x,int y){ return &cells[y*WIDTH+x]; }
	void Draw();
	void GameCycle();
	~GameField();
};
}
#endif