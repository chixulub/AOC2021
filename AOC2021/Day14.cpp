#define _CRT_SECURE_NO_WARNINGS
#include "Common.h"

using namespace std;

static auto stoi_transform = [](string const& s) { return stoi(s); };

string Apply(map<string, char> const& rules, string const& in)
{
	string out;
	out += in[0];
	foreach_pair(in, [&](char a, char b) {
		char p[2] = {a,b};
		string part(p, 2);

		if (rules.count(part))
		{
			out += rules.at(part);
		}
		out += b;
	});

	return out;
}

namespace
{

struct Rule
{
	char left, right;
	char symbol;
	Rule* left_rule = 0;
	Rule* right_rule = 0;
	size_t index = 0;

	string str() const
	{
		return string(&left, 2);
	}
};

struct RuleSet
{
	vector<Rule> rules;
	vector<uint64_t> counts;
	map<char, uint64_t> char_counts;

	void insert_rule(char left, char right, char symbol)
	{
		Rule r;
		r.left = left;
		r.right = right;
		r.symbol = symbol;

		rules.push_back(r);
	}

	void link_rules()
	{
		counts = vector<size_t>(rules.size(), 0);

		for (size_t i = 0; i < rules.size(); ++i)
		{
			auto& r = rules[i];
			r.left_rule = find_rule(r.left, r.symbol);
			r.right_rule = find_rule(r.symbol, r.right);
			r.index = i;
		}
	}

	void seed(string const& seed)
	{
		foreach_pair(seed, [this](char left, char right)
		{
			auto r = find_rule(left, right);
			++counts[r->index];
		});

		for (auto c : seed)
		{
			++char_counts[c];
		}
	}

	Rule* find_rule(char left, char right)
	{
		for (size_t i = 0; i < rules.size(); ++i)
		{
			auto r = &rules[i];

			if (r->left == left && r->right == right)
			{
				return r;
			}
		}

		return nullptr;
	}

	void expand()
	{
		vector<uint64_t> next(counts.size(), 0);

		for (auto& rule : rules)
		{
			auto r = rule.right_rule;
			auto c = counts[rule.index];
			next[rule.left_rule->index] += c;
			next[rule.right_rule->index] += c;

			char_counts[rule.symbol] += c;
		}

		swap(counts, next);
	}

	uint64_t score() const
	{
		uint64_t maximum = 0;
		uint64_t minimum = numeric_limits<uint64_t>::max();
		for (auto it : char_counts)
		{
			maximum = max(it.second, maximum);
			minimum = min(it.second, minimum);
		}

		return maximum - minimum;
	}
};
}

static auto day = setDay(14, "Extended Polymerization",
	[&](auto answer)
	{
		RuleSet rules;
			
		for (auto line : lines_in_file("input/14.txt"))
		{
			rules.insert_rule(line[0], line[1], line[6]);
		}

		rules.link_rules();
		rules.seed("CFFPOHBCVVNPHCNBKVNV");

		for (int i = 0; i < 10; ++i)
		{
			rules.expand();
		}

		auto part1 = rules.score();

		for (int i = 10; i < 40; ++i)
		{
			rules.expand();
		}

		auto part2 = rules.score();

		answer(1, part1);
		answer(2, part2);
	}
);
