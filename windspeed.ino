/*
 * To calculate the wind speed, we need some data.
 * 
 * 
 * 
 * KM/H PER VOLT
 * 
 * The sensor label says:
 *   0.4 V ==  0   m/s
 *   2   V == 23.4 m/s
 * 
 * This means 1.6 V per 23.4 m/s. 1V per (23.4 / 1.6) = 14.625 m/s.
 * 1 m/s == 3.6 km/h. This means 1V per (14.625 * 3.6) = 52.65 km/h.
 * 
 * This means the formula is:
 * kmh = (volt - 0.4) * (23.4 / (2 - 0.4)) * 3.6);
 * 
 * 
 * 
 * VOLT PER ANALOGDATA
 * 
 * According to the MCU documentation:
 *   0 V == 0
 *   3.3 V == 1024
 * 
 * This means 3.3 V per 1024. 1 analog data = (3.3 / 1024) = 0.0048828125 V.
 * 
 * This means the formula is:
 * volt = analogData * (3.3 / 1024);
 * 
 * 
 * 
 * KM/H PER ANALOGDATA
 * 
 * If these two formulas are combined, this is the result:
 * 
 * kmh = ((analogData * (3.3 / 1024)) - 0.4) * (23.4 / (2 - 0.4)) * 3.6;
 * 
 * If this formula is simplified (see https://www.symbolab.com/solver/simplify-calculator)
 * the result is:
 * 
 * kmh = 52.65 * (0.0048828125 * analogData - 0.4)
 * 
 * 
 * 
 */

float getWindspeed() {
  float analogData = analogRead(A0);
  float kmh = ((analogData * (3.3 / 1024)) - 0.4) * (23.4 / (2 - 0.4)) * 3.6;
  if (kmh < 2.5) return 0;
  return kmh;
}

