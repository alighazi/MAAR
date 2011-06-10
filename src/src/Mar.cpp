#include "MAR.h"

namespace MAAR
{
	Mar::Mar(int MaxLength, int x ,int y, GameField *gameField)
		:MAX_LENGHT(MaxLength),field(gameField)
	{
		maar=new MaarCell[MAX_LENGHT];
		maar[0].type=MaarCell::Head;
		maar[0].dir=DIR_Right;
		maar[0].x=x;
		maar[1].type=MaarCell::Body;
		maar[1].dir=DIR_Right;
		maar[1].x=x-1;
		maar[2].type=MaarCell::Tail;
		maar[2].x=x-2;

		maar[0].y=maar[1].y=maar[2].y=y;
	}
	Mar::~Mar()
	{
		delete[] maar;
	}

	void Mar::Cycle(Direction direction)
	{
		bool lengthMaxed=false;
		bool ateFruit=false;
		int tailIndex;
		for(int i=MAX_LENGHT-1; i>=0; i--)
		{
			MaarCell &cell=maar[i];			
			int &x=cell.x, &y=cell.y;
			//doing type specific ops on current Maar body type
			switch(cell.type)
			{
			case MaarCell::Head:
				//assign the direction, don't let the Maar to reverse its direction
				if((direction==DIR_Left && cell.dir!=DIR_Right)
					||(direction==DIR_Right && cell.dir!=DIR_Left)
					||(direction==DIR_Up && cell.dir!=DIR_Down)
					||(direction==DIR_Down && cell.dir!=DIR_Up))
					cell.dir=direction;
				break;

			case MaarCell::Tail:
				tailIndex = i;
				Length = tailIndex + 1;
				lengthMaxed = tailIndex == MAX_LENGHT - 1;
				cell.dir=maar[i-1].dir;
				break;
			case MaarCell::Body:
				cell.dir=maar[i-1].dir;
				break;
			case MaarCell::Empty:
				continue;
				break;
			}		
		}


		for(int i=0; i<Length; i++)
		{
			MaarCell &cell=maar[i];	
			int &x=cell.x, &y=cell.y;

			if(cell.type==MaarCell::Tail)
			{
				if(ateFruit)
					continue;

				field->GetCell(x,y)->content=GameCell::Empty;
				field->GetCell(x,y)->maar=NULL;
			}

			switch(maar[i].dir)
			{
			case DIR_Up:					
					maar[i].y++;
				break;
			case DIR_Down:
					maar[i].y--;
				break;
			case DIR_Left:
					maar[i].x--;
				break;
			case DIR_Right:					
					maar[i].x++;
				break;
			}			
			if(y==field->HEIGHT)
				y=0;
			if(y<0)
				y=field->HEIGHT-1;
			if(x<0)
				x=field->WIDTH-1;
			if(x==field->WIDTH)
				x=0;

			if(cell.type==MaarCell::Head)
			{
				//self collision!
				if(Game::GetInstance()->IsSelfCollisionEnable() && field->GetCell(x,y)->content==GameCell::Kerm)
				{
					Game::GetInstance()->SetGameState(FINISHED);
					//TODO: Replace with a cross platform sound playing function
				}

				if(field->GetCell(x,y)->content==GameCell::Fruit && !lengthMaxed)
				{
					ateFruit=true;
					Length++;
					maar[tailIndex+1]=maar[tailIndex];
					maar[tailIndex].type=MaarCell::Body;
					field->GetCell(rand()%field->WIDTH,rand()%field->HEIGHT)->content=GameCell::Fruit;
					//TODO: Replace with a cross platform sound playing function
				}
			}

			field->GetCell(x,y)->content=GameCell::Kerm;
			field->GetCell(x,y)->maar=&cell;
		}//end for
	}//end method
}//end Maar namespace

