#include "GameField.h"
#include <gl/GLee.h>
namespace MAAR
{
	GameField::GameField(int Width, int Height):WIDTH(Width),HEIGHT(Height)
	{
		cells.resize(HEIGHT * WIDTH);
		for(int i=0; i<cells.size(); i++)
			cells[i].content=GameCell::Empty;

		//coin in the first fruit
		GetCell(rand()%WIDTH, rand()%HEIGHT)->content=GameCell::Fruit;
	}

	RECTf GameField::GetRect(int x, int y)
	{
		return RECTf(GameCell::dimensions.x*x
					,GameCell::dimensions.y*(y+1)	
					,GameCell::dimensions.x*(x+1)							
					,GameCell::dimensions.y*y);
	}

	void GameField::Draw()
	{
		//Draw background
		glColor3ubv(GameCell::GetContentColor(GameCell::Empty));
		glRectf(0,0,WIDTH*GameCell::dimensions.x,HEIGHT*GameCell::dimensions.y);
		
		for(int i=0;i<HEIGHT;i++)
		{
			for(int j=0;j<WIDTH;j++)
			{
				if(GetCell(j,i)->content!=GameCell::Empty)
				{
					GameCell *c=GetCell(j,i);
					glColor3ubv(c->GetColor());
					RECTf r=GetRect(j,i);
					glRectf(r.left,r.bottom,r.right,r.top);
				}
			}
		}
	}

	void GameField::GameCycle()
	{
	
	}

	GameField::~GameField()
	{

	}
}