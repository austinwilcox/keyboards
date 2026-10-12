# Void40 wiring guide: RP2040-Zero with one rotary encoder

## Assumptions

- Board: Waveshare-style **RP2040-Zero**, which breaks out **GP0-GP15 and GP26-GP29** (20 usable GPIOs).
- Layout: a typical 40% with **4 rows x up to 12 columns**. I couldn't find a layout for "Void40" that I trust, so if yours has fewer columns, leave the extra pins unused. If it has more, tell me and the plan needs rework.
- Hand-wired, so pin choices are flexible.
- Firmware not written yet, so the config should be made to match this table.

Pin budget: 4 rows + 12 columns + 3 encoder pins = **19 of 20 GPIOs**.

---

## Pin assignments

| Function | Pin(s) |
|---|---|
| Rows R0-R3 | GP0, GP1, GP2, GP3 |
| Columns C0-C11 | GP4 through GP15 |
| Encoder A (Out A) | GP26 |
| Encoder B (Out B) | GP27 |
| Encoder switch (pin 1) | GP28 |
| Encoder GND (middle pin) and switch pin 2 | Any GND pin |
| Spare | GP29 |
| Avoid | GP16 (drives the onboard RGB LED) |

### Block diagram

```
                    +-----------------+
 Matrix rows  <---- | GP0 - GP3       |
 (R0 - R3)          |                 |
                    |   RP2040-Zero   |   GP26 ----> Encoder Out A
 Matrix cols  <---- | GP4 - GP15      |   GP27 ----> Encoder Out B
 (C0 - C11)         |                 |   GP28 ----> Encoder switch pin 1
                    |                 |   GND  ----> Encoder GND + switch pin 2
                    +-----------------+
```

---

## Matrix wiring

- Put **one diode on every switch**.
- Point the diode **stripe (cathode) toward the row wire**. In firmware this is `COL2ROW`.
- Each row wire connects all switches in that row. Each column wire connects all switches in that column.

---

## Encoder wiring

Typical EC11-style encoder:

- **Three-pin side:** Out A, GND (middle), Out B
- **Two-pin side:** push switch

| Encoder pin | Connects to |
|---|---|
| Out A | GP26 |
| Out B | GP27 |
| Middle pin (GND) | GND |
| Switch pin 1 | GP28 |
| Switch pin 2 | GND |

Notes:

- No external resistors or diodes are needed. Use the microcontroller's **internal pull-ups** on the encoder pins (QMK enables these for encoder pins automatically; in KMK, configure the pins with pull-ups).
- Optional hardware debounce: 10 nF capacitors from A and B to GND. Software debounce is usually enough.
- Check your encoder's datasheet or use a multimeter in continuity mode, since pin order can vary between models.

### Why the encoder doesn't go in the matrix

- A and B are quadrature signals that firmware needs to read quickly and in order. Matrix scanning can miss transitions, especially when the knob is turned fast.
- Keyboard firmware such as QMK and KMK expects encoder A/B on dedicated GPIOs.
- The **push switch is the one exception**. It's an ordinary button, so it can either go direct to a GPIO and GND, or into the matrix as a normal key with a diode.

---

## Firmware notes

### QMK

- Define the encoder pins in `keyboard.json`:

  ```json
  "encoder": {
      "enabled": true,
      "rotary": [
          { "pin_a": "GP26", "pin_b": "GP27" }
      ]
  }
  ```

- Set `ENCODER_RESOLUTION` in `config.h` to match your encoder (commonly 4, sometimes 2 or 1) if it skips or double-counts steps.
- QMK's encoder support handles only A and B. For the push switch, the easiest route is to **wire it into the matrix as a regular key** (one diode, one spare matrix position) instead of on GP28. Use GP28 only if you plan to write custom code to read it.

### KMK

- Use the `EncoderHandler` module with `pin_a`, `pin_b`, and `pin_button`, which supports a direct-wired switch on GP28.

### Both

- Set the diode direction to `COL2ROW` to match the diode orientation above.
- Update pin names in your config to match the table. A config copied from a different board may reference pins that don't exist on the RP2040-Zero (for example GP20, GP21, GP23).

---

## Troubleshooting

| Symptom | Fix |
|---|---|
| Knob counts backwards | Swap the A and B pins in config |
| Skipped or doubled steps | Adjust the encoder resolution; check debounce |
| Erratic encoder readings | Confirm pull-ups are enabled on A, B, and the switch |
| Switch not registering | Confirm the two switch pins are the pair on the opposite side from A/GND/B |
| Ghost or missing keys | Check diode orientation and that every switch has its own diode |

---

## Before you solder

- Verify the pin labels printed on your specific RP2040-Zero. Clones sometimes differ.
- Confirm the real row and column counts of your Void40 layout and adjust the table if needed.
