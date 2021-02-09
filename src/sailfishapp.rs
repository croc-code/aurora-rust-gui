use crate::qstring::QString;

cpp! {{
    #include <sailfishapp.h>
    #include <QtCore/QDebug>
    #include <QtGui/QGuiApplication>
    #include <QtQuick/QQuickView>
    #include <QtQml/QQmlEngine>
    #include <memory>

    struct SailfishAppHolder {
        std::unique_ptr<QGuiApplication> app;
        std::unique_ptr<QQuickView> view;

        SailfishAppHolder() {
            qDebug() << "SailfishAppHolder::SailfishAppHolder()";
            int argc = 1;
            char *argv[] = { "aurora-rust-gui" };
            app.reset(SailfishApp::application(argc, argv));
            view.reset(SailfishApp::createView());
            view->engine()->addImportPath("/usr/share/aurora-rust-gui/qml");
        }
    };
}}

cpp_class!(
    pub unsafe struct SailfishApp as "SailfishAppHolder"
);

impl SailfishApp {
    /// Creates a new SailfishApp.
    pub fn new() -> Self {
        cpp!(unsafe [] -> SailfishApp as "SailfishAppHolder" {
            qDebug() << "SailfishApp::new()";
            return SailfishAppHolder();
        })
    }

    /// Sets the main QML (see QQuickView::setSource for details).
    pub fn set_source(&mut self, url: QString) {
        cpp!(unsafe [self as "SailfishAppHolder *", url as "QString"] {
            const auto full_url = QString("/usr/share/aurora-rust-gui/qml/%1").arg(url);
            qDebug() << "SailfishApp::set_source()" << full_url;
            self->view->setSource(full_url);
        });
    }

    /// Shows the main view.
    pub fn show(&self) {
        cpp!(unsafe [self as "SailfishAppHolder *"] {
            qDebug() << "SailfishApp::show()";
            self->view->showFullScreen();
        })
    }

    /// Launches the application.
    pub fn exec(&self) {
        cpp!(unsafe [self as "SailfishAppHolder *"] {
            qDebug() << "SailfishApp::exec()";
            self->app->exec();
        })
    }
}
