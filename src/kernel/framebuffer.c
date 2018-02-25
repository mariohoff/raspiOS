#include <kernel/framebuffer.h>
#include <kernel/mailbox.h>
#include <kernel/peripheral.h>


typedef struct {
	uint32_t width;
	uint32_t height;
	uint32_t vwidth;
	uint32_t vheight;
	uint32_t bytes;
	uint32_t depth;
	uint32_t x;
	uint32_t y;
	uint32_t * pointer;
	uint32_t size;
} framebuffer_init_t;

framebuffer_init_t fbinit __attribute__((aligned(16)));

int framebuffer_init(void) {
	mail_message_t msg;

	fbinit.width = SCREEN_WIDTH;
	fbinit.height = SCREEN_HEIGHT;
	fbinit.vwidth = SCREEN_WIDTH;
	fbinit.vheight = SCREEN_HEIGHT;
	fbinit.depth = COLORDEPTH;
        fbinit.bytes = 0;
        fbinit.x = 0;
        fbinit.y = 0;
	msg.data = ((uint32_t)&fbinit + 0x40000000) >> 4;

	mailbox_send(msg, FRAMEBUFFER_CHANNEL);
	msg = mailbox_read(FRAMEBUFFER_CHANNEL);

	if (!msg.data)
		return -1;

        fbinfo.width = fbinit.width;
        fbinfo.height = fbinit.height;
        fbinfo.pitch = fbinit.bytes;
        fbinfo.buf = fbinit.pointer;
        fbinfo.buf_size = fbinit.size;
        fbinfo.chars_width = fbinfo.width / CHAR_WIDTH;
        fbinfo.chars_height = fbinfo.height / CHAR_HEIGHT;
        fbinfo.chars_x = 0;
        fbinfo.chars_y = 0;
	return 0;
}
