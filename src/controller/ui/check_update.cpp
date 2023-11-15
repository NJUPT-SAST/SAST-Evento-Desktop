#include "check_update.h"
#include "repository.h"

void CheckUpdate::check() {
    getRepo()->checkUpdate().then([this](EventoResult<std::pair<QString, QString>> result) {
            if (!result) {
                emit checkErrorEvent(result.message());
                return;
            }
            auto [version, description] = result.take();
            emit checkSuccessEvent(version, description);
        });
}

CheckUpdate* CheckUpdate::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine) {
    return new CheckUpdate();
}
