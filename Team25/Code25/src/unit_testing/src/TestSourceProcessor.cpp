
#include "SourceProcessor.h"
#include "catch.hpp"

#include "PKB/PkbPopulator.h"

TEST_CASE("Test processFile()") {
    SourceProcessor sp;
    std::string fileLocation = "sample_source.txt";
    std::string fileInput = "procedure Example {\n"
                                 "  x = 2;\n"
                                 "  z = 3;\n"
                                 "  i = 5;\n"
                                 "  while (i!=0) {\n"
                                 "    x = x - 1;\n"
                                 "    if (x==1) then {\n"
                                 "      z = x + 1; }\n"
                                 "    else {\n"
                                 "      y = z + x; }\n"
                                 "    z = z + x + i;\n"
                                 "    call q;\n"
                                 "    i = i - 1; }\n"
                                 "  call p; }";

    std::ofstream file(fileLocation);
    file << fileInput;
    file.close();

    std::string expectedOutput = "procedure Example {  x = 2;  z = 3;  i = 5;  while (i!=0) {    x = x - 1;    if (x==1) then {      z = x + 1; }    else {      y = z + x; }    z = z + x + i;    call q;    i = i - 1; }  call p; }";
    std::string output = sp.processFile(fileLocation);
    REQUIRE(output == expectedOutput);

    std::remove(fileLocation.c_str());
}

TEST_CASE("Test processSimple()") {
    SourceProcessor sp;
    VariableStore vs;
    ConstantStore cs;
    FollowsStore fs;
    ProcedureStore ps;
    StatementStore ss;
    PatternStore patts;
    FollowsStarStore fstars;
    ModifiesProcStore mprocs;
    ModifiesStore ms;
    ParentStarStore pStars;
    ParentStore parents;
    UsesStore uses;
    std::shared_ptr vsPointer = std::make_shared<VariableStore>(vs);
    std::shared_ptr csPointer = std::make_shared<ConstantStore>(cs);
    std::shared_ptr fsPointer = std::make_shared<FollowsStore>(fs);
    std::shared_ptr psPointer = std::make_shared<ProcedureStore>(ps);
    std::shared_ptr ssPointer = std::make_shared<StatementStore>(ss);
    std::shared_ptr pattsPointer = std::make_shared<PatternStore>(patts);
    std::shared_ptr<FollowsStarStore> fstarsPointer = std::make_shared<FollowsStarStore>(fstars);
    std::shared_ptr<ModifiesProcStore> mprocsPointer = std::make_shared<ModifiesProcStore>(mprocs);
    std::shared_ptr<ModifiesStore> msPointer = std::make_shared<ModifiesStore>(ms);
    std::shared_ptr<ParentStarStore> pStarsPointer = std::make_shared<ParentStarStore>(pStars);
    std::shared_ptr<ParentStore> parentsPointer = std::make_shared<ParentStore>(parents);
    std::shared_ptr<UsesStore> usesPointer = std::make_shared<UsesStore>(uses);

    PkbPopulator pkbPop(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, usesPointer);
    std::string fileLocation = "sample_source.txt";
    std::string fileInput = "procedure Example {\n"
                                 "  x = 2;\n"
                                 "  z = 3;\n"
                                 "  } "
                                ;


    std::ofstream file(fileLocation);
    file << fileInput;
    file.close();
    //std::cout << vs.getAllVar().size() << std::endl;

    sp.processSimple(fileLocation, &pkbPop);

    //std::cout << vs.getAllVar().size() << std::endl;

}