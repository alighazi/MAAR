#ifndef MAR_H
#define MAR_H
#include "Game.h"
#include "MaarCell.h"
#include "GameField.h"

namespace MAAR
{
	class Mar
	{
	private:
		int tailIndex;

	public:
		int Length;
		const int MAX_LENGHT;
		MaarCell *maar;	
		GameField *field;
		Mar(int MaxLength, int x ,int y, GameField *gameField);
		~Mar();
		inline MaarCell operator[](int i) { return maar[i]; }	
		void Cycle(Direction direction);
	};
}
#endif



