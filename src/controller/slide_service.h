#ifndef SLIDESERVICE_H
#define SLIDESERVICE_H
#include "slide.h"
#include <shared_mutex>
#include <vector>
class SlideService {
std::shared_mutex mutex;
std::vector<Slide> slides;
private:
SlideService() = default;
public:
static SlideService& getInstance() {static SlideService singleton;return singleton;}
void load_HomeSlide(   const   int   size);
};
#endif // SLIDESERVICE_H
