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
		inline int getIndex() const { return index; }
		Element() = delete;
		Element(int index, std::string line);
		Element(int index, std::string line, RegexResult reg);
		virtual ~Element();
		virtual void toCode(std::string & code) = 0;
		virtual void createData(std::string & code) {}
	};
}

#endif // !ELEMENT_H


