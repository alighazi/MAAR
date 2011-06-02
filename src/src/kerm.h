#include <vector>

using std::vector;

struct RECTf
{
    float    left;
    float    top;
    float    right;
    float    bottom;
	RECTf(float Left, float Top, float Right, float Bottom):left(Left),top(Top),right(Right),bottom(Bottom)	{}
} ;


enum Direction
{
	DIR_Up=0,
	DIR_Left,
	DIR_Down,
	DIR_Right
};
class KermCell
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
	KermCell()
	{
		x=y=0;
		type=Empty;
		dir=DIR_Left;
	}
};



class GameCell
{
private:
	static GLubyte colors[4][3];
public:
	enum Content{Empty=0, Kerm=1, Fruit=2, Wall=3};
	static vec2f dimensions;
	Content content;
	KermCell *kerm;
	GameCell()
	{
	}
	
	static void SetContentColor(Content c, GLubyte r,GLubyte g, GLubyte b)
	{
		colors[(int)c][0]=r;
		colors[(int)c][1]=g;
		colors[(int)c][2]=b;
	}

	static GLubyte* GetContentColor(Content c)
	{
		return colors[(int)c];
	}

	GLubyte* GetColor()
	{

		GLubyte ret[3];
		if(content==Kerm)
			switch(kerm->type)
			{
			case KermCell::Head:
				ret[0]= 0xff;
				ret[1]= 0xff;
				ret[2]= 0;
				return ret;
			case KermCell::Tail:
				ret[0]=0xff;
				ret[1]=0;
				ret[2]=0xff;
				return ret;
			}
		return colors[(int)content];
	}

};

class EntityBase
{
public:
	virtual void Draw(){}
	virtual void Update()=0;
};
//Kind of manager class for GameCell
class GameField
{
private:
	vector<GameCell> cells;
public:
	const int WIDTH,HEIGHT;	
	GLubyte BackGroundColor[3];

	GameField(int Width, int Height):WIDTH(Width),HEIGHT(Height)
	{
		cells.resize(HEIGHT * WIDTH);
		for(int i=0; i<cells.size(); i++)
			cells[i].content=GameCell::Empty;

		//coin in the first fruit
		GetCell(rand()%WIDTH, rand()%HEIGHT)->content=GameCell::Fruit;
	}

	//calculates the rectangle dedicated to this cell based on the gamefield size
	RECTf GetRect(int x, int y)
	{
		return RECTf(GameCell::dimensions.x*x
					,GameCell::dimensions.y*(y+1)	
					,GameCell::dimensions.x*(x+1)							
					,GameCell::dimensions.y*y);
	}

	inline GameCell* GetCell(int x,int y)
	{
		return &cells[y*WIDTH+x];
	}

	//Draws 
	void Draw()
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
					glutWireSphere(1,32,32);
					glRectf(r.left,r.bottom,r.right,r.top);
				}
			}
		}
	}

	void GameCycle()
	{
	
	}

	~GameField()
	{

	}
};

vec2f GameCell::dimensions;
GLubyte GameCell::colors[4][3]={{32,32,32},{255,255,0},{255,0,255},{100,20,0}};


class Kerm
{
private:
	int tailIndex;
	
public:
	int Length;
	const int MAX_LENGHT;
	KermCell *kerm;	
	GameField *field;

	Kerm(int MaxLength, int x ,int y, GameField *gameField)
		:MAX_LENGHT(MaxLength),field(gameField)
	{
		kerm=new KermCell[MAX_LENGHT];
		kerm[0].type=KermCell::Head;
		kerm[0].dir=DIR_Right;
		kerm[0].x=x;
		kerm[1].type=KermCell::Body;
		kerm[1].dir=DIR_Right;
		kerm[1].x=x-1;
		kerm[2].type=KermCell::Tail;
		kerm[2].x=x-2;

		kerm[0].y=kerm[1].y=kerm[2].y=y;
	}
	~Kerm()
	{
		delete[] kerm;
	}

	KermCell operator[](int i)
	{
		return kerm[i];
	}
	
	void ResetCells()
	{		
		for(int i=0; i<MAX_LENGHT; i++)
			field->GetCell(kerm[i].x, kerm[i].y)->content=GameCell::Empty;
	}

	/*
	Kerm:    =OOOk
	indexes: 43210
	0: head, 4: tail 3,2,1: body	
	*/

	void Cycle(Direction direction)
	{
		bool lengthMaxed=false;
		bool ateFruit=false;
		int tailIndex;
		ResetCells();
		for(int i=MAX_LENGHT-1; i>=0; i--)
		{
			KermCell &cell=kerm[i];			
			int &x=cell.x, &y=cell.y;
			//doing type specific ops on current kerm body type
			switch(cell.type)
			{
			case KermCell::Head:
				//assign the direction, don't let the kerm to reverse its direction
				if((direction==DIR_Left && cell.dir!=DIR_Right)
					||(direction==DIR_Right && cell.dir!=DIR_Left)
					||(direction==DIR_Up && cell.dir!=DIR_Down)
					||(direction==DIR_Down && cell.dir!=DIR_Up))
					cell.dir=direction;
				break;

			case KermCell::Tail:
				tailIndex = i;
				Length = tailIndex + 1;
				lengthMaxed = tailIndex == MAX_LENGHT - 1;
				cell.dir=kerm[i-1].dir;
				break;
			case KermCell::Body:
				cell.dir=kerm[i-1].dir;
				break;
			case KermCell::Empty:
				continue;
				break;
			}		
		}


		for(int i=0; i<Length; i++)
		{
			KermCell &cell=kerm[i];	
			int &x=cell.x, &y=cell.y;

			if(cell.type==KermCell::Tail)
			{
				if(ateFruit)
					continue;

				field->GetCell(x,y)->content=GameCell::Empty;
				field->GetCell(x,y)->kerm=NULL;
			}

			switch(kerm[i].dir)
			{
			case DIR_Up:					
					kerm[i].y++;
				break;
			case DIR_Down:
					kerm[i].y--;
				break;
			case DIR_Left:
					kerm[i].x--;
				break;
			case DIR_Right:					
					kerm[i].x++;
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

			
			if(cell.type==KermCell::Head && field->GetCell(x,y)->content==GameCell::Fruit && !lengthMaxed)
			{
				ateFruit=true;
				Length++;
				kerm[tailIndex+1]=kerm[tailIndex];
				kerm[tailIndex].type=KermCell::Body;
				field->GetCell(rand()%field->WIDTH,rand()%field->HEIGHT)->content=GameCell::Fruit;
				MessageBeep(MB_ICONEXCLAMATION);
			}


			field->GetCell(x,y)->content=GameCell::Kerm;
			field->GetCell(x,y)->kerm=&cell;
		}	

	}
};





class KermGame
{
private:
	static KermGame *_instance;
	int _lastPressedKey;
	vec2i gridDimensions;
public:
	static vec2i windowDimensions;
	int updateInterval;
	GameField *game;
	Kerm *kerm;
	inline static KermGame* GetInstance(){return _instance;}
	inline void SetLastPressedKey(int key){_lastPressedKey=key;}
	KermGame()
	{
		gridDimensions=vec2i(40,30);
		SetSize(windowDimensions.x,windowDimensions.y);
		updateInterval=50;
		game=new GameField(gridDimensions.x,gridDimensions.y);
		kerm=new Kerm(40, 20,15, game);
		GameCell::SetContentColor(GameCell::Empty, 50,60,70);
		GameCell::SetContentColor(GameCell::Kerm, 0xff,0,0);
		GameCell::SetContentColor(GameCell::Fruit, 0x20,0xff,0);
		GameCell::SetContentColor(GameCell::Wall, 0x50,0x20,0x20);
	}
	void SetSize(int width, int height)
	{
		KermGame::windowDimensions=vec2i(width, height);
		GameCell::dimensions=vec2f(KermGame::windowDimensions.x/gridDimensions.x,KermGame::windowDimensions.y/gridDimensions.y);
		
	}
	void Update(float dts)
	{
		Direction dir=DIR_Right;
		switch(_lastPressedKey)
		{
		case GLUT_KEY_LEFT:
			dir=DIR_Left;
			break;
		case GLUT_KEY_RIGHT:
			dir=DIR_Right;
			break;
		case GLUT_KEY_UP:
			dir=DIR_Up;
			break;
		case GLUT_KEY_DOWN:
			dir=DIR_Down;
			break;
		}
		kerm->Cycle(dir);
	}
	void Draw()
	{
		game->Draw();
	}
	~KermGame()
	{
		delete game;
		delete kerm;
	}
};

vec2i KermGame::windowDimensions=vec2i(800, 600);
KermGame *KermGame::_instance=new KermGame();
