#define _CRT_SECURE_NO_WARNINGS
#include "Common.h"

using namespace std;

static map<char, string> binmap =
{
	{'0', "0000"},
	{'1', "0001"},
	{'2', "0010"},
	{'3', "0011"},
	{'4', "0100"},
	{'5', "0101"},
	{'6', "0110"},
	{'7', "0111"},
	{'8', "1000"},
	{'9', "1001"},
	{'A', "1010"},
	{'B', "1011"},
	{'C', "1100"},
	{'D', "1101"},
	{'E', "1110"},
	{'F', "1111"}
};

string to_bits(string const& input)
{
	string output = "";

	for (char c : input)
	{
		output += binmap[c];
	}

	return output;
}

int read_num(char const* bits, int num_bits)
{
	int num = 0;

	for (int i = 0; i< num_bits; ++i)
	{
		num = (num << 1) + (bits[i] == '1');
	}

	return num;
}

int read_literal(char const* bits, uint64_t& output)
{
	int i = 0;
	output = 0;
	while (bits[i] == '1')
	{
		output = (output << 4) + read_num(&bits[i + 1], 4);
		i += 5;
	}

	output = (output << 4) + read_num(&bits[i + 1], 4);
	i += 5;

	return i;
}

uint64_t eval_operator(int op, vector<uint64_t> const& values)
{
	uint64_t result = 0;

	switch (op)
	{
	case 0: for (auto v : values) { result += v; } break;
	case 1: { result = 1; for (auto v : values) { result *= v; } } break;
	case 2: result = std::ranges::min(values); break;
	case 3: result = std::ranges::max(values); break;
	case 5: result = values[0] > values[1];  break;
	case 6: result = values[0] < values[1]; break;
	case 7: result = values[0] == values[1]; break;
	}

	return result;
}

int read_packet(char const* packet, uint64_t& value);

int read_operator(int op, char const* bits, uint64_t& value)
{
	int i = 0;

	vector<uint64_t> values;

	if (bits[0] == '1')
	{
		int num_sub_packets = read_num(bits + 1, 11);
		i = 12;

		for (int s = 0; s < num_sub_packets; ++s)
		{
			uint64_t sub_value = 0;
			i += read_packet(bits + i, sub_value);
			values.push_back(sub_value);
		}
	}
	else
	{
		int num_sub_bits = read_num(bits + 1, 15);
		i = 16;

		while (i < num_sub_bits + 16)
		{
			uint64_t sub_value = 0;
			i += read_packet(bits + i, sub_value);
			values.push_back(sub_value);
		}
	}

	value = eval_operator(op, values);
	return i;
}

static uint64_t version_sum = 0;

int read_packet(char const* packet, uint64_t& value)
{
	int version = read_num(packet, 3);
	int type = read_num(packet + 3, 3);

	version_sum += version;

	int offset = 6;
	switch (type)
	{
	case 4:
		{
			offset += read_literal(packet + offset, value);			
		}
		break;
	default:
		{
			offset += read_operator(type, packet + offset, value);
		}
	}

	return offset;
}

static auto day = setDay(16, "Packet Decoder",
	[&](auto answer)
	{
		auto input = to_bits(lines_in_file("input/16.txt").front());

		uint64_t part2 = 0;
		read_packet(input.c_str(), part2);

		uint64_t part1 = version_sum;

		answer(1, part1);
		answer(2, part2);
	}
);
