#include "common.h"
#include "signal.h"

char* ident =
    "$Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/targucode/cfe/RCS/os.c,v 1.2 1992/08/12 21:07:39 wsj Exp $";

static int D_1001D864[] = { -1,
                            MSG_HANGUP,
                            MSG_INTERRUPT,
                            MSG_QUIT,
                            MSG_ILLEGAL_INSTRUCTION,
                            MSG_TRACE_TRAP,
                            MSG_IOT_INSTRUCTION,
                            MSG_EMT_INSTRUCTION,
                            MSG_FLOAT_EXCEPTION,
                            MSG_KILL,
                            MSG_BUS_ERROR,
                            MSG_SEGMENTATION_FAULT,
                            MSG_BAD_SYSTEM_CALL_ARG,
                            MSG_PIPE_WRITE_NO_READER,
                            MSG_ALARM_CLOCK,
                            MSG_SOFT_TERMINATION_SIGNAL,
                            MSG_SIGUSR1,
                            MSG_SIGUSR2,
                            MSG_CHILD_DEATH,
                            MSG_POWER_FAIL_RESTART,
                            MSG_TTY_STOP_NOT_FROM_TTY,
                            MSG_TTY_STOP,
                            MSG_POLL_EVENT,
                            MSG_IO_POSSIBLE,
                            MSG_URGENT_IO_CONDITION,
                            MSG_WINDOW_SIZE_CHANGE,
                            MSG_VIRTUAL_TIME_ALARM,
                            MSG_PROFILING_ALARM,
                            MSG_CONTINUE_STOPPED_PROCESS,
                            MSG_BG_TTY_READ_TO_PG,
                            MSG_TTLOSTOP_OUTPUT_READ,
                            MSG_RESOURCE_LOST };

void report_crash(int signo) {
    if (signo >= 1 && signo < NSIG) {
        error(D_1001D864[signo], LEVEL_FATAL, -1, infile);
    } else {
        error(MSG_UNKNOWN_SIGNAL, LEVEL_FATAL, -1, signo, infile);
    }
}

void catchall(void) {
    int signo;

    signal(SIGHUP, SIG_IGN);

    for (signo = SIGINT; signo < NSIG; signo++) {
        if (signo != SIGTSTP && signo != SIGCONT && signo != SIGWINCH && signo != SIGCHLD &&
            signal(signo, report_crash) == SIG_IGN) {
            signal(signo, SIG_IGN);
        }
    }
}
