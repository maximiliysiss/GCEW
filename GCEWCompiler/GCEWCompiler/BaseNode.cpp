#include "BaseNode.h"
#include "Term.h"

namespace gcew::trees::parser
{
	std::string BaseNode::tryGetType()
	{
		if (dynamic_cast<Term*>(this)) {
			return dynamic_cast<Term*>(this)->getType();
		}
		else if (dynamic_cast<Node*>(this)) {
			return dynamic_cast<Node*>(this)->tryGetType();
		}
		return std::string();
	}

	BaseNode::BaseNode()
	{
		name = gcew::commons::createUniqueGUID();
	}

	BaseNode::~BaseNode()
	{
	}

}
