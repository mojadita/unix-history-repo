/*
 * System call switch table.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * created from	Id: syscalls.master,v 1.17 1999/08/11 13:29:48 marcel Exp 
 */

#include "opt_compat.h"
#include <sys/param.h>
#include <sys/sysent.h>
#include <sys/sysproto.h>
#include <i386/linux/linux.h>
#include <i386/linux/linux_proto.h>

/* The casts are bogus but will do for now. */
struct sysent linux_sysent[] = {
	{ 0, (sy_call_t *)linux_setup },		/* 0 = linux_setup */
	{ 1, (sy_call_t *)exit },			/* 1 = exit */
	{ 0, (sy_call_t *)linux_fork },			/* 2 = linux_fork */
	{ 3, (sy_call_t *)read },			/* 3 = read */
	{ 3, (sy_call_t *)write },			/* 4 = write */
	{ 3, (sy_call_t *)linux_open },			/* 5 = linux_open */
	{ 1, (sy_call_t *)close },			/* 6 = close */
	{ 3, (sy_call_t *)linux_waitpid },		/* 7 = linux_waitpid */
	{ 2, (sy_call_t *)linux_creat },		/* 8 = linux_creat */
	{ 2, (sy_call_t *)link },			/* 9 = link */
	{ 1, (sy_call_t *)linux_unlink },		/* 10 = linux_unlink */
	{ 3, (sy_call_t *)linux_execve },		/* 11 = linux_execve */
	{ 1, (sy_call_t *)linux_chdir },		/* 12 = linux_chdir */
	{ 1, (sy_call_t *)linux_time },			/* 13 = linux_time */
	{ 3, (sy_call_t *)linux_mknod },		/* 14 = linux_mknod */
	{ 2, (sy_call_t *)linux_chmod },		/* 15 = linux_chmod */
	{ 3, (sy_call_t *)linux_lchown },		/* 16 = linux_lchown */
	{ 1, (sy_call_t *)linux_break },		/* 17 = linux_break */
	{ 2, (sy_call_t *)linux_stat },			/* 18 = linux_stat */
	{ 3, (sy_call_t *)linux_lseek },		/* 19 = linux_lseek */
	{ 0, (sy_call_t *)getpid },			/* 20 = getpid */
	{ 0, (sy_call_t *)linux_mount },		/* 21 = linux_mount */
	{ 0, (sy_call_t *)linux_umount },		/* 22 = linux_umount */
	{ 1, (sy_call_t *)setuid },			/* 23 = setuid */
	{ 0, (sy_call_t *)getuid },			/* 24 = getuid */
	{ 0, (sy_call_t *)linux_stime },		/* 25 = linux_stime */
	{ 0, (sy_call_t *)linux_ptrace },		/* 26 = linux_ptrace */
	{ 1, (sy_call_t *)linux_alarm },		/* 27 = linux_alarm */
	{ 2, (sy_call_t *)linux_fstat },		/* 28 = linux_fstat */
	{ 0, (sy_call_t *)linux_pause },		/* 29 = linux_pause */
	{ 2, (sy_call_t *)linux_utime },		/* 30 = linux_utime */
	{ 0, (sy_call_t *)linux_stty },			/* 31 = linux_stty */
	{ 0, (sy_call_t *)linux_gtty },			/* 32 = linux_gtty */
	{ 2, (sy_call_t *)linux_access },		/* 33 = linux_access */
	{ 1, (sy_call_t *)linux_nice },			/* 34 = linux_nice */
	{ 0, (sy_call_t *)linux_ftime },		/* 35 = linux_ftime */
	{ 0, (sy_call_t *)sync },			/* 36 = sync */
	{ 2, (sy_call_t *)linux_kill },			/* 37 = linux_kill */
	{ 2, (sy_call_t *)linux_rename },		/* 38 = linux_rename */
	{ 2, (sy_call_t *)linux_mkdir },		/* 39 = linux_mkdir */
	{ 1, (sy_call_t *)linux_rmdir },		/* 40 = linux_rmdir */
	{ 1, (sy_call_t *)dup },			/* 41 = dup */
	{ 1, (sy_call_t *)linux_pipe },			/* 42 = linux_pipe */
	{ 1, (sy_call_t *)linux_times },		/* 43 = linux_times */
	{ 0, (sy_call_t *)linux_prof },			/* 44 = linux_prof */
	{ 1, (sy_call_t *)linux_brk },			/* 45 = linux_brk */
	{ 1, (sy_call_t *)setgid },			/* 46 = setgid */
	{ 0, (sy_call_t *)getgid },			/* 47 = getgid */
	{ 2, (sy_call_t *)linux_signal },		/* 48 = linux_signal */
	{ 0, (sy_call_t *)geteuid },			/* 49 = geteuid */
	{ 0, (sy_call_t *)getegid },			/* 50 = getegid */
	{ 1, (sy_call_t *)acct },			/* 51 = acct */
	{ 0, (sy_call_t *)linux_phys },			/* 52 = linux_phys */
	{ 0, (sy_call_t *)linux_lock },			/* 53 = linux_lock */
	{ 3, (sy_call_t *)linux_ioctl },		/* 54 = linux_ioctl */
	{ 3, (sy_call_t *)linux_fcntl },		/* 55 = linux_fcntl */
	{ 0, (sy_call_t *)linux_mpx },			/* 56 = linux_mpx */
	{ 2, (sy_call_t *)setpgid },			/* 57 = setpgid */
	{ 0, (sy_call_t *)linux_ulimit },		/* 58 = linux_ulimit */
	{ 1, (sy_call_t *)linux_olduname },		/* 59 = linux_olduname */
	{ 1, (sy_call_t *)umask },			/* 60 = umask */
	{ 1, (sy_call_t *)chroot },			/* 61 = chroot */
	{ 0, (sy_call_t *)linux_ustat },		/* 62 = linux_ustat */
	{ 2, (sy_call_t *)dup2 },			/* 63 = dup2 */
	{ 0, (sy_call_t *)getppid },			/* 64 = getppid */
	{ 0, (sy_call_t *)getpgrp },			/* 65 = getpgrp */
	{ 0, (sy_call_t *)setsid },			/* 66 = setsid */
	{ 3, (sy_call_t *)linux_sigaction },		/* 67 = linux_sigaction */
	{ 0, (sy_call_t *)linux_siggetmask },		/* 68 = linux_siggetmask */
	{ 1, (sy_call_t *)linux_sigsetmask },		/* 69 = linux_sigsetmask */
	{ 2, (sy_call_t *)setreuid },			/* 70 = setreuid */
	{ 2, (sy_call_t *)setregid },			/* 71 = setregid */
	{ 3, (sy_call_t *)linux_sigsuspend },		/* 72 = linux_sigsuspend */
	{ 1, (sy_call_t *)linux_sigpending },		/* 73 = linux_sigpending */
	{ 2, (sy_call_t *)osethostname },		/* 74 = osethostname */
	{ 2, (sy_call_t *)linux_setrlimit },		/* 75 = linux_setrlimit */
	{ 2, (sy_call_t *)linux_getrlimit },		/* 76 = linux_getrlimit */
	{ 2, (sy_call_t *)getrusage },			/* 77 = getrusage */
	{ 2, (sy_call_t *)gettimeofday },		/* 78 = gettimeofday */
	{ 2, (sy_call_t *)settimeofday },		/* 79 = settimeofday */
	{ 2, (sy_call_t *)linux_getgroups },		/* 80 = linux_getgroups */
	{ 2, (sy_call_t *)linux_setgroups },		/* 81 = linux_setgroups */
	{ 1, (sy_call_t *)linux_select },		/* 82 = linux_select */
	{ 2, (sy_call_t *)linux_symlink },		/* 83 = linux_symlink */
	{ 2, (sy_call_t *)ostat },			/* 84 = ostat */
	{ 3, (sy_call_t *)linux_readlink },		/* 85 = linux_readlink */
	{ 1, (sy_call_t *)linux_uselib },		/* 86 = linux_uselib */
	{ 1, (sy_call_t *)swapon },			/* 87 = swapon */
	{ 1, (sy_call_t *)reboot },			/* 88 = reboot */
	{ 3, (sy_call_t *)linux_readdir },		/* 89 = linux_readdir */
	{ 1, (sy_call_t *)linux_mmap },			/* 90 = linux_mmap */
	{ 2, (sy_call_t *)munmap },			/* 91 = munmap */
	{ 2, (sy_call_t *)linux_truncate },		/* 92 = linux_truncate */
	{ 2, (sy_call_t *)oftruncate },			/* 93 = oftruncate */
	{ 2, (sy_call_t *)fchmod },			/* 94 = fchmod */
	{ 3, (sy_call_t *)fchown },			/* 95 = fchown */
	{ 2, (sy_call_t *)getpriority },		/* 96 = getpriority */
	{ 3, (sy_call_t *)setpriority },		/* 97 = setpriority */
	{ 4, (sy_call_t *)profil },			/* 98 = profil */
	{ 2, (sy_call_t *)linux_statfs },		/* 99 = linux_statfs */
	{ 2, (sy_call_t *)linux_fstatfs },		/* 100 = linux_fstatfs */
	{ 3, (sy_call_t *)linux_ioperm },		/* 101 = linux_ioperm */
	{ 2, (sy_call_t *)linux_socketcall },		/* 102 = linux_socketcall */
	{ 1, (sy_call_t *)linux_ksyslog },		/* 103 = linux_ksyslog */
	{ 3, (sy_call_t *)linux_setitimer },		/* 104 = linux_setitimer */
	{ 2, (sy_call_t *)linux_getitimer },		/* 105 = linux_getitimer */
	{ 2, (sy_call_t *)linux_newstat },		/* 106 = linux_newstat */
	{ 2, (sy_call_t *)linux_newlstat },		/* 107 = linux_newlstat */
	{ 2, (sy_call_t *)linux_newfstat },		/* 108 = linux_newfstat */
	{ 1, (sy_call_t *)linux_uname },		/* 109 = linux_uname */
	{ 1, (sy_call_t *)linux_iopl },			/* 110 = linux_iopl */
	{ 0, (sy_call_t *)linux_vhangup },		/* 111 = linux_vhangup */
	{ 0, (sy_call_t *)linux_idle },			/* 112 = linux_idle */
	{ 0, (sy_call_t *)linux_vm86 },			/* 113 = linux_vm86 */
	{ 4, (sy_call_t *)linux_wait4 },		/* 114 = linux_wait4 */
	{ 0, (sy_call_t *)linux_swapoff },		/* 115 = linux_swapoff */
	{ 0, (sy_call_t *)linux_sysinfo },		/* 116 = linux_sysinfo */
	{ 5, (sy_call_t *)linux_ipc },			/* 117 = linux_ipc */
	{ 1, (sy_call_t *)fsync },			/* 118 = fsync */
	{ 1, (sy_call_t *)linux_sigreturn },		/* 119 = linux_sigreturn */
	{ 2, (sy_call_t *)linux_clone },		/* 120 = linux_clone */
	{ 2, (sy_call_t *)setdomainname },		/* 121 = setdomainname */
	{ 1, (sy_call_t *)linux_newuname },		/* 122 = linux_newuname */
	{ 3, (sy_call_t *)linux_modify_ldt },		/* 123 = linux_modify_ldt */
	{ 0, (sy_call_t *)linux_adjtimex },		/* 124 = linux_adjtimex */
	{ 3, (sy_call_t *)mprotect },			/* 125 = mprotect */
	{ 3, (sy_call_t *)linux_sigprocmask },		/* 126 = linux_sigprocmask */
	{ 0, (sy_call_t *)linux_create_module },		/* 127 = linux_create_module */
	{ 0, (sy_call_t *)linux_init_module },		/* 128 = linux_init_module */
	{ 0, (sy_call_t *)linux_delete_module },		/* 129 = linux_delete_module */
	{ 0, (sy_call_t *)linux_get_kernel_syms },		/* 130 = linux_get_kernel_syms */
	{ 0, (sy_call_t *)linux_quotactl },		/* 131 = linux_quotactl */
	{ 1, (sy_call_t *)linux_getpgid },		/* 132 = linux_getpgid */
	{ 1, (sy_call_t *)fchdir },			/* 133 = fchdir */
	{ 0, (sy_call_t *)linux_bdflush },		/* 134 = linux_bdflush */
	{ 0, (sy_call_t *)nosys },			/* 135 = sysfs */
	{ 1, (sy_call_t *)linux_personality },		/* 136 = linux_personality */
	{ 0, (sy_call_t *)nosys },			/* 137 = afs_syscall */
	{ 0, (sy_call_t *)nosys },			/* 138 = setfsuid */
	{ 0, (sy_call_t *)nosys },			/* 139 = getfsuid */
	{ 5, (sy_call_t *)linux_llseek },		/* 140 = linux_llseek */
	{ 3, (sy_call_t *)linux_getdents },		/* 141 = linux_getdents */
	{ 5, (sy_call_t *)linux_newselect },		/* 142 = linux_newselect */
	{ 2, (sy_call_t *)flock },			/* 143 = flock */
	{ 3, (sy_call_t *)linux_msync },		/* 144 = linux_msync */
	{ 3, (sy_call_t *)readv },			/* 145 = readv */
	{ 3, (sy_call_t *)writev },			/* 146 = writev */
	{ 0, (sy_call_t *)nosys },			/* 147 = getsid */
	{ 0, (sy_call_t *)nosys },			/* 148 = fdatasync */
	{ 0, (sy_call_t *)nosys },			/* 149 = _sysctl */
	{ 2, (sy_call_t *)mlock },			/* 150 = mlock */
	{ 2, (sy_call_t *)munlock },			/* 151 = munlock */
	{ 1, (sy_call_t *)mlockall },			/* 152 = mlockall */
	{ 0, (sy_call_t *)munlockall },			/* 153 = munlockall */
	{ 2, (sy_call_t *)sched_setparam },		/* 154 = sched_setparam */
	{ 2, (sy_call_t *)sched_getparam },		/* 155 = sched_getparam */
	{ 3, (sy_call_t *)sched_setscheduler },		/* 156 = sched_setscheduler */
	{ 1, (sy_call_t *)sched_getscheduler },		/* 157 = sched_getscheduler */
	{ 0, (sy_call_t *)sched_yield },		/* 158 = sched_yield */
	{ 1, (sy_call_t *)sched_get_priority_max },		/* 159 = sched_get_priority_max */
	{ 1, (sy_call_t *)sched_get_priority_min },		/* 160 = sched_get_priority_min */
	{ 2, (sy_call_t *)sched_rr_get_interval },		/* 161 = sched_rr_get_interval */
	{ 2, (sy_call_t *)nanosleep },			/* 162 = nanosleep */
	{ 4, (sy_call_t *)linux_mremap },		/* 163 = linux_mremap */
	{ 0, (sy_call_t *)nosys },			/* 164 = setresuid */
	{ 0, (sy_call_t *)nosys },			/* 165 = getresuid */
	{ 0, (sy_call_t *)nosys },			/* 166 = new_vm86 */
	{ 0, (sy_call_t *)nosys },			/* 167 = query_module */
	{ 3, (sy_call_t *)poll },			/* 168 = poll */
	{ 0, (sy_call_t *)nosys },			/* 169 = nfsservctl */
	{ 0, (sy_call_t *)nosys },			/* 170 = setresgid */
	{ 0, (sy_call_t *)nosys },			/* 171 = getresgid */
	{ 0, (sy_call_t *)nosys },			/* 172 = prctl */
	{ 0, (sy_call_t *)nosys },			/* 173 = rt_sigreturn */
	{ 0, (sy_call_t *)nosys },			/* 174 = rt_sigaction */
	{ 0, (sy_call_t *)nosys },			/* 175 = rt_sigprocmask */
	{ 0, (sy_call_t *)nosys },			/* 176 = rt_sigpending */
	{ 0, (sy_call_t *)nosys },			/* 177 = rt_sigtimedwait */
	{ 0, (sy_call_t *)nosys },			/* 178 = rt_sigqueueinfo */
	{ 0, (sy_call_t *)nosys },			/* 179 = rt_sigsuspend */
	{ 0, (sy_call_t *)nosys },			/* 180 = pread */
	{ 0, (sy_call_t *)nosys },			/* 181 = pwrite */
	{ 3, (sy_call_t *)linux_chown },		/* 182 = linux_chown */
};
