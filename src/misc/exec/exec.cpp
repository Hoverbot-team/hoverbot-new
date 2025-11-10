#include "misc/exec/exec.hpp"

int exec::command(const char* cmd) {
    int a = system(cmd);
    if(a != 0){
        throw a;
    }
    return a;
}
