#ifndef SOURCETREEVIEW_H
#define SOURCETREEVIEW_H

//#include "Typedefs.h"
//#include "SourcePlaylistInterface.h"

#include <QTreeView>
#include <QMenu>

class SourceTreePopupDialog;
class CollectionModel;
class PlaylistModel;
class SourcesModel;
class SourcesProxyModel;
class SourceDelegate;

namespace Tomahawk
{
    class LatchManager;
}

class SourceTreeView : public QTreeView
{
Q_OBJECT

public:
    explicit SourceTreeView( QWidget* parent = 0 );
    ~SourceTreeView();

public slots:
    void showOfflineSources( bool offlineSourcesShown );

    void renamePlaylist( const Tomahawk::playlist_ptr& playlist );
    void renamePlaylist();

    void update( const QModelIndex &index );

signals:
    void onOnline( const QModelIndex& index );
    void onOffline( const QModelIndex& index );

    void latchRequest( const Tomahawk::source_ptr& source );
    void unlatchRequest( const Tomahawk::source_ptr& source );
    void catchUpRequest();
    void latchModeChangeRequest( const Tomahawk::source_ptr& source, bool realtime );

private slots:
    void onItemExpanded( const QModelIndex& idx );
    void onItemActivated( const QModelIndex& index );
    void selectRequest( const QPersistentModelIndex& idx );
    void expandRequest( const QPersistentModelIndex& idx );
    void toggleExpandRequest( const QPersistentModelIndex& idx );
    void onItemDoubleClicked( const QModelIndex& idx );

    void loadPlaylist();
    void deletePlaylist( const QModelIndex& = QModelIndex() );
    void copyPlaylistLink();
    void exportPlaylist();
    void addToLocal();

    void latchOnOrCatchUp();
    void latchOff();
    void latchOnOrCatchUp( const Tomahawk::source_ptr& source );
    void latchOff( const Tomahawk::source_ptr& source );
    void latchModeToggled( bool checked );

    void onCustomContextMenu( const QPoint& pos );
    void onSelectionChanged();

    void onDeletePlaylistResult( bool result );

    void shortLinkReady( const Tomahawk::playlist_ptr& playlist, const QUrl& shortUrl );

protected:
    void drawRow( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const;
    void drawBranches( QPainter *painter, const QRect &rect, const QModelIndex &index ) const;

    virtual void paintEvent( QPaintEvent* event );

    virtual void dragEnterEvent( QDragEnterEvent* event );
    virtual void dragLeaveEvent( QDragLeaveEvent* event );
    virtual void dragMoveEvent( QDragMoveEvent* event );
    virtual void dropEvent( QDropEvent* event );
    virtual void keyPressEvent( QKeyEvent* event );

private:
    void setupMenus();

    template< typename T >
    T* itemFromIndex( const QModelIndex& index ) const;

    SourcesModel* m_model;
    SourcesProxyModel* m_proxyModel;
    QModelIndex m_contextMenuIndex;
    SourceDelegate* m_delegate;
    Tomahawk::LatchManager* m_latchManager;
    QPointer<SourceTreePopupDialog> m_popupDialog;

    QMenu m_playlistMenu;
    QMenu m_roPlaylistMenu;
    QMenu m_latchMenu;
    QMenu m_privacyMenu;

    bool m_dragging;
    QRect m_dropRect;
    QPersistentModelIndex m_dropIndex;

    QPersistentModelIndex m_selectedIndex;
};

#endif // SOURCETREEVIEW_H
