LTC4150 Coulomb Counter on Arduino Uno with LCD Display
=======================================================

SparkFun LTC4150 Coulomb Counter
--------------------------------

- [Hookup Guide](https://learn.sparkfun.com/tutorials/ltc4150-coulomb-counter-hookup-guide/all)
- [LTC4150 Datasheet](https://cdn.sparkfun.com/datasheets/BreakoutBoards/LTC4150fc.pdf)
- [Schematic](https://cdn.sparkfun.com/datasheets/BreakoutBoards/LTC4150_BOB_v10.pdf)
- [GitHub Repo](https://github.com/sparkfun/LTC4150_Coulomb_Counter_BOB)
- [Product Page](https://www.sparkfun.com/sparkfun-coulomb-counter-breakout-ltc4150.html)

DFRobot LCD1602 Module (P/N DFR0555)
------------------------------------

- [Product Page](https://www.dfrobot.com/product-1724.html)
- [Datasheet](https://github.com/Arduinolibrary/DFRobot_Gravity_I2C_LCD1602_Display_module/blob/master/LCD%20Datasheet.pdf)
  - **Warning:** Apparently the I2C address for the RGB controller has changed, according to
    [this forum post](https://forum.digikey.com/t/dfr0555-backlight-firmware-control/38735).
    See code: I did have to use `0x6B`.
- [Arduino Library](https://github.com/DFRobot/DFRobot_RGBLCD1602)
