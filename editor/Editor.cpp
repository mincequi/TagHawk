#include "Editor.h"

#include <functional>

#include <QDebug>
#include <QHeaderView>
#include <QMenu>
#include <QStandardItemModel>
#include <QTreeView>

#include "EditorDefines.h"
#include "EditorUtil.h"
#include "CategorizeArtistsModel.h"
#include "CorrectArtistsModel.h"
#include "config/Config.h"


namespace editor {

Editor::Editor(QObject *parent)
    : QObject(parent),
      m_correctArtistsModel(new CorrectArtistsModel(this)),
      m_categorizeArtistsModel(new CategorizeArtistsModel(this)),
      m_genreView(nullptr),
      m_ambiguousTagsView(nullptr)
{
}

CorrectArtistsModel* Editor::correctArtistsModel()
{
    return m_correctArtistsModel;
}

CategorizeArtistsModel* Editor::categorizeArtistsModel()
{
    return m_categorizeArtistsModel;
}

void Editor::clear()
{
}

void Editor::correctAlbum(const QString& artist, const QString& misspelledAlbum, const QString& correctedAlbum)
{
}

void Editor::setYear(const QString& artist, const QString& album, const QString& year)
{
}

} // namespace editor
