/*Copyright (c) 2018 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#ifndef NEW_PARSER_H
#define NEW_PARSER_H



#include <istream>
#include <functional>
#include <list>
#include <map>
#include <optional>
#include <regex>
#include <string>
#include <utility>



namespace commonItems
{

typedef std::function<void(const std::string&, std::istream&)> parsingFunction;

class parser
{
	public:
		parser() = default;
		~parser() = default;
		parser(const parser&) = default;
		parser(parser&&) = default;
		parser& operator=(const parser&) = default;
		parser& operator=(parser&&) = default;

		void registerKeyword(std::string keyword, parsingFunction);
		void registerKeyword(std::regex keyword, parsingFunction);
		void parseStream(std::istream& theStream);
		void parseFile(const std::string& filename);

		void clearRegisteredKeywords() noexcept;

		std::optional<std::string> getNextToken(std::istream& theStream);
		std::optional<std::string> getNextTokenWithoutMatching(std::istream& theStream);

	private:
		std::map<std::string, parsingFunction> registeredKeywordStrings;
		std::list<std::pair<std::regex, parsingFunction>> registeredKeywordRegexes;
		std::string nextToken;
		int braceDepth = 0;
};

}



#endif // NEW_PARSER_H