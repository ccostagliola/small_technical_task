/*********************************************************************
Copyright (c) 2023, Claudio Costagliola Fiedler
All rights reserved.

This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
**********************************************************************/
#ifndef H_ACCOUNT_MGR
#define H_ACCOUNT_MGR

#include <unordered_map>
#include <memory>
#include <string>
#include <sstream>

#include <accountId.h>
#include <account.h>
#include <personAccount.h>
#include <enterpriseAccount.h>
#include <visitor.h>

/* ************************
 * Modify the following typedef to change the type of the id part of AccountId
 * The type used must have a std::hash instantiation or a hash functor defined.
 * ************************/
/** This type defines the type of the id part of the AccountId class. */
typedef int AccountId_IdPartType;
/*************************/

/** This typedef defines the type of the id AccountId classes used in the application. */
typedef AccountId<AccountId_IdPartType> accountIdType;

class AccountMgr {
public:
    /**
     * @brief Construct a new Account Mgr object
     * 
     */
    AccountMgr();

    /**
     * @brief Adds money to the account identified by id.
     * 
     * @param id The AccountId object that identifies the account.
     * @param amount The amount of money to add. It must be > 0.
     * @return true The amount was successfuly added to the account.
     * @return false The amount couldn't be added becuause it's a negative number.
     * Or the account doesn't exist.
     */
    bool topUpAccount(const accountIdType& id, int amount);

    /**
     * @brief Withdraws money from the account identified by id.
     * 
     * @param id The AccountId object that identifies the account.
     * @param amount The amount of money to withdraw. It must be > 0 and less than the current balance of the account.
     * @return true The amount was successfuly withdrawn from the account.
     * @return false The amount couldn't be added because it's a negative number or is greater than the current balance of the acount. Or the account doesn't exist.
     */
    bool withdrawFromAccount(const accountIdType& id, int amount);

    /**
     * @brief Returns a string with the details of the account
     * 
     * @param id The id of the object.
     * @return std::string The details of the account.
     */
    std::string getAccountDetails(const accountIdType& id) const;

    /**
     * @brief Inserts a new person account into the internal database of the object.
     * 
     * @param firstName The first name of the account's owner.
     * @param lastName The last name of the account's owner.
     * @return const accountIdType& The AccountId object of the just created account.
     */
    const accountIdType& insertNewPersonAccount(const std::string& firstName, const std::string& lastName);

    /**
     * @brief Inserts a new enterprise account into the internal database of the object.
     * 
     * @param yTunnus The Y-tunnus identifier of the enterprise.
     * @param companyName The enterprise name.
     * @return const accountIdType& The AccountId object of the just created account.
     */
    const accountIdType& insertNewEnterpriseAccount(const std::string& yTunnus, const std::string& companyName);

private:
    PersonAccount<AccountId_IdPartType>* createNewPersonAccountPtr(const std::string& firstName, const std::string& lastName);
    EnterpriseAccount<AccountId_IdPartType>* createNewEnterpriseAccountPtr(const std::string& yTunnus, const std::string& companyName);
    typedef std::unordered_map<accountIdType, std::unique_ptr<AbstractAccount<AccountId_IdPartType>>, AccountIdHashFunctor<AccountId_IdPartType> > AccountMgrUnorderedMap;
    AccountMgrUnorderedMap m_actMgrDB;
};

template<typename T_Id>
class AccountDetailsVisitor : public Visitor<T_Id> {
public:
    AccountDetailsVisitor();
    void VisitPersonAccount(const PersonAccount<T_Id> *account) override;
    void VisitEnterpriseAccount(const EnterpriseAccount<T_Id> *account) override;
    const std::string& accountDetails() const;

private:
    std::string m_accountDetails;
};

//IMPLEMENTATION
template<typename T_Id>
AccountDetailsVisitor<T_Id>::AccountDetailsVisitor() :
    m_accountDetails()
{}

template<typename T_Id>
const std::string& AccountDetailsVisitor<T_Id>::accountDetails() const {

    return m_accountDetails;
}

template<typename T_Id>
void AccountDetailsVisitor<T_Id>::VisitPersonAccount(const PersonAccount<T_Id> *account) {

    std::ostringstream s;

    s << std::string("Account type: Person") << std::endl;
    s << std::string("Account Id: id: ") << account->id().id() << ", creation date: \"" << account->id().creationDate() << "\"" << std::endl;
    s << std::string("First Name: ") << account->firstName() << std::endl;
    s << std::string("Last Name: ") << account->lastName() << std::endl;
    s << std::string("Balance: ") << account->balance() << std::endl;
    m_accountDetails = s.str();
}

template<typename T_Id>
void AccountDetailsVisitor<T_Id>::VisitEnterpriseAccount(const EnterpriseAccount<T_Id> *account) {

    std::ostringstream s;

    s << std::string("Account type: Enterprise") << std::endl;
    s << std::string("Account Id: id: ") << account->id().id() << ", creation date: \"" << account->id().creationDate() << "\"" << std::endl;
    s << std::string("Y-Tunnus: ") << account->yTunnus() << std::endl;
    s << std::string("Company Name: ") << account->companyName() << std::endl;
    s << std::string("Balance: ") << account->balance() << std::endl;
    m_accountDetails = s.str();
}

#endif //H_ACCOUNT_MGR