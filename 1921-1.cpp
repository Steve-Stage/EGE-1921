/*
 *
 * 19-21 (1 куча)
 *
 * moves(a) - вектор возможных вариантов после хода при изначальном кол-ве (a) камней в куче
 *
 * game(s, p, b, ms)
 *
 * s - начальная сумма кучи
 * p - игрок, который должен победить (1 или 2, т.е. Петя или Ваня)
 * b - границы ходов относительно игрока p,
 *	т.е. { 1, 1 } - игрок должен победить за свой первый ход, { 2, 4 } - игрок должен победить за 2, 3 или 4 хода (не за
 *1 ход) ms - минимальная сумма, при которой игрок побеждает
 *
 * возвращает 1, если игрок p может победить вне зависимости от ходов своего противника, и 0 в ином случае
 *
 */

#include <vector>
#include <pair>

std::vector<int> moves(int a)
{
	return { a + 1, a + 4, a * 3 };
}

int g(int x, int s, int p, std::pair<int, int> b, int ms)
{
	int cp = ((x + 1) % 2) + 1;
	int l = 2 * b.first - int(p == 1), r = 2 * b.second - int(p == 1);
	if (s >= ms)
		return int((cp == p) && (x >= l) && (x <= r));
	if (x > r)
		return 0;
	else
	{
		bool won = true;
		if (cp == p)
		{
			for (auto m : moves(s))
			{
				if (g(x + 1, m, p, b, ms) == 0)
				{
					won = false;
					break;
				}
			}
		}
		else
		{
			for (auto m : moves(s))
			{
				if (g(x + 1, m, p, b, ms) == 1)
				{
					won = false;
					break;
				}
			}
			won = !won;
		}
		return int(won);
	}
}

int game(int s, int p, std::pair<int, int> b, int ms)
{
	bool won = true;
	switch (p)
	{
		case 1:
		{
			for (auto m : moves(s))
			{
				if (g(1, m, p, b, ms) == 1)
				{
					won = false;
					break;
				}
			}
			won = !won;
			break;
		}
		case 2:
		{
			for (auto m : moves(s))
			{
				if (g(1, m, p, b, ms) == 0)
				{
					won = false;
					break;
				}
			}
			break;
		}
	}
	return int(won);
}