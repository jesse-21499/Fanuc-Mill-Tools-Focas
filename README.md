# FanucMillTools
Small utility to get and set parameters,tools and workpiece offsets to Fanuc CNC via Ethernet. Tested with controls series 30i-31i (MAX_AXIS=32).
Fwlib64.dll and fwlibe64.dll must be copied in the same path as executable.
It's recommended to introduce a maximum range of 5000 parameters to avoid excessive execution time.
Additions:
NC File Download to CNC with option to correct flatness deviation on 2D Contour operations (Preliminar). Samples provided in separate folder.
