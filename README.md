LTC4150 Coulomb Counter on Arduino Uno with LCD Display
=======================================================

SparkFun® LTC4150 Coulomb Counter
---------------------------------

- [Hookup Guide](https://learn.sparkfun.com/tutorials/ltc4150-coulomb-counter-hookup-guide/all)
- [LTC4150 Datasheet](https://cdn.sparkfun.com/datasheets/BreakoutBoards/LTC4150fc.pdf)
- [Schematic](https://cdn.sparkfun.com/datasheets/BreakoutBoards/LTC4150_BOB_v10.pdf)
- [GitHub Repo](https://github.com/sparkfun/LTC4150_Coulomb_Counter_BOB)
- [Product Page](https://www.sparkfun.com/sparkfun-coulomb-counter-breakout-ltc4150.html)
  - Operating Voltage: 2.7 - 8.5V, Operating Current: 1A max

DFRobot® LCD1602 Module (P/N DFR0555)
-------------------------------------

- [Product Page](https://www.dfrobot.com/product-1724.html)
- [Datasheet](https://github.com/Arduinolibrary/DFRobot_Gravity_I2C_LCD1602_Display_module/blob/master/LCD%20Datasheet.pdf)
  - **Warning:** Apparently the I2C address for the RGB controller has changed, according to
    [this forum post](https://forum.digikey.com/t/dfr0555-backlight-firmware-control/38735).
    See code: I did have to use `0x6B`.
- [Arduino Library](https://github.com/DFRobot/DFRobot_RGBLCD1602)

Hookup
------

- The breakout board is connected to the Arduino Uno via its pins 2 through 7,
  "VIO" at pin 2 and "SHDN" at pin 7.
- On the breakout board:
  - The battery or other power supply goes to "IN" or JST connector (these are identical)
  - The system drawing the current goes to "OUT"
  - Note that the negative connections of "IN", "OUT", and the "GND" pin are all the same net
- If supplying the Arduino Uno externally, note its VIN pin can take 6 to 20V.
- The LCD's SDA and SCL pins are labeled; it can be supplied from 3.3-5V;
  can simply connect to Arduino Uno's 5V.
