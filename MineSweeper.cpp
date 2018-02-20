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
	bool m_dead = false;
	bool m_won = false;
	int m_minecount = 40;

	int toX(int index) {
		return index - (index / 20) * 20;
	}

	int toY(int index) {
		return index / 20;
	}

	int toIndex(int x, int y) {
		return 20 * y + x;
	}

	bool isOutOfBounds(int x, int y) {
		if (x < 0 || x > 19 || y < 0 || y > 19) {
			return true;
		}
		return false;
	}

	void calcNumbers() {
		for (int k = 0; k < 400; k++) {
			if (!m_minefield[k]) {
				int count = 0;
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						int x = toX(k) + 1 - j;
						int y = toY(k) + 1 - i;
						if (!isOutOfBounds(x, y)) {
							if (m_minefield[toIndex(x, y)]) {
								count++;
							}
						}
					}
				}
				m_numbers[k] = count;
			}
		}
	}

protected:
	virtual bool onCreate() {
		srand(time(NULL));
		m_dead = false;
		m_won = false;
		for (int i = 0; i < 400; i++) {
			m_minefield[i] = false;
			m_view[i] = "";
			m_numbers[i] = 0;
		}
		for (int i = 0; i < m_minecount; i++) {
			bool done = false;
			while (!done) {
				int r = rand() % 400;
				if (!m_minefield[r]) {
					m_minefield[r] = true;
					done = true;
				}
			}
		}
		calcNumbers();
		return true;
	}

	virtual bool onUpdate(Input t_input, float t_elapsedTime)
	{
		if (m_dead || m_won) {
			if (t_input.getKey(VK_SPACE).m_pressed) {
				onCreate();
			}
		}
		else if (t_input.getMouseKey(0).m_pressed && !m_dead && !m_won) {
			int x = t_input.getMouseX();
			int y = t_input.getMouseY();
			if (m_minefield[toIndex(x, y)]) {
				m_view[toIndex(x, y)] = "X"; // Hit a mine.
				m_dead = true;
			}
			else {
				// Uncovering the clicked square.
				m_view[toIndex(x, y)] = std::to_string(m_numbers[toIndex(x, y)]);

				// If 0 mines are next to the clicked square.
				if (m_view[toIndex(x, y)] == "0") {
					m_view[toIndex(x, y)] = " ";

					// Runs 20 times to make sure all squares are uncovered.
					for (int a = 0; a < 20; a++) {

						// Looping through all squares.
						for (int k = 0; k < 400; k++) {

							// If square is 0, uncover all squares around it.
							if (m_view[k] == " ") {
								for (int i = 0; i < 3; i++) {
									for (int j = 0; j < 3; j++) {
										int x = toX(k) + 1 - j;
										int y = toY(k) + 1 - i;

										// Only uncover square if the index is within bounds.
										if (!isOutOfBounds(x, y)) {
											m_view[toIndex(x, y)] = std::to_string(m_numbers[toIndex(x, y)]);
											if (m_view[toIndex(x, y)] == "0") {
												m_view[toIndex(x, y)] = " ";
											}
										}
									}
								}
							}
						}
					}
				}

				// Checking if player has won.
				int num = 0;
				for (int i = 0; i < 400; i++) {
					if (m_view[i] == "") {
						num++;
					}
				}
				if (num == m_minecount) {
					m_won = true;
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
			else if (m_view[i] == "X") {
				t_graphics.DrawString(toX(i), toY(i), m_view[i], BEFG_WHITE);
			}
			else {
				t_graphics.DrawString(toX(i), toY(i), m_view[i], BEFG_DARK_GREEN);
			}
		}
		if (m_dead) {
			t_graphics.DrawString(6, 10, "You died");
			t_graphics.DrawString(0, 11, "Press Space to Retry");
		}
		if (m_won) {
			t_graphics.DrawString(6, 10, "You won!");
			t_graphics.DrawString(0, 11, "Press Space to Retry");
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