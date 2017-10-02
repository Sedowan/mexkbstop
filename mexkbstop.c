/* mexkbstop.c
 *
 * The functions used in mexkbstop.c are there to initiate the listening (init_mexkbstop), automatically recognize the combination of "CTRL + D" beeing pressed and giving back a "true/1" if asked (mexkbstop). The function closes by using stop_mexkbstop.
 *
 * (Thank you) The function and functionalaty is inspirated by Nathanael Perraudin using his function kbstop.m on github:
 * https://github.com/epfl-lts2/unlocbox/blob/master/utils/kbstop.m    (you need to download this function from the repo there)
 *
 * (Thank you) The inital implimentation is referred to Amanda Ng on matlabcentral:
 * https://de.mathworks.com/matlabcentral/fileexchange/30622-non-wait-detection-of-keyboard-input--including-mex-implementation-?focused=5178714&tab=overview
 * 
 * 
 * See the mexkbstop_Demo.c below:
   
   
    #include "mex.h"
    #include "time.h"
    #include "mexKbstop.c"

    void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
    {
        
        
        clock_t t;
        bool k;
    
        if (init_mexKbstop()) {
            return;
        } else {
            k = init_mexKbstop();
        }
    
    
        t = clock();
        int i = 0;
        mexPrintf("Wait 5 seconds ...\n");
        mexEvalString("drawnow");
    
        k = mexKbstop();
    
        while ((clock()-t)/CLOCKS_PER_SEC < 5) {  
            k = mexKbstop();
            i++;
            mexPrintf("timestamp: %d\n", i);
            if (k == 1) {
                mexPrintf("Interrupted by Ctrl+d!\n");
                break;
            }
        
        }
    
        stop_mexKbstop();
    
    }
 
 * 
 * To compile the files use mex -v mexkbstop_Demo.c
 * 
 */


#include "mex.h"
#include "time.h"

bool init_mexKbstop(void) {
    mxArray *parIn, *parOut;
    parIn = mxCreateString("init");
    mexCallMATLAB(1, &parOut, 1, &parIn, "kbstopwrapper");
    
    return *mxGetPr(parOut);
}

bool stop_mexKbstop(void) {
    mxArray *par;
    // flush any previous calls to kbhit, otherwise may quit while retrieving key data */
    mexEvalString("drawnow");
    mxArray *parOut;
    par = mxCreateString("stop");
    mexCallMATLAB(1, &parOut, 1, &par, "kbstopwrapper");
    
    return *mxGetPr(parOut);
}

bool mexKbstop(void) {
    mxArray *par;
    mxArray *parOut;
    mexCallMATLAB(1, &parOut, 0, 0, "kbstopwrapper"); // --> try to give back a string
    return *mxGetPr(parOut);
}
