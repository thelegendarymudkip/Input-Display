---SNES Input Viewer v1.1.4---
-Created by TheLegendaryMudkip-

SNES Input Viewer is a program that allows you to visualize the input from a SNES controller on your monitor.
There are a few things you need to keep in mind, however.

-Limitations-
Currently this program only has support for SNES controllers, but that may change in the future.

I do not know if it supports every kind of SNES controller that can be plugged in. If it doesn't work, let me know. Details
of the kind of SNES controller you are using would be helpful. An PM on twitch should suffice, but fell free to try and
contact me in other ways if you cannot get hold of me there.

You need to have your controller plugged in to a port from port 0 to port 7, whichever you specified in the settings file.

-Settings Format-
The first line is the Red value of the background, which ranges from 0 to 255. The second line is the Green value of the background,
, the third line is the Blue value of the background, and the last line is the controller port. Don't bother trying to overflow the colour data, a bitwise and
operation with 255 (equivalent to a mod 256 operation) is performed on the RGB, values from the file, and a bitwise & operation
with 7 (equivalent to a mod 8 operation) is performed on the controller port.