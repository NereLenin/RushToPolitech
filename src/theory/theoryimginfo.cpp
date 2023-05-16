#include "theoryimginfo.h"

TheoryImgInfo::TheoryImgInfo(){
    positionInText = 0;
}

TheoryImgInfo::TheoryImgInfo(QString tag, int position){
    if(!tag.contains("<img src = \"") || !tag.contains("\">"))
    {
        qDebug()  << "try to parse not correct tag" << tag;
        return;
    }

    imageUrl = tag.remove("<img src = \"").remove("\">");
    positionInText = position;
}

const QString &TheoryImgInfo::getImageUrl() const{
    return imageUrl;
}

int TheoryImgInfo::getPositionInText() const{
    return positionInText;
}

