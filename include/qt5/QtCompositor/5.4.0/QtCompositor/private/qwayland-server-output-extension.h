#ifndef QT_WAYLAND_SERVER_OUTPUT_EXTENSION
#define QT_WAYLAND_SERVER_OUTPUT_EXTENSION

#include "wayland-server.h"
#include <QtCompositor/private/wayland-output-extension-server-protocol.h>
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

#if !defined(Q_WAYLAND_SERVER_OUTPUT_EXTENSION_EXPORT)
#  if defined(QT_SHARED)
#    define Q_WAYLAND_SERVER_OUTPUT_EXTENSION_EXPORT Q_DECL_EXPORT
#  else
#    define Q_WAYLAND_SERVER_OUTPUT_EXTENSION_EXPORT
#  endif
#endif

namespace QtWaylandServer {
    class Q_WAYLAND_SERVER_OUTPUT_EXTENSION_EXPORT qt_output_extension
    {
    public:
        qt_output_extension(struct ::wl_client *client, int id, int version);
        qt_output_extension(struct ::wl_display *display, int version);
        qt_output_extension();

        virtual ~qt_output_extension();

        class Resource
        {
        public:
            Resource() : output_extension_object(0), handle(0) {}
            virtual ~Resource() {}

            qt_output_extension *output_extension_object;
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
        virtual Resource *output_extension_allocate();

        virtual void output_extension_bind_resource(Resource *resource);
        virtual void output_extension_destroy_resource(Resource *resource);

        virtual void output_extension_get_extended_output(Resource *resource, uint32_t id, struct ::wl_resource *output);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);

        static const struct ::qt_output_extension_interface m_qt_output_extension_interface;

        static void handle_get_extended_output(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t id,
            struct ::wl_resource *output);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
    };

    class Q_WAYLAND_SERVER_OUTPUT_EXTENSION_EXPORT qt_extended_output
    {
    public:
        qt_extended_output(struct ::wl_client *client, int id, int version);
        qt_extended_output(struct ::wl_display *display, int version);
        qt_extended_output();

        virtual ~qt_extended_output();

        class Resource
        {
        public:
            Resource() : extended_output_object(0), handle(0) {}
            virtual ~Resource() {}

            qt_extended_output *extended_output_object;
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
        virtual Resource *extended_output_allocate();

        virtual void extended_output_bind_resource(Resource *resource);
        virtual void extended_output_destroy_resource(Resource *resource);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
    };
}

QT_END_NAMESPACE

#endif
