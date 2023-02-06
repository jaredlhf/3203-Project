#include "SourceProcessor.h"
#include "catch.hpp"

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
    std::string fileLocation = "sample_source.txt";
    std::string fileInput = "procedure Example {\n"
                                 "  x = 2;\n"
                                 "  z = 3;\n"
                                 "  } "
                                ;


    std::ofstream file(fileLocation);
    file << fileInput;
    file.close();

    sp.processSimple(fileLocation);

}