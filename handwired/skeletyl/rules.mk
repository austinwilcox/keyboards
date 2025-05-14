# MCU name
MCU = atmega32u4
TAP_DANCE_ENABLE = yes

# Bootloader selection
BOOTLOADER = caterina

# Build options
# Enable or disable features as needed
# MOUSEKEY_ENABLE = no      # Disable mouse keys
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
SPLIT_KEYBOARD = yes
COMMAND_ENABLE = no       # Disable command feature
NKRO_ENABLE = yes         # Enable N-Key Rollover
BACKLIGHT_ENABLE = no     # Disable backlight
RGBLIGHT_ENABLE = no      # Disable RGB lighting
