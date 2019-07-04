#pragma once
#ifndef ENUMS_H
#define ENUMS_H

namespace gcew::commons
{
	enum RegexResult {
		Include,
		Type,
		For,
		While,
		If,
		Else,
		Function,
		Procedure,
		NotClassic,
		FigureClose,
		FigureOpen,
		Mathematic,
		Assigment,
		Call,
		Break,
		Continue,
		PureAsm,
		Class,
		Struct,
		Return,
		Block
	};
}

#endif // !ENUMS_H
