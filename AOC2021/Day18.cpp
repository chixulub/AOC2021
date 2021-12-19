#define _CRT_SECURE_NO_WARNINGS
#include "Common.h"

using namespace std;

void check(string const& str)
{
	println(str);

	int depth = 0;
	for (char c : str)
	{
		switch (c)
		{
		case '[': ++depth; print(depth); break;
		case ']': --depth; print(depth); break;
		case ',': print(depth > 4 ? '-' : ','); break;
		default: print(depth > 4 ? '!' : '*'); break;
		}
	}

	println("");
}

enum Token
{
	Start = 0,
	End = 1,
	Comma = 2,
	Number = 3
};


list<int> prepare(string const& str)
{
	list<int> tokens;

	for (char c : str)
	{
		switch (c)
		{
		case '[': tokens.push_back(Start); break;
		case ']': tokens.push_back(End); break;
		case ',': tokens.push_back(Comma); break;
		default: tokens.push_back(Number + (c-'0')); break;
		}
	}

	return tokens;
}

void show(list<int> const& tokens)
{
	for (char t : tokens)
	{
		switch (t)
		{
		case Start: print('['); break;
		case End: print(']'); break;
		case Comma: print(','); break;
		default: print(t - Number); break;
		}
	}
	println("");
}

bool split(list<int>& expr)
{
	for (auto it = expr.begin(); it != expr.end(); ++it)
	{
		if (*it > Number)
		{
			int n = *it - Number;

			if (n > 9)
			{
				int a = n / 2;
				int b = n - a;

				it = expr.erase(it);
				expr.insert(it, Start);
				expr.insert(it, Number + a);
				expr.insert(it, Comma);
				expr.insert(it, Number + b);
				expr.insert(it, End);
				return true;
			}
		}
	}

	return false;
}

bool explode(list<int>& expr)
{
	auto find_left_number = [&](auto it)
	{
		++it;

		while (it != expr.rend())
		{
			if (*it >= Number)
			{
				break;
			}

			++it;
		}

		return it;
	};

	auto find_right_number = [&](auto it)
	{
		++it;

		while (it != expr.end())
		{
			if (*it >= Number)
			{
				break;
			}

			++it;
		}

		return it;
	};

	auto start = expr.end();
	int depth = 0;
	for (auto it = expr.begin(); it != expr.end(); ++it)
	{
		char t = *it;
		if (t == Start)
		{
			++depth;
			start = it;
		}
		else if (t == End)
		{
			--depth;
		}
		else if (t == Comma)
		{

		}
		else
		{
			if (depth > 4)
			{
				auto jt = it;
				advance(jt, 2);

				int a = t - Number;
				int b = *jt - Number;

				if (auto l = find_left_number(make_reverse_iterator(it)); l != expr.rend())
				{
					*l += a;
				}

				if (auto r = find_right_number(jt); r != expr.end())
				{
					*r += b;
				}

				advance(jt, 2);
				auto p = expr.erase(start, jt);
				expr.insert(p, Number);
				return true;
			}
		}
	}

	return false;
}

void reduce(list<int>& expr)
{
	for (;;)
	{
		if (explode(expr))
		{
			continue;
		}

		if (split(expr))
		{
			continue;
		}

		break;
	}
}

void add(list<int>& lhs, list<int>& rhs)
{
	if (lhs.empty())
	{
		lhs = rhs;
	}
	else
	{
		lhs.push_front(Start);
		lhs.push_back(Comma);
		lhs.splice(lhs.end(), rhs);
		lhs.push_back(End);
	}
}

list<int>::iterator eval(list<int>::iterator it, uint64_t& value)
{
	if (*it >= Number)
	{
		value = *it - Number;
		return ++it;
	}
	else if (*it == Start)
	{
		uint64_t a=0, b=0;

		it = eval(++it, a);
		it = eval(++it, b);

		value = 3 * a + 2 * b;
		return ++it;
	}

	println("ERROR!");
	return it;
}

static auto day = setDay(18, "Snailfish",
	[&](auto answer)
	{
		auto lines = lines_in_file("input/18.txt");
		list<int> expr;
		for (auto line : lines)
		{
			auto rhs = prepare(line);

			add(expr, rhs);
			reduce(expr);
		}
		show(expr);

		uint64_t part1 = 0;
		eval(expr.begin(), part1);

		answer(1, part1);

		uint64_t part2 = 0;

		for (size_t i = 0; i < lines.size()-1; ++i)
		{
			for (size_t j = i + 1; j < lines.size(); ++j)
			{
				uint64_t val = 0;

				{
					auto a = prepare(lines[i]);
					auto b = prepare(lines[j]);

					add(a, b);
					reduce(a);
					eval(a.begin(), val);

					part2 = max(part2, val);
				}

				{
					auto a = prepare(lines[j]);
					auto b = prepare(lines[i]);

					add(a, b);
					reduce(a);
					eval(a.begin(), val);

					part2 = max(part2, val);
				}
			}
		}

		answer(2, part2);
	}
);
