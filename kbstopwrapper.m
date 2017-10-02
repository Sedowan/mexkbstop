% get the result of the kbstop.m into a value which is readable by the c-function mexkbstop.c

function int = kbstopwrapper(cmd)
    if nargin == 0
        cmd = 'test';
    end
    int = 0;
    bool = kbstop(cmd);
    
    if bool == 1
        int = 1;
    else
        int = 0;
    end
    
end
