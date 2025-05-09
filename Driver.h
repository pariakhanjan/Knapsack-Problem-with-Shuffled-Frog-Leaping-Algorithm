#include "systemc.h"
#include "FrogLeapingController.h"

SC_MODULE(Driver) {
    sc_out<bool> start; 
    sc_in<bool> Clk;

    void StimGen() {
        start.write(false); 
        wait();
        start.write(true);
        wait(); 
        start.write(false);
        wait();
        sc_stop();
    }

    SC_CTOR(Driver) {
        SC_THREAD(StimGen);
        sensitive << Clk.pos();
    }
};