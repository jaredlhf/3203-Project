#include <memory>
#include "SourceProcessor.h"


// converts file specified by filename into string, with \n characters removed
std::string SourceProcessor::processFile(std::string &filename) {
    ifstream inputFile;
    inputFile.open(filename);
    stringstream strStream;
    strStream << inputFile.rdbuf();
    string res = strStream.str();
    res.erase(std::remove(res.begin(), res.end(), '\n'), res.end());
    return res;
}

void SourceProcessor::processSimple(std::string &filename, std::shared_ptr<PkbPopulator> pkbPopulator) {
    std::string fileStr = processFile(filename);

    std::shared_ptr<SPUtils> spUtils = std::make_shared<SPUtils>();

    Tokenizer t;
    t.tokenize(fileStr);

    Parser p(std::make_shared<Tokenizer>(t), spUtils);
    std::vector<std::shared_ptr<ParserDTO>> programDTOs = p.parseProgram();

    std::shared_ptr<SelectiveExtractor> selectiveExtractor = std::make_shared<SelectiveExtractor>(pkbPopulator, spUtils);

    for (auto programDTO : programDTOs) {
        std::shared_ptr<ProcedureNode> root = std::dynamic_pointer_cast<ProcedureNode>(programDTO->getNode());

        std::shared_ptr<CFGNode> cfgRoot = programDTO->getCFGNode();
        std::string procName = programDTO->getProcName();
        selectiveExtractor->visitProgramTree(root);
        selectiveExtractor->visitCFG(cfgRoot, procName);
    }

}