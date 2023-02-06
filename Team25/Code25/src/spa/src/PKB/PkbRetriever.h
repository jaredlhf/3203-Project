#include <stdio.h>
#include <unordered_set>
#include <string>

using namespace std;

#include "VariableStore.h"
#include "ConstantStore.h"
#include "FollowsStore.h"
#include "ProcedureStore.h"
#include "StatementStore.h"

class PkbRetriever{
private:
	VariableStore* varStorage;
	ConstantStore* constStorage;
	FollowsStore* followsStorage;
	ProcedureStore* procedureStorage;
	StatementStore* statementStorage;

public:
	PkbRetriever(VariableStore* varStore, ConstantStore* constStore, FollowsStore* followsStore, ProcedureStore* procedureStore, StatementStore* statementStore);
	std::unordered_set<std::string> getAllVar();
	std::unordered_set<int> getAllConst();
	int getFollowee(int rightLineNum);
	int getFollower(int leftLineNum);
	std::unordered_set<int> getAllFollowers();
	std::unordered_set<int> getAllFollowees();
	std::unordered_set<string> getAllProc();
	std::unordered_set<int> getAllStmt(string stmtType);
};