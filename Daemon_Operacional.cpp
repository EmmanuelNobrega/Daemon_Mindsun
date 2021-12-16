
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
   
static void skeleton_daemon()
{
    pid_t pid;
    
    /* Fork off the parent process */
    pid = fork();
    
    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);
    
     /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);
    
    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);
    
    /* Catch, ignore and handle signals */
    /*TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
    
    /* Fork off for the second time*/
    pid = fork();
    
    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);
    
    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);
    
    /* Set new file permissions */
    umask(774);
    
    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/home/emmanuel");
    
    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
    {
        close (x);
    }
    
    /* Open the log file */
    openlog ("executar_script_como_backup_daemon", LOG_PID, LOG_DAEMON);
}


int main()
{

    skeleton_daemon();
    
    while (1)
    {

//printf("%c",'\a'); comando pra mandar beep
    if(system("ping -c 4 www.google.com 1> /dev/null")){
    syslog (LOG_NOTICE, "There is no internet connection");
int condicao1 = 1;
        while(condicao1) {
            if(system("ping -c 4 www.google.com 1> /dev/null")){
    syslog (LOG_NOTICE, "There is no internet connection");
}
            else {
                condicao1 = 0;
    syslog (LOG_NOTICE, "Internet connection is up again, restarting program.");
//system("./executavel_a_ser_reiniciado");


}
sleep (30);
}
}else {
//        cout<<"There is internet connection  \n";

}

//timeout no windows, sleep no linux
// /nobreak no timeout faz com que nao de  pra apertar tecla pra continuar.

sleep(30);



    }
   
    syslog (LOG_NOTICE, "executar_script_como_backup_daemon terminated.");
    closelog();
    
    return EXIT_SUCCESS;
}

