
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
    
    /* Bifurcar o processo pai */
    pid = fork();
    
    /* Em caso de erro */
    if (pid < 0)
        exit(EXIT_FAILURE);
    
     /* Em caso de sucesso, deixe o processo pai encerrar */
    if (pid > 0)
        exit(EXIT_SUCCESS);
    
    /* Em caso de sucesso, o processo filho vira o lider de sessao */
    if (setsid() < 0)
        exit(EXIT_FAILURE);
    
    /* Catch, ignore and handle signals */
    /*TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
    
    /* Bifurcar de novo*/
    pid = fork();
    
    /* Em caso de erro */
    if (pid < 0)
        exit(EXIT_FAILURE);
    
    /* Em caso de sucesso, deixe o processo pai encerrar */
    if (pid > 0)
        exit(EXIT_SUCCESS);
    
    /* Permissoes do arquivo */
    umask(774);
    
    /* Importante: mudar o diretorio para um diretorio de trabalho */
    /* uo algum outro diretorio apropriado  */
    chdir("/home/aluno/emmanuel_mindsun");
    
    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
    {
        close (x);
    }
    
    // Abrir os logs antes do loop
    openlog ("Daemon_Mindsun", LOG_PID, LOG_DAEMON);
}


int main()
{

    skeleton_daemon();
    
    while (1)
    {

//printf("%c",'\a'); comando pra mandar beep
    if(system("ping -c 4 www.google.com 1> /dev/null")){
    syslog (LOG_NOTICE, "There is no internet connection.");
        int condicao1 = 1;
            while(condicao1) {
                sleep (30);
                if(system("ping -c 4 www.google.com 1> /dev/null")){
                    syslog (LOG_WARNING, "There is no internet connection.");
                                                                    }
                else{
                    condicao1 = 0;
                    syslog (LOG_NOTICE, "Internet connection is up again, restarting program.");
    //system("./executavel_a_ser_reiniciado");
                    }

                            }
}else {
    syslog (LOG_NOTICE, "Ping sucessful.");      

     }

//timeout no windows, sleep no linux
// /nobreak no timeout faz com que nao de  pra apertar tecla pra continuar.

sleep(30);



    }
   
    syslog (LOG_NOTICE, "Daemon_Mindsun encerrado.");
    closelog();
    
    return EXIT_SUCCESS;
}

