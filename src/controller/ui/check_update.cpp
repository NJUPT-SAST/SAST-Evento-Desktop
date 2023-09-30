#include "check_update.h"
#include "repository.h"

#include <QtConcurrent>

void CheckUpdate::check() {
    auto future = getRepo()->checkUpdate().then([=](EventoResult<std::pair<QString, QString>> result) {
        if (!result) {
            emit checkErrorEvent(result.message());
            return;
        }
        auto [version, description] = result.take();
        emit checkSuccessEvent(version, description);
    });

    QtConcurrent::run([=]() {
        auto f(future);
        f.waitForFinished();
    });
}

CheckUpdate *CheckUpdate::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine) {
    return new CheckUpdate();
}
