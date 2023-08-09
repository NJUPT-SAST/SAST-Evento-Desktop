#ifndef SLIDEIMAGESERVICE_H
#define SLIDEIMAGESERVICE_H

#include "baseservice.h"

class SlideImageService : public BaseService
{
    Q_OBJECT
public:
    explicit SlideImageService(QObject *parent = nullptr, Repository* repository = QInjection::Inject)
        : BaseService(parent, repository) {}

    Image loadImage(int eventId);

    std::vector<Image> loadImageModel(int eventId);

    std::vector<Slide> loadSlideModel();
};

#endif // SLIDEIMAGESERVICE_H
