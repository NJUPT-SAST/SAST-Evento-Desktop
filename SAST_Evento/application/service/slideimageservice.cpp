#include "slideimageservice.h"

Image SlideImageService::loadImage(int eventId)
{
    return m_repository->image(eventId);
}

std::vector<Image> SlideImageService::loadImageModel(int eventId)
{
    return m_repository->imageModel(eventId);
}

std::vector<Slide> SlideImageService::loadSlideModel()
{
    return m_repository->slideModel();
}
