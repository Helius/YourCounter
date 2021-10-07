#include <QtTest>
#include <usecases/addnewtransactionusecase.h>
#include <repos/itransactionrepo.h>
#include "AutoTest.h"

class MockTransactionRepo
    : public ITransactionRepo
{
public:
    bool hasColumnAmount(int ) override { return true; }
    float columnAmountOverAll(int ) override { return 0.0; }
    float calcAmount(int , int ) override { return 0.0; }
    const Categories &getCategories() override {
        static Categories t {
            {"cat1"},
            {"cat2"},
        };
        return t;
    };

    void addTransaction(Transaction t) override {
        m_transactions.push_back(t);
    };
    float max() override { return 0; }
    float min() override { return 0; }
    const Transactions & getTransactions() override { return m_transactions; }
    Transactions m_transactions;
private:
};

class test_AddTransactionUseCase : public QObject
{
    Q_OBJECT

public:
    test_AddTransactionUseCase() {
        repo = std::make_shared<MockTransactionRepo>();
    };
    ~test_AddTransactionUseCase() {};

private slots:
    void test_check_amount();
    void test_empty_category();
    void test_new_category();
private:
    std::shared_ptr<MockTransactionRepo> repo;
};


void test_AddTransactionUseCase::test_check_amount()
{
    AddNewTransactionUseCaseUnq usecase = std::make_unique<AddNewTransactionUseCase>(repo);
    Transaction t ("cat1", 0, QDateTime::currentDateTime(), QString());

    QSignalSpy spyInvalid(usecase.get(), &AddNewTransactionUseCase::transactionInvalid);
    QSignalSpy spyAdded(usecase.get(), &AddNewTransactionUseCase::transactionAdded);
    QSignalSpy spyAsk(usecase.get(), &AddNewTransactionUseCase::isItNewCategory);

    usecase->addTransaction(t);

    QCOMPARE(spyInvalid.count(), 1);
    QList<QVariant> arguments = spyInvalid.takeFirst();
    QVERIFY(arguments.at(0).toInt() == static_cast<int>(AddNewTransactionUseCase::InvalidReason::BadAmount));
    QCOMPARE(spyAdded.count(), 0);
    QCOMPARE(spyAsk.count(), 0);

    spyInvalid.clear();
    spyAdded.clear();
    spyAsk.clear();
    repo->m_transactions.clear();

    Transaction t1 ("cat1", 1, QDateTime::currentDateTime(), QString());

    usecase->addTransaction(t1);

    QCOMPARE(spyAdded.count(), 1);
    QCOMPARE(spyInvalid.count(), 0);
    QCOMPARE(spyAsk.count(), 0);
    QVERIFY(repo->getTransactions().size());
    QCOMPARE(repo->getTransactions().front(), t1);

    spyInvalid.clear();
    spyAdded.clear();
    spyAsk.clear();
    repo->m_transactions.clear();
}

void test_AddTransactionUseCase::test_empty_category()
{

    AddNewTransactionUseCaseUnq usecase = std::make_unique<AddNewTransactionUseCase>(repo);
    Transaction t ("", 1, QDateTime::currentDateTime(), QString());

    QSignalSpy spyInvalid(usecase.get(), &AddNewTransactionUseCase::transactionInvalid);
    QSignalSpy spyAdded(usecase.get(), &AddNewTransactionUseCase::transactionAdded);
    QSignalSpy spyAsk(usecase.get(), &AddNewTransactionUseCase::isItNewCategory);

    repo->m_transactions.clear();
    usecase->addTransaction(t);

    QCOMPARE(spyAdded.count(), 0);
    QCOMPARE(spyInvalid.count(), 1);
    QList<QVariant> arguments = spyInvalid.takeFirst();
    QVERIFY(arguments.at(0).toInt() == static_cast<int>(AddNewTransactionUseCase::InvalidReason::EmptyCategory));
    QCOMPARE(spyAsk.count(), 0);
    QVERIFY(repo->getTransactions().empty());

    spyInvalid.clear();
    spyAdded.clear();
    spyAsk.clear();
    repo->m_transactions.clear();

    t.category = "cat1";

    usecase->addTransaction(t);

    QCOMPARE(spyAdded.count(), 1);
    QCOMPARE(spyInvalid.count(), 0);
    QCOMPARE(spyAsk.count(), 0);
    QVERIFY(!repo->getTransactions().empty());
    QCOMPARE(repo->getTransactions().front(), t);

    spyInvalid.clear();
    spyAdded.clear();
    spyAsk.clear();
    repo->m_transactions.clear();
}

void test_AddTransactionUseCase::test_new_category()
{

    AddNewTransactionUseCaseUnq usecase = std::make_unique<AddNewTransactionUseCase>(repo);
    Transaction t ("new cat", 1, QDateTime::currentDateTime(), QString());

    QSignalSpy spyInvalid(usecase.get(), &AddNewTransactionUseCase::transactionInvalid);
    QSignalSpy spyAdded(usecase.get(), &AddNewTransactionUseCase::transactionAdded);
    QSignalSpy spyAsk(usecase.get(), &AddNewTransactionUseCase::isItNewCategory);

    usecase->addTransaction(t);

    QCOMPARE(spyAdded.count(), 0);
    QCOMPARE(spyInvalid.count(), 0);
    QCOMPARE(spyAsk.count(), 1);

    spyInvalid.clear();
    spyAdded.clear();
    spyAsk.clear();
    repo->m_transactions.clear();

    usecase->addTransaction(t, true);

    QCOMPARE(spyAdded.count(), 1);
    QCOMPARE(spyInvalid.count(), 0);
    QCOMPARE(spyAsk.count(), 0);
    QVERIFY(!repo->getTransactions().empty());
    QCOMPARE(repo->getTransactions().front(), t);
}

DECLARE_TEST(test_AddTransactionUseCase)
#include "test_addtransactionusecase.moc"
