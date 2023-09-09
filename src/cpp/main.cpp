/*********************************************************************
Copyright (c) 2023, Claudio Costagliola Fiedler
All rights reserved.

This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
**********************************************************************/
#include <iostream>
#include <string>
#include <charconv>

#include <accountMgr.h>
#include <accountId.h>

void createNewPersonAccount(AccountMgr& db) {

    std::string firstName;
    std::string lastName;
    std::cout << "First name? ";
    std::cin >> firstName;
    std::cout << "Last name? ";
    std::cin >> lastName;

    accountIdType id = db.insertNewPersonAccount(firstName, lastName);
    std::cout   << "Account created: {" << id.id() << ", "
                << id.creationDate() << "}" <<  std::endl;
}

void createNewEnterpriseAccount(AccountMgr& db) {

    std::string yTunnus;
    std::string companyName;
    std::cout << "Y tunnus? ";
    std::cin >> yTunnus;
    std::cout << "Company name? ";
    std::cin >> companyName;

    accountIdType id = db.insertNewEnterpriseAccount(yTunnus, companyName);
    std::cout   << "Account created: {" << id.id() << ", "
                << id.creationDate() << "}" <<  std::endl;
}

void addBalance(AccountMgr& db) {

    std::string sId;
    std::string creationDate;
    std::string sAmount;
    std::cout << "Id? ";
    std::cin >> sId;
    std::cout << "Creation Date? ";
    std::cin >> creationDate;
    std::cout << "Amount (> 0)? ";
    std::cin >> sAmount;

    int id;
    std::from_chars_result r = std::from_chars(sId.data(), sId.data() + sId.size(), id);
    if (r.ec == std::errc::invalid_argument) {
        std::cout << "Wrong argument Id!" << std::endl;
        return;
    }

    int amount;
    r = std::from_chars(sAmount.data(), sAmount.data() + sAmount.size(), amount);
    if ((r.ec == std::errc::invalid_argument) || (amount < 0)) {
        std::cout << "Wrong argument Amount!" << std::endl;
        return;
    }

    accountIdType aId(id, creationDate);
    if (db.topUpAccount(aId, amount))  {
        std::cout << "Success!" << std::endl;
    } else {
        std::cout << "Error!" << std::endl;
    }
}

void decreaseBalance(AccountMgr& db) {

    std::string sId;
    std::string creationDate;
    std::string sAmount;
    std::cout << "Id? ";
    std::cin >> sId;
    std::cout << "Creation Date? ";
    std::cin >> creationDate;
    std::cout << "Amount (> 0)? ";
    std::cin >> sAmount;

    int id;
    std::from_chars_result r = std::from_chars(sId.data(), sId.data() + sId.size(), id);
    if (r.ec == std::errc::invalid_argument) {
        std::cout << "Wrong argument Id!" << std::endl;
        return;
    }

    int amount;
    r = std::from_chars(sAmount.data(), sAmount.data() + sAmount.size(), amount);
    if ((r.ec == std::errc::invalid_argument) || (amount < 0)) {
        std::cout << "Wrong argument Amount!" << std::endl;
        return;
    }

    accountIdType aId(id, creationDate);
    if (db.withdrawFromAccount(aId, amount))  {
        std::cout << "Success!" << std::endl;
    } else {
        std::cout << "Error!" << std::endl;
    }
}

void accountDetails(AccountMgr& db) {

    std::string sId;
    std::string creationDate;
    std::cout << "Id? ";
    std::cin >> sId;
    std::cout << "Creation Date? ";
    std::cin >> creationDate;

    int id;
    std::from_chars_result r = std::from_chars(sId.data(), sId.data() + sId.size(), id);
    if (r.ec == std::errc::invalid_argument) {
        std::cout << "Wrong argument Id!" << std::endl;
        return;
    }

    accountIdType aId(id, creationDate);
    std::cout << "****" << std::endl;
    std::cout << db.getAccountDetails(aId) << std::endl;
    std::cout << "****" << std::endl;
}

void processOption(const std::string& op, AccountMgr& db) {

    if (op == "1") {
        createNewPersonAccount(db);
    } else if (op == "2") {
        createNewEnterpriseAccount(db);
    } else if (op == "3") {
        addBalance(db);
    } else if (op == "4") {
        decreaseBalance(db);
    } else if (op == "5") {
        accountDetails(db);
    } else {
        std::cout << "INVALID OPTION!" << std::endl;
    }
}

int main(int argc, char* argv[]) {

    AccountMgr db;

    std::string option;
    while (option != "6") {
        std::cout << "Options" << std::endl;
        std::cout << "-------" << std::endl;
        std::cout << "1.- Create new person account" << std::endl;
        std::cout << "2.- Create new enterprise account" << std::endl;
        std::cout << "3.- Add balance to account" << std::endl;
        std::cout << "4.- Decrease balance from account" << std::endl;
        std::cout << "5.- Get account details" << std::endl;
        std::cout << "6.- Salir" << std::endl;
        std::cout << "? ";
        std::cin >> option;

        if (option != "6") {
            processOption(option, db);
        }
    }

    return 0;
}