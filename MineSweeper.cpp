#include "BrokenEngine2D.hpp"
#include <time.h>

class MineSweeper : public BrokenEngine2D
{
public:
	MineSweeper() {
	}

private:
	bool m_minefield[400];

protected:
	virtual bool onCreate() {
		srand(time(NULL));
		for (int i = 0; i < 400; i++) {
			m_minefield[i] = false;
		}
		for (int i = 0; i < 40; i++) {
			m_minefield[rand() % 400] = true;
		}
		return true;
	}

	virtual bool onUpdate(Input t_input, float t_elapsedTime)
	{

		return true;
	}

	virtual bool onRender(Graphics t_graphics)
	{
		t_graphics.Clear();
		for (int i = 0; i < 400; i++){
			if (!m_minefield[i]) {
				t_graphics.Draw(i - (i / 20) * 20, i / 20);
			}
		}
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