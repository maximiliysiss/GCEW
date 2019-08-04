#pragma once
#ifndef COMPILECONFIGURATION_H
#define COMPILECONFIGURATION_H

#include <string>
#include <map>
#include "tinyxml.h"
#include "Instruments.h"

constexpr auto COMMONS = "commons";

namespace gcew::commons
{

	class CompileConfiguration
	{
		static CompileConfiguration  * compileConfiguration;
		std::string pathForCompile;
		std::string libsPath;
	public:
		static std::string path;
		static std::string workPath;
		static CompileConfiguration & instance();
		static std::map<std::string, std::map<Operations, std::string>> typeOperation;
		static std::string getTypeInitializeByValue(std::string value);
		inline std::string getCompilePath() const { return pathForCompile; }
		inline std::string getLibsPath() const { return libsPath; }
	private:
		CompileConfiguration();
		void load();
	};


}
#endif // !COMPILECONFIGURATION_H


