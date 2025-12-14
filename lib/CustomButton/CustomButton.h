#ifndef CUSTOM_BUTTON_H
#define CUSTOM_BUTTON_H

#include <Arduino.h>

class CustomButton
{
public:
    // Tipe function pointer untuk callback
    typedef void (*ButtonCallback)(void);

    // Konstruktor: parameter pin dan durasi long press (default 5000 ms)
    CustomButton(uint8_t pin, unsigned long longPressDuration = 5000);

    // Inisialisasi pin tombol (misalnya, INPUT_PULLUP)
    void begin();

    // Fungsi update yang harus dipanggil secara periodik
    void update();

    // Set callback yang akan terpanggil ketika tombol ditekan lama
    void setLongPressCallback(ButtonCallback callback);
    void setLongPressCallbackDefault();

    // Callback baru untuk short press
    void setShortPressCallback(ButtonCallback callback);  // Tambah ini!

    // Method task yang dipanggil oleh wrapper
    void buttonTask();

    static void onLongPressDefault();

    // Wrapper static untuk task RTOS
    static void buttonTaskWrapper(void *pvParameters);

private:
    uint8_t _pin;
    unsigned long _longPressDuration; // Durasi long press (ms)
    unsigned long _pressStartTime;    // Waktu tombol mulai ditekan
    bool _isPressed;                  // Status tombol ditekan
    bool _actionTriggered;            // Flag untuk memastikan callback hanya terpanggil sekali per penekanan
    ButtonCallback _callback;         // Callback function
    ButtonCallback _shortPressCallback;  // Tambah ini!
};

#endif // CUSTOM_BUTTON_H
