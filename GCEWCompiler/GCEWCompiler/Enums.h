#pragma once

namespace gcew::commons
{
	enum Operations {
		FieldSet = 0,
		Convert = 1,
		Plus = '+',
		Minus = '-',
		Multiply = '*',
		Divide = '/',
		And = '&',
		Or = '|',
		Greater = '>',
		Lower = '<',
		Equal = '=',
		Not = '!',
		Mod = '%'
	};

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
