#ifndef QT_WAYLAND_XDG_SHELL
#define QT_WAYLAND_XDG_SHELL

#include <QtWaylandClient/private/wayland-xdg-shell-client-protocol.h>
#include <QByteArray>
#include <QString>

QT_BEGIN_NAMESPACE

#if !defined(Q_WAYLAND_CLIENT_XDG_SHELL_EXPORT)
#  if defined(QT_SHARED)
#    define Q_WAYLAND_CLIENT_XDG_SHELL_EXPORT Q_DECL_EXPORT
#  else
#    define Q_WAYLAND_CLIENT_XDG_SHELL_EXPORT
#  endif
#endif

namespace QtWayland {
    class Q_WAYLAND_CLIENT_XDG_SHELL_EXPORT xdg_shell
    {
    public:
        xdg_shell(struct ::wl_registry *registry, int id, int version);
        xdg_shell(struct ::xdg_shell *object);
        xdg_shell();

        virtual ~xdg_shell();

        void init(struct ::wl_registry *registry, int id, int version);
        void init(struct ::xdg_shell *object);

        struct ::xdg_shell *object() { return m_xdg_shell; }
        const struct ::xdg_shell *object() const { return m_xdg_shell; }

        bool isInitialized() const;

        enum version {
            version_current = 3 // Always the latest version
        };

        void use_unstable_version(int32_t version);
        struct ::xdg_surface *get_xdg_surface(struct ::wl_surface *surface);
        struct ::xdg_popup *get_xdg_popup(struct ::wl_surface *surface, struct ::wl_surface *parent, struct ::wl_seat *seat, uint32_t serial, int32_t x, int32_t y, uint32_t flags);
        void pong(uint32_t serial);

    protected:
        virtual void xdg_shell_ping(uint32_t serial);

    private:
        void init_listener();
        static const struct xdg_shell_listener m_xdg_shell_listener;
        static void handle_ping(
            void *data,
            struct ::xdg_shell *object,
            uint32_t serial);
        struct ::xdg_shell *m_xdg_shell;
    };

    class Q_WAYLAND_CLIENT_XDG_SHELL_EXPORT xdg_surface
    {
    public:
        xdg_surface(struct ::wl_registry *registry, int id, int version);
        xdg_surface(struct ::xdg_surface *object);
        xdg_surface();

        virtual ~xdg_surface();

        void init(struct ::wl_registry *registry, int id, int version);
        void init(struct ::xdg_surface *object);

        struct ::xdg_surface *object() { return m_xdg_surface; }
        const struct ::xdg_surface *object() const { return m_xdg_surface; }

        bool isInitialized() const;

        enum resize_edge {
            resize_edge_none = 0,
            resize_edge_top = 1,
            resize_edge_bottom = 2,
            resize_edge_left = 4,
            resize_edge_top_left = 5,
            resize_edge_bottom_left = 6,
            resize_edge_right = 8,
            resize_edge_top_right = 9,
            resize_edge_bottom_right = 10
        };

        enum state {
            state_maximized = 1, // the surface is maximized
            state_fullscreen = 2 // the surface is fullscreen
        };

        void destroy();
        void set_transient_for(struct ::wl_surface *parent);
        void set_margin(int32_t left_margin, int32_t right_margin, int32_t top_margin, int32_t bottom_margin);
        void set_title(const QString &title);
        void set_app_id(const QString &app_id);
        void move(struct ::wl_seat *seat, uint32_t serial);
        void resize(struct ::wl_seat *seat, uint32_t serial, uint32_t edges);
        void set_output(struct ::wl_output *output);
        void request_change_state(uint32_t state_type, uint32_t value, uint32_t serial);
        void ack_change_state(uint32_t state_type, uint32_t value, uint32_t serial);
        void set_minimized();

    protected:
        virtual void xdg_surface_configure(int32_t width, int32_t height);
        virtual void xdg_surface_change_state(uint32_t state_type, uint32_t value, uint32_t serial);
        virtual void xdg_surface_activated();
        virtual void xdg_surface_deactivated();
        virtual void xdg_surface_close();

    private:
        void init_listener();
        static const struct xdg_surface_listener m_xdg_surface_listener;
        static void handle_configure(
            void *data,
            struct ::xdg_surface *object,
            int32_t width,
            int32_t height);
        static void handle_change_state(
            void *data,
            struct ::xdg_surface *object,
            uint32_t state_type,
            uint32_t value,
            uint32_t serial);
        static void handle_activated(
            void *data,
            struct ::xdg_surface *object);
        static void handle_deactivated(
            void *data,
            struct ::xdg_surface *object);
        static void handle_close(
            void *data,
            struct ::xdg_surface *object);
        struct ::xdg_surface *m_xdg_surface;
    };

    class Q_WAYLAND_CLIENT_XDG_SHELL_EXPORT xdg_popup
    {
    public:
        xdg_popup(struct ::wl_registry *registry, int id, int version);
        xdg_popup(struct ::xdg_popup *object);
        xdg_popup();

        virtual ~xdg_popup();

        void init(struct ::wl_registry *registry, int id, int version);
        void init(struct ::xdg_popup *object);

        struct ::xdg_popup *object() { return m_xdg_popup; }
        const struct ::xdg_popup *object() const { return m_xdg_popup; }

        bool isInitialized() const;

        void destroy();

    protected:
        virtual void xdg_popup_popup_done(uint32_t serial);

    private:
        void init_listener();
        static const struct xdg_popup_listener m_xdg_popup_listener;
        static void handle_popup_done(
            void *data,
            struct ::xdg_popup *object,
            uint32_t serial);
        struct ::xdg_popup *m_xdg_popup;
    };
}

QT_END_NAMESPACE

#endif
