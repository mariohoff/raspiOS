## RaspiOS

Here I try to build my own operating system for a raspberry pi Model B+
I am not really sure where the road will go from here and maybe I will start
adding support for the Raspi2 and above (which should only be a different
mailbox if I read that correctly).

### What works for now:

- Booting
- Initialize and set GPIO 
- basic screen output (pixel and line drawing)
- string output

### ToDo:

- a lot!

### What's documented for now?

Nothing, but I will try to catch up sometime.

### Links and tutorials

For me everything started with this tutorial from cambridge:
http://www.cl.cam.ac.uk/projects/raspberrypi/tutorials/os/

I have to admit that I don't really like writing assembly and so I started to
port everything to C now. What helped me with that is:

The kernel skeleton from osdev
https://wiki.osdev.org/Raspberry_Pi_Bare_Bones

and just lateley another tutorial which i really appreciate!
https://jsandler18.github.io/
https://github.com/jsandler18/raspi-kernel


