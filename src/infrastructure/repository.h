#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "network/EventoNetworkClient.h"

inline auto getRepo() {
    return EventoNetworkClient::getInstance();
}

#endif // REPOSITORY_H
