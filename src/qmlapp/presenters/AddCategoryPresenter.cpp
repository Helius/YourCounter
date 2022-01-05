#include "AddCategoryPresenter.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>

AddCategoryPresenter::AddCategoryPresenter(AddNewCategoryUseCaseUnq usecase)
    : m_usecase(std::move(usecase))
{
    Q_ASSERT(m_usecase);

    connect(m_usecase.get(), &AddNewCategoryUseCase::categoryInvalid,
        this, [](AddNewCategoryUseCase::InvalidReason r) {
            switch (r) {
            case AddNewCategoryUseCase::InvalidReason::EmptyName:
                qDebug() << "Name is empty";
                break;
            case AddNewCategoryUseCase::InvalidReason::NameAlreadyExist:
                qDebug() << "Name already exist";
                break;
            case AddNewCategoryUseCase::InvalidReason::GroupNotFound:
                qDebug() << "Group not found";
                break;
            }
        });

    connect(m_usecase.get(), &AddNewCategoryUseCase::categoryAdded,
        this, &AddCategoryPresenter::closePopup);
}

void AddCategoryPresenter::add()
{
    auto c = Category::createRequest(m_name, m_groupId);
    m_usecase->addCategory(c);
}
