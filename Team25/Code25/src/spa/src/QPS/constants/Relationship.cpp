#include "Relationship.h"

Relationship::Relationship(const std::string& arg1, const std::string& arg2) {
    this->arg1 = arg1;
    this -> arg2 = arg2;
}

std::string Relationship::getKeyword() {
    return this->keyword;
}

bool Relationship::compare(std::shared_ptr<Relationship> other) {
    return this->keyword == other->keyword && this->arg1 == other->arg1 && this->arg2 == other->arg2;
}

std::shared_ptr<Relationship> Relationship::create(const std::string& keyword, const std::string& arg1, const std::string& arg2) {
    if (keyword == Constants::FOLLOWS) return std::make_shared<FollowsRelationship>(FollowsRelationship(arg1, arg2));
    if (keyword == Constants::FOLLOWSST) return std::make_shared<FollowsSTRelationship>(FollowsSTRelationship(arg1, arg2));
    if (keyword == Constants::PARENT) return std::make_shared<ParentRelationship>(ParentRelationship(arg1, arg2));
    if (keyword == Constants::PARENTST) return std::make_shared<ParentSTRelationship>(ParentSTRelationship(arg1, arg2));
    if (keyword == Constants::USES) return std::make_shared<UsesRelationship>(UsesRelationship(arg1, arg2));
    if (keyword == Constants::MODIFIES) return std::make_shared<ModifiesRelationship>(ModifiesRelationship(arg1, arg2));
    if (keyword == Constants::CALLS) return std::make_shared<CallsRelationship>(CallsRelationship(arg1, arg2));
    if (keyword == Constants::CALLSST) return std::make_shared<CallsSTRelationship>(CallsSTRelationship(arg1, arg2));
    if (keyword == Constants::NEXT) return std::make_shared<NextRelationship>(NextRelationship(arg1, arg2));
    if (keyword == Constants::NEXTST) return std::make_shared<NextSTRelationship>(NextSTRelationship(arg1, arg2));

    return std::make_shared<Relationship>(arg1, arg2);
}

std::vector<std::shared_ptr<Entity>> Relationship::verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) {
    return {};
}

FollowsRelationship::FollowsRelationship(const std::string& arg1, const std::string& arg2) : Relationship(arg1, arg2) {
    keyword = Constants::FOLLOWS;
}

std::vector<std::shared_ptr<Entity>> FollowsRelationship::verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) {
    std::shared_ptr<Entity> arg1Value = ParserUtils::getValidStmtRef(arg1, declarations);
    std::shared_ptr<Entity> arg2Value = ParserUtils::getValidStmtRef(arg2, declarations);

    return { arg1Value, arg2Value };
}

FollowsSTRelationship::FollowsSTRelationship(const std::string& arg1, const std::string& arg2) : Relationship(arg1, arg2) {
    keyword = Constants::FOLLOWSST;
}

std::vector<std::shared_ptr<Entity>> FollowsSTRelationship::verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) {
    std::shared_ptr<Entity> arg1Value = ParserUtils::getValidStmtRef(arg1, declarations);
    std::shared_ptr<Entity> arg2Value = ParserUtils::getValidStmtRef(arg2, declarations);

    return { arg1Value, arg2Value };
}

ParentRelationship::ParentRelationship(const std::string& arg1, const std::string& arg2) : Relationship(arg1, arg2) {
    keyword = Constants::PARENT;
}

std::vector<std::shared_ptr<Entity>> ParentRelationship::verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) {
    std::shared_ptr<Entity> arg1Value = ParserUtils::getValidStmtRef(arg1, declarations);
    std::shared_ptr<Entity> arg2Value = ParserUtils::getValidStmtRef(arg2, declarations);

    return { arg1Value, arg2Value };
}

ParentSTRelationship::ParentSTRelationship(const std::string& arg1, const std::string& arg2) : Relationship(arg1, arg2) {
    keyword = Constants::PARENTST;
}

std::vector<std::shared_ptr<Entity>> ParentSTRelationship::verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) {
    std::shared_ptr<Entity> arg1Value = ParserUtils::getValidStmtRef(arg1, declarations);
    std::shared_ptr<Entity> arg2Value = ParserUtils::getValidStmtRef(arg2, declarations);

    return { arg1Value, arg2Value };
}

UsesRelationship::UsesRelationship(const std::string& arg1, const std::string& arg2) : Relationship(arg1, arg2) {
    keyword = Constants::USES;
}

std::vector<std::shared_ptr<Entity>> UsesRelationship::verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) {
    // checks if this is procedure call
    std::shared_ptr<Entity> arg1Value = ParserUtils::getValidProcRef(arg1, declarations);
    std::shared_ptr<Entity> arg2Value = ParserUtils::getValidEntRef(arg2, declarations);

    if (ParserUtils::isExpectedSynonym(arg1Value, Constants::READ)) {
        return { Synonym::create(Constants::SEMANTIC_ERROR, ""), arg2Value };
    }
    return { arg1Value, arg2Value };
}

ModifiesRelationship::ModifiesRelationship(const std::string& arg1, const std::string& arg2) : Relationship(arg1, arg2) {
    keyword = Constants::MODIFIES;
}

std::vector<std::shared_ptr<Entity>> ModifiesRelationship::verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) {
    // checks if this is procedure call
    std::shared_ptr<Entity> arg1Value = ParserUtils::getValidProcRef(arg1, declarations);
    std::shared_ptr<Entity> arg2Value = ParserUtils::getValidEntRef(arg2, declarations);

    if (ParserUtils::isExpectedSynonym(arg1Value, Constants::PRINT)) {
        return { Synonym::create(Constants::SEMANTIC_ERROR, ""), arg2Value };
    }
    return { arg1Value, arg2Value };
}

CallsRelationship::CallsRelationship(const std::string& arg1, const std::string& arg2) : Relationship(arg1, arg2) {
    keyword = Constants::CALLS;
}

std::vector<std::shared_ptr<Entity>> CallsRelationship::verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) {
    std::shared_ptr<Entity> arg1Value = ParserUtils::getValidEntRef(arg1, declarations);
    std::shared_ptr<Entity> arg2Value = ParserUtils::getValidEntRef(arg2, declarations);

    return { arg1Value, arg2Value };
}

CallsSTRelationship::CallsSTRelationship(const std::string& arg1, const std::string& arg2) : Relationship(arg1, arg2) {
    keyword = Constants::CALLSST;
}

std::vector<std::shared_ptr<Entity>> CallsSTRelationship::verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) {
    std::shared_ptr<Entity> arg1Value = ParserUtils::getValidEntRef(arg1, declarations);
    std::shared_ptr<Entity> arg2Value = ParserUtils::getValidEntRef(arg2, declarations);

    return { arg1Value, arg2Value };
}

NextRelationship::NextRelationship(const std::string& arg1, const std::string& arg2) : Relationship(arg1, arg2) {
    keyword = Constants::NEXT;
}

std::vector<std::shared_ptr<Entity>> NextRelationship::verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) {
    std::shared_ptr<Entity> arg1Value = ParserUtils::getValidStmtRef(arg1, declarations);
    std::shared_ptr<Entity> arg2Value = ParserUtils::getValidStmtRef(arg2, declarations);

    return { arg1Value, arg2Value };
}

NextSTRelationship::NextSTRelationship(const std::string& arg1, const std::string& arg2) : Relationship(arg1, arg2) {
    keyword = Constants::NEXTST;
}

std::vector<std::shared_ptr<Entity>> NextSTRelationship::verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) {
    std::shared_ptr<Entity> arg1Value = ParserUtils::getValidStmtRef(arg1, declarations);
    std::shared_ptr<Entity> arg2Value = ParserUtils::getValidStmtRef(arg2, declarations);

    return { arg1Value, arg2Value };
}