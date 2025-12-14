#include "CustomButton.h"

// Konstruktor: parameter pin dan durasi long press (default 5000 ms) (pin, durasi long press dalam ms)
CustomButton::CustomButton(uint8_t pin, unsigned long longPressDuration)
    : _pin(pin),
      _longPressDuration(longPressDuration),
      _pressStartTime(0),
      _isPressed(false),
      _actionTriggered(false),
      _callback(nullptr),
      _shortPressCallback(nullptr) // Tambah ini!
{
}


void CustomButton::begin()
{
    // Asumsikan tombol aktif LOW (gunakan pull-up internal)
    pinMode(_pin, INPUT_PULLUP);
}

void CustomButton::setLongPressCallback(ButtonCallback callback)
{
    _callback = callback;
}

void CustomButton::setLongPressCallbackDefault()
{
    _callback = CustomButton::onLongPressDefault;
}

void CustomButton::setShortPressCallback(ButtonCallback callback)
{
    _shortPressCallback = callback;
}

void CustomButton::update() {
    bool currentState = !digitalRead(_pin); // Tombol aktif LOW
    if (currentState && !_isPressed) {
        _isPressed = true;
        _pressStartTime = millis();
    } else if (!currentState && _isPressed) {
        _isPressed = false;
        unsigned long pressDuration = millis() - _pressStartTime;

        Serial.print("[DEBUG] Button released after "); 
        Serial.print(pressDuration);
        Serial.println(" ms");

        if (pressDuration < _longPressDuration) { // Short press
            Serial.println("[DEBUG] Calling short press callback...");
            if (_shortPressCallback) {
                Serial.println("[DEBUG] Callback function found, executing now!");
                _shortPressCallback();
            } else {
                Serial.println("[ERROR] No short press callback set!");
            }
        }
    }
}

void CustomButton::buttonTask()
{
    // Fungsi non-static member task yang dipanggil oleh wrapper
    while (1)
    {
        update();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

// Callback yang akan dipanggil ketika tombol ditekan selama 5 detik
void CustomButton::onLongPressDefault()
{
    Serial.println("Tombol boot ditekan selama 5 detik!");
    // Tambahkan aksi yang diinginkan, misalnya masuk mode AP atau reset konfigurasi.
}

void CustomButton::buttonTaskWrapper(void *pvParameters)
{
    // Cast pvParameters ke objek CustomButton
    CustomButton *self = static_cast<CustomButton *>(pvParameters);
    self->buttonTask();
}