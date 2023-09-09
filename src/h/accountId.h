/*********************************************************************
Copyright (c) 2023, Claudio Costagliola Fiedler
All rights reserved.

This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
**********************************************************************/
#ifndef H_ACCOUNT_ID
#define H_ACCOUNT_ID

#include <cstddef>
#include <string>

/**
 * @brief A class that represents the identification of an Account.
 * 
 * @tparam T_Id Defines the type to be used as the Id part of the AccountId class.
 */
template<typename T_Id> class AccountId {
public:
    /**
     * @brief Construct a new Account Id object
     * 
     */
    AccountId();

    /**
     * @brief Copy constructor.
     * 
     * @param other The AccountId object to be copied.
     */
    AccountId(const AccountId<T_Id>& other);

    /**
     * @brief Custom constructor to build a filled AccountId.
     * 
     * @param _id The id part of the account. This number must be unique.
     * @param _creationDate A string representing the date when the account was created.
     */
    AccountId(const T_Id& _id, const std::string& _creationDate);

    /**
     * @brief The assignment operator
     * 
     * @param rhs Right hand side of the assignation operation..
     * @return AccountId<T_Id>& Returns the just assigned object, allowing to chain the assignation.
     */
    AccountId<T_Id>& operator=(const AccountId<T_Id>& rhs);

    /**
     * @brief Returns the id part of the AccountId
     * 
     * @return const T_Id& The id part of the AccountId
     */
    const T_Id& id() const;

    /**
     * @brief Returns the creation date.
     * 
     * @return const std::string& The creation date.
     */
    const std::string& creationDate() const;

    /**
     * @brief The equality comparator. It's a requirement to insert objects of this class
     * in std::unordered_map.
     * 
     * @param rhs The right hand side of the comparison.
     * @return true Objects are equal, i.e., all their corresponding attributes are equal.
     * @return false Objects are different.
     */
    bool operator==(const AccountId<T_Id>& rhs) const;

private:
    T_Id m_Id;
    std::string m_creationDate;
};

/**
 * @brief Implementation of a hash functions taking into account all the attributes of the class. This
 * is a requirement to insert objects of this class into unordered_map.
 * 
 * @tparam T_Id Defines the type to be used as the Id part of the AccountId class.
 */
template<typename T_Id>
class AccountIdHashFunctor {
public:
    /**
     * @brief Defines () operator and allows objects of this class to be called as functions (functor).
     * 
     * @param aid The AccountId object to calculate its hash.
     * @return size_t The hash value of the object.
     */
    size_t operator()(const AccountId<T_Id>& aid) const {
        return (std::hash<T_Id>()(aid.id())) ^ (std::hash<std::string>()(aid.creationDate()));
    }
};

//IMPLEMENTATIONS
template<typename T_Id>
AccountId<T_Id>::AccountId() :
    m_Id(),
    m_creationDate()
{}

template<typename T_Id>
AccountId<T_Id>::AccountId(const T_Id& _id, const std::string& _creationDate) :
    m_Id(_id),
    m_creationDate(_creationDate)
{}

template<typename T_Id>
AccountId<T_Id>::AccountId(const AccountId<T_Id>& other) :
    m_Id(other.m_Id),
    m_creationDate(other.m_creationDate)
{}

template<typename T_Id>
AccountId<T_Id>& AccountId<T_Id>::operator=(const AccountId<T_Id>& rhs) {
    m_Id = rhs.m_Id;
    m_creationDate = rhs.m_creationDate;

    return *this;
}

template<typename T_Id>
const T_Id& AccountId<T_Id>::id() const {

    return m_Id;
}

template<typename T_Id>
const std::string& AccountId<T_Id>::creationDate() const {

    return m_creationDate;
}

template<typename T_Id>
bool AccountId<T_Id>::operator==(const AccountId<T_Id>& rhs) const {

    return (m_Id == rhs.m_Id) && (m_creationDate == rhs.m_creationDate);
}

#endif //H_ACCOUNT_ID