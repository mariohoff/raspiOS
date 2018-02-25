#include <stdint.h>
#include "peripheral.h"

#ifndef MAILBOX_H
#define MAILBOX_H

#define MAILBOX_BASE PERIPHERAL_BASE + MAILBOX_OFFSET
#define MAIL0_READ (((mail_message_t *)(0x00 + MAILBOX_BASE)))
#define MAIL0_STATUS (((mail_status_t *)(0x18 + MAILBOX_BASE)))
#define MAIL0_WRITE (((mail_message_t *)(0x20 + MAILBOX_BASE)))
#define PROPERTY_CHANNEL 8
#define FRAMEBUFFER_CHANNEL 1

typedef struct {
    uint8_t channel: 4;
    uint32_t data: 28;
} mail_message_t;

typedef struct {
    uint32_t reserved: 30;
    uint8_t empty: 1;
    uint8_t full:1;
} mail_status_t;

mail_message_t mailbox_read(int channel);
void mailbox_send(mail_message_t msg, int channel);

#endif
