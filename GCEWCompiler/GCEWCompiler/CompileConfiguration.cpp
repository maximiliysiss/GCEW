#include "CompileConfiguration.h"
#include <iostream>
#include <filesystem>


namespace gcew::commons
{
	CompileConfiguration* CompileConfiguration::compileConfiguration = nullptr;
	std::string CompileConfiguration::path = "";
	std::string CompileConfiguration::workPath = "";

	CompileConfiguration& CompileConfiguration::instance()
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

	std::map<std::string, std::map<Operations, std::string>> CompileConfiguration::typeOperation;

	void CompileConfiguration::load()
	{
		if (path.length() == 0)
			throw std::exception("path is null");

		auto configPath = std::filesystem::path(this->path);

		std::cout << "Load configuration " << configPath.string() << std::endl;
		std::cout << "Is exists configuration: " << std::boolalpha << std::filesystem::exists(configPath) << std::endl;

		try {

			TiXmlDocument doc;
			TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");
			doc.LinkEndChild(decl);
			doc.LoadFile(path.c_str(), TIXML_ENCODING_UTF8);
			if (doc.Error())
				throw std::exception(doc.ErrorDesc());

			TiXmlElement* global = doc.FirstChildElement();
			libsPath = global->Attribute("Libs");
			pathForCompile = global->Attribute("Compile");

			auto typeOpers = global->FirstChild("typeOperations");

			for (auto tag = typeOpers->FirstChildElement(); tag != nullptr; tag = tag->NextSiblingElement()) {
				std::string name = tag->Attribute("name");
				std::map<Operations, std::string> operations;
				for (auto tagInner = tag->FirstChildElement(); tagInner != nullptr; tagInner = tagInner->NextSiblingElement()) {
					std::string value = tagInner->Attribute("value");
					Operations oper = (Operations)std::stoi(tagInner->Attribute("type"));
					operations[oper] = value;
				}
				typeOperation[name] = operations;
			}
		}
		catch (std::exception ex) {
			std::cout << "Exception load configuration: " << ex.what() << std::endl;
			throw ex;
		}
	}

}