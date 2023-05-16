#ifndef THEORYIMGINFO_H
#define THEORYIMGINFO_H
#include <QString>
#include <QDebug>

class TheoryImgInfo
{
private:
    QString imageUrl;
    int positionInText;
public:
    TheoryImgInfo();
    TheoryImgInfo(QString tag, int position);

    const QString& getImageUrl() const;
    int getPositionInText() const;
};

#endif // THEORYIMGINFO_H
