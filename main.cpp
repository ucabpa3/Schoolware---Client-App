#include <QApplication>
#include <QWebSettings>
#include <QWebView>
#include <QGraphicsWebView>
#include <QWebPage>
#include <jsbridgeobj.h>
#include <QDebug>
#include "html5applicationviewer.h"

void SetupGlobalWebSettings(){
    QWebSettings* settings = QWebSettings::globalSettings();
    //    QWebSettings* settings = webView->page()->settings();

        settings->setAttribute(QWebSettings::AutoLoadImages,                    true);  // default : true
        settings->setAttribute(QWebSettings::AutoLoadImages,                    true);  // default : true
        settings->setAttribute(QWebSettings::DnsPrefetchEnabled,                    true);  // default : false

        settings->setAttribute(QWebSettings::PluginsEnabled,                    true);  // default : false
        settings->setAttribute(QWebSettings::PluginsEnabled,                    true);  // default : false
        settings->setAttribute(QWebSettings::PrivateBrowsingEnabled,                false);  // default : false

        settings->setAttribute(QWebSettings::JavascriptEnabled,                 true);  // default : true
        settings->setAttribute(QWebSettings::JavascriptCanOpenWindows,              false);  // default : false
        settings->setAttribute(QWebSettings::JavascriptCanAccessClipboard,          false);  // default : false
        settings->setAttribute(QWebSettings::JavaEnabled,                           false);  // default : false, currently Java applets are not supported.

        settings->setAttribute(QWebSettings::DeveloperExtrasEnabled,                false);  // default : false

        settings->setAttribute(QWebSettings::SpatialNavigationEnabled,              true);  // default : false
        settings->setAttribute(QWebSettings::LinksIncludedInFocusChain,         true);  // default : true
        settings->setAttribute(QWebSettings::ZoomTextOnly,                          false);  // default : false
        settings->setAttribute(QWebSettings::PrintElementBackgrounds,           true);  // default : true

        settings->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled,         false);  // default : false
        settings->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled,         false);  // default : false
        settings->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled,     false);  // default : false

        settings->setAttribute(QWebSettings::LocalStorageEnabled,                   false);  // default : false
    //    settings->setAttribute(QWebSettings::LocalStorageDatabaseEnabled,           false);  // default : false, deprecated, use LocalStrageEnabled instead.
        settings->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls,       true);  // default : false
        settings->setAttribute(QWebSettings::LocalContentCanAccessFileUrls,     true);  // default : true

        settings->setAttribute(QWebSettings::XSSAuditingEnabled,                    false);  // default : false
        settings->setAttribute(QWebSettings::AcceleratedCompositingEnabled,     true);  // default : true
        settings->setAttribute(QWebSettings::TiledBackingStoreEnabled,              false);  // default : false
        settings->setAttribute(QWebSettings::FrameFlatteningEnabled,                false);  // default : false
        settings->setAttribute(QWebSettings::SiteSpecificQuirksEnabled,         true);  // default : true

        //settings->setLocalStoragePath(QString("/Users/costas/Documents"));
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Html5ApplicationViewer viewer;
    SetupGlobalWebSettings();
    viewer.setOrientation(Html5ApplicationViewer::ScreenOrientationAuto);
    viewer.showMaximized();
    viewer.loadFile(QLatin1String("SchoolWareWebSite/index.html"));

    QWebPage *page = viewer.webView()->page();
    QWebFrame *frame = page->mainFrame();

    JSBridgeObj *s = new JSBridgeObj();
    s->setFrame(frame);
    frame->addToJavaScriptWindowObject(QString("linker"), s);

    return app.exec();
}
