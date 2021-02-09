#ifndef QT_WAYLAND_SERVER_INPUT_METHOD
#define QT_WAYLAND_SERVER_INPUT_METHOD

#include "wayland-server.h"
#include <QtCompositor/private/wayland-input-method-server-protocol.h>
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

#if !defined(Q_WAYLAND_SERVER_INPUT_METHOD_EXPORT)
#  if defined(QT_SHARED)
#    define Q_WAYLAND_SERVER_INPUT_METHOD_EXPORT Q_DECL_EXPORT
#  else
#    define Q_WAYLAND_SERVER_INPUT_METHOD_EXPORT
#  endif
#endif

namespace QtWaylandServer {
    class Q_WAYLAND_SERVER_INPUT_METHOD_EXPORT wl_input_method_context
    {
    public:
        wl_input_method_context(struct ::wl_client *client, int id, int version);
        wl_input_method_context(struct ::wl_display *display, int version);
        wl_input_method_context();

        virtual ~wl_input_method_context();

        class Resource
        {
        public:
            Resource() : input_method_context_object(0), handle(0) {}
            virtual ~Resource() {}

            wl_input_method_context *input_method_context_object;
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

        void send_surrounding_text(const QString &text, uint32_t cursor, uint32_t anchor);
        void send_surrounding_text(struct ::wl_resource *resource, const QString &text, uint32_t cursor, uint32_t anchor);
        void send_reset();
        void send_reset(struct ::wl_resource *resource);
        void send_content_type(uint32_t hint, uint32_t purpose);
        void send_content_type(struct ::wl_resource *resource, uint32_t hint, uint32_t purpose);
        void send_invoke_action(uint32_t button, uint32_t index);
        void send_invoke_action(struct ::wl_resource *resource, uint32_t button, uint32_t index);
        void send_commit_state(uint32_t serial);
        void send_commit_state(struct ::wl_resource *resource, uint32_t serial);
        void send_preferred_language(const QString &language);
        void send_preferred_language(struct ::wl_resource *resource, const QString &language);

    protected:
        virtual Resource *input_method_context_allocate();

        virtual void input_method_context_bind_resource(Resource *resource);
        virtual void input_method_context_destroy_resource(Resource *resource);

        virtual void input_method_context_destroy(Resource *resource);
        virtual void input_method_context_commit_string(Resource *resource, uint32_t serial, const QString &text);
        virtual void input_method_context_preedit_string(Resource *resource, uint32_t serial, const QString &text, const QString &commit);
        virtual void input_method_context_preedit_styling(Resource *resource, uint32_t index, uint32_t length, uint32_t style);
        virtual void input_method_context_preedit_cursor(Resource *resource, int32_t index);
        virtual void input_method_context_delete_surrounding_text(Resource *resource, int32_t index, uint32_t length);
        virtual void input_method_context_cursor_position(Resource *resource, int32_t index, int32_t anchor);
        virtual void input_method_context_modifiers_map(Resource *resource, wl_array *map);
        virtual void input_method_context_keysym(Resource *resource, uint32_t serial, uint32_t time, uint32_t sym, uint32_t state, uint32_t modifiers);
        virtual void input_method_context_grab_keyboard(Resource *resource, uint32_t keyboard);
        virtual void input_method_context_key(Resource *resource, uint32_t serial, uint32_t time, uint32_t key, uint32_t state);
        virtual void input_method_context_modifiers(Resource *resource, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group);
        virtual void input_method_context_language(Resource *resource, uint32_t serial, const QString &language);
        virtual void input_method_context_text_direction(Resource *resource, uint32_t serial, uint32_t direction);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);

        static const struct ::wl_input_method_context_interface m_wl_input_method_context_interface;

        static void handle_destroy(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_commit_string(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t serial,
            const char *text);
        static void handle_preedit_string(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t serial,
            const char *text,
            const char *commit);
        static void handle_preedit_styling(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t index,
            uint32_t length,
            uint32_t style);
        static void handle_preedit_cursor(
            ::wl_client *client,
            struct wl_resource *resource,
            int32_t index);
        static void handle_delete_surrounding_text(
            ::wl_client *client,
            struct wl_resource *resource,
            int32_t index,
            uint32_t length);
        static void handle_cursor_position(
            ::wl_client *client,
            struct wl_resource *resource,
            int32_t index,
            int32_t anchor);
        static void handle_modifiers_map(
            ::wl_client *client,
            struct wl_resource *resource,
            wl_array *map);
        static void handle_keysym(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t serial,
            uint32_t time,
            uint32_t sym,
            uint32_t state,
            uint32_t modifiers);
        static void handle_grab_keyboard(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t keyboard);
        static void handle_key(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t serial,
            uint32_t time,
            uint32_t key,
            uint32_t state);
        static void handle_modifiers(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t serial,
            uint32_t mods_depressed,
            uint32_t mods_latched,
            uint32_t mods_locked,
            uint32_t group);
        static void handle_language(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t serial,
            const char *language);
        static void handle_text_direction(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t serial,
            uint32_t direction);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
    };

    class Q_WAYLAND_SERVER_INPUT_METHOD_EXPORT wl_input_method
    {
    public:
        wl_input_method(struct ::wl_client *client, int id, int version);
        wl_input_method(struct ::wl_display *display, int version);
        wl_input_method();

        virtual ~wl_input_method();

        class Resource
        {
        public:
            Resource() : input_method_object(0), handle(0) {}
            virtual ~Resource() {}

            wl_input_method *input_method_object;
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

        void send_activate(struct ::wl_resource *id);
        void send_activate(struct ::wl_resource *resource, struct ::wl_resource *id);
        void send_deactivate(struct ::wl_resource *context);
        void send_deactivate(struct ::wl_resource *resource, struct ::wl_resource *context);

    protected:
        virtual Resource *input_method_allocate();

        virtual void input_method_bind_resource(Resource *resource);
        virtual void input_method_destroy_resource(Resource *resource);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
    };

    class Q_WAYLAND_SERVER_INPUT_METHOD_EXPORT wl_input_panel
    {
    public:
        wl_input_panel(struct ::wl_client *client, int id, int version);
        wl_input_panel(struct ::wl_display *display, int version);
        wl_input_panel();

        virtual ~wl_input_panel();

        class Resource
        {
        public:
            Resource() : input_panel_object(0), handle(0) {}
            virtual ~Resource() {}

            wl_input_panel *input_panel_object;
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
        virtual Resource *input_panel_allocate();

        virtual void input_panel_bind_resource(Resource *resource);
        virtual void input_panel_destroy_resource(Resource *resource);

        virtual void input_panel_get_input_panel_surface(Resource *resource, uint32_t id, struct ::wl_resource *surface);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);

        static const struct ::wl_input_panel_interface m_wl_input_panel_interface;

        static void handle_get_input_panel_surface(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t id,
            struct ::wl_resource *surface);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
    };

    class Q_WAYLAND_SERVER_INPUT_METHOD_EXPORT wl_input_panel_surface
    {
    public:
        wl_input_panel_surface(struct ::wl_client *client, int id, int version);
        wl_input_panel_surface(struct ::wl_display *display, int version);
        wl_input_panel_surface();

        virtual ~wl_input_panel_surface();

        class Resource
        {
        public:
            Resource() : input_panel_surface_object(0), handle(0) {}
            virtual ~Resource() {}

            wl_input_panel_surface *input_panel_surface_object;
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

        enum position {
            position_center_bottom = 0
        };

    protected:
        virtual Resource *input_panel_surface_allocate();

        virtual void input_panel_surface_bind_resource(Resource *resource);
        virtual void input_panel_surface_destroy_resource(Resource *resource);

        virtual void input_panel_surface_set_toplevel(Resource *resource, struct ::wl_resource *output, uint32_t position);
        virtual void input_panel_surface_set_overlay_panel(Resource *resource);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);

        static const struct ::wl_input_panel_surface_interface m_wl_input_panel_surface_interface;

        static void handle_set_toplevel(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *output,
            uint32_t position);
        static void handle_set_overlay_panel(
            ::wl_client *client,
            struct wl_resource *resource);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
    };
}

QT_END_NAMESPACE

#endif
