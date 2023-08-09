#include "eventservice.h"

Evento EventService::loadEvento(int eventId)
{
    return m_repository->evento(eventId);
}

std::vector<UndertakingEvento> EventService::loadUndertakingEvento()
{
    return m_repository->undertakingEventoModel();
}
