# mexkbstop
Use "CTRL + D" to stop your mexfunction. Returns a "1"/bool true if the combination was pressed during execution of c functions in MATLAB.

The .m function used to find the pressed combination is from another repo on github - unlocbox/utils/kbstop.m

The kbstopwrapper.m provides a usable value to the mex - c-function in which you want to test the combination. It is maybe not the cleanest or best solution.
