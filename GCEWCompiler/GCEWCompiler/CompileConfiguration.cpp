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

	CompileConfiguration::CompileConfiguration()
	{
	}

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