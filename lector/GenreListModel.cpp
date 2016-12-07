#include "GenreListModel.h"


GenreListModel::GenreListModel(QObject *parent)
    : QStringListModel(parent)
{
}

GenreListModel::~GenreListModel()
{
}

void GenreListModel::add(const QString& genre)
{
    if (genre.isEmpty() || stringList().contains(genre)) {
        return;
    }

    int row = rowCount();
    insertRow(row);
    setData(index(row), genre);

    emit changed();
}

void GenreListModel::remove(const QString& genre)
{
    int index = stringList().indexOf(genre);
    if (index == -1) {
        return;
    }

    removeRow(index);

    emit changed();
}
