
#include <stdint.h>
#include <kernel/input.h>
#include <usbd/usbd.h>
#include <device/hid/keyboard.h>

extern void KeyboardUpdate();
extern char KeyboardGetChar();

static uint32_t* keyb_addr = 0;
static uint16_t keyb_old_down[6];

char keys_normal[] =
{
        0x0, 0x0, 0x0, 0x0, 'a', 'b', 'c', 'd',
        'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
        'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
        'u', 'v', 'w', 'x', 'y', 'z', '1', '2',
        '3', '4', '5', '6', '7', '8', '9', '0',
        '\n', 0x0, '\b', '\t', ' ', '-', '=', '[',
        ']', '\\', '#', ';', '\'', '`', ',', '.',
        '/', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0, '/', '*', '-', '+',
        '\n', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', '0', '.', '\\', 0x0, 0x0, '='
};

char keys_shift[] =
{
        0x0, 0x0, 0x0, 0x0, 'A', 'B', 'C', 'D',
        'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
        'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
        'U', 'V', 'W', 'X', 'Y', 'Z', '!', '\"',
        '§', '$', '%', '&', '/', '(', ')', '=',
        '\n', 0x0, '\b', '\t', ' ', '-', '=', '[',
        ']', '\\', '#', ';', '\'', '`', ',', '.',
        '/', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0, '/', '*', '-', '+',
        '\n', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', '0', '.', '\\', 0x0, 0x0, '='
};

void keyboard_init(void) 
{
        int i;
        UsbInitialise();
        for(i = 0; i < 6; i++)
                keyb_old_down[i] = 0;
}

void keyboard_update(void)
{
        KeyboardUpdate();
        /*int keyb_count, key_down_count = 0;
        int i;

        UsbCheckForChange();
        keyb_count = KeyboardCount();
        if(keyb_count == 0) {
                keyb_addr = (uint32_t *) 0;
                return;
        } else {
                int i;
                for(i = 0; i < 6; i++) {
                        keyb_old_down[i] = KeyboardGetKeyDown(keyb_addr, i);
                }
        }
       
        keyb_count = KeyboardCount(); 
        for(i=0; i < keyb_count; i++) {
                keyb_addr = (uint32_t *) KeyboardGetAddress(i);
                key_down_count =  KeyboardGetKeyDownCount(keyb_addr);
        }*/
}

char keyboard_getchar(void)
{
        return KeyboardGetChar();
        /*int index = 0;
        for(index = 0; index < 6; index++) {
                char key = KeyboardGetKeyDown( keyb_addr, index);
                if(key > 0 && key <= 104) {
                        return keys_normal[key];
                }
        }

        if(keyb_addr == 0)
                return 0;

        int is_down = 0;
        for(index = 0; index < 6; index++) {
                is_down = KeyboardGetKeyDown((uint32_t) keyb_addr, index);
                if(is_down == 0) {
                        keyb_old_down[index] = is_down;
                        continue;
                }
                if(keyb_old_down[index] == is_down) { //key was already down
                        continue;
                }

                if(is_down > 104) //char out of range
                        continue;

                struct KeyboardModifiers mod = KeyboardGetModifiers(keyb_addr); // get modfiers
                if((mod.LeftShift == 0) && (mod.RightShift == 0)) {
                        key = keys_normal[is_down];
                } else {
                        key = keys_shift[is_down];
                }

                if(key != 0) {
                        return key;
                }
        }
        return 0;*/
}
