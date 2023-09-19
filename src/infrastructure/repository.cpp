#include "repository.h"
#include "network/repositoryImpl.h"

Repository* getRepo() {
    return NetworkRepository::getInstance();
}
