#include "slide_model.h"

int SlideModel::rowCount(const QModelIndex& parent) const {
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.size();
}

QVariant SlideModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    const auto& element = m_data.at(index.row());

    switch (role) {
    case Role::Id:
        return element.id;
    case Role::Title:
        return element.title;
    case Role::Link:
        return element.link;
    case Role::Url:
        return element.url;
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> SlideModel::roleNames() const {
    static QHash<int, QByteArray> roles;

    if (roles.isEmpty()) {
        roles.insert(Id, "id");
        roles.insert(Title, "title");
        roles.insert(Link, "link");
        roles.insert(Url, "url");
    }
    return roles;
}

void SlideModel::resetModel(std::vector<Slide>&& model) {
    beginResetModel();
    m_data = std::move(model);
    endResetModel();
}

void SlideModel::resetModel(const QStringList& slideList) {
    std::vector<Slide> model;
    for (const auto& slide : slideList) {
        model.emplace_back("", slide);
    }
    beginResetModel();
    m_data = std::move(model);
    endResetModel();

}

void SlideModel::removeById(const int id) {
    beginResetModel();
    m_data.erase(
        std::remove_if(m_data.begin(), m_data.end(), [id](const auto& e) { return e.id == id; }),
        m_data.end());
    endResetModel();
}

SlideModel* SlideModel::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine) {
    auto pInstance = getInstance();
    QJSEngine::setObjectOwnership(pInstance, QQmlEngine::CppOwnership);
    return pInstance;
}

SlideModel* SlideModel::getInstance() {
    static SlideModel singleton;
    return &singleton;
}
