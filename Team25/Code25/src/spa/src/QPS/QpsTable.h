#include <string>
#include <vector>
#include <set>
#include <memory>


class QpsTable : public std::enable_shared_from_this<QpsTable> {
private:
	std::vector<std::string> headers;
	std::set<std::vector<std::string>> data;

public:
	// Constructor functions
	QpsTable();
	QpsTable(std::vector<std::string> headers);
	QpsTable(std::vector<std::string> headers, std::set<std::vector<std::string>> data);

	// Static QpsTable functions
	static std::shared_ptr<QpsTable> create();
	static std::shared_ptr<QpsTable> create(std::vector<std::string> headers);
	static std::shared_ptr<QpsTable> create(std::vector<std::string> headers, std::set<std::vector<std::string>> data);

	// QpsTable instance functions
	std::vector<std::string> getHeaders();
	std::set<std::vector<std::string>> getData();
	bool canAdd(std::vector<std::string> row);
	void addRow(std::vector<std::string> row);
	std::set<std::string> getColResults(int headerIdx);
	std::set<std::string> getColResults(const std::string& headerName);
	bool hasOverlappingHeaders(std::shared_ptr<QpsTable> other);
	std::vector<std::pair<int, int>> getCommonHeaderIndices(std::shared_ptr<QpsTable> other);
	std::vector<std::string> getUniqueHeaders(std::shared_ptr<QpsTable> other);
	std::shared_ptr<QpsTable> crossProduct(std::shared_ptr<QpsTable> other);
	bool canMergeInnerJoinRows(std::vector<std::string> row1, 
		std::vector<std::string> row2, std::vector<std::pair<int, int>> cmnHeadIdx);
	std::vector<std::string> mergeInnerJoinRows(std::vector<std::string> row1, 
		std::vector<std::string> row2, std::vector<std::pair<int, int>> cmnHeadIdx);
	std::shared_ptr<QpsTable> innerJoin(std::shared_ptr<QpsTable> other);
	std::shared_ptr<QpsTable> join(std::shared_ptr<QpsTable> other);
};