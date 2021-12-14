#include "Common.h"

using namespace std;

static auto stoi_transform = [](string const& s) { return stoi(s); };

struct Node
{
	string name;
	vector<Node*> reachable;
};

map<string, Node*> nodes;

void add_edge(string const& from, string const& to)
{
	if (nodes.count(from) == 0) { nodes.emplace(from, new Node()).first->second->name = from; }
	if (nodes.count(to) == 0) { nodes.emplace(to, new Node()).first->second->name = to; }

	nodes[from]->reachable.push_back(nodes[to]);
	nodes[to]->reachable.push_back(nodes[from]);
}

uint64_t part1 = 0;

void traverse(Node const* node, set<Node const*> forbidden, Node const* end)
{
	if (node == end)
	{
		++part1;
		return;
	}

	for (auto& next : node->reachable)
	{
		if (forbidden.count(next) == 0)
		{
			auto next_forbidden = forbidden;
			if (node->name[0] & 32)
			{
				next_forbidden.insert(node);
			}

			traverse(next, next_forbidden, end);
		}
	}
}

bool is_small(Node const* node)
{
	return node->name[0] & 32;
}

auto expired = new Node();
uint64_t part2 = 0;
void traverse2(Node const* node, set<Node const*> forbidden, Node const* end, Node const* exception)
{

	if (node == end)
	{
		if (exception == nullptr || exception == expired)
		{
			++part2;
		}

		return;
	}

	for (auto& next : node->reachable)
	{
		if (forbidden.count(next) == 0)
		{
			if (is_small(node))
			{
				auto next_forbidden = forbidden;

				if (exception == nullptr)
				{
					traverse2(next, forbidden, end, node);

					next_forbidden.insert(node);
					traverse2(next, next_forbidden, end, nullptr);
				}
				else
				{
					next_forbidden.insert(node);

					if (node == exception)
					{
						traverse2(next, next_forbidden, end, expired);
					}
					else
					{
						traverse2(next, next_forbidden, end, exception);
					}
				}
			}
			else
			{
				traverse2(next, forbidden, end, exception);
			}

		}
	}
}

static auto day = setDay(12, "Passage Pathing",
	[&](auto answer)
	{
		nodes = {};
		part1 = part2 = 0;

		for (auto& line : lines_in_file("input/12.txt"))
		{
			auto i = line.find('-');

			auto from = line.substr(0, i);
			auto to = line.substr(i+1);

			add_edge(from, to);
		}

		traverse(nodes["start"], {}, nodes["end"]);
		traverse2(nodes["start"], { nodes["start"] }, nodes["end"], nullptr);

		answer(1, part1);
		answer(2, part2);
	}
);
