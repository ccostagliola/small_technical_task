/*********************************************************************
Copyright (c) 2023, Claudio Costagliola Fiedler
All rights reserved.

This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
**********************************************************************/
#ifndef H_ENTERPRISEACCOUNT
#define H_ENTERPRISEACCOUNT

#include <string>
#include <unordered_map>

#include <account.h>

template <typename T_Id>
class EnterpriseAccount : public Account<T_Id> {
public:
    /**
     * @brief Construct a new Enterprise Account object
     * 
     */
    EnterpriseAccount();

    /**
     * @brief The copy constructor.
     * 
     * @param other The class to copy their values from.
     */
    EnterpriseAccount(const EnterpriseAccount<T_Id>& other);

    /**
     * @brief The assignment operator.
     * 
     * @param rhs The object to copy all their attributes from.
     * @return EnterpriseAccount<T_Id>& Return the object just assigned,
     * allowing assignation chaining.
     */
    EnterpriseAccount<T_Id>& operator=(const EnterpriseAccount<T_Id>& rhs);

    /**
     * @brief Sets the Y-tunnus of the account's owner.
     * 
     * @param _yTunnus The Y-tunnus.
     */
    void setYTunnus(const std::string& _yTunnus);

    /**
     * @brief Sets the Company Name of the account's owner.
     * 
     * @param _companyName The Company Name.
     */
    void setCompanyName(const std::string& _companyName);

    /**
     * @brief Returns the Y-tunnus.
     * 
     * @return const std::string& The Y-tunnus.
     */
    const std::string& yTunnus() const;

    /**
     * @brief Returns the Company Name of the account's owner.
     * 
     * @return const std::string& The Company Name.
     */
    const std::string& companyName() const;

    /**
     * @brief Method to implement the Visitor pattern.
     * 
     * @param visitor The visitor object.
     */
    virtual void accept(Visitor<T_Id> *visitor) override;

    /**
     * @brief The equality operator.
     * 
     * @param rhs The object to compare with this.
     * @return true Objects are equal.
     * @return false Object are different.
     */
    bool operator==(const EnterpriseAccount<T_Id>& rhs) const;

private:
    int m_balance;
    std::string m_yTunnus;
    std::string m_companyName;
};

//IMPLEMENTATION
template <typename T_Id>
EnterpriseAccount<T_Id>::EnterpriseAccount() :
    Account<T_Id>(),
    m_yTunnus(),
    m_companyName()
{}

template <typename T_Id>
EnterpriseAccount<T_Id>::EnterpriseAccount(const EnterpriseAccount<T_Id>& other) :
    Account<T_Id>(),
    m_yTunnus(other.m_yTunnus),
    m_companyName(other.m_companyName)
{
    this->addToBalance(other.balance());
}

template <typename T_Id>
EnterpriseAccount<T_Id>& EnterpriseAccount<T_Id>::operator=(const EnterpriseAccount<T_Id>& rhs) {

    this->setId(rhs.id());
    this->setYTunnus(rhs.yTunnus());
    this->setCompanyName(rhs.companyName());
    this->addToBalance(rhs.balance());

    return *this;
}

template <typename T_Id>
void EnterpriseAccount<T_Id>::setYTunnus(const std::string& _yTunnus) {

    m_yTunnus = _yTunnus;
}

template <typename T_Id>
void EnterpriseAccount<T_Id>::setCompanyName(const std::string& _companyName) {

    m_companyName = _companyName;
}

template <typename T_Id>
const std::string& EnterpriseAccount<T_Id>::yTunnus() const {

    return m_yTunnus;
}

template <typename T_Id>
const std::string& EnterpriseAccount<T_Id>::companyName() const {

    return m_companyName;
}

template <typename T_Id>
void EnterpriseAccount<T_Id>::accept(Visitor<T_Id> *visitor) {

    visitor->VisitEnterpriseAccount(this);
}

template <typename T_Id>
bool EnterpriseAccount<T_Id>::operator==(const EnterpriseAccount<T_Id>& rhs) const {

    return     (this->id() == rhs.id())
            && (m_yTunnus == rhs.yTunnus())
            && (m_companyName == rhs.companyName())
            && (this->balance() == rhs.balance());
}

#endif //H_ENTERPRISEACCOUNT