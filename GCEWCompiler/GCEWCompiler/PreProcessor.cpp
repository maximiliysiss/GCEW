#include "PreProcessor.h"

std::string gcew::trees::preprocessor::PreProcessor::preProcessorIncluder(std::string path, std::ofstream * fileOutput, bool isLocal)
{
	gcew::commons::CompileConfiguration & conf = gcew::commons::CompileConfiguration::instance();

	std::ifstream file(path);
	std::ofstream * outputFile;
	if (fileOutput)
		outputFile = fileOutput;
	else
		outputFile = new std::ofstream(path.substr(0, path.find_last_of('.')) + "_gen.gcew");

	std::string tmp;
	while (std::getline(file, tmp)) {
		gcew::commons::RegexResult reg = gcew::regulars::TreeRegularBuilder::regex(tmp);
		switch (reg) {
		case gcew::commons::RegexResult::Include:
		{
			gcew::trees::elements::operations::IncludeOperation include(0, tmp);
			if (include.isLocalFile()) {
				std::filesystem::path p(conf.workPath + conf.getCompilePath());
				p += std::filesystem::path::preferred_separator;
				preProcessorIncluder(p.string() + std::filesystem::path(include.getFileName()).filename().string(), outputFile);
			}
			else
				preProcessorIncluder(include.getFileName() + ".gcew", outputFile, false);
			break;
		}
		default:
			(*outputFile) << tmp << std::endl;
			break;
		}
	}


	if (!fileOutput)
		outputFile->close();

	file.close();
	if (isLocal)
		std::filesystem::remove(std::filesystem::path(path));

	if (fileOutput)
		return "";
	return path.substr(0, path.find_last_of('.')) + "_gen.gcew";
}
