/*********************************************************************
Copyright (c) 2023, Claudio Costagliola Fiedler
All rights reserved.

This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
**********************************************************************/
#include <personAccount.h>
#include <enterpriseAccount.h>
#include <accountMgr.h>
#include <accountId.h>

#include <gtest/gtest.h>

//PersonAccount
TEST(PersonAccount, ConstructionAndOperators) {

  PersonAccount<AccountId_IdPartType> pa1;
  ASSERT_EQ(pa1.firstName(), "");
  ASSERT_EQ(pa1.lastName(), "");
  ASSERT_EQ(pa1.balance(), 0);

  PersonAccount<AccountId_IdPartType> pa2;
  ASSERT_TRUE(pa1 == pa2);
  pa1.setFirstName("FN");
  pa1.setLastName("LN");
  EXPECT_TRUE(pa1.addToBalance(100));
  ASSERT_EQ(pa1.balance(), 100);
  ASSERT_FALSE(pa1 == pa2);
  pa2 = pa1;
  ASSERT_EQ(pa2.firstName(), "FN");
  ASSERT_EQ(pa2.lastName(), "LN");
  ASSERT_EQ(pa2.balance(), 100);

  PersonAccount<AccountId_IdPartType> pa3(pa2);
  ASSERT_EQ(pa3.firstName(), "FN");
  ASSERT_EQ(pa3.lastName(), "LN");
  ASSERT_EQ(pa3.balance(), 100);
}

TEST(PersonAccount, GettersSetters) {

  PersonAccount<AccountId_IdPartType> pa;
  ASSERT_EQ(pa.firstName(), "");
  ASSERT_EQ(pa.lastName(), "");
  ASSERT_EQ(pa.balance(), 0);

  pa.setFirstName("XXX");
  pa.setLastName("YYY");
  EXPECT_TRUE(pa.addToBalance(100));
  EXPECT_EQ(pa.firstName(), "XXX");
  EXPECT_EQ(pa.lastName(), "YYY");
  EXPECT_EQ(pa.balance(), 100);
}

TEST(PersonAccount, BalanceOperations) {

  PersonAccount<AccountId_IdPartType> pa;
  ASSERT_EQ(pa.balance(), 0);
  
  EXPECT_FALSE(pa.decreaseFromBalance(-1));
  EXPECT_EQ(pa.balance(), 0);
  EXPECT_FALSE(pa.decreaseFromBalance(1));
  EXPECT_EQ(pa.balance(), 0);

  EXPECT_FALSE(pa.addToBalance(-1));
  EXPECT_EQ(pa.balance(), 0);
  EXPECT_TRUE(pa.addToBalance(10));
  EXPECT_EQ(pa.balance(), 10);

  EXPECT_TRUE(pa.decreaseFromBalance(5));
  EXPECT_EQ(pa.balance(), 5);
}

//EnterpriseAccount
TEST(EnterpriseAccount, ConstructionAndOperators) {

  EnterpriseAccount<AccountId_IdPartType> ea1;
  ASSERT_EQ(ea1.yTunnus(), "");
  ASSERT_EQ(ea1.companyName(), "");
  ASSERT_EQ(ea1.balance(), 0);

  EnterpriseAccount<AccountId_IdPartType> ea2;
  ASSERT_TRUE(ea1 == ea2);
  ea1.setYTunnus("YT");
  ea1.setCompanyName("CN");
  EXPECT_TRUE(ea1.addToBalance(100));
  ASSERT_EQ(ea1.balance(), 100);
  ASSERT_FALSE(ea1 == ea2);
  ea2 = ea1;
  ASSERT_EQ(ea2.yTunnus(), "YT");
  ASSERT_EQ(ea2.companyName(), "CN");
  ASSERT_EQ(ea2.balance(), 100);

  EnterpriseAccount<AccountId_IdPartType> ea3(ea2);
  ASSERT_EQ(ea3.yTunnus(), "YT");
  ASSERT_EQ(ea3.companyName(), "CN");
  ASSERT_EQ(ea3.balance(), 100);
}

TEST(EnterpriseAccount, GettersSetters) {

  EnterpriseAccount<AccountId_IdPartType> ea;
  ASSERT_EQ(ea.yTunnus(), "");
  ASSERT_EQ(ea.companyName(), "");
  ASSERT_EQ(ea.balance(), 0);

  ea.setYTunnus("XXX");
  ea.setCompanyName("YYY");
  EXPECT_TRUE(ea.addToBalance(100));
  EXPECT_EQ(ea.yTunnus(), "XXX");
  EXPECT_EQ(ea.companyName(), "YYY");
  EXPECT_EQ(ea.balance(), 100);
}

TEST(EnterpriseAccount, BalanceOperations) {

  EnterpriseAccount<AccountId_IdPartType> pa;
  ASSERT_EQ(pa.balance(), 0);
  
  EXPECT_FALSE(pa.decreaseFromBalance(-1));
  EXPECT_EQ(pa.balance(), 0);
  EXPECT_FALSE(pa.decreaseFromBalance(1));
  EXPECT_EQ(pa.balance(), 0);

  EXPECT_FALSE(pa.addToBalance(-1));
  EXPECT_EQ(pa.balance(), 0);
  EXPECT_TRUE(pa.addToBalance(10));
  EXPECT_EQ(pa.balance(), 10);

  EXPECT_TRUE(pa.decreaseFromBalance(5));
  EXPECT_EQ(pa.balance(), 5);
}

//AccountId
TEST(AccountId, ConstructionAndOperators) {
  AccountId<AccountId_IdPartType> id1;
  ASSERT_EQ(id1.id(), 0);
  ASSERT_EQ(id1.creationDate(), "");

  AccountId<AccountId_IdPartType> id2(100, "XXX");
  ASSERT_EQ(id2.id(), 100);
  ASSERT_EQ(id2.creationDate(), "XXX");

  AccountId<AccountId_IdPartType> id3(id2);
  ASSERT_EQ(id3.id(), 100);
  ASSERT_EQ(id3.creationDate(), "XXX");

  id1 = id2;
  ASSERT_EQ(id1.id(), 100);
  ASSERT_EQ(id1.creationDate(), "XXX");

  ASSERT_TRUE(id2 == id3);
  AccountId<AccountId_IdPartType> id4;
  ASSERT_FALSE(id1 == id4);
}

TEST(AccountMgr, CreateAccount) {
  AccountMgr mgr;

  accountIdType idp1 = mgr.insertNewPersonAccount("FirstName1", "LastName1");
  AccountId_IdPartType iId = idp1.id();

  std::time_t t = std::time(nullptr);
  std::tm tm = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&tm, "%Y%m%d");
  
  ASSERT_EQ(idp1.creationDate(), oss.str());
  accountIdType idp2 = mgr.insertNewPersonAccount("FirstName2", "LastName2");
  ASSERT_EQ(idp2.creationDate(), oss.str());
  ASSERT_NE(idp1.id(), idp2.id());

  accountIdType ide1 = mgr.insertNewEnterpriseAccount("YTunnus1", "CompanyName1");
  ASSERT_EQ(ide1.creationDate(), oss.str());
  ASSERT_NE(ide1.id(), idp1.id());
  ASSERT_NE(ide1.id(), idp2.id());
}

TEST(AccountMgr, Balance) {
  AccountMgr mgr;

  accountIdType idp1 = mgr.insertNewPersonAccount("FirstName1", "LastName1");
  accountIdType idp2;
  EXPECT_FALSE(mgr.withdrawFromAccount(idp2, 10));
  EXPECT_FALSE(mgr.withdrawFromAccount(idp1, 10));
  EXPECT_FALSE(mgr.withdrawFromAccount(idp1, -10));

  EXPECT_FALSE(mgr.topUpAccount(idp2, 10));
  EXPECT_FALSE(mgr.topUpAccount(idp1, -10));

  EXPECT_TRUE(mgr.topUpAccount(idp1, 10));
  EXPECT_TRUE(mgr.withdrawFromAccount(idp1, 5));
}

TEST(AccountMgr, GetDetails) {
  AccountMgr mgr;

  accountIdType idp1 = mgr.insertNewPersonAccount("FirstName1", "LastName1");
  accountIdType ide1 = mgr.insertNewEnterpriseAccount("YTunnus1", "CompanyName1");
  accountIdType idp2;

  EXPECT_NE(mgr.getAccountDetails(idp1).find("Account type: Person"), std::string::npos);
  EXPECT_NE(mgr.getAccountDetails(idp1).find("First Name: FirstName1"), std::string::npos);

  EXPECT_NE(mgr.getAccountDetails(ide1).find("Account type: Enterprise"), std::string::npos);
  EXPECT_NE(mgr.getAccountDetails(ide1).find("Y-Tunnus: YTunnus1"), std::string::npos);

  EXPECT_NE(mgr.getAccountDetails(idp2).find("<ACCOUNT NOT FOUND>"), std::string::npos);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}