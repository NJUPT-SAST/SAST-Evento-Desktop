#ifndef APPLICATIONINJECTOR_H
#define APPLICATIONINJECTOR_H

#include "infrastructure/di/RepositoryInjector.h"
#include "infrastructure/di/ServiceInjector.h"

using namespace QInjection;

class ApplicationStarter {
   public:
    static void init(char* argv[]) {
        ServiceInjector::init();
        RepositoryInjector::init();
    }
};

#endif  // APPLICATIONINJECTOR_H
