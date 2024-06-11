# include <stdio.h>
# include <stdlib.h>

# include "sh/prompt.h"
# include "sh/common.h"
# include "sh/logger.h"
# include "sh/login.h" 
# include "sh/cmd.h"
# include "sh/sighandler.c"


int main(int argc, char* argv[]) {

    // TODO: user login

    welcome();
    user_menu();

    char cmd_buf[MAX_CMD_LEN];
    envt.tot=0;
    
    while (1) {
        print_prompt();
        scan_cmd(cmd_buf);
        exec_cmd(cmd_buf);
    }
    
    exit(0);
}