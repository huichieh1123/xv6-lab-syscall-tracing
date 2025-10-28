#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: strace [program] [args...]\n");
        exit(1);
    }
    int pid = fork();
    if (pid < 0) {
        printf("strace: fork failed\n");
        exit(1);
    }
    if (pid > 0) {
        trace(pid);
        wait(0);
    } else {
        // child: exec the target program
        char *args[argc];
        for (int i = 1; i < argc; i++)
            args[i-1] = argv[i];
        args[argc-1] = 0;
        exec(argv[1], args);
        // exec failed
        printf("strace: exec %s failed\n", argv[1]);
        exit(1);
    }

    return 0;
}
