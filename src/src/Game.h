#ifndef GAME_H
#define GAME_H
namespace MAAR
{
enum GameState
{
	RUNNING=0,
	PAUSED,
	FINISHED
};

class Game
{
private:
protected:
	static Game* _instance;
	GameState gameState;
	bool selfCollision;
public:
	inline bool IsSelfCollisionEnable(){return selfCollision;}
	inline GameState GetGameState(){return gameState;}
	void SetGameState(GameState state){gameState=state;}
	inline static Game* GetInstance(){return _instance;}

};

}
#endif