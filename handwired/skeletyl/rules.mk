# MCU name
MCU = atmega32u4
TAP_DANCE_ENABLE = yes

# Bootloader selection
BOOTLOADER = caterina

# Build options
# Enable or disable features as needed
# MOUSEKEY_ENABLE = no      # Disable mouse keys
EXTRAKEY_ENABLE = yes     # Enable extra keys (system control, media control)
CONSOLE_ENABLE = no       # Disable console for debugging
COMMAND_ENABLE = no       # Disable command feature
NKRO_ENABLE = yes         # Enable N-Key Rollover
BACKLIGHT_ENABLE = no     # Disable backlight
RGBLIGHT_ENABLE = no      # Disable RGB lighting

# AUDIO_SUPPORTED = no        # Audio is not supported

# MOUSE_SHARED_EP = no # Unify multiple HID interfaces into a single Endpoint

# SERIAL_DRIVER = usart
