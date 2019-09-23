#pragma once
#include "Element.h"
#include "Instruments.h"
#include "BaseNode.h"
#include "Parser.h"

namespace  gcew::trees::elements
{

	class Variable
		:public Element
	{
	protected:
		std::string name;
		std::string codeName;
		std::string type;
		gcew::trees::parser::BaseNode * exp;
	public:
		virtual bool isCallFunction(std::string name) override;
		virtual void postWork(void * tree) override;
		inline std::string getCodeName() const { return codeName; }
		inline std::string getName() const { return name; }
		inline std::string getType() const { return type; }
		Variable(int index, std::string line);
		void toCode(std::string & code);
		virtual void createData(std::string & code) override;
		~Variable();
	};
}


