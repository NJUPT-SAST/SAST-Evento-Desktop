#ifndef APPLICATIONINJECTOR_H
#define APPLICATIONINJECTOR_H

#include "infrastructure/di/repository_injector.h"
#include "infrastructure/di/service_injector.h"

using namespace QInjection;

class ApplicationStarter {
   public:
    static void init(char* argv[]) {
        ServiceInjector::init();
        RepositoryInjector::init();
    }
};

#endif  // APPLICATIONINJECTOR_H
