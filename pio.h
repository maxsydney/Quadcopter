#define BIT(X) (1 << (X))

typedef enum pio_state_enum
{
    PIO_HIGH=1,
    PIO_LOW
} pio_state;

void toggle_pin(uint8_t pin);