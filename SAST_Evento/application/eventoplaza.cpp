#include "eventoplaza.h"
#include "src/controller/slidesmodel.h"

EventoPlaza::EventoPlaza()
    : m_slidesModel(SlidesModel::getInstance())
{}

EventoPlaza* EventoPlaza::getInstance()
{
    static EventoPlaza instance;
    return &instance;
}

void EventoPlaza::onClickEvento(EventoID id)
{

}

void EventoPlaza::onClickSlide(QString id)
{

}
