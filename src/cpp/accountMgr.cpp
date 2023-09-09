/*********************************************************************
Copyright (c) 2023, Claudio Costagliola Fiedler
All rights reserved.

This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
**********************************************************************/
#include <accountMgr.h>
#include <accountId.h>
#include <singletonUniqueIdGenerator.h>
#include <sstream>
#include <iomanip>
#include <ctime>

AccountMgr::AccountMgr() :
    m_actMgrDB()
{}

bool AccountMgr::topUpAccount(const accountIdType& id, int amount) {

    auto it = m_actMgrDB.find(id);
    if (it != m_actMgrDB.end()) {
        return (*it).second->addToBalance(amount);
    }
    return false;
}

bool AccountMgr::withdrawFromAccount(const accountIdType& id, int amount) {

    auto it = m_actMgrDB.find(id);
    if (it != m_actMgrDB.end()) {
        return (*it).second->decreaseFromBalance(amount);
    }
    return false;
}

PersonAccount<AccountId_IdPartType>* AccountMgr::createNewPersonAccountPtr(const std::string& firstName, const std::string& lastName) {

    PersonAccount<AccountId_IdPartType>* account = new PersonAccount<AccountId_IdPartType>;
    account->setFirstName(firstName);
    account->setLastName(lastName);

    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d");
    AccountId<AccountId_IdPartType> id(SingletonUniqueIdGenerator::instance().incrementAndReturn(), oss.str());
    account->setId(id);

    return account;
}

EnterpriseAccount<AccountId_IdPartType>* AccountMgr::createNewEnterpriseAccountPtr(const std::string& yTunnus, const std::string& companyName) {

    EnterpriseAccount<AccountId_IdPartType>* account = new EnterpriseAccount<AccountId_IdPartType>;
    account->setYTunnus(yTunnus);
    account->setCompanyName(companyName);

    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d");
    AccountId<AccountId_IdPartType> id(SingletonUniqueIdGenerator::instance().incrementAndReturn(), oss.str());
    account->setId(id);

    return account;
}

const accountIdType& AccountMgr::insertNewPersonAccount(const std::string& firstName, const std::string& lastName) {

    PersonAccount<AccountId_IdPartType>* account = createNewPersonAccountPtr(firstName, lastName);
    m_actMgrDB[account->id()] = std::unique_ptr<AbstractAccount<AccountId_IdPartType>>(account);

    return account->id();
}

const accountIdType& AccountMgr::insertNewEnterpriseAccount(const std::string& yTunnus, const std::string& companyName) {

    EnterpriseAccount<AccountId_IdPartType>* account = createNewEnterpriseAccountPtr(yTunnus, companyName);
    m_actMgrDB[account->id()] = std::unique_ptr<AbstractAccount<AccountId_IdPartType>>(account);

    return account->id();
}

std::string AccountMgr::getAccountDetails(const accountIdType& id) const {

    AccountDetailsVisitor<AccountId_IdPartType> visitor;
    auto it = m_actMgrDB.find(id);
    if (it != m_actMgrDB.end()) {
        (*it).second->accept(&visitor);
        return visitor.accountDetails();
    }
    return "<ACCOUNT NOT FOUND>";
}