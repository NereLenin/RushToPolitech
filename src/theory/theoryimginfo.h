#ifndef THEORYIMGINFO_H
#define THEORYIMGINFO_H
#include <QString>
#include <QDebug>

class TheoryImgInfo
{
private:
    public:
    QString imageUrl;

    int positionInText;

    TheoryImgInfo();
    TheoryImgInfo(QString tag, int position);

    QString getImageUrl();

    int getPositionInText();
};

#endif // THEORYIMGINFO_H
