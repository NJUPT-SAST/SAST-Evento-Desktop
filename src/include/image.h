#ifndef IMAGE_H
#define IMAGE_H

#include <QString>

#include "types.h"
#include "slide.h"

#define PICTURE_PATH(fileName) QString("qrc:/res/image/department/") + QString(fileName)

class ImageManagement {
    enum DepartmentName{
        Cpp,
        Csharp,
        Python,
        Lambda,
        Graphics,
        FrontEnd,
        BackEnd,
        Linux,
        Algorithm,
        Game,
        Safe,
        Other,
    };

    inline static QStringList pictures[] = {
        { PICTURE_PATH("cpp_1.svg"), PICTURE_PATH("cpp_2.png"), PICTURE_PATH("cpp_3.png") },
        { PICTURE_PATH("cs_1.svg"), PICTURE_PATH("cs_2.png"), PICTURE_PATH("cs_3.png") },
        { PICTURE_PATH("py_1.png"), },
        { PICTURE_PATH("lambda_1.svg"), PICTURE_PATH("lambda_2.png"), PICTURE_PATH("lambda_3.png") },
        { PICTURE_PATH("graphics.jpg"), PICTURE_PATH("graphics_2.jpg"), PICTURE_PATH("graphics_3.jpg") },
        { PICTURE_PATH("frontend_1.png"), PICTURE_PATH("frontend_2.png"), PICTURE_PATH("frontend_3.png") },
        { PICTURE_PATH("backend_1.jpg") },
        { PICTURE_PATH("linux_1.jpg"), PICTURE_PATH("linux_2.jpg"), PICTURE_PATH("linux_3.jpg") },
        { PICTURE_PATH("algorithm_1.jpg"), PICTURE_PATH("algorithm_2.jpg"), PICTURE_PATH("algorithm_3.jpg") },
        { PICTURE_PATH("game_1.svg"), PICTURE_PATH("game_2.jpg"), PICTURE_PATH("game_3.jpg") },
        { PICTURE_PATH("safe_1.jpg"), PICTURE_PATH("safe_2.jpg"), PICTURE_PATH("safe_3.jpg") },
        { PICTURE_PATH("sast_1.png"), PICTURE_PATH("sast_2.png"), PICTURE_PATH("sast_3.png") },
        { PICTURE_PATH("sast_uni1.png"), PICTURE_PATH("sast_uni2.png")},
    };

    inline static std::vector<Slide> defaultSlideList = { Slide("SAST", PICTURE_PATH("sast_1.png")),
                                                            Slide("SAST Evento", PICTURE_PATH("sast_2.png")),
                                                            Slide("软件研发部", PICTURE_PATH("sast_3.png")),
                                                          };

public:
    inline static QStringList pictureConvertor(const std::vector<Department>& departments) {
        if (departments.empty())
            return pictures[Other];
        auto name = departments[0].name;
        if (name.contains("C++")) return pictures[Cpp];
//        if (name.contains("C#")) return pictures[Csharp];
        if (name.contains("Python")) return pictures[Python];
//        if (name.contains("Lambda")) return pictures[Lambda];
//        if (name.contains("Graphics")) return pictures[Graphics];
        if (name.contains("前端")) return pictures[FrontEnd];
        if (name.contains("后端")) return pictures[BackEnd];
//        if (name.contains("运维")) return pictures[Linux];
//        if (name.contains("算法")) return pictures[Algorithm];
        if (name.contains("游戏")) return pictures[Game];
//        if (name.contains("安全")) return pictures[Safe];
        return pictures[Other];
    }

    inline static std::vector<Slide>& fillSlideList(std::vector<Slide>& list) {
        auto size = list.size();
        for (int i = 0; i < 3 - size; ++i) {
            list.push_back(defaultSlideList[i]);
        }
        return list;
    }
};

#endif // IMAGE_H
