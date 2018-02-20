#include "BrokenEngine2D.hpp"
#include <time.h>
#include <string>

class MineSweeper : public BrokenEngine2D
{
public:
	MineSweeper() {
	}

private:
	bool m_minefield[400];
	int m_numbers[400];
	std::string m_view[400];

	int toX(int index) {
		return index - (index / 20) * 20;
	}

	int toY(int index) {
		return index / 20;
	}

	int toIndex(int x, int y) {
		return 20 * y + x;
	}

	void calcNumbers() {
		for (int i = 0; i < 400; i++) {
			if (!m_minefield[i]) {
				int count = 0;
				if (toY(i) != 0 && toX(i) != 0) {
					if (m_minefield[toIndex(toX(i) - 1, toY(i) - 1)]) {
						count++;
					}
				}
				if (toY(i) != 0) {
					if (m_minefield[toIndex(toX(i), toY(i) - 1)]) {
						count++;
					}
				}
				if (toY(i) != 0 && toX(i) != 19) {
					if (m_minefield[toIndex(toX(i) + 1, toY(i) - 1)]) {
						count++;
					}
				}
				if (toX(i) != 0) {
					if (m_minefield[toIndex(toX(i) - 1, toY(i))]) {
						count++;
					}
				}
				if (toX(i) != 19) {
					if (m_minefield[toIndex(toX(i) + 1, toY(i))]) {
						count++;
					}
				}
				if (toX(i) != 0 && toY(i) != 19) {
					if (m_minefield[toIndex(toX(i) - 1, toY(i) + 1)]) {
						count++;
					}
				}
				if (toY(i) != 19) {
					if (m_minefield[toIndex(toX(i), toY(i) + 1)]) {
						count++;
					}
				}
				if (toY(i) != 19 && toX(i) != 19) {
					if (m_minefield[toIndex(toX(i) + 1, toY(i) + 1)]) {
						count++;
					}
				}
				m_numbers[i] = count;
			}
		}
	}

protected:
	virtual bool onCreate() {
		srand(time(NULL));
		for (int i = 0; i < 400; i++) {
			m_minefield[i] = false;
			m_view[i] = "";
		}
		for (int i = 0; i < 40; i++) {
			int r = rand() % 400;
			m_minefield[r] = true;
		}
		calcNumbers();
		return true;
	}

	virtual bool onUpdate(Input t_input, float t_elapsedTime)
	{
		if (t_input.getMouseKey(0).m_pressed) {
			int x = t_input.getMouseX();
			int y = t_input.getMouseY();
			if (m_minefield[toIndex(x, y)]) {
				m_view[toIndex(x, y)] = "x";
			}
			else {
				m_view[toIndex(x, y)] = std::to_string(m_numbers[toIndex(x, y)]);
				if (m_view[toIndex(x, y)] == "0") {
					m_view[toIndex(x, y)] = " ";
				}
			}
		}
		return true;
	}

	virtual bool onRender(Graphics t_graphics)
	{
		t_graphics.Clear();
		for (int i = 0; i < 400; i++) {
			t_graphics.Draw(toX(i), toY(i));
			if (m_view[i] == "1") {
				t_graphics.DrawString(toX(i), toY(i), m_view[i], BEFG_CYAN);
			}
			else if (m_view[i] == "2") {
				t_graphics.DrawString(toX(i), toY(i), m_view[i], BEFG_GREEN);
			}
			else if (m_view[i] == "3") {
				t_graphics.DrawString(toX(i), toY(i), m_view[i], BEFG_RED);
			}
			else if (m_view[i] == "4") {
				t_graphics.DrawString(toX(i), toY(i), m_view[i], BEFG_DARK_CYAN);
			}
			else {
				t_graphics.DrawString(toX(i), toY(i), m_view[i], BEFG_DARK_GREEN);
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