#include <iostream>
#include <fstream>
#include <string>
#include "Instruments.h"
#include "TreeRegularBuilder.h"
#include "IncludeOperation.h"
#include "CompileConfiguration.h"
#include <filesystem>

using std::cout;
using namespace std::filesystem;

void correctFiles(std::string path, std::string pathTo) {
	std::ifstream inFile(path);
	std::ofstream outFile(pathTo + std::filesystem::path(path).filename().string());

	std::string tmp;
	bool isComment = false;
	while (std::getline(inFile, tmp)) {
		gcew::commons::commentEraser(tmp, isComment);
		tmp = gcew::commons::codeCorrector(tmp);

		std::stringstream ss(tmp);
		std::string includeFinder;
		while (std::getline(ss, includeFinder)) {
			if (gcew::regulars::TreeRegularBuilder::regex(includeFinder) == gcew::commons::RegexResult::Include) {
				gcew::trees::elements::operations::IncludeOperation include(0, includeFinder);
				if (include.isLocalFile()) {
					std::filesystem::path p = std::filesystem::path(path).parent_path();
					p += std::filesystem::path::preferred_separator;
					correctFiles(p.string() + include.getFileName(), pathTo);
				}
			}
		}

		if (tmp.length() > 0 && !isComment)
			outFile << tmp << std::endl;
	}

	inFile.close();
	outFile.close();
}

int main(int argc, char ** argv)
{
	if (argc < 2) {
		cout << "Not found arguments\n";
		return EXIT_FAILURE;
	}

	gcew::commons::CompileConfiguration::path = "configuration.xml";

	auto & conf = gcew::commons::CompileConfiguration::instance();

	std::string fileExecute = argv[1];
	path p = absolute(path(fileExecute));
	path fileFolder = p.parent_path();
	fileFolder += path::preferred_separator;
	fileFolder += conf.getCompilePath();
	fileFolder += path::preferred_separator;
	if (exists(fileFolder))
		remove_all(fileFolder);
	create_directory(fileFolder);
	correctFiles(p.string(), fileFolder.string());

	return 0;
}