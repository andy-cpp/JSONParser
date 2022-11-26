#include "parser.hpp"
#include <stdexcept>
Parser::Parser(char const* src)
{
	context.src = src;
	context.length = strlen(src);
	context.index = 0;
}

Object ParseValue(ParserContext& ctx);

void CheckWhitespace(ParserContext& ctx)
{
	for (unsigned i = ctx.index; i < ctx.length; ++i)
	{
		if (!isblank(ctx.src[i]) && !isspace(ctx.src[i])) {
			throw std::runtime_error("[Parser::Parse]: extra data found");
		}
	}
}

Object Parser::Parse()
{
	Object value = ParseValue(context);
	CheckWhitespace(context);
	return value;
}

Object ParseNumber(ParserContext& ctx)
{
	size_t len = 0;
	long double number = std::stold(&ctx.src[ctx.index], &len);
	ctx.index += len;
	return number;
}

std::string ParseStr(ParserContext& ctx)
{	
	size_t i = ctx.index + 1;

	while (ctx.src[i] != '"')
	{
		++i;
	}

	char const* ptr = ctx.src + ctx.index + 1;
	size_t len = i - (ctx.index + 1);
	ctx.index = i + 1;
	return std::string(ptr, len);
}

Object::array_t ParseArray(ParserContext& ctx)
{
	Object::array_t array;
	size_t startpos = ctx.index++;
	size_t i = 1; // we skip opening bracket
	bool expect_value = true;
	bool expect_comma = false;
	bool comma_last = false;
	while (true)
	{
		char const& c = ctx.src[ctx.index];

		if (isblank(c) || isspace(c)) {
			++ctx.index;
			continue;
		}

		if (c == ']')
		{
			if (comma_last)
				throw std::runtime_error("[ParseArray]: expected value");
			else {
				++ctx.index;
				break;
			}
		}

		else if (c == ',')
		{
			expect_comma = false;
			expect_value = true;
			comma_last = true;
			++ctx.index;
			continue;
		}

		else if (expect_value)
		{
			array.push_back(ParseValue(ctx));
			expect_comma = true;
			expect_value = false;
			
		}
		else
		{
			throw std::runtime_error("[ParseArray]: unexpected character");
		}

		comma_last = false;
	}



	return array;
}

Object::dictionary_t ParseDictionary(ParserContext& ctx)
{
	Object::dictionary_t dict;
	++ctx.index;

	bool expect_key = true;
	bool expect_value = false;
	bool expect_delimiter = false;
	bool last_delimiter = false;
	bool last_comma = false;
	bool expect_comma = false;
	std::string key;

	while (true)
	{
		char const& c = ctx.src[ctx.index];

		if (isblank(c) || isspace(c)) {
			++ctx.index;
			continue;
		}

		else if (c == '}')
		{
			if (last_delimiter || expect_delimiter || last_comma) {
				throw std::runtime_error("[ParseDictionary]: expected value");
			}
			else {
				++ctx.index;
				break;
			}
		}
		else if (expect_key)
		{
			key = ParseStr(ctx);
			expect_delimiter = true;
			expect_key = false;
			expect_value = false;
		}
		else if (expect_value)
		{
			Object value = ParseValue(ctx);
			expect_value = false;
			expect_key = false;
			expect_comma = true;
			dict[key] = value;
		}
		else if (c == ',' && expect_comma)
		{
			expect_key = true;
			expect_comma = false;
			last_comma = true;
			++ctx.index;
			continue;
		}

		else if (c == ':' && expect_delimiter)
		{
			expect_value = true;
			expect_delimiter = false;
			last_delimiter = true;
			++ctx.index;
			continue;
		}
		else {
			throw std::runtime_error("[ParseDictionary]: unexpected character");

		}
		last_delimiter = false;
		last_comma = false;
	}

	return dict;
}

Object ParseValue(ParserContext& ctx)
{
	char c = ctx.src[ctx.index];
	while (isspace(c) || isblank(c))
	{
		c = ctx.src[++ctx.index];
	}

	switch (c)
	{
	case '"':
		// str
		return ParseStr(ctx);
		break;
	case '{':
		return ParseDictionary(ctx);
		break;
	case '[':
		return ParseArray(ctx);
		break;
	default:
	{
		if (isalnum(c))
		{
			return ParseNumber(ctx);
		}
		throw std::runtime_error("[ParseValue]: invalid value at index " + std::to_string(ctx.index));
	}
	}
}
