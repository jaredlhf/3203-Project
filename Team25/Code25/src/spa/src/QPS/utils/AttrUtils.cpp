#include "AttrUtils.h"

bool AttrUtils::hasValidAttr(const std::string &synKeyword,
                             const std::string &attrName) {
  if (synKeyword == Constants::STMT)
    return attrName == Constants::STMTNUM;
  if (synKeyword == Constants::READ)
    return (attrName == Constants::STMTNUM) || (attrName == Constants::VARNAME);
  if (synKeyword == Constants::PRINT)
    return (attrName == Constants::STMTNUM) || (attrName == Constants::VARNAME);
  if (synKeyword == Constants::CALL)
    return (attrName == Constants::STMTNUM) ||
           (attrName == Constants::PROCNAME);
  if (synKeyword == Constants::WHILE)
    return attrName == Constants::STMTNUM;
  if (synKeyword == Constants::IF)
    return attrName == Constants::STMTNUM;
  if (synKeyword == Constants::ASSIGN)
    return attrName == Constants::STMTNUM;
  if (synKeyword == Constants::VARIABLE)
    return attrName == Constants::VARNAME;
  if (synKeyword == Constants::CONSTANT)
    return attrName == Constants::VALUE;
  if (synKeyword == Constants::PROCEDURE)
    return attrName == Constants::PROCNAME;
  if (synKeyword == Constants::BOOLEAN)
    return false;
  if (synKeyword == Constants::SYNTAX_ERROR)
    return false;
  if (synKeyword == Constants::SEMANTIC_ERROR)
    return false;
}

bool AttrUtils::hasValidAttr(std::shared_ptr<Synonym> syn,
                             const std::string &attrName) {
  return AttrUtils::hasValidAttr(syn->getKeyword(), attrName);
}