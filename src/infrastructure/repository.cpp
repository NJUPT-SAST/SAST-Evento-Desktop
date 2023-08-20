#include "repository.h"
#include "local/repositoryimpl.h"

Repository* getRepo() {
    return repositoryImpl::getInstance();
}
