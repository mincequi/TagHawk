#ifndef TAGARTISTSMODEL_H
#define TAGARTISTSMODEL_H

#include <QAbstractItemModel>
#include <QMap>


namespace editor {

class TagArtistsModel : public QAbstractItemModel
{
public:
    TagArtistsModel();

private:
    struct Data {
        QMap<int, QString>  tags;
        int                 currentIndex = -1;
        bool                isUserChecked = false;
    };

    QMap<QString, Data>     m_data;
};

} // namespace editor

#endif // TAGARTISTSMODEL_H
