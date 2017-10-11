#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "zhelpers.h"
#include "app.h"

int main (int argc, char *argv[])
{
    if ((argc < 3)) {
        printf("You need to provide 2 args (usage: %s frontendAddress backendAddress, e.g. tcp://*:5030 tcp://*:5031)\n", argv[0]);
        exit(1);
    }

    void *context = newContext();
    //  Socket facing clients

    printf("frontend address provided = %s\n", argv[1]);
    printf("backend address provided = %s\n", argv[2]);

    void *frontend = frontendSocket(context);
    printf("bind frontend socket\n");
    int rc = bindSocket(frontend, argv[1]);
    assert(rc == 0);

    //  Socket facing services
    void *backend = backendSocket(context);
    printf("bind backend socket\n");
    rc = bindSocket(backend, argv[2]);
    assert(rc == 0);

    //  Start the proxy
    printf("start zmq proxy\n");
    zmq_proxy (frontend, backend, NULL);

    //  We never get here…
    closeSocket (frontend);
    closeSocket (backend);
    destroyContext (context);
    printf("zmq broker is exiting\n");
    return 0;
}

