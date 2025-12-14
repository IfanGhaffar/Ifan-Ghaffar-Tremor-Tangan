#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <math.h>

// Definisi pin untuk koneksi SPI ke layar GC9307
#define TFT_MOSI 35
#define TFT_SCLK 36
#define TFT_CS   40
#define TFT_DC   41
#define TFT_RST  42
#define TFT_BL   38

// Definisi ukuran layar
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 170

#define I2C_SDA 9            // Pin SDA untuk ESP32 S3 Master
#define I2C_SCL 46           // Pin SCL untuk ESP32 S3 Master
#define I2C_SLAVE_ADDR 0x08  // Alamat I2C Slave

// Inisialisasi komunikasi SPI dengan layar GC9307 menggunakan Arduino_GFX
Arduino_DataBus *bus = new Arduino_ESP32SPI(11 /* DC */, 10 /* CS */, 12 /* SCK */, 13 /* MOSI */, GFX_NOT_DEFINED /* MISO */);
Arduino_GFX *gfx = new Arduino_GC9A01(bus, 1 /* RST */, 1 /* rotation */, true /* IPS */, SCREEN_HEIGHT, SCREEN_WIDTH, 35 /* col offset 1 */, 0 /* row offset 1 */, 35 /* col offset 2 */, 0 /* row offset 2 */);

void setup() 
{
  Wire.begin(I2C_SDA, I2C_SCL);  // Inisialisasi I2C sebagai master
  Serial.begin(115200);

  // Inisialisasi LCD
  gfx->begin();
  gfx->fillScreen(BLACK);
  gfx->setCursor(10, 10);
  gfx->setTextColor(WHITE);
  gfx->setTextSize(2);
  gfx->invertDisplay(true);
  gfx->setRotation(3);


  // Set backlight LCD
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);  // Aktifkan backlight

  // // Tampilkan judul dan garis pemisah
  // gfx->setCursor(10, 10);
  // gfx->println("Data Counter dari Slave");
  // gfx->drawLine(10, 35, 310, 35, WHITE);  // Garis pemisah
}

void loop() 
{
  Wire.requestFrom(I2C_SLAVE_ADDR, 2);  // Minta 2 byte dari slave

  if (Wire.available() >= 2) {          // Cek apakah ada 2 byte data
      int receivedData = (Wire.read() << 8) | Wire.read();  // Gabungkan byte tinggi dan rendah
      Serial.print("Data diterima dari slave: ");
      Serial.println(receivedData);     // Tampilkan data ke Serial Monitor

      // Tampilkan data ke LCD
      gfx->fillRect(10, 40, 220, 30, BLACK);  // Hapus teks lama
      gfx->setCursor(10, 40);
      gfx->print("Data: ");
      gfx->println(receivedData);
  } else {
      Serial.println("Gagal menerima data!");
  }

  delay(1000);  // Minta data setiap 1 detik
}
