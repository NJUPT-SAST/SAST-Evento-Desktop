#include "plaza.h"
#include "convertor.h"
#include "slide_model.h"
#include "undertaking_evento_model.h"
#include "latest_evento_model.h"
#include "local/repositoryimpl.h"

PlazaController::PlazaController(QObject *parent)
    : m_repository(new repositoryImpl)
{

}

void PlazaController::loadPlazaInfo()
{
    EventoException err;
    SlideModel::getInstance()->resetModel(
        Convertor<std::vector<DTO_Slide>,
                  std::vector<Slide>>()(
        m_repository->get_home_slide_list(3, err)
    ));

    if ((int)err.code()) {
        emit loadPlazaErrorEvent(err.message());
        return;
    }

    UndertakingEventoModel::getInstance()->resetModel(
        Convertor<std::vector<DTO_Evento>,
                  std::vector<UndertakingEvento>>()(
            m_repository->get_undertaking_list(err)
    ));

    if ((int)err.code()) {
        emit loadPlazaErrorEvent(err.message());
        return;
    }

    LatestEventoModel::getInstance()->resetModel(
        Convertor<std::vector<DTO_Evento>,
                  std::vector<LatestEvento>>()(
            m_repository->get_latest_list(err)
    ));

    if ((int)err.code()) {
        emit loadPlazaErrorEvent(err.message());
        return;
    }

    emit loadPlazaSuccessEvent();
}
