#include "QPS/QpsTable.h"
#include "catch.hpp"

// TEST CASES FOR FACTORY FUNCTIONS
TEST_CASE("QpsTable factory method with no args returns the right output") {
	std::shared_ptr<QpsTable> res = QpsTable::create();

	REQUIRE(res->getHeaders().size() == 0);
	REQUIRE(res->getData().size() == 0);
}

TEST_CASE("QpsTable factory method with header args returns the right output") {
	std::vector<std::string> headers({ "x", "s1" });
	std::vector<std::string> expectedHeaders({ "x", "s1" });
	std::shared_ptr<QpsTable> res = QpsTable::create(headers);

	REQUIRE(res->getHeaders() == expectedHeaders);
}

TEST_CASE("QpsTable factory method with header and data args returns the right output") {
	std::vector<std::string> headers({ "x", "s1" });
	std::vector<std::string> expectedHeaders({ "x", "s1" });
	std::set<std::vector<std::string>> data({ headers, expectedHeaders });
	std::set<std::vector<std::string>> expectedData({ headers, expectedHeaders });
	std::shared_ptr<QpsTable> res = QpsTable::create(headers, data);

	REQUIRE(res->getHeaders() == expectedHeaders);
	REQUIRE(res->getData() == expectedData);
}

TEST_CASE("QpsTable canAdd function returns true for valid input") {
	std::vector<std::string> headers({ "x", "s1" });
	std::shared_ptr<QpsTable> res = QpsTable::create(headers);
	std::vector<std::string> validRow({ "x", "s" });

	REQUIRE(res->canAdd(validRow) == true);
}

TEST_CASE("QpsTable canAdd function returns false for invalid input") {
	std::vector<std::string> headers({ "x", "s1" });
	std::shared_ptr<QpsTable> res = QpsTable::create(headers);
	std::vector<std::string> invalidRow({ "x", "s", "y"});

	REQUIRE(res->canAdd(invalidRow) == false);
}

TEST_CASE("QpsTable addRow function adds a new row to the table") {
	std::vector<std::string> headers({ "x", "s1" });
	std::vector<std::string> initialRow({ "v", "1" });
	std::set<std::vector<std::string>> initialRows({ initialRow });
	std::vector<std::string> toAdd({ "x", "s" });
	std::set<std::vector<std::string>> expectedData({ initialRow, toAdd });
	std::shared_ptr<QpsTable> res = QpsTable::create(headers, initialRows);


	res->addRow(toAdd);


	REQUIRE(res->getData() == expectedData);
}

TEST_CASE("QpsTable getColResults (with int arg) function returns right values with arg that is in range") {
	std::vector<std::string> headers({ "x", "s1" });
	std::vector<std::string> row1({ "v", "1" });
	std::vector<std::string> row2({ "v", "1" });
	std::vector<std::string> row3({ "3", "4" });
	std::vector<std::string> row4({ "c", "4" });
	std::set<std::vector<std::string>> initialRows({ row1, row2, row3, row4 });

	std::set<std::string> expected({ "v", "3", "c" });
	std::shared_ptr<QpsTable> res = QpsTable::create(headers, initialRows);

	REQUIRE(res->getColResults(0) == expected);
}

TEST_CASE("QpsTable getColResults (with int arg) function returns empty set with arg that is below range") {
	std::vector<std::string> headers({ "x", "s1" });
	std::vector<std::string> row1({ "v", "1" });
	std::vector<std::string> row2({ "v", "1" });
	std::vector<std::string> row3({ "3", "4" });
	std::vector<std::string> row4({ "c", "4" });
	std::set<std::vector<std::string>> initialRows({ row1, row2, row3, row4 });

	std::set<std::string> expected;
	std::shared_ptr<QpsTable> res = QpsTable::create(headers, initialRows);

	REQUIRE(res->getColResults(-1) == expected);
}

TEST_CASE("QpsTable getColResults (with int arg) function returns empty set with arg that is above range") {
	std::vector<std::string> headers({ "x", "s1" });
	std::vector<std::string> row1({ "v", "1" });
	std::vector<std::string> row2({ "v", "1" });
	std::vector<std::string> row3({ "3", "4" });
	std::vector<std::string> row4({ "c", "4" });
	std::set<std::vector<std::string>> initialRows({ row1, row2, row3, row4 });

	std::set<std::string> expected;
	std::shared_ptr<QpsTable> res = QpsTable::create(headers, initialRows);

	REQUIRE(res->getColResults(2) == expected);
}

TEST_CASE("QpsTable getColResults (with string arg) function returns results for header that exists") {
	std::vector<std::string> headers({ "x", "s1" });
	std::vector<std::string> row1({ "v", "1" });
	std::vector<std::string> row2({ "v", "1" });
	std::vector<std::string> row3({ "3", "4" });
	std::vector<std::string> row4({ "c", "4" });
	std::set<std::vector<std::string>> initialRows({ row1, row2, row3, row4 });

	std::set<std::string> expected({ "v", "3", "c" });
	std::shared_ptr<QpsTable> res = QpsTable::create(headers, initialRows);

	REQUIRE(res->getColResults("x") == expected);
}

TEST_CASE("QpsTable getColResults (with string arg) function returns empty set for header that doesnt exist") {
	std::vector<std::string> headers({ "x", "s1" });
	std::vector<std::string> row1({ "v", "1" });
	std::vector<std::string> row2({ "v", "1" });
	std::vector<std::string> row3({ "3", "4" });
	std::vector<std::string> row4({ "c", "4" });
	std::set<std::vector<std::string>> initialRows({ row1, row2, row3, row4 });

	std::set<std::string> expected;
	std::shared_ptr<QpsTable> res = QpsTable::create(headers, initialRows);

	REQUIRE(res->getColResults("xD") == expected);
}

TEST_CASE("QpsTable hasOverlappingHeaders function returns true for other table with 1 same value") {
	std::vector<std::string> headers1({ "x", "s1" });
	std::vector<std::string> headers2({ "x", "vv" });
	std::shared_ptr<QpsTable> res1 = QpsTable::create(headers1);
	std::shared_ptr<QpsTable> res2 = QpsTable::create(headers2);

	REQUIRE(res1->hasOverlappingHeaders(res2) == true);
	REQUIRE(res2->hasOverlappingHeaders(res1) == true);
}

TEST_CASE("QpsTable hasOverlappingHeaders function returns true for other table with all same values") {
	std::vector<std::string> headers1({ "x", "s1" });
	std::vector<std::string> headers2({ "x", "s1" });
	std::shared_ptr<QpsTable> res1 = QpsTable::create(headers1);
	std::shared_ptr<QpsTable> res2 = QpsTable::create(headers2);

	REQUIRE(res1->hasOverlappingHeaders(res2) == true);
	REQUIRE(res2->hasOverlappingHeaders(res1) == true);
}

TEST_CASE("QpsTable hasOverlappingHeaders function returns true for other table with no same values") {
	std::vector<std::string> headers1({ "x", "s1" });
	std::vector<std::string> headers2({ "1", "vv" });
	std::shared_ptr<QpsTable> res1 = QpsTable::create(headers1);
	std::shared_ptr<QpsTable> res2 = QpsTable::create(headers2);

	REQUIRE(res1->hasOverlappingHeaders(res2) == false);
	REQUIRE(res2->hasOverlappingHeaders(res1) == false);
}

TEST_CASE("QpsTable getCommonHeaderIndices function returns the right values for headers with common values") {
	std::vector<std::string> headers1({ "x", "s1", "z"});
	std::vector<std::string> headers2({ "vv", "z", "x"});
	std::shared_ptr<QpsTable> table1 = QpsTable::create(headers1);
	std::shared_ptr<QpsTable> table2 = QpsTable::create(headers2);

	std::vector<std::pair<int, int>> expected({ {0, 2}, {2, 1} });
	std::vector<std::pair<int, int>> res = table1->getCommonHeaderIndices(table2);

	REQUIRE(res == expected);
}

TEST_CASE("QpsTable getUniqueHeaders function returns the right values for some overlapping headers in right order") {
	std::vector<std::string> headers1({ "x", "y", "z" });
	std::vector<std::string> headers2({ "a", "x", "b", "y", "c" });
	std::shared_ptr<QpsTable> table1 = QpsTable::create(headers1);
	std::shared_ptr<QpsTable> table2 = QpsTable::create(headers2);

	std::vector<std::string> expected({ "x", "y", "z", "a", "b", "c" });
	std::vector<std::string> res = table1->getUniqueHeaders(table2);

	REQUIRE(res == expected);
	REQUIRE(table1->getHeaders() == headers1);
	REQUIRE(table2->getHeaders() == headers2);
}

TEST_CASE("QpsTable getUniqueHeaders function returns the right values for all overlapping headers in right order") {
	std::vector<std::string> headers1({ "x", "y", "z" });
	std::vector<std::string> headers2({ "x", "y", "z" });
	std::shared_ptr<QpsTable> table1 = QpsTable::create(headers1);
	std::shared_ptr<QpsTable> table2 = QpsTable::create(headers2);

	std::vector<std::string> expected({ "x", "y", "z" });
	std::vector<std::string> res = table1->getUniqueHeaders(table2);

	REQUIRE(res == expected);
	REQUIRE(table1->getHeaders() == headers1);
	REQUIRE(table2->getHeaders() == headers2);
}

TEST_CASE("QpsTable getUniqueHeaders function returns the right values for no overlapping headers in right order") {
	std::vector<std::string> headers1({ "x", "y", "z" });
	std::vector<std::string> headers2({ "a", "b", "c" });
	std::shared_ptr<QpsTable> table1 = QpsTable::create(headers1);
	std::shared_ptr<QpsTable> table2 = QpsTable::create(headers2);

	std::vector<std::string> expected({ "x", "y", "z", "a", "b", "c" });
	std::vector<std::string> res = table1->getUniqueHeaders(table2);

	REQUIRE(res == expected);
	REQUIRE(table1->getHeaders() == headers1);
	REQUIRE(table2->getHeaders() == headers2);
}

TEST_CASE("QpsTable crossProduct function returns the right resultant table") {
	std::vector<std::string> headers1({ "x", "s1" });
	std::vector<std::string> headers2({ "1", "vv" });
	std::vector<std::string> expectedHeader({ "x", "s1", "1", "vv" });
	
	std::vector<std::string> res1Row1({ "1", "x1" });
	std::vector<std::string> res1Row2({ "v", "s" });
	std::set<std::vector<std::string>> res1Data({ res1Row1, res1Row2 });

	std::vector<std::string> res2Row1({ "2", "x2" });
	std::vector<std::string> res2Row2({ "v2", "s2" });
	std::set<std::vector<std::string>> res2Data({ res2Row1, res2Row2 });

	std::vector<std::string> expectedRow1({ "1", "x1", "2", "x2" });
	std::vector<std::string> expectedRow2({ "1", "x1", "v2", "s2" });
	std::vector<std::string> expectedRow3({ "v", "s", "2", "x2" });
	std::vector<std::string> expectedRow4({ "v", "s", "v2", "s2" });
	std::set<std::vector<std::string>> expectedData({ expectedRow1, expectedRow2, expectedRow3, expectedRow4 });

	std::shared_ptr<QpsTable> res1 = QpsTable::create(headers1, res1Data);
	std::shared_ptr<QpsTable> res2 = QpsTable::create(headers2, res2Data);
	std::shared_ptr<QpsTable> resTable = res1->crossProduct(res2);

	REQUIRE(res1->getHeaders() == headers1);
	REQUIRE(res1->getData() == res1Data);
	REQUIRE(res2->getHeaders() == headers2);
	REQUIRE(res2->getData() == res2Data);
	REQUIRE(resTable->getHeaders() == expectedHeader);
	REQUIRE(resTable->getData() == expectedData);
}

TEST_CASE("QpsTable canMergeInnerJoinRows function returns true for rows that can join") {
	std::vector<std::string> row1({ "w", "x", "y", "z" });
	std::vector<std::string> row2({ "x", "b", "w", "z" });
	std::vector<std::string> header1({ "1", "2", "3", "4" });
	std::vector<std::pair<int, int>> cmnIdx({ {0, 2}, {1, 0} });
	std::shared_ptr<QpsTable> table1 = QpsTable::create(header1);

	bool res = table1->canMergeInnerJoinRows(row1, row2, cmnIdx);

	REQUIRE(res == true);
}

TEST_CASE("QpsTable mergeInnerJoinRows function returns the right joined row") {
	std::vector<std::string> row1({ "w", "x", "y", "z" });
	size_t row1Len = row1.size();
	std::vector<std::string> row2({ "x", "b", "w", "z" });
	size_t row2Len = row2.size();
	std::vector<std::string> header1({ "1", "2", "3", "4" });
	std::vector<std::pair<int, int>> cmnIdx({ {0, 2}, {1, 0} });
	std::shared_ptr<QpsTable> table1 = QpsTable::create(header1);
	std::vector<std::string> expected({ "w", "x", "y", "z", "b", "z" });

	std::vector<std::string> res = table1->mergeInnerJoinRows(row1, row2, cmnIdx);

	REQUIRE(res == expected);
	REQUIRE(row1.size() == row1Len);
	REQUIRE(row2.size() == row2Len);
}

TEST_CASE("QpsTable canMergeInnerJoinRows function returns false for rows that cant join") {
	std::vector<std::string> row1({ "w", "x", "y", "z" });
	std::vector<std::string> row2({ "x", "b", "w", "z" });
	std::vector<std::string> header1({ "1", "2", "3", "4" });
	std::vector<std::pair<int, int>> cmnIdx({ {1, 1} });
	std::shared_ptr<QpsTable> table1 = QpsTable::create(header1);

	bool res = table1->canMergeInnerJoinRows(row1, row2, cmnIdx);

	REQUIRE(res == false);
}

TEST_CASE("QpsTable innerJoin function returns right result for 1 common header") {
	std::vector<std::string> t1row1({ "x", "y", "z" });
	std::vector<std::string> t1row2({ "p", "q", "r" });
	std::set<std::vector<std::string>> t1Data({ t1row1, t1row2 });

	std::vector<std::string> t2row1({ "r", "z", "x", "3"});
	std::vector<std::string> t2row2({ "s", "z", "t", "4" });
	std::vector<std::string> t2row3({ "1", "2", "3", "4" });
	std::set<std::vector<std::string>> t2Data({ t2row1, t2row2, t2row3 });

	std::vector<std::string> expectedRow1({ "x", "y", "z", "r", "x", "3" });
	std::vector<std::string> expectedRow2({ "x", "y", "z", "s", "t", "4" });
	std::set<std::vector<std::string>> expectedData({ expectedRow1, expectedRow2 });

	std::vector<std::string> header1({ "a", "b", "c" });
	std::vector<std::string> header2({ "v", "c", "q", "r"});

	std::shared_ptr<QpsTable> table1 = QpsTable::create(header1, t1Data);
	std::shared_ptr<QpsTable> table2 = QpsTable::create(header2, t2Data);

	std::set<std::vector<std::string>> resData = table1->innerJoin(table2)->getData();

	REQUIRE(resData == expectedData);
}

TEST_CASE("QpsTable innerJoin function returns right result for 2 common headers") {
	std::vector<std::string> t1row1({ "x", "y", "z" });
	std::vector<std::string> t1row2({ "p", "q", "r" });
	std::vector<std::string> t1row3({ "1", "2", "3" });
	std::vector<std::string> t1row4({ "x", "v", "z" });
	std::set<std::vector<std::string>> t1Data({ t1row1, t1row2, t1row3, t1row4 });

	std::vector<std::string> t2row1({ "e", "z", "x", "f" });
	std::vector<std::string> t2row2({ "g", "z", "x", "h" });
	std::vector<std::string> t2row3({ "i", "z", "1", "j" });
	std::vector<std::string> t2row4({ "k", "r", "p", "l" });
	std::vector<std::string> t2row5({ "m", "r", "p", "n" });
	std::set<std::vector<std::string>> t2Data({ t2row1, t2row2, t2row3, t2row4, t2row5 });

	std::vector<std::string> expectedRow1({ "x", "y", "z", "e", "f" });
	std::vector<std::string> expectedRow2({ "x", "v", "z", "e", "f" });
	std::vector<std::string> expectedRow3({ "x", "y", "z", "g", "h" });
	std::vector<std::string> expectedRow4({ "x", "v", "z", "g", "h" });
	std::vector<std::string> expectedRow5({ "p", "q", "r", "k", "l" });
	std::vector<std::string> expectedRow6({ "p", "q", "r", "m", "n" });
	std::set<std::vector<std::string>> expectedData({ expectedRow1, expectedRow2, 
		expectedRow3, expectedRow4, expectedRow5, expectedRow6 });

	std::vector<std::string> header1({ "a", "b", "c" });
	std::vector<std::string> header2({ "v", "c", "a", "r" });

	std::shared_ptr<QpsTable> table1 = QpsTable::create(header1, t1Data);
	std::shared_ptr<QpsTable> table2 = QpsTable::create(header2, t2Data);

	std::set<std::vector<std::string>> resData = table1->innerJoin(table2)->getData();

	REQUIRE(resData == expectedData);
}

TEST_CASE("QpsTable innerJoin function returns right result for 2 common headers with same num of rows") {
	std::vector<std::string> t1row1({ "1", "2" });
	std::vector<std::string> t1row2({ "1", "3" });
	std::vector<std::string> t1row3({ "4", "2" });
	std::vector<std::string> t1row4({ "5", "3" });
	std::set<std::vector<std::string>> t1Data({ t1row1, t1row2, t1row3, t1row4 });

	std::vector<std::string> t2row1({ "3", "1" });
	std::vector<std::string> t2row2({ "2", "5" });
	std::vector<std::string> t2row3({ "3", "6" });
	std::vector<std::string> t2row4({ "2", "4" });
	std::set<std::vector<std::string>> t2Data({ t2row1, t2row2, t2row3, t2row4 });

	std::vector<std::string> expectedRow1({ "1", "3" });
	std::vector<std::string> expectedRow2({ "4", "2" });
	std::set<std::vector<std::string>> expectedData({ expectedRow1, expectedRow2 });

	std::vector<std::string> header1({ "a1", "v1" });
	std::vector<std::string> header2({ "v1", "a1" });

	std::shared_ptr<QpsTable> table1 = QpsTable::create(header1, t1Data);
	std::shared_ptr<QpsTable> table2 = QpsTable::create(header2, t2Data);

	std::set<std::vector<std::string>> resData = table1->innerJoin(table2)->getData();

	REQUIRE(resData == expectedData);
}

TEST_CASE("QpsTable join function returns right result for 1 empty table as arg") {
	std::vector<std::string> t1row1({ "1", "2" });
	std::vector<std::string> t1row2({ "1", "3" });
	std::vector<std::string> t1row3({ "4", "2" });
	std::vector<std::string> t1row4({ "5", "3" });
	std::set<std::vector<std::string>> t1Data({ t1row1, t1row2, t1row3, t1row4 });

	std::vector<std::string> expectedrow1({ "1", "2" });
	std::vector<std::string> expectedrow2({ "1", "3" });
	std::vector<std::string> expectedrow3({ "4", "2" });
	std::vector<std::string> expectedrow4({ "5", "3" });
	std::set<std::vector<std::string>> expectedData({ expectedrow1, expectedrow2, expectedrow3, expectedrow4 });

	std::vector<std::string> header1({ "a1", "v1" });
	std::vector<std::string> expectedHeader({ "a1", "v1" });

	std::shared_ptr<QpsTable> table1 = QpsTable::create(header1, t1Data);
	std::shared_ptr<QpsTable> table2 = QpsTable::create();

	std::shared_ptr<QpsTable> resTable = table1->join(table2);

	REQUIRE(resTable->getData() == expectedData);
	REQUIRE(resTable->getHeaders() == expectedHeader);
	REQUIRE(table1->getData() == expectedData);
	REQUIRE(table1->getHeaders() == expectedHeader);
}

TEST_CASE("QpsTable join function returns right result for 1 empty table as caller") {
	std::vector<std::string> t1row1({ "1", "2" });
	std::vector<std::string> t1row2({ "1", "3" });
	std::vector<std::string> t1row3({ "4", "2" });
	std::vector<std::string> t1row4({ "5", "3" });
	std::set<std::vector<std::string>> t1Data({ t1row1, t1row2, t1row3, t1row4 });

	std::vector<std::string> expectedrow1({ "1", "2" });
	std::vector<std::string> expectedrow2({ "1", "3" });
	std::vector<std::string> expectedrow3({ "4", "2" });
	std::vector<std::string> expectedrow4({ "5", "3" });
	std::set<std::vector<std::string>> expectedData({ expectedrow1, expectedrow2, expectedrow3, expectedrow4 });

	std::vector<std::string> header1({ "a1", "v1" });
	std::vector<std::string> expectedHeader({ "a1", "v1" });

	std::shared_ptr<QpsTable> table1 = QpsTable::create(header1, t1Data);
	std::shared_ptr<QpsTable> table2 = QpsTable::create();

	std::shared_ptr<QpsTable> resTable = table2->join(table1);

	REQUIRE(resTable->getData() == expectedData);
	REQUIRE(resTable->getHeaders() == expectedHeader);
	REQUIRE(table1->getData() == expectedData);
	REQUIRE(table1->getHeaders() == expectedHeader);
}

TEST_CASE("QpsTable join function returns right result for no common headers (cross product)") {
	std::vector<std::string> headers1({ "x", "s1" });
	std::vector<std::string> headers2({ "1", "vv" });
	std::vector<std::string> expectedHeader({ "x", "s1", "1", "vv" });

	std::vector<std::string> res1Row1({ "1", "x1" });
	std::vector<std::string> res1Row2({ "v", "s" });
	std::set<std::vector<std::string>> res1Data({ res1Row1, res1Row2 });

	std::vector<std::string> res2Row1({ "2", "x2" });
	std::vector<std::string> res2Row2({ "v2", "s2" });
	std::set<std::vector<std::string>> res2Data({ res2Row1, res2Row2 });

	std::vector<std::string> expectedRow1({ "1", "x1", "2", "x2" });
	std::vector<std::string> expectedRow2({ "1", "x1", "v2", "s2" });
	std::vector<std::string> expectedRow3({ "v", "s", "2", "x2" });
	std::vector<std::string> expectedRow4({ "v", "s", "v2", "s2" });
	std::set<std::vector<std::string>> expectedData({ expectedRow1, expectedRow2, expectedRow3, expectedRow4 });

	std::shared_ptr<QpsTable> res1 = QpsTable::create(headers1, res1Data);
	std::shared_ptr<QpsTable> res2 = QpsTable::create(headers2, res2Data);
	std::shared_ptr<QpsTable> resTable = res1->join(res2);

	REQUIRE(res1->getHeaders() == headers1);
	REQUIRE(res1->getData() == res1Data);
	REQUIRE(res2->getHeaders() == headers2);
	REQUIRE(res2->getData() == res2Data);
	REQUIRE(resTable->getHeaders() == expectedHeader);
	REQUIRE(resTable->getData() == expectedData);
}

TEST_CASE("QpsTable join function returns right result for tables with common headers (inner join)") {
	std::vector<std::string> t1row1({ "x", "y", "z" });
	std::vector<std::string> t1row2({ "p", "q", "r" });
	std::vector<std::string> t1row3({ "1", "2", "3" });
	std::vector<std::string> t1row4({ "x", "v", "z" });
	std::set<std::vector<std::string>> t1Data({ t1row1, t1row2, t1row3, t1row4 });

	std::vector<std::string> t2row1({ "e", "z", "x", "f" });
	std::vector<std::string> t2row2({ "g", "z", "x", "h" });
	std::vector<std::string> t2row3({ "i", "z", "1", "j" });
	std::vector<std::string> t2row4({ "k", "r", "p", "l" });
	std::vector<std::string> t2row5({ "m", "r", "p", "n" });
	std::set<std::vector<std::string>> t2Data({ t2row1, t2row2, t2row3, t2row4, t2row5 });

	std::vector<std::string> expectedRow1({ "x", "y", "z", "e", "f" });
	std::vector<std::string> expectedRow2({ "x", "v", "z", "e", "f" });
	std::vector<std::string> expectedRow3({ "x", "y", "z", "g", "h" });
	std::vector<std::string> expectedRow4({ "x", "v", "z", "g", "h" });
	std::vector<std::string> expectedRow5({ "p", "q", "r", "k", "l" });
	std::vector<std::string> expectedRow6({ "p", "q", "r", "m", "n" });
	std::set<std::vector<std::string>> expectedData({ expectedRow1, expectedRow2,
		expectedRow3, expectedRow4, expectedRow5, expectedRow6 });

	std::vector<std::string> header1({ "a", "b", "c" });
	std::vector<std::string> header2({ "v", "c", "a", "r" });
	std::vector<std::string> expectedHeader({ "a", "b", "c", "v", "r" });

	std::shared_ptr<QpsTable> table1 = QpsTable::create(header1, t1Data);
	std::shared_ptr<QpsTable> table2 = QpsTable::create(header2, t2Data);

	std::shared_ptr<QpsTable> resTable = table1->join(table2);

	REQUIRE(table1->getHeaders() == header1);
	REQUIRE(table1->getData() == t1Data);
	REQUIRE(table2->getHeaders() == header2);
	REQUIRE(table2->getData() == t2Data);
	REQUIRE(resTable->getHeaders() == expectedHeader);
	REQUIRE(resTable->getData() == expectedData);
}