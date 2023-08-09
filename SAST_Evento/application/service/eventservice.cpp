#include "eventservice.h"

std::vector<UndertakingEvento> EventService::loadUndertakingEvento()
{
    return m_repository->undertakingEventoModel();
}
