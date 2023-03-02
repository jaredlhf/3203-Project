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
    if (keyword == Constants::FOLLOWSST) return std::make_shared<FollowsTRelationship>(FollowsTRelationship(arg1, arg2));
    if (keyword == Constants::PARENT) return std::make_shared<ParentRelationship>(ParentRelationship(arg1, arg2));
    if (keyword == Constants::PARENTST) return std::make_shared<ParentTRelationship>(ParentTRelationship(arg1, arg2));
    if (keyword == Constants::USES) return std::make_shared<UsesSRelationship>(UsesSRelationship(arg1, arg2));
    if (keyword == Constants::MODIFIES) return std::make_shared<ModifiesSSRelationship>(ModifiesSSRelationship(arg1, arg2));

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

FollowsTRelationship::FollowsTRelationship(const std::string& arg1, const std::string& arg2) : Relationship(arg1, arg2) {
    keyword = Constants::FOLLOWSST;
}

std::vector<std::shared_ptr<Entity>> FollowsTRelationship::verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) {
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

ParentTRelationship::ParentTRelationship(const std::string& arg1, const std::string& arg2) : Relationship(arg1, arg2) {
    keyword = Constants::PARENTST;
}

std::vector<std::shared_ptr<Entity>> ParentTRelationship::verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) {
    std::shared_ptr<Entity> arg1Value = ParserUtils::getValidStmtRef(arg1, declarations);
    std::shared_ptr<Entity> arg2Value = ParserUtils::getValidStmtRef(arg2, declarations);

    return { arg1Value, arg2Value };
}

UsesSRelationship::UsesSRelationship(const std::string& arg1, const std::string& arg2) : Relationship(arg1, arg2) {
    keyword = Constants::USES;
}

std::vector<std::shared_ptr<Entity>> UsesSRelationship::verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) {
    std::shared_ptr<Entity> arg1Value = ParserUtils::getValidStmtRef(arg1, declarations);
    std::shared_ptr<Entity> arg2Value = ParserUtils::getValidEntRef(arg2, declarations);

    return { arg1Value, arg2Value };
}

ModifiesSSRelationship::ModifiesSSRelationship(const std::string& arg1, const std::string& arg2) : Relationship(arg1, arg2) {
    keyword = Constants::MODIFIES;
}

std::vector<std::shared_ptr<Entity>> ModifiesSSRelationship::verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) {
    std::shared_ptr<Entity> arg1Value = ParserUtils::getValidStmtRef(arg1, declarations);
    std::shared_ptr<Entity> arg2Value = ParserUtils::getValidEntRef(arg2, declarations);

    return { arg1Value, arg2Value };
}
