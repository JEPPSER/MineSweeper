#include "BrokenEngine2D.hpp"

class MineSweeper : public BrokenEngine2D
{
public:
	MineSweeper() {
	}

private:

protected:
	virtual bool onCreate() {
		
		return true;
	}

	virtual bool onUpdate(Input t_input, float t_elapsedTime)
	{

		return true;
	}

	virtual bool onRender(Graphics t_graphics)
	{
		t_graphics.Clear();
		t_graphics.Fill(0, 0, 30, 30, 0x2593, BEFG_GREY);
		return true;
	}
};

int main()
{
	MineSweeper game;
	game.createWindow(20, 20, 20, 20);
	game.start();
	return 0;
}