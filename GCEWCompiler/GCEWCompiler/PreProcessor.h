#pragma once
#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <string>
#include <filesystem>
#include <fstream>
#include "TreeRegularBuilder.h"
#include "IncludeOperation.h"

namespace gcew::trees::preprocessor
{
	struct PreProcessor
	{
		static std::string preProcessorIncluder(std::string path, std::ofstream * file, bool isLocal = true);
	};
}


#endif // !PREPROCESSOR_H


