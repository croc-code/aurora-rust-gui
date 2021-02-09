#ifndef QT_WAYLAND_OUTPUT_EXTENSION
#define QT_WAYLAND_OUTPUT_EXTENSION

#include <QtWaylandClient/private/wayland-output-extension-client-protocol.h>
#include <QByteArray>
#include <QString>

QT_BEGIN_NAMESPACE

#if !defined(Q_WAYLAND_CLIENT_OUTPUT_EXTENSION_EXPORT)
#  if defined(QT_SHARED)
#    define Q_WAYLAND_CLIENT_OUTPUT_EXTENSION_EXPORT Q_DECL_EXPORT
#  else
#    define Q_WAYLAND_CLIENT_OUTPUT_EXTENSION_EXPORT
#  endif
#endif

namespace QtWayland {
    class Q_WAYLAND_CLIENT_OUTPUT_EXTENSION_EXPORT qt_output_extension
    {
    public:
        qt_output_extension(struct ::wl_registry *registry, int id, int version);
        qt_output_extension(struct ::qt_output_extension *object);
        qt_output_extension();

        virtual ~qt_output_extension();

        void init(struct ::wl_registry *registry, int id, int version);
        void init(struct ::qt_output_extension *object);

        struct ::qt_output_extension *object() { return m_qt_output_extension; }
        const struct ::qt_output_extension *object() const { return m_qt_output_extension; }

        bool isInitialized() const;

        struct ::qt_extended_output *get_extended_output(struct ::wl_output *output);

    private:
        struct ::qt_output_extension *m_qt_output_extension;
    };

    class Q_WAYLAND_CLIENT_OUTPUT_EXTENSION_EXPORT qt_extended_output
    {
    public:
        qt_extended_output(struct ::wl_registry *registry, int id, int version);
        qt_extended_output(struct ::qt_extended_output *object);
        qt_extended_output();

        virtual ~qt_extended_output();

        void init(struct ::wl_registry *registry, int id, int version);
        void init(struct ::qt_extended_output *object);

        struct ::qt_extended_output *object() { return m_qt_extended_output; }
        const struct ::qt_extended_output *object() const { return m_qt_extended_output; }

        bool isInitialized() const;

    private:
        struct ::qt_extended_output *m_qt_extended_output;
    };
}

QT_END_NAMESPACE

#endif
