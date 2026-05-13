#include <DFRobot_RGBLCD1602.h>

#if !defined(pin_size_t)
typedef uint8_t pin_size_t;
#endif

constexpr pin_size_t PIN_VIO = 2;
constexpr pin_size_t PIN_INT = 3;
constexpr pin_size_t PIN_POL = 4;  // PD4
constexpr pin_size_t PIN_GND = 5;
constexpr pin_size_t PIN_CLR = 6;
constexpr pin_size_t PIN_SDN = 7;
#define PIN_POL_REG PIND
#define PIN_POL_BIT PIND4

DFRobot_RGBLCD1602 lcd(0x6B,16,2);

void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.setBacklight(true);
  lcd.setCursor(0, 0);
  lcd.print(F("+0 -0"));
  lcd.setCursor(0, 1);
  lcd.print(F("0 mAh"));

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(PIN_GND, OUTPUT);
  digitalWrite(PIN_GND, LOW);
  pinMode(PIN_VIO, OUTPUT);  // I/O reference voltage
  digitalWrite(PIN_VIO, HIGH);
  /* The INT and POL pins are open-drain and pulled up to VIO on the breakout board,
   * but for testing with a button instead of the LTC4150, we'll also enable the
   * ATmega328P's I/O pull-ups; it doesn't hurt. */
  pinMode(PIN_INT, INPUT_PULLUP);
  pinMode(PIN_POL, INPUT_PULLUP);
  pinMode(PIN_CLR, INPUT);  // tied to INT on breakout board via SJ1 by default
  pinMode(PIN_SDN, INPUT);  // pulled up to VIO on breakout board

  // First clear all interrupt flags to prevent phantom interrupts (write 1 to clear)
  EIFR  = _BV(INTF0) | _BV(INTF1);
  PCIFR = _BV(PCIF0) | _BV(PCIF1) | _BV(PCIF2);
  attachInterrupt(digitalPinToInterrupt(PIN_INT), isr, FALLING);
}

// Using a 32-bit tick counter means over +/-700 kAh can be counted.
static volatile uint32_t chg_count = 0;
static volatile uint32_t dis_count = 0;

/* LTC4150 with CLR tied to INT (as is the default on the breakout board, via SJ1)
 * guarantees a 1us pulse width. At an Arduino Uno's 16MHz clock rate (62.5n
 * period), that's 16 cycles per pulse, so enough for the ATmega328P to sample and
 * latch the interrupt. Note: As discussed below, maximum pulse frequency is
 * 1.6275 Hz, but still code the ISR to be as efficient as possible. */
void isr() {
  // POL=LOW=discharging, POL=HIGH=charging
  if (bitRead(PIN_POL_REG, PIN_POL_BIT)) chg_count++; else dis_count++;
}

void loop() {
  static uint32_t chg = 0;
  static uint32_t dis = 0;
  /* The following read of the volatile variables may be interrupted by the ISR, leading
   * to a bad read. But since this is only a check as to whether the ISR fired or not,
   * and the below code then uses an atomic read to update the output, that's fine. */
  if ( chg_count!=chg || dis_count!=dis ) {
    digitalWrite(LED_BUILTIN, HIGH);

    // copy over volatile values in an atomic block
    noInterrupts();
    chg = chg_count;
    dis = dis_count;
    interrupts();

    /* The breakout board has a 0.05 Ohm sense resistor and 1A maximum current. Using the
    * typical G_VF value 32.55Hz/V and the equations from the datasheet, we can calculate
    * that 1Ah causes 5859 INTs. At 1A, INT will pulse at 5859/3600 = 1.6275 Hz, or every
    * 3600/5859 = 400/651 = 0.614439...s. Note The LTC4150 datasheet apparently doesn't
    * specify a maximum INT pulse width when CLR is tied to INT. */
    constexpr double mAh_per_INT = 1000.0/5859.0;

    const double mAh = ( ((int64_t)chg) - ((int64_t)dis) ) * mAh_per_INT;

    lcd.setCursor(0, 0);
    lcd.print('+');
    lcd.print(chg, DEC);
    lcd.print(F(" -"));
    lcd.print(dis, DEC);
    lcd.setCursor(0, 1);
    lcd.print(mAh, 3);
    lcd.print(F(" mAh        "));

    Serial.print('+');
    Serial.print(chg, DEC);
    Serial.print(F(", -"));
    Serial.print(dis, DEC);
    Serial.print(F(", "));
    Serial.print(mAh, 6);
    Serial.println(F(" mAh"));

    digitalWrite(LED_BUILTIN, LOW);
  }
}
