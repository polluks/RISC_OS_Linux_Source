#define _GNU_SOURCE

#include <stddef.h>
#include <stdio.h>

#include <attr/xattr.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <poll.h>
#include <sched.h>
#include <signal.h>
#include <sys/auxv.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include <asm/hwcap.h>
#include <linux/filter.h>
#include <linux/memfd.h>
#include <linux/ptrace.h>
#include <linux/seccomp.h>

#define SA_RESTORER  0x04000000

#define DEF2(name, value) \
  fprintf(ass, "ix_%s * 0x%x\n", name, (unsigned)value); \
  fprintf(c, "#define ix_%s 0x%x\n", name, (unsigned)value);
#define DEF(x) DEF2(#x, x)
  
#define SYSDEF(x) \
  fprintf(ass, "%s * 0x%x\n", #x, x); \
  fprintf(c, "#define %s 0x%x\n", #x, x);

#define EDEF(x) \
  fprintf(ass, "ix_%s * %i\n", #x, x); \
  fprintf(c, "#define ix_%s %i\n", #x, x);

int main(void) {
  FILE *ass, *c;

  ass = fopen("LinuxSyscalls", "w");
  c = fopen("h/syscall_defs", "w");

  EDEF(EPERM)
  EDEF(ENOENT)
  EDEF(ESRCH)
  EDEF(EINTR)
  EDEF(EIO)
  EDEF(ENXIO)
  EDEF(E2BIG)
  EDEF(ENOEXEC)
  EDEF(EBADF)
  EDEF(ECHILD)
  EDEF(EAGAIN)
  EDEF(ENOMEM)
  EDEF(EACCES)
  EDEF(EFAULT)
  EDEF(ENOTBLK)
  EDEF(EBUSY)
  EDEF(EEXIST)
  EDEF(EXDEV)
  EDEF(ENODEV)
  EDEF(ENOTDIR)
  EDEF(EISDIR)
  EDEF(EINVAL)
  EDEF(ENFILE)
  EDEF(EMFILE)
  EDEF(ENOTTY)
  EDEF(ETXTBSY)
  EDEF(EFBIG)
  EDEF(ENOSPC)
  EDEF(ESPIPE)
  EDEF(EROFS)
  EDEF(EMLINK)
  EDEF(EPIPE)
  EDEF(EDOM)
  EDEF(ERANGE)
  EDEF(EDEADLK)
  EDEF(ENAMETOOLONG)
  EDEF(ENOLCK)
  EDEF(ENOSYS)
  EDEF(ENOTEMPTY)
  EDEF(ELOOP)
  EDEF(EWOULDBLOCK)
  EDEF(ENOMSG)
  EDEF(EIDRM)
  EDEF(ECHRNG)
  EDEF(EL2NSYNC)
  EDEF(EL3HLT)
  EDEF(EL3RST)
  EDEF(ELNRNG)
  EDEF(EUNATCH)
  EDEF(ENOCSI)
  EDEF(EL2HLT)
  EDEF(EBADE)
  EDEF(EBADR)
  EDEF(EXFULL)
  EDEF(ENOANO)
  EDEF(EBADRQC)
  EDEF(EBADSLT)
  EDEF(EDEADLOCK)
  EDEF(EBFONT)
  EDEF(ENOSTR)
  EDEF(ENODATA)
  EDEF(ETIME)
  EDEF(ENOSR)
  EDEF(ENONET)
  EDEF(ENOPKG)
  EDEF(EREMOTE)
  EDEF(ENOLINK)
  EDEF(EADV)
  EDEF(ESRMNT)
  EDEF(ECOMM)
  EDEF(EPROTO)
  EDEF(EMULTIHOP)
  EDEF(EDOTDOT)
  EDEF(EBADMSG)
  EDEF(EOVERFLOW)
  EDEF(ENOTUNIQ)
  EDEF(EBADFD)
  EDEF(EREMCHG)
  EDEF(ELIBACC)
  EDEF(ELIBBAD)
  EDEF(ELIBSCN)
  EDEF(ELIBMAX)
  EDEF(ELIBEXEC)
  EDEF(EILSEQ)
  EDEF(ERESTART)
  EDEF(ESTRPIPE)
  EDEF(EUSERS)
  EDEF(ENOTSOCK)
  EDEF(EDESTADDRREQ)
  EDEF(EMSGSIZE)
  EDEF(EPROTOTYPE)
  EDEF(ENOPROTOOPT)
  EDEF(EPROTONOSUPPORT)
  EDEF(ESOCKTNOSUPPORT)
  EDEF(EOPNOTSUPP)
  EDEF(EPFNOSUPPORT)
  EDEF(EAFNOSUPPORT)
  EDEF(EADDRINUSE)
  EDEF(EADDRNOTAVAIL)
  EDEF(ENETDOWN)
  EDEF(ENETUNREACH)
  EDEF(ENETRESET)
  EDEF(ECONNABORTED)
  EDEF(ECONNRESET)
  EDEF(ENOBUFS)
  EDEF(EISCONN)
  EDEF(ENOTCONN)
  EDEF(ESHUTDOWN)
  EDEF(ETOOMANYREFS)
  EDEF(ETIMEDOUT)
  EDEF(ECONNREFUSED)
  EDEF(EHOSTDOWN)
  EDEF(EHOSTUNREACH)
  EDEF(EALREADY)
  EDEF(EINPROGRESS)
  EDEF(ESTALE)
  EDEF(EUCLEAN)
  EDEF(ENOTNAM)
  EDEF(ENAVAIL)
  EDEF(EISNAM)
  EDEF(EREMOTEIO)
  EDEF(EDQUOT)
  EDEF(ENOMEDIUM)
  EDEF(EMEDIUMTYPE)
  EDEF(ECANCELED)
  EDEF(ENOKEY)
  EDEF(EKEYEXPIRED)
  EDEF(EKEYREVOKED)
  EDEF(EKEYREJECTED)
  EDEF(EOWNERDEAD)
  EDEF(ENOTRECOVERABLE)
  EDEF(ERFKILL)
  EDEF(EHWPOISON)

  DEF(AT_FDCWD)
  DEF(AT_HWCAP)
  DEF(AT_HWCAP2)
  DEF(BPF_ABS)
  DEF(BPF_JEQ)
  DEF(BPF_JGE)
  DEF(BPF_JMP)
  DEF(BPF_K)
  DEF(BPF_LD)
  DEF(BPF_RET)
  DEF(BPF_W)
  DEF(CLOCK_MONOTONIC)
  DEF(CLOCK_MONOTONIC_RAW)
  DEF(CLOCK_REALTIME)
  DEF(CLONE_VM)
  DEF(ECHO)
  DEF(F_GETFL)
  DEF(F_SETFL)
  DEF(F_SETOWN)
  DEF(F_SETSIG)
  DEF(HWCAP2_AES)
  DEF(HWCAP2_CRC32)
  DEF(HWCAP2_PMULL)
  DEF(HWCAP2_SHA1)
  DEF(HWCAP2_SHA2)
  DEF(HWCAP_26BIT)
  DEF(HWCAP_CRUNCH)
  DEF(HWCAP_EDSP)
  DEF(HWCAP_EVTSTRM)
  DEF(HWCAP_FAST_MULT)
  DEF(HWCAP_FPA)
  DEF(HWCAP_HALF)
  DEF(HWCAP_IDIV)
  DEF(HWCAP_IDIVA)
  DEF(HWCAP_IDIVT)
  DEF(HWCAP_IWMMXT)
  DEF(HWCAP_JAVA)
  DEF(HWCAP_LPAE)
  DEF(HWCAP_NEON)
  DEF(HWCAP_SWP)
  DEF(HWCAP_THUMB)
  DEF(HWCAP_THUMBEE)
  DEF(HWCAP_TLS)
  DEF(HWCAP_VFP)
  DEF(HWCAP_VFPD32)
  DEF(HWCAP_VFPv3)
  DEF(HWCAP_VFPv3D16)
  DEF(HWCAP_VFPv4)
  DEF(ICANON)
  DEF(IGNCR)
  DEF(INLCR)
  DEF(MAP_ANONYMOUS)
  DEF(MAP_FIXED)
  DEF(MAP_NORESERVE)
  DEF(MAP_PRIVATE)
  DEF(MAP_SHARED)
  DEF(MFD_CLOEXEC)
  DEF(MINSIGSTKSZ)
  DEF(MSG_CTRUNC)
  DEF(MSG_DONTROUTE)
  DEF(MSG_DONTWAIT)
  DEF(MSG_EOR)
  DEF(MSG_OOB)
  DEF(MSG_PEEK)
  DEF(MSG_TRUNC)
  DEF(MSG_WAITALL)
  DEF(O_ASYNC)
  DEF(O_CLOEXEC)
  DEF(O_CREAT)
  DEF(O_DIRECTORY)
  DEF(O_EXCL)
  DEF(O_NOFOLLOW)
  DEF(O_NONBLOCK)
  DEF(O_PATH)
  DEF(O_RDONLY)
  DEF(O_RDWR)
  DEF(O_TRUNC)
  DEF(PATH_MAX)
  DEF(POLLERR)
  DEF(POLLHUP)
  DEF(POLLIN)
  DEF(POLLMSG)
  DEF(POLLNVAL)
  DEF(POLLOUT)
  DEF(POLLPRI)
  DEF(POLLRDBAND)
  DEF(POLLRDHUP)
  DEF(POLLRDNORM)
  DEF(POLLREMOVE)
  DEF(POLLWRBAND)
  DEF(POLLWRNORM)
  DEF(PROT_EXEC)
  DEF(PROT_NONE)
  DEF(PROT_READ)
  DEF(PROT_WRITE)
  DEF(PR_SET_NO_NEW_PRIVS)
  DEF(PR_SET_PDEATHSIG)
  DEF(PR_SET_SECCOMP)
  DEF(PTRACE_CONT)
  DEF(PTRACE_GETREGS)
  DEF(PTRACE_O_TRACESYSGOOD)
  DEF(PTRACE_SETOPTIONS)
  DEF(PTRACE_SETREGS)
  DEF(PTRACE_SET_SYSCALL)
  DEF(PTRACE_SYSCALL)
  DEF(PTRACE_TRACEME)
  DEF(SA_NODEFER)
  DEF(SA_ONSTACK)
  DEF(SA_RESTART)
  DEF(SA_RESTORER)
  DEF(SA_SIGINFO)
  DEF(SECCOMP_MODE_FILTER)
  DEF(SECCOMP_RET_ALLOW)
  DEF(SECCOMP_RET_TRAP)
  DEF(SEEK_CUR)
  DEF(SEEK_END)
  DEF(SEEK_SET)
  DEF(SIGBUS)
  DEF(SIGCHLD)
  DEF(SIGEV_SIGNAL)
  DEF(SIGHUP)
  DEF(SIGILL)
  DEF(SIGINT)
  DEF(SIGSEGV)
  DEF(SIGSTOP)
  DEF(SIGSYS)
  DEF(SIGTERM)
  DEF(SIGTRAP)
  DEF(SIGTSTP)
  DEF(SIGTTIN)
  DEF(SIGTTOU)
  DEF(SIGUSR1)
  DEF(SIGUSR2)
  DEF(SIG_BLOCK)
  DEF(SIG_SETMASK)
  DEF(SIG_UNBLOCK)
  DEF(SOCK_CLOEXEC)
  DEF(SOCK_SEQPACKET)
  DEF(SOL_SOCKET)
  DEF(SO_BROADCAST)
  DEF(SO_BSDCOMPAT)
  DEF(SO_DEBUG)
  DEF(SO_DONTROUTE)
  DEF(SO_ERROR)
  DEF(SO_KEEPALIVE)
  DEF(SO_LINGER)
  DEF(SO_NO_CHECK)
  DEF(SO_OOBINLINE)
  DEF(SO_PASSCRED)
  DEF(SO_PEERCRED)
  DEF(SO_PRIORITY)
  DEF(SO_RCVBUF)
  DEF(SO_RCVBUFFORCE)
  DEF(SO_RCVLOWAT)
  DEF(SO_RCVTIMEO)
  DEF(SO_REUSEADDR)
  DEF(SO_REUSEPORT)
  DEF(SO_SNDBUF)
  DEF(SO_SNDBUFFORCE)
  DEF(SO_SNDLOWAT)
  DEF(SO_SNDTIMEO)
  DEF(SO_TYPE)
  DEF(S_IFDIR)
  DEF(TCGETS)
  DEF(TCP_CORK)
  DEF(TCP_MAXSEG)
  DEF(TCP_NODELAY)
  DEF(TCSETS)
  DEF(TIMER_ABSTIME)
  DEF(UTIME_NOW)
  DEF(UTIME_OMIT)
  DEF(VMIN)
  DEF(VTIME)
  DEF(WNOHANG)
  DEF(XATTR_CREATE)
  DEF(__WALL)

  DEF2("struct_ucontext_mcontext", offsetof(struct ucontext, uc_mcontext))
  DEF2("struct_ucontext_registers", offsetof(struct ucontext, uc_mcontext.arm_r0))

#include "syscall_list.h"

  fputs("\n END\n", ass);

  return 0;
}
