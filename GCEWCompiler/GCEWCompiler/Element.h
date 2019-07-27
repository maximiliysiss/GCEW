#pragma once
#ifndef ELEMENT_H
#include <string>
#include "Enums.h"

#define ELEMENT_H

namespace  gcew::trees::elements
{
	using namespace gcew::commons;

	class Element
	{
	protected:
		int index;
		std::string line;
		RegexResult nodeType;
	public:
		inline RegexResult getRegexType() const { return nodeType; }
		inline int getIndex() const { return index; }
		Element() = delete;
		Element(int index, std::string line);
		Element(int index, std::string line, RegexResult reg);
		virtual ~Element();
		virtual void createInitializeData(std::string & code) {}
		virtual void toCode(std::string & code) = 0;
		virtual void createData(std::string & code) {}
	};
}

#endif // !ELEMENT_H


