#include <QtTest>
#include "../src/repos/idatecolumnadapter.h"
#include "../src/repos/itransactionprovider.h"
#include "../src/repos/transactionrepo.h"
#include "AutoTest.h"

class MockDateColumnAdapter
    : public IDateColumnAdapter
{
    // IDateColumnAdapter interface
public:
    bool isSame(int column, const QDateTime & dateTime) override
    {
        return column == QDateTime::currentDateTime().daysTo(dateTime);
    }

    bool isCurrent(int) override { return false; }
    QString columnName(int ) override { return {}; }
    int columnCount() override { return {}; }
    void setScale(TimeScale) override {return; };
    TimeScale scale() override { return {}; }
};

class MockTransactionProvider
    : public ITransactionProvider {

public:
    void setTransactions(Transactions transactions)
    {
        m_transactions = std::move(transactions);
        loadTransactions();
    }
    void loadTransactions() override;
private:
    Transactions m_transactions;
};

void MockTransactionProvider::loadTransactions()
{
    emit transactionReady(m_transactions);
}

class test_TransactionRepo : public QObject
{
    Q_OBJECT

public:
    test_TransactionRepo();
    ~test_TransactionRepo();

private slots:
    void test_category_counting();
    void test_has_amount();
    void test_summ_overall();
    void test_calc_amount();

private:
    std::unique_ptr<MockTransactionProvider> provider;
    std::unique_ptr<MockDateColumnAdapter> adapter;
};


test_TransactionRepo::test_TransactionRepo()
{
    provider = std::make_unique<MockTransactionProvider>();
    adapter = std::make_unique<MockDateColumnAdapter>();
}

test_TransactionRepo::~test_TransactionRepo()
{}

void test_TransactionRepo::test_summ_overall()
{
    auto repo = std::make_unique<TransactionRepo>(adapter.get(), provider.get());
    provider->setTransactions({
                  {"cat1", 1, QDateTime::currentDateTime()},
                  {"cat2", 1, QDateTime::currentDateTime()},

                  {"cat3", -5, QDateTime::currentDateTime().addDays(1)},
                  {"cat4", 10, QDateTime::currentDateTime().addDays(1)},

                  {"cat5", 11, QDateTime::currentDateTime().addDays(3)}
                  });

    QCOMPARE(repo->columnAmountOverAll(0), 2);
    QCOMPARE(repo->columnAmountOverAll(1), 5);
    QCOMPARE(repo->columnAmountOverAll(2), 0);
    QCOMPARE(repo->columnAmountOverAll(3), 11);
}

void test_TransactionRepo::test_calc_amount()
{
    auto repo = std::make_unique<TransactionRepo>(adapter.get(), provider.get());
    provider->setTransactions({
                  {"cat1", -100, QDateTime::currentDateTime()},
                  {"cat1", 1, QDateTime::currentDateTime()},

                  {"cat2", 1, QDateTime::currentDateTime()},

                  {"cat3", -5, QDateTime::currentDateTime().addDays(1)},
                  {"cat3", 10, QDateTime::currentDateTime().addDays(1)},

                  {"cat4", 11, QDateTime::currentDateTime().addDays(3)}
                  });

    //cat1
    QCOMPARE(repo->calcAmount(0, 0), -99); // day 0
    QCOMPARE(repo->calcAmount(0, 1), 0);   // day 1
    QCOMPARE(repo->calcAmount(0, 2), 0);   // day 2

    //cat2
    QCOMPARE(repo->calcAmount(1, 0), 1); // day 0
    QCOMPARE(repo->calcAmount(1, 1), 0); // day 1
    QCOMPARE(repo->calcAmount(1, 3), 0); // day 3

    //cat3
    QCOMPARE(repo->calcAmount(2, 1), 5); // day 1
    QCOMPARE(repo->calcAmount(2, 0), 0); // day 0
    QCOMPARE(repo->calcAmount(2, 3), 0); // day 3

    //cat4
    QCOMPARE(repo->calcAmount(3, 0), 0); // day 0
    QCOMPARE(repo->calcAmount(3, 3), 11);// day 3
    QCOMPARE(repo->calcAmount(3, 4), 0); // day 4
}

void test_TransactionRepo::test_category_counting()
{
    auto repo = std::make_unique<TransactionRepo>(adapter.get(), provider.get());
    provider->setTransactions({
                  {"cat1", 10, QDateTime::currentDateTime()},
                  {"cat2", 10, QDateTime::currentDateTime()},
                  {"cat1", 10, QDateTime::currentDateTime()}
                  });

    auto ts = repo->getCategories();

    QCOMPARE(ts.size(), 2);
    QCOMPARE(ts[0], "cat1");
    QCOMPARE(ts[1], "cat2");
}

void test_TransactionRepo::test_has_amount()
{
    auto repo = std::make_unique<TransactionRepo>(adapter.get(), provider.get());
    provider->setTransactions({
                  {"cat1", 10, QDateTime::currentDateTime()},
                  {"cat2", 10, QDateTime::currentDateTime().addDays(1)},
                  {"cat1", 10, QDateTime::currentDateTime().addDays(3)}
                  });

    QVERIFY(repo->hasColumnAmount(0));
    QVERIFY(repo->hasColumnAmount(1));
    QVERIFY(!repo->hasColumnAmount(2));
    QVERIFY(repo->hasColumnAmount(3));
    QVERIFY(!repo->hasColumnAmount(100));
}




DECLARE_TEST(test_TransactionRepo)
#include "test_transactionrepo.moc"
