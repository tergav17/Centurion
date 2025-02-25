#include <inttypes.h>

#define MUX0_BASE 0xf200
#define NUM_MUX_UNITS 4

struct MuxUnit
{
        int in_fd;
        int out_fd;
	char mode;
        unsigned char status;
        unsigned char lastc;
        int baud;
        unsigned char tx_done;
        int64_t rx_ready_time;
        int64_t tx_done_time;
};

/* Status register bits */
#define MUX_RX_READY   (1 << 0)
#define MUX_TX_READY   (1 << 1)
#define MUX_PARITY_ERR (1 << 2)
#define MUX_FRAME_ERR  (1 << 3)
#define MUX_OVERRUN    (1 << 4)
#define MUX_CTS        (1 << 5)

/* Interrupt status register bits */
#define MUX_IRQ_RX 0
#define MUX_IRQ_TX 1
#define MUX_UNIT_MASK 0x06

void mux_init(void);
void mux_attach(unsigned unit, char mode, int in_fd, int out_fd);
void mux_poll(unsigned trace);

void mux_write(uint16_t addr, uint8_t val, uint32_t trace);
uint8_t mux_read(uint16_t addr, uint32_t trace);

void mux_set_read_ready(unsigned unit, unsigned trace);
int mux_get_in_poll_fd(unsigned unit);
int mux_get_in_fd(unsigned unit);

void mux_poll_fds(unsigned trace);
