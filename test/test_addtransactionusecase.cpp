#include <QtTest>
#include "../src/domain/usecases/addnewtransactionusecase.h"
#include <src/domain/repos/itransactionrepo.h>
#include "AutoTest.h"

class MockTransactionRepo
    : public ITransactionRepo
{
public:
    bool hasColumnAmount(int ) override { return true; }
    float columnAmountOverAll(int ) override { return 0.0; }
    float calcAmount(int , int ) override { return 0.0; }
    const std::vector<QString> &getCategories() override {
        static Categories t {
            {"cat1"},
            {"cat2"},
        };
        return t;
    };

    void addTransaction(Transaction t) override {
        transactionUnq = std::make_unique<Transaction>(std::move(t));

    };
    float max() override { return 0; }
    float min() override { return 0; }
    std::unique_ptr<Transaction> transactionUnq;
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
private:
    std::shared_ptr<MockTransactionRepo> repo;
};



void test_AddTransactionUseCase::test_check_amount()
{
    AddNewTransactionUseCaseUnq usecase = std::make_unique<AddNewTransactionUseCase>(repo);
    Transaction t ("Category", 0, QDateTime::currentDateTime(), QString());

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


    Transaction t1 ("cat1", 1, QDateTime::currentDateTime(), QString());

    usecase->addTransaction(t1);

    QCOMPARE(spyAdded.count(), 1);
    QCOMPARE(spyInvalid.count(), 0);
    QCOMPARE(spyAsk.count(), 0);
    QVERIFY(repo->transactionUnq);
    QCOMPARE(*(repo->transactionUnq), t1);

    spyInvalid.clear();
    spyAdded.clear();
    spyAsk.clear();


    Transaction t2 ("new cat", -1, QDateTime::currentDateTime(), QString());
    connect(usecase.get(), &AddNewTransactionUseCase::isItNewCategory, this, [](){
        return false;
        }, Qt::ConnectionType::UniqueConnection);
    usecase->addTransaction(t2);

    QCOMPARE(spyAdded.count(), 0);
    QCOMPARE(spyInvalid.count(), 0);
    QCOMPARE(spyAsk.count(), 1);
    QVERIFY(repo->transactionUnq);
    QCOMPARE(*(repo->transactionUnq), t1);

    spyInvalid.clear();
    spyAdded.clear();
    spyAsk.clear();

    connect(usecase.get(), &AddNewTransactionUseCase::isItNewCategory, this, [](){
        return true;
        }, Qt::ConnectionType::UniqueConnection);
    usecase->addTransaction(t2);

    QCOMPARE(spyAdded.count(), 1);
    QCOMPARE(spyInvalid.count(), 0);
    QCOMPARE(spyAsk.count(), 1);
    QVERIFY(repo->transactionUnq);
    QCOMPARE(*(repo->transactionUnq), t2);
}

DECLARE_TEST(test_AddTransactionUseCase)
#include "test_addtransactionusecase.moc"
