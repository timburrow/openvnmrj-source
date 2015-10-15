/*
 * Copyright (C) 2015  University of Oregon
 *
 * You may distribute under the terms of either the GNU General Public
 * License or the Apache License, as specified in the LICENSE file.
 *
 * For more information, see the LICENSE file.
 */
/* 
*/

#include <stdio.h>
#include <sys/file.h>
#include <fcntl.h>

/*--------------------------------------------------------------------------
| lockfile(name)
| This function addes the '.lock' to name passed and attempts to
| exclusively create it. 
|				Author:  Greg Brissey 1/28/88
|				Modified for enter    2/20/90
+--------------------------------------------------------------------------*/
lockfile(lockfile)
char	*lockfile;
{
char	lock[1024];
int	lockfd,iter;
   strcpy(lock,lockfile);
   strcat(lock,".lock");
/*  Use the O_EXCL bit to insure exclusive access.  */
   lockfd = open( lock, O_CREAT | O_EXCL, 0666 );
   if (lockfd >= 0) 
   {  close(lockfd);
      return( 0 );               /* Got it */
   }
   return(1);
}
/*--------------------------------------------------------------------------
| unlockfile(name)
| This function removes the '.lock' file generated by lockfile().
|				Author:  Greg Brissey 1/28/88
+--------------------------------------------------------------------------*/
unlockfile(lockfile)
char	*lockfile;
{
char	lock[1024];
int	iter;
   strcpy(lock,lockfile);
   strcat(lock,".lock");
   if (unlink(lock) != 0)	/* remove lock file */
   {  fprintf(stderr,"unlockfile: could not remove lock file:'%s'\n",lock);
      return(1);
   }
   return(0);
}