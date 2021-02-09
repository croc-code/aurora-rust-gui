#ifndef QT_WAYLAND_SERVER_WINDOWMANAGER
#define QT_WAYLAND_SERVER_WINDOWMANAGER

#include "wayland-server.h"
#include <QtCompositor/private/wayland-windowmanager-server-protocol.h>
#include <QByteArray>
#include <QMultiMap>
#include <QString>

#ifndef WAYLAND_VERSION_CHECK
#define WAYLAND_VERSION_CHECK(major, minor, micro) \
    ((WAYLAND_VERSION_MAJOR > (major)) || \
    (WAYLAND_VERSION_MAJOR == (major) && WAYLAND_VERSION_MINOR > (minor)) || \
    (WAYLAND_VERSION_MAJOR == (major) && WAYLAND_VERSION_MINOR == (minor) && WAYLAND_VERSION_MICRO >= (micro)))
#endif

QT_BEGIN_NAMESPACE

#if !defined(Q_WAYLAND_SERVER_WINDOWMANAGER_EXPORT)
#  if defined(QT_SHARED)
#    define Q_WAYLAND_SERVER_WINDOWMANAGER_EXPORT Q_DECL_EXPORT
#  else
#    define Q_WAYLAND_SERVER_WINDOWMANAGER_EXPORT
#  endif
#endif

namespace QtWaylandServer {
    class Q_WAYLAND_SERVER_WINDOWMANAGER_EXPORT qt_windowmanager
    {
    public:
        qt_windowmanager(struct ::wl_client *client, int id, int version);
        qt_windowmanager(struct ::wl_display *display, int version);
        qt_windowmanager();

        virtual ~qt_windowmanager();

        class Resource
        {
        public:
            Resource() : windowmanager_object(0), handle(0) {}
            virtual ~Resource() {}

            qt_windowmanager *windowmanager_object;
            struct ::wl_resource *handle;

            struct ::wl_client *client() const { return handle->client; }
            int version() const { return wl_resource_get_version(handle); }

            static Resource *fromResource(struct ::wl_resource *resource) { return static_cast<Resource *>(resource->data); }
        };

        void init(struct ::wl_client *client, int id, int version);
        void init(struct ::wl_display *display, int version);

        Resource *add(struct ::wl_client *client, int version);
        Resource *add(struct ::wl_client *client, int id, int version);
        Resource *add(struct wl_list *resource_list, struct ::wl_client *client, int id, int version);

        Resource *resource() { return m_resource; }
        const Resource *resource() const { return m_resource; }

        QMultiMap<struct ::wl_client*, Resource*> resourceMap() { return m_resource_map; }
        const QMultiMap<struct ::wl_client*, Resource*> resourceMap() const { return m_resource_map; }

        bool isGlobal() const { return m_global != 0; }
        bool isResource() const { return m_resource != 0; }

        void send_hints(int32_t show_is_fullscreen);
        void send_hints(struct ::wl_resource *resource, int32_t show_is_fullscreen);
        void send_quit();
        void send_quit(struct ::wl_resource *resource);

    protected:
        virtual Resource *windowmanager_allocate();

        virtual void windowmanager_bind_resource(Resource *resource);
        virtual void windowmanager_destroy_resource(Resource *resource);

        virtual void windowmanager_open_url(Resource *resource, uint32_t remaining, const QString &url);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);

        static const struct ::qt_windowmanager_interface m_qt_windowmanager_interface;

        static void handle_open_url(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t remaining,
            const char *url);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
    };
}

QT_END_NAMESPACE

#endif
