#include "CompileConfiguration.h"


namespace gcew::commons
{
	CompileConfiguration * CompileConfiguration::compileConfiguration = nullptr;
	std::string CompileConfiguration::path = "";
	std::string CompileConfiguration::workPath = "";

	CompileConfiguration & CompileConfiguration::instance()
	{
		if (compileConfiguration)
			return *compileConfiguration;
		compileConfiguration = new CompileConfiguration();
		compileConfiguration->load();
		return *compileConfiguration;
	}

	std::string CompileConfiguration::getTypeInitializeByValue(std::string value)
	{
		if (value.find('.') != std::string::npos && gcew::commons::isNumber(value))
			return "double";
		if (gcew::commons::isNumber(value))
			return "int";
		if (std::count(value.begin(), value.end(), '\'') >= 2)
			return "string";
		return  "";
	}

	CompileConfiguration::CompileConfiguration()
	{
	}

	std::map < std::string, std::map<Operations, std::string>> CompileConfiguration::typeOperation = {
		{COMMONS,{
			{Operations::Plus, "fadd"},
			{Operations::Minus, "fsub"},
			{Operations::Multiply, "fmul"},
			{Operations::Divide, "fdiv"},
		}},
		{"int",{
			{Operations::Plus, "fiadd"},
			{Operations::Minus, "fisub"},
			{Operations::Divide, "fimul"},
			{Operations::Multiply, "fidiv"},
			{Operations::FieldSet, "fild"},
			{Operations::Convert, "dword"},
			{Operations::FieldGet, "fistp"}
		}},
		{"double",{
			{Operations::Plus, "fadd"},
			{Operations::Minus, "fsub"},
			{Operations::Divide, "fmul"},
			{Operations::Multiply, "fdiv"},
			{Operations::FieldSet, "fld"},
			{Operations::Convert, "real8"},
			{Operations::FieldGet, "fstp"}
		}},
		{"float",{
			{Operations::Plus, "fadd"},
			{Operations::Minus, "fsub"},
			{Operations::Divide, "fmul"},
			{Operations::Multiply, "fdiv"},
			{Operations::FieldSet, "fld"},
			{Operations::Convert, "real8"},
			{Operations::FieldGet, "fstp"}
		}},
		{"bool",{
			{Operations::Convert, "byte"},
			{Operations::BoolStart, "startbool"},
			{Operations::BoolTrue, "outtrue"},
			{Operations::BoolFalse, "outfalse"},
		}},
		{"string",{
			{Operations::Convert, ""}
		}}
	};

	void CompileConfiguration::load()
	{
		if (path.length() == 0)
			throw std::exception("path is null");

		TiXmlDocument doc;
		TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");
		doc.LinkEndChild(decl);
		doc.LoadFile(path.c_str(), TIXML_ENCODING_UTF8);
		if (doc.Error())
			throw std::exception(doc.ErrorDesc());

		TiXmlElement * global = doc.FirstChildElement();
		libsPath = global->Attribute("Libs");
		pathForCompile = global->Attribute("Compile");

		for (auto tag = global->FirstChildElement(); tag != nullptr; tag = tag->NextSiblingElement()) {
			std::string name = tag->Attribute("Name");
			std::string value = tag->Attribute("Value");
			compilerPairs[name] = value;
		}
	}

}