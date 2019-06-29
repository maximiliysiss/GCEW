#pragma once
#ifndef COMPILECONFIGURATION_H
#define COMPILECONFIGURATION_H

#include <string>
#include <map>
#include "tinyxml.h"

namespace gcew::commons
{

	class CompileConfiguration
	{
		static CompileConfiguration  * compileConfiguration;
		std::map<std::string, std::string> compilerPairs;
		std::string pathForCompile;
		std::string libsPath;
	public:
		static std::string path;
		static std::string workPath;
		static CompileConfiguration & instance();
		inline std::string getCompilePath() const { return pathForCompile; }
		inline std::string getLibsPath() const { return libsPath; }
	private:
		CompileConfiguration();
		void load();
	};


}
#endif // !COMPILECONFIGURATION_H


