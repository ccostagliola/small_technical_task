/*********************************************************************
Copyright (c) 2023, Claudio Costagliola Fiedler
All rights reserved.

This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
**********************************************************************/
#ifndef H_PERSONACCOUNT
#define H_PERSONACCOUNT

#include <string>
#include <unordered_map>

#include <account.h>

template <typename T_Id>
class PersonAccount : public Account<T_Id> {
public:
    /**
     * @brief Construct a new Person Account object
     * 
     */
    PersonAccount();

    /**
     * @brief The copy constructor.
     * 
     * @param other The class to copy their values from.
     */
    PersonAccount(const PersonAccount<T_Id>& other);

    /**
     * @brief The assignment operator.
     * 
     * @param rhs The object to copy all their attributes from.
     * @return PersonAccount<T_Id>& Return the object just assigned,
     * allowing assignation chaining.
     */
    PersonAccount<T_Id>& operator=(const PersonAccount<T_Id>& rhs);

    /**
     * @brief Set the First Name of the account's owner.
     * 
     * @param _firstName The first name.
     */
    void setFirstName(const std::string& _firstName);

    /**
     * @brief Set the Last Name object of the account's owner.
     * 
     * @param _lastName The last name.
     */
    void setLastName(const std::string& _lastName);

    /**
     * @brief Returns the first name of the accoun't owner.
     * 
     * @return const std::string& The first name.
     */
    const std::string& firstName() const;

    /**
     * @brief Returns the last name of the accoun't owner.
     * 
     * @return const std::string& The last name.
     */
    const std::string& lastName() const;

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
    bool operator==(const PersonAccount<T_Id>& rhs) const;

private:
    int m_balance;
    std::string m_firstName;
    std::string m_lastName;
};

//IMPLEMENTATION
template <typename T_Id>
PersonAccount<T_Id>::PersonAccount() :
    Account<T_Id>(),
    m_firstName(),
    m_lastName()
{}

template <typename T_Id>
PersonAccount<T_Id>::PersonAccount(const PersonAccount<T_Id>& other) :
    Account<T_Id>(),
    m_firstName(other.m_firstName),
    m_lastName(other.m_lastName)
{
    this->addToBalance(other.balance());
}

template <typename T_Id>
PersonAccount<T_Id>& PersonAccount<T_Id>::operator=(const PersonAccount<T_Id>& rhs) {

    this->setId(rhs.id());
    this->setFirstName(rhs.firstName());
    this->setLastName(rhs.lastName());
    this->addToBalance(rhs.balance());

    return *this;
}

template <typename T_Id>
void PersonAccount<T_Id>::setFirstName(const std::string& _firstName) {

    m_firstName = _firstName;
}

template <typename T_Id>
void PersonAccount<T_Id>::setLastName(const std::string& _lastName) {

    m_lastName = _lastName;
}

template <typename T_Id>
const std::string& PersonAccount<T_Id>::firstName() const {

    return m_firstName;
}

template <typename T_Id>
const std::string& PersonAccount<T_Id>::lastName() const {

    return m_lastName;
}

template <typename T_Id>
void PersonAccount<T_Id>::accept(Visitor<T_Id> *visitor) {

    visitor->VisitPersonAccount(this);
}

template <typename T_Id>
bool PersonAccount<T_Id>::operator==(const PersonAccount<T_Id>& rhs) const {

    return     (this->id() == rhs.id())
            && (m_firstName == rhs.firstName())
            && (m_lastName == rhs.lastName())
            && (this->balance() == rhs.balance());
}

#endif //H_PERSONACCOUNT