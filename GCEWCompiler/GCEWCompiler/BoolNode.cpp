#include "BoolNode.h"

gcew::trees::parser::BoolNode::BoolNode(std::string operationType)
{
	boolOperationName = operationType + gcew::commons::createUniqueGUID();
}

gcew::trees::parser::BoolNode::~BoolNode()
{
}
