#pragma once

#include <string>
#include "../constants/Constants.h"
#include "../constants/Entity.h"
#include "../constants/Synonym.h"
#include "../constants/Value.h"
#include "../constants/Wildcard.h"
#include "../utils/ParserUtils.h"

class Relationship {
    protected:
        std::string keyword;
        std::string arg1;
        std::string arg2;
        
    public:
        // Constructor
        Relationship(const std::string& arg1, const std::string& arg2);

        // instance functions
        std::string getKeyword();
        bool compare(std::shared_ptr<Relationship> other);

        // static class functions
        static std::shared_ptr<Relationship> create(const std::string& keyword, const std::string& arg1, const std::string& arg2);

        // functions to override
        virtual std::vector<std::shared_ptr<Entity>> verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations);
};

class FollowsRelationship : public Relationship {
    public:
        FollowsRelationship(const std::string& arg1, const std::string& arg2);
        virtual std::vector<std::shared_ptr<Entity>> verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) override;
};

class FollowsTRelationship : public Relationship {
    public:
        FollowsTRelationship(const std::string& arg1, const std::string& arg2);
        virtual std::vector<std::shared_ptr<Entity>> verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) override;
};

class ParentRelationship : public Relationship {
    public:
        ParentRelationship(const std::string& arg1, const std::string& arg2);
        virtual std::vector<std::shared_ptr<Entity>> verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) override;
};

class ParentTRelationship : public Relationship {
    public:
        ParentTRelationship(const std::string& arg1, const std::string& arg2);
        virtual std::vector<std::shared_ptr<Entity>> verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) override;
};

class UsesSRelationship : public Relationship {
    public:
        UsesSRelationship(const std::string& arg1, const std::string& arg2);
        virtual std::vector<std::shared_ptr<Entity>> verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) override;
};

class ModifiesSSRelationship : public Relationship {
    public:
        ModifiesSSRelationship(const std::string& arg1, const std::string& arg2);
        virtual std::vector<std::shared_ptr<Entity>> verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations) override;
};