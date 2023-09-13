/*********************************************************************
Copyright (c) 2023, Claudio Costagliola Fiedler
All rights reserved.

This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
**********************************************************************/
#ifndef H_ABSTRACT_ACCOUNT
#define H_ABSTRACT_ACCOUNT

#include <string>
#include <unordered_map>
#include <accountId.h>
#include <visitor.h>

/**
 * 
 * @brief Pure virtual base class for the Account class hierarchy.
 *
 * This class represents an account. It declares the basic
 * operations to be performed in any kind of account.
 * 
 * @tparam T_Id The type of the Id part of the class
 * AccountId used to identify each individual account.
  */
template<typename T_Id>
class AbstractAccount {
public:
    /**
     * @brief Method used to add balance to the account.
     * 
     * @param amount The amount of money to add. Must be > 0.
     * @return true Successful operation, amount added to balance.
     * @return false Error ocurred, balance not modified.
     */
    virtual bool addToBalance(int amount) = 0;

    /**
     * @brief Method used to decrease balance from the account.
     * 
     * @param amount The amount of money to decrease. Must be > 0.
     * @return true Successful operation, amount decrease from balance.
     * @return false Error ocurred, balance not modified.
     */
    virtual bool decreaseFromBalance(int amount) = 0;


    /**
     * @brief Returns the balance of the account
     * 
     * @return int The balance
     */
    virtual int balance() const = 0;

    /**
     * @brief Returns the id of the account.
     * 
     * @return const AccountId<T_Id>& The account id.
     */
    virtual const AccountId<T_Id>& id() const = 0;

    /**
     * @brief Method to implement the Visitor Pattern.
     * 
     * @param visitor A concrete visitor object. The object must extend Visitor<T_Id> abstract class.
     */
    virtual void accept(Visitor<T_Id> *visitor) = 0;
};

#endif //H_ABSTRACT_ACCOUNT