#ifndef __unp_h
#define __unp_h
//#include "../lib/config.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<time.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<fcntl.h>
#include<netdb.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/uio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/un.h>
#endif
#ifdef HAVE_SYS_SELECT_H
#include<sys/select.h>
#endif
#ifdef HAVE_SYS_SYSCTL_H
#include<sys/sysctl.h>
#endif
#ifdef HAVE_POLL_H
#include<poll.h>
#endif
#ifdef HAVE_SYS_EVENT_H
#include<sys/event.h>
#endif
#ifdef HAVE_STRINGS_H
#include<strings.h>
#endif
#ifdef HAVE_SYS_IOCTL_H
#endif
#ifdef HAVE_SYS_FILEIO_H
#include<sys/fileio.h>
#endif
#ifdef HAVE_SYS_SOCKIO_H
#include<sys/sockio.h>
#endif
#ifdef HAVE_PTHREAD_H
#include<pthread.h>
#endif
#ifdef HAVE_NETIF_DEL_H
#include<net/if_dl.h>
#endif
#ifdef HAVE_NETINET_SCTP_H
#include<netinet/sctp.h>
#endif
#ifdef __osf__
#undef recv
#undef send
#define recv(a,b,c,d) recvfrom(a,b,c,d,0,0)
#define recv(a,b,c,d) recvfrom(a,b,c,d,0,0)
#endif
#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff
#endif
#ifndef SHUT_RD
#define SHUT_RD 0
#define SHUT_WR 1
#define SHUT_RDWR 2
#endif
#ifndef INET_ADDRSTRLEN
#define INET_ADDRSTRLEN 16
#endif
#ifndef INET6_ADDRLEN
#define INET6_ADDRLEN 46
#endif
#ifndef HAVE_BZERO
#define bzero(ptr,n) memset(ptr,0,n)
#endif
#ifndef HAVE_GETHOSTBYNAME2
#define gethostbyname2(host,family) gethostbyname((host))
#endif
struct unp_in_pktinfo{
	struct in_addr ipi_addr;
	int ipi_ifindex;
};
#ifndef CMSG_LEN
#define CMSGLEN(size) (sizeof(struct cmsghdr) + (size))
#endif
#ifndef CMSG_SPACE
#define CMSG_SPACE(size) (sizeof(struct cmsghdr) + (size))
#endif
#ifndef SUN_LEN
#define SUN_LEN(su) \
	(sizeof(*(su)) - sizeof((su)->sun_path) + strlen((su)->sun_path))
#endif
#ifndef AF_LOCAL
#define AF_LOCAL AF_UNIX
#endif
#ifndef PF_LOCAL
#define PF_LOCAL PF_UNIX
#endif
#ifndef INFTIM
#define INFTIM (-1)
#ifndef HAVE_POLL_H
#define INFTIM_UNPH
#endif
#endif
#define LISTENQ 1024
#define MAXLINE 4096
#define BUFFSIZE 8192
#define SERV_PORT 9877
#define SERV_PORT_STR "9877"
#define UNIXSTR_PATH "/tmp/unix.str"
#define UNIXDG_PATH "/tmp/unix.dg"
#define SA struct sockaddr
#define HAVE_STRUCT_SOCKADDR_STORAGE
#ifndef HAVE_STRUCT_SOCKADDR_STORAGE
#define __SS_MAXSIZE 128
#define __SS_ALIGNSIZE (sizeof(int64_t))
#ifdef HAVE_SOCKADDR_SA_LEN
#define __SS_PAD1SIZE (__SS_ALIGNSIZE - sizeof(u_char) - sizeof(sa_family_t))
#else
#define __SS_PAD1SIZE (__SS_ALIGNSIZE - sizeof(sa_family_t))
#endif
#define __SS_PAD2SIZE (__SS_MAXSIZE - 2*__SS_ALIGNSIZE)
struct sockaddr_storage {
	#ifdef HAVE_SOCKADDR_SA_LEN
		u_char ss_len;
	#endif
		sa_family_t ss_family;
		char __ss_pad1[__SS_PAD1SIZE];
		int64_t __ss_align;
		char __ss_pad2[__SS_PAD2SIZE];
};
#endif
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)
typedef void Sigfunc (int);
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
#ifndef HAVE_ADDRINFO_STRUCT
//#include "../lib/addrinfo.h"
#endif
#ifndef HAVE_IF_NAMEINDEX_STRUCT
struct if_nameindex {
	unsigned int if_index;
	char *if_name;
};
#endif
/*
#ifndef HAVE_TIMESPEC_STRUCT
struct timespec{
	time_t tv_sec;
	long tv_nsec;
};
#endif*/
