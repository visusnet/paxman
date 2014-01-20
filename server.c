#include <SDL/SDL_net.h>
#include "server.h"

int main (int argc, char **argv)
{
	TCPsocket sockfd, serverfd;
	IPaddress ip;
	SDLNet_SocketSet set;
	
	if (SDL_Init(0)==-1) 
	{
		printf("SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}	
	
	if(SDLNet_ResolveHost(&ip,NULL,9999)==-1) 
	{
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(1);
	}

	tcpsock=SDLNet_TCP_Open(&ip);
	if(!tcpsock) 
	{
		printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(2);
	}
	
	set=SDLNet_AllocSocketSet(16);
	if(!set) 
	{
		printf("SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
		exit(1); //most of the time this is a major error, but do what you want.
	}
	
	while (1)
	{
		sockfd = SDLNET_TCP_Accept (serverfd);
	}
	
	return 0;
}
