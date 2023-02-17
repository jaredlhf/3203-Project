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

    Parser p(std::make_shared<Tokenizer>(t), pkbPopulator);
    std::shared_ptr<TNode> root = std::make_shared<ProcedureNode>(p.parseProgram());

    std::shared_ptr<SelectiveExtractor> se = std::make_shared<SelectiveExtractor>();

    std::stack<shared_ptr<TNode>> stack;
    stack.push(root);
    while (!stack.empty()) {
        std::shared_ptr<TNode> node = stack.top();
        stack.pop();
        std::cout << "accepting" << std::endl;
        node->accept(se);

        for (const auto child: node->getChildren()) {
            stack.push(child);
        }
    }


}