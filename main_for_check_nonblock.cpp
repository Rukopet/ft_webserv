
#include <sys/event.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <set>
#include <map>
#include <vector>

#include <iostream>
int
main(int argc, char **argv)
{
	struct	kevent tevent;	 /* Event triggered */
	int kq, fd, ret, fd2;

	fd = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	/* Create kqueue. */
	kq = kqueue();
	if (kq	== -1)
		err(EXIT_FAILURE, "kqueue() failed");

	/* Initialize kevent structure. */
	std::set<int> a;
//	std::map<int, std::vector<int>> b;
	std::vector<int> v1;
//	std::cout << v1 << std::endl;

//	struct	kevent *event = new struct kevent[2];
	std::vector<struct kevent> mine;
	struct kevent tmp;
	mine.push_back(tmp);
	mine.push_back(tmp);
//	mine.erase(std::find(mine.begin(), mine.end(), tmp.ident));

	EV_SET(&mine[0],	fd, EVFILT_VNODE, EV_ADD | EV_CLEAR, NOTE_WRITE,
		   0,	NULL);
	EV_SET(&mine[1],	fd2, EVFILT_VNODE, EV_ADD | EV_CLEAR, NOTE_WRITE,
		   0,	NULL);
	/* Attach event to the	kqueue.	*/
	ret = kevent(kq, mine.data(), 2, NULL, 0, NULL);
	if (ret == -1)
		err(EXIT_FAILURE, "kevent register");
//	if (event->flags & EV_ERROR)
//		errx(EXIT_FAILURE,	"Event error: %s", strerror(event[0].data));

	for (;;) {
		/*	Sleep until something happens. */
		ret = kevent(kq, NULL, 0, &tevent,	1, NULL);
		if	(ret ==	-1) {
			err(EXIT_FAILURE, "kevent wait");
		} else if (ret > 0) {
			printf("Something was written in '%s'\n", argv[1]);
		}
	}
}


//int
//main(int argc, char *argv[])
//{
//	struct in_addr addr;
//
//	if (argc != 2) {
//		fprintf(stderr, "%s <dotted-address>\n", argv[0]);
//		exit(EXIT_FAILURE);
//	}
//
//	if (inet_addr(argv[1]) == INADDR_NONE) {
//		fprintf(stderr, "Invalid address\n");
//		exit(EXIT_FAILURE);
//	}
//
//	addr.s_addr = inet_addr(argv[1]);
//	printf("%s\n", inet_ntoa(addr));
//	exit(EXIT_SUCCESS);
//}