#include "slide_service.h"
#include "slide_model.h"
#include "dto/slide.h"

Slide::Slide(const DTO_Slide& src) : id(src.id), title(src.title), link(src.link), url(src.url) {}
