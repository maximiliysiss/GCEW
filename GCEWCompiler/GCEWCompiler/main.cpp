#include <iostream>
#include <fstream>
#include <string>
#include "Tree.h"
#include "Instruments.h"
#include "TreeRegularBuilder.h"
#include "IncludeOperation.h"
#include "CompileConfiguration.h"
#include "PreProcessor.h"
#include "ElementsContrustor.h"
#include <filesystem>

using std::cout;
using namespace std::filesystem;
using namespace gcew::trees::structural;
using namespace gcew::trees::elements::operations;

std::string correctFiles(std::string path, std::string pathTo) {
	std::ifstream inFile(path);
	std::string resultPath = pathTo + std::filesystem::path(path).filename().string();
	std::ofstream outFile(resultPath);

	std::string tmp;
	bool isComment = false;
	while (std::getline(inFile, tmp)) {
		gcew::commons::commentEraser(tmp, isComment);
		tmp = trim(tmp);
		tmp = gcew::commons::codeCorrector(tmp);

		std::stringstream ss(tmp);
		std::string includeFinder;
		while (std::getline(ss, includeFinder)) {
			gcew::commons::RegexResult reg = gcew::regulars::TreeRegularBuilder::regex(includeFinder);
			if (reg == gcew::commons::RegexResult::Include) {
				gcew::trees::elements::operations::IncludeOperation include(0, includeFinder);
				if (include.isLocalFile())
					correctFiles(include.getFileName(), pathTo);
			}
		}

		if (tmp.length() > 0 && !isComment)
			outFile << tmp << (isBracketCorrect(tmp) ? "\n" : "");
	}

	inFile.close();
	outFile.close();
	return resultPath;
}

Tree * generateTree(std::string path) {
	std::ifstream fileRead(path);
	std::string line;
	int index = 0;
	Tree * root = new Tree(0, "", RegexResult::NotClassic);
	while (std::getline(fileRead, line)) {
		RegexResult reg = gcew::regulars::TreeRegularBuilder::regex(line);
		switch (reg) {
		case RegexResult::Type:
		case RegexResult::Assigment:
		case RegexResult::Break:
		case RegexResult::Call:
		case RegexResult::Continue:
			root->addOperation(gcew::trees::construct_elements(reg, index, line));
			break;
		case RegexResult::Else:
		{
			ElseTree * elseTree = (ElseTree*)gcew::trees::construct_elements(reg, index, line);
			std::getline(fileRead, line);
			root->findIfTreePrev()->setElse(elseTree);
			root = root->addChild(elseTree);
			break;
		}
		case RegexResult::FigureClose:
			root = root->getParent();
			break;
		case RegexResult::FigureOpen:
			root = root->addChild(new Tree(index, "", RegexResult::Block));
			break;
		case RegexResult::While:
		case RegexResult::Function:
		case RegexResult::For:
		case RegexResult::If:
		case RegexResult::PureAsm:
			root = root->addChild((Tree*)gcew::trees::construct_elements(reg, index, line));
			std::getline(fileRead, line);
			break;
		case RegexResult::Return:
		{
			gcew::trees::elements::operations::ReturnOperation * ret = (ReturnOperation*)gcew::trees::construct_elements(reg, index, line);
			ret->setFunctionTree((FunctionTree*)root);
			root->addOperation(ret);
			break;
		}
		}
		index++;
	}
	return nullptr;
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
	conf.workPath = fileFolder.string();
	fileFolder += conf.getCompilePath();
	fileFolder += path::preferred_separator;

	if (exists(fileFolder))
		remove_all(fileFolder);
	create_directory(fileFolder);
	p = correctFiles(p.string(), fileFolder.string());
	p = gcew::trees::preprocessor::PreProcessor::preProcessorIncluder(p.string(), nullptr);
	generateTree(p.string());

	return 0;
}