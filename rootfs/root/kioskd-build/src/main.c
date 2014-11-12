#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include "kioskd.h"

const unsigned short DEFAULT_SERVER_PORT = 24054;
const double DEFAULT_RENDER_INTERVAL = 1.0/25.0;

void run_kioskd(unsigned short server_port, double render_interval) {
    Kioskd* kioskd = InitKioskd(server_port, render_interval);
    
    RunKioskd(kioskd);
    
    DestroyKioskd(kioskd);
    kioskd = NULL;
}


int main(int argc, char** argv) {
    
    int make_daemon = 0;
    double render_interval = DEFAULT_RENDER_INTERVAL;
    unsigned short server_port = DEFAULT_SERVER_PORT;
    
    // first set our options from cmdline
    struct option options[] = {
        { "daemon", 0, NULL, 'd' },
        { "port", 1, NULL, 'p' },
        { "render-interval", 1, NULL, 'i' },
    };
    
    int c;
    while(1) {
        int option_index = 0;
        
        c = getopt_long(argc, argv, "dp:", options, &option_index);
        
        if(c == -1) { break; }
        
        switch(c) {
            
            case 0:
                // long-only args with option, we don't have those
                break;
            
            case 'd':
                make_daemon = 1;
                break;
                
            case 'p':
                server_port = (unsigned short) atoi(optarg);
                break;
                
            case 'i':
                render_interval =  atof(optarg);
                
            case '?':
                break;
                
            default:
                abort();
                break;
        }
                    
    }
    
    
    // possibly make it a daemon
    if(make_daemon) {
        if(daemon(0, 0) != 0) {
            fprintf(stderr, "%s", "Could not make daemon!");
            abort();
        }
    }   
    
    
    run_kioskd(server_port, render_interval);
    
    return 0;
}