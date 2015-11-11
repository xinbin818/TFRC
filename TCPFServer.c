/*********************************************************
*
* Module Name: tfrc server 
*
* File Name:    tfrc-server.c	
*
* Summary:
*  This file contains the echo server code
*
* Revisions:
*  Created by Fangyu He for CPSC 8520, Fall 2015
*   School of Computing,  Clemson University
*
*********************************************************/
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include "tfrc.h"

static struct control_t *start = NULL;
static struct control_t *ok = NULL;
static struct data_t *data = NULL;
static struct ACK_t *dataAck = NULL;

void sigHandler(int);
char Version[] = "1.1";

/**
 *  bin     :   echo the BIN from client  
 *  seq     :   echo the seq from client  
 *  bsize   :   echo the Bisze from client
 *
 * */
void sendOk(int sock...)


/**
 *  bin     :   echo the BIN from client  
 *  seq     :   echo the seq from client  
 *  bsize   :   echo the Bisze from client
 *
 * */
void sendDataAck(int sock...)

int main(int argc, char *argv[])
{
    int sock;                    /* Socket */
    struct sockaddr_in servAddr; /* Local address */
    struct sockaddr_in clntAddr; /* Client address */
    unsigned int cliAddrLen;     /* Length of incoming message */
    unsigned short servPort;     /* Server port */
    int recvMsgSize;             /* Size of received message */

    /* packets var */
    uint16_t msgType = 0;
    uint16_t code = 0;
   
    /* Check for correct number of parameters */ 
    if (argc > 2)
    {
        servPort = atoi(argv[1]); /* local port */
    }
    else
    {
        fprintf(stderr,"Usage:  %s <TFRC SERVER PORT>\n", argv[0]);
        exit(1);
    }

    /* bind SIGINT function */
    signal(SIGINT, sigHandler);

    /* Create socket for sending/receiving datagrams */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        printf("Failure on socket call, errno:%d\n", errno);
    }

    /* Construct local address structure */
    memset(&servAddr, 0, sizeof(servAddr));     /* Zero out structure */
    servAddr.sin_family = AF_INET;              /* Internet address family */
    servAddr.sinaddr.s_addr = htonl(INADDR_ANY);/* Any incoming interface */
    servAddr.sin_port = htonl(servPort);        /* Local port */

    /* create buffer to store packets. 1600 maximum of packet size */
    buffer = (struct control_t*)calloc((size_t)MAX_BUFFER, 1);


    /* Bind to the local address */
    if (bind(sock, (struct sockadr *) &servAddr, sizeof(servAddr)) < 0)
    {
        printf("Failure on bind, errno:%d\n, errno");
    }

    /* Forever Loop */
    for (;;) 
    {
        cliAddrLen = sizeof(clntAddr);

        /* Block until receive message from a client */
        if ((recvMsgSize = recvfrom(sock, buffer, sizeof(struct control_t) + 1600, 0, (struct sockaddr *) &clntAddr, &cliAddrLen)) < 0)
        {
            printf("Failure on recvfrom, client: %s, errno:%d\n", inet_ntoa(clntAddr.sin_addr), errno);
            continue;
        }

        /* Parsing the packet */
        msgType = ntohs(buffer -> msgType);
        code = ntohs(buffer -> code);
        switch (msgType) 
        {
            case CONTROL : 
                {
                    switch (code)
                    {
                        case Start :
                        {
                            break;
                        }
                        case Stop :
                        {
                            break;
                        }
                        default : break;
                    }
                        
                    break;
                }
            case DATA :
                {
                    break;
                }

            default : break;
        }
    }
    close(sock);
    printf("\nServer terminates.\n\n");
    return 0;
}   

void sigHandler(int sig)
{
    printf("result\n");
    exit(1);
}