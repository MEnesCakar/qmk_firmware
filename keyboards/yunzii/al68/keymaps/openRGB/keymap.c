/* Copyright 2022 Jacky
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =  { ENCODER_CCW_CW(QK_MACRO_12, QK_MACRO_13)  },
    [1] =  { ENCODER_CCW_CW(QK_MACRO_14,QK_MACRO_15)  }
};
#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi_blocker(
    KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,     KC_BSPC,    KC_MUTE,
    KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,    KC_BSLS,    KC_DELETE,
    KC_CAPS,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,                KC_ENT,     KC_PAGE_UP,
    KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,                KC_UP,      KC_PAGE_DOWN,
    KC_LCTL,    KC_LGUI,    KC_LALT,                            KC_SPC,                             MO(1),      KC_RCTL,                            KC_LEFT,    KC_DOWN,    KC_RIGHT    
    ),
    [1] = LAYOUT_65_ansi_blocker(
    KC_GRV,     KC_BRID,    KC_BRIU,    _______,    KC_MYCM,    KC_MAIL,    KC_WHOM,    KC_MPRV,    KC_MPLY,    KC_MNXT,    _______,    KC_VOLD,    KC_VOLU,    _______,    _______,
    _______,    KC_BLE1,    KC_BLE2,    KC_BLE3,    KC_24G,     _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    RGB_MOD,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                RGB_HUI,    _______, 
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                RGB_VAI,    _______,
    _______,    _______,     _______,                           _______,                           _______,    _______,                            RGB_SPD,    RGB_VAD,    RGB_SPI 
    )
};

uint8_t color_buffer[RGB_MATRIX_LED_COUNT * 2] = {0};
uint8_t brightness_buffer[RGB_MATRIX_LED_COUNT] = {[0 ... RGB_MATRIX_LED_COUNT - 1] = 255};

#ifdef VIA_ENABLE
void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t channel_id = data[1];
    if (channel_id != id_custom_channel) return;

    uint8_t *command_id = &(data[0]);
    uint8_t value_id    = data[2];
    uint8_t led_index   = data[3];
    uint8_t led_count   = data[4];

    switch (*command_id) {
        case id_custom_set_value:
            if (value_id == 1) {
                memcpy(color_buffer + led_index * 2, data + 5, led_count * 2);
            } else if (value_id == 2) {
                memcpy(brightness_buffer + led_index, data + 5, led_count);
            }
            break;

        case id_custom_get_value:
            if (value_id == 1) {
                memcpy(data + 5, color_buffer + led_index * 2, led_count * 2);
            } else if (value_id == 2) {
                memcpy(data + 5, brightness_buffer + led_index, led_count);
            }
            break;

        case id_custom_save:
            // optional: implement persistent save here
            break;

        default:
            *command_id = id_unhandled;
            break;
    }
}
#endif // VIA_ENABLE