#include "QpsTable.h"
#include <algorithm>
#include <iostream>

// QPSTABLE CONSTRUCTOR FUNCTIONS
QpsTable::QpsTable() {

}

QpsTable::QpsTable(std::vector<std::string> headers) {
	this->headers = headers;
}

QpsTable::QpsTable(std::vector<std::string> headers, std::set<std::vector<std::string>> data) {
	this->headers = headers;
	this->data = data;
}

// QPSTABLE STATIC FUNCTIONS
std::shared_ptr<QpsTable> QpsTable::create() {
	return std::make_shared<QpsTable>(QpsTable());
}

std::shared_ptr<QpsTable> QpsTable::create(std::vector<std::string> headers) {
	return std::make_shared<QpsTable>(QpsTable(headers));
}

std::shared_ptr<QpsTable> QpsTable::create(std::vector<std::string> headers, std::set<std::vector<std::string>> data) {
	return std::make_shared<QpsTable>(QpsTable(headers, data));
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> QpsTable::getDefaultSynErr() {
	return std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>>(Constants::ClauseResult::SYN_ERR,
		QpsTable::create());
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> QpsTable::getDefaultSemErr() {
	return std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>>(Constants::ClauseResult::SEM_ERR,
		QpsTable::create());
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> QpsTable::getDefaultNoMatch() {
	return std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>>(Constants::ClauseResult::NO_MATCH,
		QpsTable::create());
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> QpsTable::getDefaultOk() {
	return std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>>(Constants::ClauseResult::OK,
		QpsTable::create());
}

// QPSTABLE INSTANCE FUNCTIONS
std::vector<std::string> QpsTable::getHeaders() {
	return this->headers;
}

std::set<std::vector<std::string>> QpsTable::getData() {
	return this->data;
}

bool QpsTable::canAdd(std::vector<std::string> row) {
 return row.size() == this->headers.size();
}

void QpsTable::addRow(std::vector<std::string> row) {
	this->data.insert(row);
}

/* Returns the set of answers in a column, or an empty set if the header idx is not in range */
std::set<std::string> QpsTable::getColResults(int headerIdx) {
	std::set<std::string> res;
	if (headerIdx < 0 || headerIdx >= this->headers.size()) {
		return res;
	}

	for (std::vector<std::string> row : this->data) {
		res.insert(row[headerIdx]);
	}

	return res;
}

/* Returns the set of answers in a column, or an empty set if the header name is not in table*/
std::set<std::string> QpsTable::getColResults(const std::string& headerName) {
	ptrdiff_t pos = find(this->headers.begin(), this->headers.end(), headerName) - this->headers.begin();
	return this->getColResults(pos);
}

bool QpsTable::hasOverlappingHeaders(std::shared_ptr<QpsTable> other) {
	std::vector<std::string> otherHeaders = other->headers;
	for (std::string header : this->headers) {
		if (std::find(otherHeaders.begin(), otherHeaders.end(), header) != otherHeaders.end())
		{
			return true;
		}
	}

	return false;
}

std::vector<std::pair<int, int>> QpsTable::getCommonHeaderIndices(std::shared_ptr<QpsTable> other) {
	std::vector<std::pair<int, int>> res;
	for (int i = 0; i < this->headers.size(); i++) {
		for (int j = 0; j < other->headers.size(); j++) {
			if (this->headers[i] == other->headers[j]) {
				res.push_back(std::pair<int, int>(i, j));
			}
		}
	}

	return res;
}

/*
	Returns a vector of unique headers, with this->headers in order at the front, and other->headers
	at the back in the same order, with any duplicate headers removed.

	E.g. this->headers = {"x", "y", "z"}, other->headers = {"a", "x", "b", "y", "c"}
	returns {"x", "y", "z", "a", "b", "c"}
*/
std::vector<std::string> QpsTable::getUniqueHeaders(std::shared_ptr<QpsTable> other) {
	std::vector<std::pair<int, int>> cmnHeaderIdx = this->getCommonHeaderIndices(other);
	std::vector<std::string> resHeaders = this->headers;
	std::set<int> appearedIdx;
	for (std::pair<int, int> cmnIdx : cmnHeaderIdx) {
		appearedIdx.insert(cmnIdx.second);
	}
	for (int i = 0; i < other->headers.size(); i++) {
		if (appearedIdx.find(i) == appearedIdx.end()) {
			resHeaders.push_back(other->headers[i]);
		}
	}

	return resHeaders;
}

std::shared_ptr<QpsTable> QpsTable::crossProduct(std::shared_ptr<QpsTable> other) {
	std::vector<std::string> resultHeaders = this->headers;
	std::vector<std::string> otherHeaders = other->headers;
	resultHeaders.insert(resultHeaders.end(), otherHeaders.begin(), otherHeaders.end());

	std::shared_ptr<QpsTable> res = QpsTable::create(resultHeaders);
	for (std::vector<std::string> thisRow : this->data) {
		for (std::vector<std::string> otherRow : other->data) {
			std::vector<std::string> resRow = thisRow;
			resRow.insert(resRow.end(), otherRow.begin(), otherRow.end());
			res->addRow(resRow);
		}
	}

	return res;
}

bool QpsTable::canMergeInnerJoinRows(std::vector<std::string> row1,
	std::vector<std::string> row2, std::vector<std::pair<int, int>> cmnHeadIdx) {

	for (std::pair<int, int> cmnIdx : cmnHeadIdx) {
		if (row1[cmnIdx.first] != row2[cmnIdx.second]) {
			return false;
		}
	}

	return true;
}

std::vector<std::string> QpsTable::mergeInnerJoinRows(std::vector<std::string> row1,
	std::vector<std::string> row2, std::vector<std::pair<int, int>> cmnHeadIdx) {

	std::vector<std::string> res = row1;
	std::set<int> appearedIdx;
	for (std::pair<int, int> cmnIdx : cmnHeadIdx) {
		appearedIdx.insert(cmnIdx.second);
	}

	for (int i = 0; i < row2.size(); i++) {
		if (appearedIdx.find(i) == appearedIdx.end()) {
			res.push_back(row2[i]);
		}
	}

	return res;
}

std::shared_ptr<QpsTable> QpsTable::innerJoin(std::shared_ptr<QpsTable> other) {
	/*
		Using the nested loop join algorithm for innerJoin resolution
	*/
	// Build headers and table for result
	std::vector<std::string> resHeaders = this->getUniqueHeaders(other);
	std::shared_ptr<QpsTable> res = QpsTable::create(resHeaders);
	std::vector<std::pair<int, int>> cmnHeaderIdx = this->getCommonHeaderIndices(other);

	// With "this" as the outer block, and "other" as the inner block, find rows where cmn headers' value match
	for (std::vector<std::string> thisRow : this->data) {
		for (std::vector<std::string> otherRow : other->data) {
			if (this->canMergeInnerJoinRows(thisRow, otherRow, cmnHeaderIdx)) {
				res->addRow(this->mergeInnerJoinRows(thisRow, otherRow, cmnHeaderIdx));
			}
		}
	}

	return res;
}

std::shared_ptr<QpsTable> QpsTable::join(std::shared_ptr<QpsTable> other) {
	if (this->headers.size() == 0) {
		return other;
	}

	if (other->headers.size() == 0) {
		return shared_from_this();
	}

	if (hasOverlappingHeaders(other)) {
		return this->innerJoin(other);
	}

	return this->crossProduct(other);
}
