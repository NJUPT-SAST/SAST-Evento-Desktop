#include "repository.h"
#include "network/repositoryImpl.h"
#include "local/repositoryimpl.h"

Repository* getRepo() {
    return NetworkRepository::getInstance();
}
