/*********************************************************************
Copyright (c) 2023, Claudio Costagliola Fiedler
All rights reserved.

This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
**********************************************************************/
#ifndef H_ACCOUNT
#define H_ACCOUNT

#include <string>

#include <abstractAccount.h>

/**
 * @brief An intermediate class that implements common functionality to all concrete account types.
 * 
 * @tparam T_Id The type of the Id part of the class
 * AccountId used to identify each individual account.
 */
template<typename T_Id>
class Account : public AbstractAccount<T_Id> {
public:

    /**
     * @brief Constructs a new Account object
     * 
     */
    Account();

    /**
     * @brief Adds balance to the account.
     * 
     * @param amount The amount of money to add. It must be > 0.
     * @return true The amount was added to the account's balance.
     * @return false The amount is a negative number.
     */
    bool addToBalance(int amount) override;


    /**
     * @brief Decrease balance from the account.
     * 
     * @param amount The amount of money to decrease. It must be > 0 and less than the current balance of the account.
     * @return true The amount was decreased from the account's balance.
     * @return false The amount is a negative number or is larger than the current account's balance.
     */
    bool decreaseFromBalance(int amount) override;

    /**
     * @brief Returns the current balance of the account.
     * 
     * @return int The current balance.
     */
    int balance() const;

    /**
     * @brief Returns the Id of the account.
     * 
     * @return const AccountId<T_Id>& The Id object of the account.
     */
    const AccountId<T_Id>& id() const override;

    /**
     * @brief Sets the Id object of the account.
     * 
     * @param _id The id object to set.
     */
    void setId(const AccountId<T_Id>& _id);

private:
    AccountId<T_Id> m_id;
    int m_balance;
};

//IMPLEMENTATION
template<typename T_Id>
Account<T_Id>::Account() :
    m_balance(0)
{}

template<typename T_Id>
bool Account<T_Id>::addToBalance(int amount) {

    if (amount < 0) return false;

    m_balance += amount;
    return true;
}

template<typename T_Id>
bool Account<T_Id>::decreaseFromBalance(int amount) {

    if (amount < 0) return false;

    if (amount > m_balance) {
        return false        ;
    } else {
        m_balance -= amount;
        return true;
    }
}

template<typename T_Id>
int Account<T_Id>::balance() const {

    return m_balance;
}

template<typename T_Id>
const AccountId<T_Id>& Account<T_Id>::id() const {

    return m_id;
}

template<typename T_Id>
void Account<T_Id>::setId(const AccountId<T_Id>& _id) {

    m_id = _id;
}

#endif //H_ACCOUNT