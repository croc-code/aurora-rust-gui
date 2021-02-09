#ifndef QT_WAYLAND_TEXT
#define QT_WAYLAND_TEXT

#include <QtWaylandClient/private/wayland-text-client-protocol.h>
#include <QByteArray>
#include <QString>

QT_BEGIN_NAMESPACE

#if !defined(Q_WAYLAND_CLIENT_TEXT_EXPORT)
#  if defined(QT_SHARED)
#    define Q_WAYLAND_CLIENT_TEXT_EXPORT Q_DECL_EXPORT
#  else
#    define Q_WAYLAND_CLIENT_TEXT_EXPORT
#  endif
#endif

namespace QtWayland {
    class Q_WAYLAND_CLIENT_TEXT_EXPORT wl_text_input
    {
    public:
        wl_text_input(struct ::wl_registry *registry, int id, int version);
        wl_text_input(struct ::wl_text_input *object);
        wl_text_input();

        virtual ~wl_text_input();

        void init(struct ::wl_registry *registry, int id, int version);
        void init(struct ::wl_text_input *object);

        struct ::wl_text_input *object() { return m_wl_text_input; }
        const struct ::wl_text_input *object() const { return m_wl_text_input; }

        bool isInitialized() const;

        enum content_hint {
            content_hint_none = 0x0, // no special behaviour
            content_hint_default = 0x7, // auto completion, correction and capitalization
            content_hint_password = 0xc0, // hidden and sensitive text
            content_hint_auto_completion = 0x1, // suggest word completions
            content_hint_auto_correction = 0x2, // suggest word corrections
            content_hint_auto_capitalization = 0x4, // switch to uppercase letters at the start of a sentence
            content_hint_lowercase = 0x8, // prefer lowercase letters
            content_hint_uppercase = 0x10, // prefer uppercase letters
            content_hint_titlecase = 0x20, // prefer casing for titles and headings (can be language dependent)
            content_hint_hidden_text = 0x40, // characters should be hidden
            content_hint_sensitive_data = 0x80, // typed text should not be stored
            content_hint_latin = 0x100, // just latin characters should be entered
            content_hint_multiline = 0x200 // the text input is multiline
        };

        enum content_purpose {
            content_purpose_normal = 0, // default input, allowing all characters
            content_purpose_alpha = 1, // allow only alphabetic characters
            content_purpose_digits = 2, // allow only digits
            content_purpose_number = 3, // input a number (including decimal separator and sign)
            content_purpose_phone = 4, // input a phone number
            content_purpose_url = 5, // input an URL
            content_purpose_email = 6, // input an email address
            content_purpose_name = 7, // input a name of a person
            content_purpose_password = 8, // input a password (combine with password or sensitive_data hint)
            content_purpose_date = 9, // input a date
            content_purpose_time = 10, // input a time
            content_purpose_datetime = 11, // input a date and time
            content_purpose_terminal = 12 // input for a terminal
        };

        enum preedit_style {
            preedit_style_default = 0, // default style for composing text
            preedit_style_none = 1, // style should be the same as in non-composing text
            preedit_style_active = 2,
            preedit_style_inactive = 3,
            preedit_style_highlight = 4,
            preedit_style_underline = 5,
            preedit_style_selection = 6,
            preedit_style_incorrect = 7
        };

        enum text_direction {
            text_direction_auto = 0, // automatic text direction based on text and language
            text_direction_ltr = 1, // left-to-right
            text_direction_rtl = 2 // right-to-left
        };

        void activate(struct ::wl_seat *seat, struct ::wl_surface *surface);
        void deactivate(struct ::wl_seat *seat);
        void show_input_panel();
        void hide_input_panel();
        void reset();
        void set_surrounding_text(const QString &text, uint32_t cursor, uint32_t anchor);
        void set_content_type(uint32_t hint, uint32_t purpose);
        void set_cursor_rectangle(int32_t x, int32_t y, int32_t width, int32_t height);
        void set_preferred_language(const QString &language);
        void commit_state(uint32_t serial);
        void invoke_action(uint32_t button, uint32_t index);

    protected:
        virtual void text_input_enter(struct ::wl_surface *surface);
        virtual void text_input_leave();
        virtual void text_input_modifiers_map(wl_array *map);
        virtual void text_input_input_panel_state(uint32_t state);
        virtual void text_input_preedit_string(uint32_t serial, const QString &text, const QString &commit);
        virtual void text_input_preedit_styling(uint32_t index, uint32_t length, uint32_t style);
        virtual void text_input_preedit_cursor(int32_t index);
        virtual void text_input_commit_string(uint32_t serial, const QString &text);
        virtual void text_input_cursor_position(int32_t index, int32_t anchor);
        virtual void text_input_delete_surrounding_text(int32_t index, uint32_t length);
        virtual void text_input_keysym(uint32_t serial, uint32_t time, uint32_t sym, uint32_t state, uint32_t modifiers);
        virtual void text_input_language(uint32_t serial, const QString &language);
        virtual void text_input_text_direction(uint32_t serial, uint32_t direction);

    private:
        void init_listener();
        static const struct wl_text_input_listener m_wl_text_input_listener;
        static void handle_enter(
            void *data,
            struct ::wl_text_input *object,
            struct ::wl_surface *surface);
        static void handle_leave(
            void *data,
            struct ::wl_text_input *object);
        static void handle_modifiers_map(
            void *data,
            struct ::wl_text_input *object,
            wl_array *map);
        static void handle_input_panel_state(
            void *data,
            struct ::wl_text_input *object,
            uint32_t state);
        static void handle_preedit_string(
            void *data,
            struct ::wl_text_input *object,
            uint32_t serial,
            const char *text,
            const char *commit);
        static void handle_preedit_styling(
            void *data,
            struct ::wl_text_input *object,
            uint32_t index,
            uint32_t length,
            uint32_t style);
        static void handle_preedit_cursor(
            void *data,
            struct ::wl_text_input *object,
            int32_t index);
        static void handle_commit_string(
            void *data,
            struct ::wl_text_input *object,
            uint32_t serial,
            const char *text);
        static void handle_cursor_position(
            void *data,
            struct ::wl_text_input *object,
            int32_t index,
            int32_t anchor);
        static void handle_delete_surrounding_text(
            void *data,
            struct ::wl_text_input *object,
            int32_t index,
            uint32_t length);
        static void handle_keysym(
            void *data,
            struct ::wl_text_input *object,
            uint32_t serial,
            uint32_t time,
            uint32_t sym,
            uint32_t state,
            uint32_t modifiers);
        static void handle_language(
            void *data,
            struct ::wl_text_input *object,
            uint32_t serial,
            const char *language);
        static void handle_text_direction(
            void *data,
            struct ::wl_text_input *object,
            uint32_t serial,
            uint32_t direction);
        struct ::wl_text_input *m_wl_text_input;
    };

    class Q_WAYLAND_CLIENT_TEXT_EXPORT wl_text_input_manager
    {
    public:
        wl_text_input_manager(struct ::wl_registry *registry, int id, int version);
        wl_text_input_manager(struct ::wl_text_input_manager *object);
        wl_text_input_manager();

        virtual ~wl_text_input_manager();

        void init(struct ::wl_registry *registry, int id, int version);
        void init(struct ::wl_text_input_manager *object);

        struct ::wl_text_input_manager *object() { return m_wl_text_input_manager; }
        const struct ::wl_text_input_manager *object() const { return m_wl_text_input_manager; }

        bool isInitialized() const;

        struct ::wl_text_input *create_text_input();

    private:
        struct ::wl_text_input_manager *m_wl_text_input_manager;
    };
}

QT_END_NAMESPACE

#endif
