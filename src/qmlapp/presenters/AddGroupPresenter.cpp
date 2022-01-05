#include "AddGroupPresenter.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>

AddGroupPresenter::AddGroupPresenter(AddNewGroupUseCaseUnq usecase)
    : m_usecase(std::move(usecase))
{
    Q_ASSERT(m_usecase);

    connect(m_usecase.get(), &AddNewGroupUseCase::groupInvalid,
        this, [](AddNewGroupUseCase::InvalidReason r) {
            switch (r) {
            case AddNewGroupUseCase::InvalidReason::EmptyName:
                qDebug() << "Name is empty";
                break;

            case AddNewGroupUseCase::InvalidReason::NameAlreadyExist:
                qDebug() << "Name already exist";
                break;
            }
        });

    connect(m_usecase.get(), &AddNewGroupUseCase::groupAdded,
        this, &AddGroupPresenter::closePopup);
}

void AddGroupPresenter::add()
{
    Group g = Group::createRequest(m_name);
    m_usecase->addGroup(g);
}
