#ifndef QT_WAYLAND_SUB_SURFACE_EXTENSION
#define QT_WAYLAND_SUB_SURFACE_EXTENSION

#include <QtWaylandClient/private/wayland-sub-surface-extension-client-protocol.h>
#include <QByteArray>
#include <QString>

QT_BEGIN_NAMESPACE

#if !defined(Q_WAYLAND_CLIENT_SUB_SURFACE_EXTENSION_EXPORT)
#  if defined(QT_SHARED)
#    define Q_WAYLAND_CLIENT_SUB_SURFACE_EXTENSION_EXPORT Q_DECL_EXPORT
#  else
#    define Q_WAYLAND_CLIENT_SUB_SURFACE_EXTENSION_EXPORT
#  endif
#endif

namespace QtWayland {
    class Q_WAYLAND_CLIENT_SUB_SURFACE_EXTENSION_EXPORT qt_sub_surface_extension
    {
    public:
        qt_sub_surface_extension(struct ::wl_registry *registry, int id, int version);
        qt_sub_surface_extension(struct ::qt_sub_surface_extension *object);
        qt_sub_surface_extension();

        virtual ~qt_sub_surface_extension();

        void init(struct ::wl_registry *registry, int id, int version);
        void init(struct ::qt_sub_surface_extension *object);

        struct ::qt_sub_surface_extension *object() { return m_qt_sub_surface_extension; }
        const struct ::qt_sub_surface_extension *object() const { return m_qt_sub_surface_extension; }

        bool isInitialized() const;

        struct ::qt_sub_surface *get_sub_surface_aware_surface(struct ::wl_surface *surface);

    private:
        struct ::qt_sub_surface_extension *m_qt_sub_surface_extension;
    };

    class Q_WAYLAND_CLIENT_SUB_SURFACE_EXTENSION_EXPORT qt_sub_surface
    {
    public:
        qt_sub_surface(struct ::wl_registry *registry, int id, int version);
        qt_sub_surface(struct ::qt_sub_surface *object);
        qt_sub_surface();

        virtual ~qt_sub_surface();

        void init(struct ::wl_registry *registry, int id, int version);
        void init(struct ::qt_sub_surface *object);

        struct ::qt_sub_surface *object() { return m_qt_sub_surface; }
        const struct ::qt_sub_surface *object() const { return m_qt_sub_surface; }

        bool isInitialized() const;

        void attach_sub_surface(struct ::qt_sub_surface *sub_surface, int32_t x, int32_t y);
        void move_sub_surface(struct ::qt_sub_surface *sub_surface, int32_t x, int32_t y);
        void raise(struct ::qt_sub_surface *sub_surface);
        void lower(struct ::qt_sub_surface *sub_surface);

    private:
        struct ::qt_sub_surface *m_qt_sub_surface;
    };
}

QT_END_NAMESPACE

#endif
