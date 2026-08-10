#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

// =====================================================
// 0.96" 128x64 7-PIN SPI OLED -> ESP32
// =====================================================
//
// OLED       ESP32
// --------------------
// GND   ->   GND
// VCC   ->   3.3V
// D0    ->   GPIO 18
// D1    ->   GPIO 23
// RES   ->   GPIO 4
// DC    ->   GPIO 2
// CS    ->   GPIO 5
//
// =====================================================

#define OLED_CS   5
#define OLED_DC   2
#define OLED_RST  4

U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI oled(
  U8G2_R0,
  OLED_CS,
  OLED_DC,
  OLED_RST
);


// =====================================================
// CENTER TEXT
// =====================================================

void centerText(const char *text, int y)
{
  int w = oled.getStrWidth(text);

  if (w <= 124)
  {
    oled.drawStr((128 - w) / 2, y, text);
  }
}


// =====================================================
// CLEAN LIGHTNING ICON
// Completely inside 128x64
// =====================================================

void drawBolt(int x, int y)
{
  oled.drawLine(x + 7,  y,
                x + 1,  y + 10);

  oled.drawLine(x + 1,  y + 10,
                x + 7,  y + 10);

  oled.drawLine(x + 7,  y + 10,
                x + 1,  y + 25);

  oled.drawLine(x + 1,  y + 25,
                x + 16, y + 7);

  oled.drawLine(x + 16, y + 7,
                x + 10, y + 7);

  oled.drawLine(x + 10, y + 7,
                x + 15, y);
}


// =====================================================
// 1. POWER ON
// =====================================================

void powerOn()
{
  for (int p = 0; p <= 100; p += 2)
  {
    oled.clearBuffer();

    oled.setFont(u8g2_font_5x8_tf);
    centerText("BOLTBUNNY", 16);

    oled.drawFrame(12, 28, 104, 8);

    int width = p;

    if (width > 0)
      oled.drawBox(14, 30, width, 4);

    char percent[8];
    sprintf(percent, "%d%%", p);

    centerText(percent, 50);

    oled.sendBuffer();

    delay(16);
  }

  delay(300);
}


// =====================================================
// 2. DIGITAL RAIN
// =====================================================

void rainEffect()
{
  int x[18] = {
    4, 11, 18, 26, 34, 42,
    51, 59, 67, 75, 83, 91,
    99, 107, 115, 122, 47, 72
  };

  int y[18] = {
    3, 20, 9, 31, 14, 2,
    25, 8, 37, 17, 5, 28,
    11, 34, 22, 6, 44, 50
  };

  for (int frame = 0; frame < 65; frame++)
  {
    oled.clearBuffer();

    // Rain
    for (int i = 0; i < 18; i++)
    {
      int yy = (y[i] + frame * (1 + (i % 3))) % 64;

      oled.drawVLine(x[i], yy, 3);

      if (yy > 4)
        oled.drawPixel(x[i], yy - 4);
    }

    // Clean black area behind name
    oled.setDrawColor(0);
    oled.drawBox(16, 24, 96, 19);

    oled.setDrawColor(1);

    oled.setFont(u8g2_font_7x13B_tf);
    centerText("BOLTBUNNY", 37);

    oled.sendBuffer();

    delay(30);
  }
}


// =====================================================
// 3. LIGHTNING REVEAL
// =====================================================

void boltReveal()
{
  // Energy line
  for (int i = 0; i <= 32; i += 2)
  {
    oled.clearBuffer();

    oled.drawHLine(64 - i, 31, i * 2);

    oled.sendBuffer();

    delay(20);
  }

  // Lightning
  oled.clearBuffer();

  drawBolt(57, 5);

  oled.sendBuffer();

  delay(600);

  // Flash
  oled.clearBuffer();

  drawBolt(57, 5);

  oled.sendBuffer();

  delay(100);

  oled.clearBuffer();

  oled.sendBuffer();

  delay(70);

  oled.clearBuffer();

  drawBolt(57, 5);

  oled.sendBuffer();

  delay(300);
}


// =====================================================
// 4. BOLTBUNNY BRAND REVEAL
// =====================================================

void brandReveal()
{
  const char *name = "BOLTBUNNY";

  oled.setFont(u8g2_font_7x13B_tf);

  for (int i = 1; i <= 9; i++)
  {
    oled.clearBuffer();

    // Lightning stays above
    drawBolt(57, 5);

    char text[10];

    for (int j = 0; j < i; j++)
    {
      text[j] = name[j];
    }

    text[i] = '\0';

    centerText(text, 52);

    oled.sendBuffer();

    delay(100);
  }

  delay(500);
}


// =====================================================
// 5. CLEAN GLITCH
// =====================================================

void cleanGlitch()
{
  const int offsets[6] = {
    -2, 2, -1, 1, 0, 0
  };

  for (int frame = 0; frame < 6; frame++)
  {
    oled.clearBuffer();

    oled.setFont(u8g2_font_7x13B_tf);

    int w = oled.getStrWidth("BOLTBUNNY");

    int x = (128 - w) / 2;

    x += offsets[frame];

    oled.drawStr(x, 37, "BOLTBUNNY");

    // Small controlled glitch bars
    if (frame < 5)
    {
      oled.drawBox(
        8 + frame * 5,
        15,
        10,
        2
      );

      oled.drawBox(
        91 - frame * 4,
        46,
        12,
        2
      );
    }

    oled.sendBuffer();

    delay(45);
  }

  delay(250);
}


// =====================================================
// 6. SUBSCRIBE BUTTON
// =====================================================

void subscribeAnimation()
{
  // Slide in
  for (int x = 128; x >= 12; x -= 4)
  {
    oled.clearBuffer();

    oled.drawFrame(
      x,
      20,
      104,
      24
    );

    oled.sendBuffer();

    delay(16);
  }

  // Text
  oled.clearBuffer();

  oled.drawFrame(
    12,
    20,
    104,
    24
  );

  oled.setFont(u8g2_font_7x13B_tf);

  centerText(
    "SUBSCRIBE",
    36
  );

  oled.sendBuffer();

  delay(600);


  // Pulse
  for (int i = 0; i < 4; i++)
  {
    oled.clearBuffer();

    if (i % 2 == 0)
    {
      // Filled button
      oled.drawBox(
        12,
        20,
        104,
        24
      );

      oled.setDrawColor(0);

      oled.setFont(
        u8g2_font_7x13B_tf
      );

      centerText(
        "SUBSCRIBE",
        36
      );

      oled.setDrawColor(1);
    }
    else
    {
      // Outline button
      oled.drawFrame(
        12,
        20,
        104,
        24
      );

      oled.setFont(
        u8g2_font_7x13B_tf
      );

      centerText(
        "SUBSCRIBE",
        36
      );
    }

    oled.sendBuffer();

    delay(140);
  }
}


// =====================================================
// 7. SUBSCRIBED
// =====================================================

void subscribed()
{
  oled.clearBuffer();

  oled.setFont(
    u8g2_font_7x13B_tf
  );

  centerText(
    "SUBSCRIBED",
    20
  );

  // Check mark
  oled.drawLine(
    43, 37,
    51, 45
  );

  oled.drawLine(
    51, 45,
    72, 25
  );

  oled.sendBuffer();

  delay(900);
}


// =====================================================
// 8. NOTIFICATION BELL
// =====================================================

void bellAnimation()
{
  for (int frame = 0; frame < 10; frame++)
  {
    oled.clearBuffer();

    oled.setFont(
      u8g2_font_5x8_tf
    );

    centerText(
      "NOTIFICATIONS",
      10
    );

    // Bell
    oled.drawCircle(
      64,
      29,
      9
    );

    oled.drawBox(
      55,
      29,
      18,
      9
    );

    oled.drawHLine(
      53,
      39,
      22
    );

    // Clapper
    oled.drawDisc(
      64,
      42,
      2
    );

    // Sound waves
    if (frame % 2 == 0)
    {
      oled.drawLine(
        48, 25,
        43, 20
      );

      oled.drawLine(
        80, 25,
        85, 20
      );
    }
    else
    {
      oled.drawLine(
        46, 29,
        40, 29
      );

      oled.drawLine(
        82, 29,
        88, 29
      );
    }

    oled.sendBuffer();

    delay(120);
  }
}


// =====================================================
// 9. LIKE
// =====================================================

void likeAnimation()
{
  oled.clearBuffer();

  oled.setFont(
    u8g2_font_7x13B_tf
  );

  centerText(
    "LIKE",
    23
  );

  oled.setFont(
    u8g2_font_5x8_tf
  );

  centerText(
    "MORE PROJECTS?",
    39
  );

  oled.drawFrame(
    30,
    46,
    68,
    8
  );

  oled.sendBuffer();

  delay(900);


  // Progress bar
  for (int i = 0; i <= 64; i += 4)
  {
    oled.clearBuffer();

    oled.setFont(
      u8g2_font_7x13B_tf
    );

    centerText(
      "LIKE",
      23
    );

    oled.drawFrame(
      30,
      46,
      68,
      8
    );

    if (i > 0)
      oled.drawBox(
        32,
        48,
        i,
        4
      );

    oled.sendBuffer();

    delay(30);
  }

  delay(400);
}


// =====================================================
// 10. SHARE
// =====================================================

void shareAnimation()
{
  oled.clearBuffer();

  oled.setFont(
    u8g2_font_7x13B_tf
  );

  centerText(
    "SHARE",
    20
  );

  // Share nodes
  oled.drawDisc(
    43,
    39,
    3
  );

  oled.drawDisc(
    64,
    29,
    3
  );

  oled.drawDisc(
    85,
    39,
    3
  );

  // Connections
  oled.drawLine(
    46, 38,
    61, 30
  );

  oled.drawLine(
    67, 30,
    82, 38
  );

  oled.sendBuffer();

  delay(800);


  // Moving signal
  for (int x = 46; x <= 82; x += 4)
  {
    oled.clearBuffer();

    oled.setFont(
      u8g2_font_7x13B_tf
    );

    centerText(
      "SHARE",
      20
    );

    oled.drawDisc(
      43,
      39,
      3
    );

    oled.drawDisc(
      64,
      29,
      3
    );

    oled.drawDisc(
      85,
      39,
      3
    );

    oled.drawLine(
      46, 38,
      61, 30
    );

    oled.drawLine(
      67, 30,
      82, 38
    );

    oled.drawDisc(
      x,
      35,
      2
    );

    oled.sendBuffer();

    delay(35);
  }
}


// =====================================================
// 11. PARTICLE BURST
// =====================================================

void particleBurst()
{
  int px[16] = {
    5, 14, 24, 36,
    48, 60, 72, 84,
    96, 108, 120, 18,
    42, 87, 103, 67
  };

  int py[16] = {
    9, 17, 7, 14,
    4, 10, 6, 16,
    8, 13, 5, 53,
    48, 52, 45, 57
  };

  for (int frame = 0; frame < 25; frame++)
  {
    oled.clearBuffer();

    for (int i = 0; i < 16; i++)
    {
      int xx;

      if (i % 2 == 0)
        xx = px[i] - frame;
      else
        xx = px[i] + frame;

      int yy = py[i];

      if (xx >= 0 && xx < 128)
      {
        oled.drawPixel(
          xx,
          yy
        );
      }
    }

    oled.setFont(
      u8g2_font_7x13B_tf
    );

    centerText(
      "BOLTBUNNY",
      36
    );

    oled.sendBuffer();

    delay(30);
  }
}


// =====================================================
// 12. FINAL BOLTBUNNY SCREEN
// =====================================================

void finalScreen()
{
  oled.clearBuffer();

  // Lightning
  drawBolt(
    15,
    17
  );

  oled.setFont(
    u8g2_font_7x13B_tf
  );

  oled.drawStr(
    34,
    37,
    "BOLTBUNNY"
  );

  // Clean underline
  oled.drawHLine(
    20,
    44,
    88
  );

  oled.sendBuffer();

  delay(2000);


  // Small final pulse
  for (int i = 0; i < 3; i++)
  {
    oled.clearBuffer();

    drawBolt(
      15,
      17
    );

    oled.setFont(
      u8g2_font_7x13B_tf
    );

    oled.drawStr(
      34,
      37,
      "BOLTBUNNY"
    );

    oled.drawHLine(
      20,
      44,
      88
    );

    oled.sendBuffer();

    delay(180);

    oled.clearBuffer();

    oled.sendBuffer();

    delay(80);
  }
}


// =====================================================
// SETUP
// =====================================================

void setup()
{
  oled.begin();

  powerOn();

  rainEffect();

  boltReveal();

  brandReveal();

  cleanGlitch();

  subscribeAnimation();

  subscribed();

  bellAnimation();

  likeAnimation();

  shareAnimation();

  particleBurst();

  finalScreen();
}


// =====================================================
// LOOP
// =====================================================

void loop()
{
  powerOn();

  rainEffect();

  boltReveal();

  brandReveal();

  cleanGlitch();

  subscribeAnimation();

  subscribed();

  bellAnimation();

  likeAnimation();

  shareAnimation();

  particleBurst();

  finalScreen();
}