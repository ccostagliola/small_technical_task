/*********************************************************************
Copyright (c) 2023, Claudio Costagliola Fiedler
All rights reserved.

This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
**********************************************************************/
#ifndef H_VISITOR
#define H_VISITOR

template <typename T_Id> class PersonAccount;
template <typename T_Id> class EnterpriseAccount;

/**
 * @brief Abstract clase to implement the Visitor pattern.
 * 
 * @tparam T_Id Defines the type to be used as the Id part of the AccountId class.
 */
template <typename T_Id>
class Visitor {
public:

    /**
     * @brief A concrete method to visit PersonAccount.
     * 
     * @param account The account to visit.
     */
    virtual void VisitPersonAccount(const PersonAccount<T_Id> *account) = 0;
    virtual void VisitEnterpriseAccount(const EnterpriseAccount<T_Id> *account) = 0;
};

#endif //H_VISITOR