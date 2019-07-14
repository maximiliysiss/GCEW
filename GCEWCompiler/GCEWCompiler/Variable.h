#pragma once
#include "Element.h"
#include "BaseNode.h"
#include "Term.h"
#include "Instruments.h"

namespace  gcew::trees::elements
{
	class Variable
		:public Element
	{
	protected:
		std::string name;
		std::string type;
		gcew::trees::parser::BaseNode * exp;
	public:
		inline std::string getName() const { return name; }
		inline std::string getType() const { return type; }
		Variable(int index, std::string line);
		void toCode(std::string & code);
		virtual void createInitializeData(std::string & code) override;
		virtual void createData(std::string & code) override;
		~Variable();
	};
}


