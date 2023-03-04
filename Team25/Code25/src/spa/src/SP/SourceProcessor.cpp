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

    Tokenizer t;
    t.tokenize(fileStr);

    Parser p(std::make_shared<Tokenizer>(t));

//    std::shared_ptr<TNode> root = std::make_shared<ProcedureNode>(p.parseProgram());
//    std::shared_ptr<SelectiveExtractor> selectiveExtractor = std::make_shared<SelectiveExtractor>(pkbPopulator);
//    selectiveExtractor->visitProgramTree(root);

    for (auto i : p.parseProgram()) {
        std::shared_ptr<TNode> root = std::make_shared<ProcedureNode>(i);
        std::shared_ptr<SelectiveExtractor> selectiveExtractor = std::make_shared<SelectiveExtractor>(pkbPopulator);
        selectiveExtractor->visitProgramTree(root);
    }

}