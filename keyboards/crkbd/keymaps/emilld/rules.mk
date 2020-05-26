# RGBLIGHT_ENABLE = yes
# RGB_MATRIX_ENABLE = WS2812
TAPPING_TERM = 500

BOOTMAGIC_ENABLE        = no
MOUSEKEY_ENABLE         = no
CONSOLE_ENABLE          = no
COMMAND_ENABLE          = no
EXTRAKEY_ENABLE            = yes # Audio control and System control(+450)

RGBLIGHT_ENABLE         = no
# RGB_MATRIX_ENABLE       = WS2812

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/glcdfont.c \
        ./lib/rgb_state_reader.c \
        ./lib/layer_state_reader.c \
        ./lib/logo_reader.c \
        ./lib/keylogger.c \
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/timelogger.c \
