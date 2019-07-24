#ifndef PATHOLOGYWORKSTATION_H
#define PATHOLOGYWORKSTATION_H

#include "asaplib_export.h"
#include <QMainWindow>
#include <QDir>
#include <QStringList>
#include <memory>
#include <unordered_map>

#include "PathologyViewController.h"
#include "documents/DocumentCache.h"
#include "documents/DocumentWindow.h"
#include "documents/DocumentWindowController.h"

class QHBoxLayout;
class QAction;
class QStatusBar;
class QMenuBar;
class WorkstationExtensionPluginInterface;
class QActionGroup;
class QSettings;

/*

OWNERSHIP

Workstation is the owner of all the PathologyViews
Workstation is the owner of all Plugins, also the ToolPlugins generated by ExtensionPlugins
Workstation is the owner of the MultiResolutionImage
Viewer is the owner of RenderThread, TileManager, ScaleBar, MiniMap, RenderWorkers and the Scene

*/

class ASAPLIB_EXPORT ASAP_Window : public QMainWindow
{
  Q_OBJECT

public:
  explicit ASAP_Window(QWidget* parent = 0);
  ~ASAP_Window(void);

  void setCacheSize(const unsigned long long& cacheMaxByteSize);

  unsigned long long getCacheSize(void) const;

  void openFile(const QString& fileName, const QString& factoryName = QString("default"));

  ASAP::DocumentWindow* openViewer(const QString name, QWidget* parent = 0);

signals:
  void newImageLoaded(std::weak_ptr<MultiResolutionImage>, const std::string&);
  void imageClosed(void);

private slots:
  void onViewerFocusChanged(ASAP::DocumentWindow* window);

  void on_actionClose_triggered();
  void on_actionOpen_triggered();
  void on_actionAbout_triggered();
  void onDocumentClose(const size_t document_id);

private:
  static const char* sharedLibraryExtensions;
  unsigned long long _cacheMaxByteSize;
  QSettings* _settings;

  void closeEvent(QCloseEvent *event);
  
  // Documents
  ASAP::DocumentCache				m_documents_;
  ASAP::DocumentWindowController	m_document_window_controller_;
  ASAP::PathologyViewController		m_view_controller_;

  // Plugins
  QDir _pluginsDir;
  std::vector<std::string> _extensionPluginFileNames;
  std::vector<std::string> _toolPluginFileNames;
  std::vector<std::unique_ptr<WorkstationExtensionPluginInterface>> _extensions;


  // GUI object
  QAction *actionOpen;
  QAction *actionClose;
  QAction *actionAbout;
  QActionGroup *_toolActions;
  QWidget *centralWidget;
  QHBoxLayout *horizontalLayout_2;
 // PathologyViewer *pathologyView;
  QMenuBar *menuBar;
  QMenu *menuFile;
  QMenu *menuView;
  QMenu *menuHelp;
  QToolBar *mainToolBar;
  QStatusBar *statusBar;
  ASAP::DocumentWindow* m_document_window_;
  ASAP::DocumentWindow* window2;

  // Initialize the GUI
  void initializeDocks(void);
  void setupUi(void);
  void retranslateUi(void);
  void loadPlugins(void);
  void readSettings(void);
  void writeSettings(void);
};

#endif // PATHOLOGYWORKSTATION_H
