#include "repository.h"
#include "network/EventoNetworkClient.h"

Repository* getRepo() {
    return EventoNetworkClient::getInstance();
}
