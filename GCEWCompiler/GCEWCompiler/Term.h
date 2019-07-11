#pragma once
#ifndef TERM_H
#define TERM_H

#include "BaseNode.h"

namespace gcew::trees::parser
{
	class Term :
		public BaseNode
	{
	protected:
		bool isTemp{ false };
		std::string value;
		std::string type;
	public:
		inline std::string getValue() const { return value; }
		Term(std::string value);
		~Term();
		virtual void createData(std::string & code) override;
		// Inherited via BaseNode
		virtual void toCode(std::string & code) override;
	};
}

#endif // !TERM_H


