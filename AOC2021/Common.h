#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <algorithm>
#include <regex>
#include <set>
#include <list>
#include <array>
#include <chrono>
#include <functional>

#include "ivec2.h"


extern int g_num_runs;
extern int g_active_day;

inline void setNumRuns(int runs)
{
	g_num_runs = runs;
}

inline void setActiveDay(int day)
{
	g_active_day = day;
}

using day_output = std::function<void(int, int)>;

struct Day {
	int id;
	std::string description;
	std::function<void(day_output)> run;

};

using DayMap = std::map<int, Day>;
DayMap& getDayMap();

inline Day& getDay(int id)
{
	return getDayMap().at(id);
}

template<typename Function>
bool setDay(int day, std::string const& description, Function func)
{
	getDayMap()[day] = { day, description, func };

	return true;
}

static std::string skip_str;
static char skip_char;
static int skip_int;
static double skip_float;

enum Mod
{
	Sorted = 1
};

inline std::vector<std::string> lines_in_file(std::string const& filename, uint32_t mods = 0)
{
	std::vector<std::string> lines;

	std::ifstream file;
	file.open(filename);

	std::string line;
	while (std::getline(file, line))
	{
		lines.push_back(line);
	}

	if (mods & Sorted)
	{
		std::sort(lines.begin(), lines.end());
	}

	file.close();

	return lines;
}

inline std::vector<std::stringstream> linestreams_in_file(std::string const& filename, uint32_t mods = 0)
{
	std::vector<std::stringstream> linestreams;

	std::ifstream file;
	file.open(filename);

	if (!file.is_open())
	{
		std::cout << "ERROR: Could not open " << filename << std::endl;
	}

	std::string line;
	while (std::getline(file, line))
	{
		linestreams.push_back(std::stringstream(line));
	}

	if (mods & Sorted)
	{
		std::sort(linestreams.begin(), linestreams.end(), [](auto const& a, auto const& b) { return a.str() < b.str(); });
	}

	file.close();

	return linestreams;
}

template<typename NumberType>
std::vector<NumberType> numbers_in_file(std::string const& filename, uint32_t mods = 0)
{
	std::vector<NumberType> numbers;

	std::ifstream file;
	file.open(filename);

	NumberType number;
	while (file >> number)
	{
		numbers.push_back(number);
	}

	if (mods & Sorted)
	{
		std::sort(numbers.begin(), numbers.end());
	}

	return numbers;
}

template<typename Container, typename Callback>
void foreach_pair(Container&& container, Callback&& callback)
{
	if (container.size() > 2)
	{
		auto end = container.end();
		auto it1 = container.begin();
		auto it2 = it1 + 1;

		while (it2 != end)
		{
			callback(*(it1++), *(it2++));
		}
	}
}

template<typename Container, typename Callback>
void foreach_triplet(Container&& container, Callback&& callback)
{
	if (container.size() > 2)
	{
		auto end = container.end();
		auto it1 = container.begin();
		auto it2 = it1 + 1;
		auto it3 = it2 + 1;

		while (it3 != end)
		{
			callback(*(it1++), *(it2++), *(it3++));
		}
	}
}

template<typename IntType>
struct Range
{
	struct Iterator
	{
		Iterator(IntType i) : m_value(i) {}
		Iterator(Iterator const& other) : m_value(other.m_value) {}
		bool operator != (Iterator const& other) const { return m_value != other.m_value; }
		void operator ++ () { ++m_value; }
		IntType operator * () { return m_value; }
	private:
		IntType m_value;
	};

	Range(IntType onePastLast)
		: m_begin(0)
		, m_end(onePastLast)
	{
	}

	Range(IntType first, IntType onePastLast)
		: m_begin(first)
		, m_end(onePastLast)
	{
	}

	Iterator begin() const { return Iterator(m_begin); }
	Iterator end() const { return Iterator(m_end); }

private:
	const IntType m_begin;
	const IntType m_end;
};

template<typename IntType = int>
Range<IntType> range(IntType begin, IntType end) { return Range<IntType>(begin, end); }
template<typename IntType = int>
Range<IntType> range(IntType end) { return Range<IntType>(end); }

struct Range2D
{
	struct Iterator
	{
		Iterator(ivec2 const& first, ivec2 const& onePastLast)
			: m_value(first)
			, m_xBegin(first.x)
			, m_xEnd(onePastLast.x)
		{}

		Iterator(Iterator const& other)
			: m_value(other.m_value)
			, m_xBegin(other.m_xBegin)
		{}

		bool operator != (Iterator const& other) const
		{
			return m_value != other.m_value;
		}

		void operator ++ ()
		{
			if (++m_value.x == m_xEnd)
			{
				++m_value.y;
				m_value.x = m_xBegin;
			}
		}

		ivec2 operator * ()
		{
			return m_value;
		}

	private:
		ivec2 m_value;
		int m_xBegin, m_xEnd;
	};

	Range2D(ivec2 const& onePastLast)
		: m_begin(0, 0)
		, m_end(onePastLast)
	{
	}

	Range2D(ivec2 const& first, ivec2 const& onePastLast)
		: m_begin(first)
		, m_end(onePastLast)
	{
	}

	Iterator begin() const { return Iterator(m_begin, m_end); }
	Iterator end() const { return Iterator(ivec2{ m_begin.x, m_end.y }, m_end); }

private:
	ivec2 const m_begin;
	ivec2 const m_end;
};

template<typename Extra>
struct MinMaxFilterSaver
{
	MinMaxFilterSaver(bool b)
		: m_didSave(b)
	{
	}

	template<typename... Extras>
	MinMaxFilterSaver<Extra>& save(Extras&&... extras)
	{
		m_extra = Extra{ extras... };
		return *this;
	}

	template<typename Func>
	MinMaxFilterSaver<Extra>& executeIf(Func func)
	{
		if (m_didSave)
		{
			func();
		}

		return *this;
	}

	template<typename Func>
	MinMaxFilterSaver<Extra>& executeElse(Func func)
	{
		if (!m_didSave)
		{
			func();
		}

		return *this;
	}

	operator bool()
	{
		return m_didSave;
	}

	Extra m_extra;
	bool m_didSave;
};

template<typename T, typename Extra = int>
class MaxFilter
{
	T m_currentBest = std::numeric_limits<T>::min();
	MinMaxFilterSaver<Extra> m_extraSaver{ true };
	MinMaxFilterSaver<Extra> m_extraIgnorer{ false };

public:

	inline MinMaxFilterSaver<Extra>& max(T candidate)
	{
		if (candidate > m_currentBest)
		{
			m_currentBest = candidate;

			return m_extraSaver;
		}

		return m_extraIgnorer;
	}

	inline void reset()
	{
		m_currentBest = std::numeric_limits<T>::min();
		m_extraSaver.m_extra = Extra();
	}

	inline T value() const
	{
		return m_currentBest;
	}

	inline Extra& extra()
	{
		return m_extraSaver.m_extra;
	}
};

template<typename T, typename Extra = int>
class MinFilter
{
	T m_currentBest = std::numeric_limits<T>::max();
	MinMaxFilterSaver<Extra> m_extraSaver{ true };
	MinMaxFilterSaver<Extra> m_extraIgnorer{ false };

public:

	inline MinMaxFilterSaver<Extra>& min(T candidate)
	{
		if (candidate < m_currentBest)
		{
			m_currentBest = candidate;

			return m_extraSaver;
		}

		return m_extraIgnorer;
	}

	inline void reset()
	{
		m_currentBest = std::numeric_limits<T>::min();
		m_extraSaver.m_extra = Extra();
	}

	inline T value() const
	{
		return m_currentBest;
	}

	inline Extra& extra()
	{
		return m_extraSaver.m_extra;
	}
};

/*
template<typename ComponentType, size_t Dim>
struct BoundingBox
{
	template<typename... Component>
	void add(Component&&... comp)
	{
		static_assert(tuple_size<tuple<Component...>>::value == Dim, "Wrong number of arguments.");
		array<ComponentType, Dim> arr{ comp... };
		for (size_t i = 0; i < Dim; ++i)
		{
			m_min[i].min(arr[i]);
			m_max[i].max(arr[i]);
		}
	}

	ComponentType axisSpan(int axis) const
	{
		return 1 + m_max[axis].value() - m_min[axis].value();
	}

	ComponentType axisMin(int axis) const
	{
		return m_min[axis].value();
	}

	ComponentType axisMax(int axis) const
	{
		return m_min[axis].value();
	}

	MinFilter<ComponentType> m_min[Dim];
	MaxFilter<ComponentType> m_max[Dim];
};
*/

template<typename Data>
class Grid2D
{
public:
	Grid2D(int w, int h, Data const& initial = Data())
		: m_width(w)
		, m_height(h)
	{
		m_data.reserve(w * h);
		for (int y = 0; y < m_width; ++y)
		{
			for (int x = 0; x < m_height; ++x)
			{
				m_data.emplace_back(initial);
			}
		}
	}

	Grid2D(Grid2D const& other)
		: m_width(other.m_width)
		, m_height(other.m_height)
		, m_data(other.m_data)
	{
	}

	/*
	Grid2D(BoundingBox<int, 2> const& bb, Data const& initial = Data())
		: m_width(bb.axisSpan(0))
		, m_height(bb.axisSpan(1))
	{
		m_data.reserve(m_width * m_height);
		for (int y = 0; y < m_width; ++y)
		{
			for (int x = 0; x < m_height; ++x)
			{
				m_data.emplace_back(initial);
			}
		}
	}
	*/

	Grid2D<Data> prefixSum() const
	{
		Grid2D<Data> other(*this);

		for (int y = 1; y < m_height; ++y)
		{
			for (int x = 1; x < m_width; ++x)
			{
				other.at(x, y) += other.at(x - 1, y);
			}
		}

		for (int x = 1; x < m_width; ++x)
		{
			for (int y = 1; y < m_height; ++y)
			{
				other.at(x, y) += other.at(x, y - 1);
			}
		}

		return other;
	}

	inline int width() const
	{
		return m_width;
	}

	inline int height() const
	{
		return m_height;
	}

	template<typename IntType = int>
	Range<IntType> xRange() const
	{
		return Range<IntType>(0, width());
	}

	template<typename IntType = int>
	Range<IntType> yRange() const
	{
		return Range<IntType>(0, height());
	}

	template<typename IntType = int>
	Range<IntType> indexRange() const
	{
		return Range<IntType>(0, width() * height());
	}

	Range2D range() const
	{
		return Range2D{ ivec2{0,0}, ivec2{m_width, m_height} };
	}

	inline uint32_t index(int x, int y) const
	{
		return m_width * y + x;
	}

	inline uint32_t index(ivec2 const& p) const
	{
		return m_width * p.y + p.x;
	}

	inline bool valid(ivec2 const& p) const
	{
		return valid(p.x, p.y);
	}

	inline bool valid(int x, int y) const
	{
		return (x >= 0) && (x < m_width) && (y >= 0) && (y < m_height);
	}

	inline Data* ptr(ivec2 const& p)
	{
		if (valid(p))
		{
			return &at(p);
		}

		return nullptr;
	}

	inline Data& at(ivec2 const& p)
	{
		return at(p.x, p.y);
	}

	inline Data& at(int x, int y)
	{
		if (x < 0) x = m_width + x;
		if (y < 0) y = m_height + y;
		size_t i = index(x, y);
		return m_data[i];
	}

	inline Data& operator [] (int index)
	{
		return m_data[index];
	}

	inline Data const& at(ivec2 const& p) const
	{
		return at(p.x, p.y);
	}
	inline Data const& at(int x, int y) const
	{
		return m_data[index(x, y)];
	}

	bool operator == (Grid2D const& other)
	{
		if (m_width != other.m_width || m_height != other.m_height) return false;

		for (int i = 0; i < m_width * m_height; ++i)
		{
			if (m_data[i] != other.m_data[i]) return false;
		}

		return true;
	}

private:
	int m_width;
	int m_height;
	std::vector<Data> m_data;
};

template<typename Data>
inline Data boxSum(Grid2D<Data> const& prefixGrid, ivec2 upperLeft, int boxWidth, int boxHeight)
{
	return prefixGrid.at(upperLeft + ivec2{ boxWidth - 1, boxHeight - 1 })
		- prefixGrid.at(upperLeft + ivec2{ boxWidth - 1, -1 })
		- prefixGrid.at(upperLeft + ivec2{ -1, boxHeight - 1 })
		+ prefixGrid.at(upperLeft + ivec2{ -1, -1 });
}

struct Stopwatch
{
	Stopwatch()
		: m_startTime(std::chrono::high_resolution_clock::now())
	{
	}

	~Stopwatch()
	{
		using namespace std::chrono;
		auto diff = high_resolution_clock::now() - m_startTime;
		auto ms = duration_cast<milliseconds>(diff).count();

		if (g_num_runs == 1)
		{
			std::cout << ms << "ms" << std::endl;
		}
		else
		{
			float scale = 1.0f / g_num_runs;
			std::cout << ms*scale << "ms averaged over " << g_num_runs << " runs" << std::endl;
		}
	}

	std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
};

inline void print()
{
}

template<typename T, typename... TT>
inline void print(T&& t, TT&&... tt)
{
	std::cout << t;
	print(tt...);
}

template<typename T, typename... TT>
inline void println(T&& t, TT&&... tt)
{
	std::cout << t;
	print(tt...);
	std::cout << std::endl;
}

template<typename Transform>
inline auto split(std::string const& str, char delimiter, Transform&& transform)
{
	using T = decltype(transform(std::string()));

	std::vector<T> result;

	std::stringstream ss(str);

	std::string part;
	while (std::getline(ss, part, delimiter))
	{
		if (!part.empty())
		{
			result.push_back(transform(part));
		}
	}

	return result;
};

inline void output(int part, int value)
{
	if (g_num_runs == 1)
	{
		println(part, ": ", value);
	}
};

inline void runDay(Day& day)
{
	Stopwatch localExecutionTimer;
	println("\n>>> Day ", day.id, ": \"", day.description, "\"");
	for (int i = 0; i < g_num_runs; ++i)
	{
		day.run(output);
	}
	print("<<< Day ", day.id, " took ");
}