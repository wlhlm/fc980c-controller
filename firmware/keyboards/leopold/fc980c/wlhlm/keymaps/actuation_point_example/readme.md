Keymap for adjusting the switch acuation point
==============================================

This keymap provides custom keycodes that allow adjusting the actuation point of
the Topre switches of the FC980C. The keyboard comes with an actuation point
predefined from the factory. This value will never be overwritten, rather QMK
will store the custom actuation point value in its private EEPROM store which can
easily be reset.

Actuation point adjustment keycodes
-----------------------------------

- `AP_UP` - makes the actuation point deeper
- `AP_DN` - makes the actuation point shallower
- `AP_RST` - restores the factory actuation point value
- `AP_PRINT_VAL` - types out the current actuation point value (between 0 and
  63, inclusive)
