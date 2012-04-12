#ifndef _WIN_ERR_H_
#	define _WIN_ERR_H_

void
errx(int, const char *, ...);

/* Go fix that to use errno. */
void
err(int, const char *, ...);

#endif /* _WIN_ERR_H_ */