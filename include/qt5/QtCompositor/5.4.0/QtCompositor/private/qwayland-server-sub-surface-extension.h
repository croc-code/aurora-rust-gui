#ifndef QT_WAYLAND_SERVER_SUB_SURFACE_EXTENSION
#define QT_WAYLAND_SERVER_SUB_SURFACE_EXTENSION

#include "wayland-server.h"
#include <QtCompositor/private/wayland-sub-surface-extension-server-protocol.h>
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

#if !defined(Q_WAYLAND_SERVER_SUB_SURFACE_EXTENSION_EXPORT)
#  if defined(QT_SHARED)
#    define Q_WAYLAND_SERVER_SUB_SURFACE_EXTENSION_EXPORT Q_DECL_EXPORT
#  else
#    define Q_WAYLAND_SERVER_SUB_SURFACE_EXTENSION_EXPORT
#  endif
#endif

namespace QtWaylandServer {
    class Q_WAYLAND_SERVER_SUB_SURFACE_EXTENSION_EXPORT qt_sub_surface_extension
    {
    public:
        qt_sub_surface_extension(struct ::wl_client *client, int id, int version);
        qt_sub_surface_extension(struct ::wl_display *display, int version);
        qt_sub_surface_extension();

        virtual ~qt_sub_surface_extension();

        class Resource
        {
        public:
            Resource() : sub_surface_extension_object(0), handle(0) {}
            virtual ~Resource() {}

            qt_sub_surface_extension *sub_surface_extension_object;
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

    protected:
        virtual Resource *sub_surface_extension_allocate();

        virtual void sub_surface_extension_bind_resource(Resource *resource);
        virtual void sub_surface_extension_destroy_resource(Resource *resource);

        virtual void sub_surface_extension_get_sub_surface_aware_surface(Resource *resource, uint32_t id, struct ::wl_resource *surface);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);

        static const struct ::qt_sub_surface_extension_interface m_qt_sub_surface_extension_interface;

        static void handle_get_sub_surface_aware_surface(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t id,
            struct ::wl_resource *surface);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
    };

    class Q_WAYLAND_SERVER_SUB_SURFACE_EXTENSION_EXPORT qt_sub_surface
    {
    public:
        qt_sub_surface(struct ::wl_client *client, int id, int version);
        qt_sub_surface(struct ::wl_display *display, int version);
        qt_sub_surface();

        virtual ~qt_sub_surface();

        class Resource
        {
        public:
            Resource() : sub_surface_object(0), handle(0) {}
            virtual ~Resource() {}

            qt_sub_surface *sub_surface_object;
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

    protected:
        virtual Resource *sub_surface_allocate();

        virtual void sub_surface_bind_resource(Resource *resource);
        virtual void sub_surface_destroy_resource(Resource *resource);

        virtual void sub_surface_attach_sub_surface(Resource *resource, struct ::wl_resource *sub_surface, int32_t x, int32_t y);
        virtual void sub_surface_move_sub_surface(Resource *resource, struct ::wl_resource *sub_surface, int32_t x, int32_t y);
        virtual void sub_surface_raise(Resource *resource, struct ::wl_resource *sub_surface);
        virtual void sub_surface_lower(Resource *resource, struct ::wl_resource *sub_surface);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);

        static const struct ::qt_sub_surface_interface m_qt_sub_surface_interface;

        static void handle_attach_sub_surface(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *sub_surface,
            int32_t x,
            int32_t y);
        static void handle_move_sub_surface(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *sub_surface,
            int32_t x,
            int32_t y);
        static void handle_raise(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *sub_surface);
        static void handle_lower(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *sub_surface);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
    };
}

QT_END_NAMESPACE

#endif
