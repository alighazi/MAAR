#ifndef MAARGAME_H
#define MAARGAME_H
#include "Game.h"
#include "Mar.h"

namespace MAAR
{
class MaarGame :public Game
{
private:
	int _lastPressedKey;
	vec2i gridDimensions;
public:
	static vec2i windowDimensions;
	int updateInterval;
	GameField *game;
	Mar *mar;
	inline static MaarGame* GetInstance(){return (MaarGame*) _instance;}
	inline void SetLastPressedKey(int key){_lastPressedKey=key;}
	MaarGame();
	void SetSize(int width, int height);
	void Update(float dts);
	void Draw();
	~MaarGame();
};
}
#endif