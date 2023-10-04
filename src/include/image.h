#ifndef IMAGE_H
#define IMAGE_H

#include <QString>

#include "slide.h"
#include "types.h"

#define PICTURE_PATH__(fileName) QStringLiteral(fileName)
#define PICTURE_PATH_(fileName) PICTURE_PATH__(#fileName)
#define PICTURE_PATH(fileName) PICTURE_PATH_(qrc:/res/image/department/fileName)

class ImageManagement {
    enum DepartmentName {
        Cpp,
        Csharp,
        Python,
        Lambda,
        Graphics,
        FrontEnd,
        BackEnd,
        Linux,
        Algorithms,
        Game,
        Safe,
        Others,
        Uni,
    };

    inline static const QStringList pictures[] = {
        {PICTURE_PATH(cpp_1.svg), PICTURE_PATH(cpp_2.png), PICTURE_PATH(cpp_3.png)},
        {PICTURE_PATH(cs_1.png)},
        {PICTURE_PATH(py_1.png)},
        {PICTURE_PATH(lambda_1.png), PICTURE_PATH(lambda_2.png)},
        {}, // Graphics
        {PICTURE_PATH(frontend_1.png), PICTURE_PATH(frontend_2.png), PICTURE_PATH(frontend_3.png)},
        {PICTURE_PATH(backend_1.png)},
        {}, // Linux
        {}, // Algorithms
        {PICTURE_PATH(game_1.svg), PICTURE_PATH(game_2.jpg), PICTURE_PATH(game_3.jpg)},
        {}, // Safe
        {PICTURE_PATH(sast_1.png), PICTURE_PATH(sast_2.png), PICTURE_PATH(sast_3.png)},
        {PICTURE_PATH(sast_uni1.png), PICTURE_PATH(sast_uni2.png)},
    };

    inline static const std::vector<Slide> defaultSlideList = {
        Slide("SAST", PICTURE_PATH(sast_1.png)),
        Slide("SAST Evento", PICTURE_PATH(sast_2.png)),
        Slide("软件研发部", PICTURE_PATH(sast_3.png)),
    };

public:
    inline static QStringList getDepartmentAddress(QString name) {
        QStringList result;
        if (name.contains("C++"))
            result = pictures[Cpp];
        if (name.contains("C#"))
            result = pictures[Csharp];
        if (name.contains("Python"))
            result = pictures[Python];
        if (name.contains("Lambda"))
            result = pictures[Lambda];
        if (name.contains("Graphics"))
            result = pictures[Graphics];
        if (name.contains("前端"))
            result = pictures[FrontEnd];
        if (name.contains("后端"))
            result = pictures[BackEnd];
        if (name.contains("运维"))
            result = pictures[Linux];
        if (name.contains("算法"))
            result = pictures[Algorithms];
        if (name.contains("游戏"))
            result = pictures[Game];
        if (name.contains("安全"))
            result = pictures[Safe];
        if (!result.empty())
            return result;
        return pictures[Others];
    }

    inline static QStringList pictureConvertor(const std::vector<Department>& departments) {
        int size = departments.size();
        if (!size)
            return pictures[Others];
        if (size == 1) {
            auto name = departments[0].name;
            return getDepartmentAddress(name);
        }

        QStringList addresses;
        auto name1 = departments[0].name;
        auto name2 = departments[1].name;
        if (name1.contains("院"))
            std::swap(name1, name2);

        if (name2.contains("院")) {
            addresses.append(pictures[Uni][1]);
            if (name2.contains(name1)) {
                addresses.append(getDepartmentAddress(name1));
                addresses.pop_back();
            } else {
                addresses.append(getDepartmentAddress(name1).at(0));
                addresses.append(getDepartmentAddress(name2).at(0));
            }
            return addresses;
        }

        addresses.append(pictures[Uni][0]);
        addresses.append(getDepartmentAddress(name1).at(0));
        addresses.append(getDepartmentAddress(name2).at(0));
        return addresses;
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
