#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)exit.c	5.2 (Berkeley) %G%";
#endif LIBC_SCCS and not lint

exit(code)
	int code;
{

	_cleanup();
	_exit(code);
}
