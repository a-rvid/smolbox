#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

#define SLEEP_ABOUT "Pause for NUMBER seconds."
#define SLEEP_USAGE "NUMBER"

#define NSEC_PER_SEC 1000000000L

#define STRTOL_NAN_ERROR "strtol: Not a Number"

int sleepcmd(int argc, char **argv) {
    if (argc < 2) {
        fputs("sleep: missing operand\n", stderr);
        return 1;
    }

    char *arg = argv[1];
    char *dot = strchr(arg, '.');
    char *frac_part = "";
    if (dot) {
        *dot = '\0';
        frac_part = dot + 1;
    }

    errno = 0;
    char *endptr;
    long seconds = strtol(arg, &endptr, 10);
    if (errno != 0 || endptr == arg) {
        write(2, STRTOL_NAN_ERROR, sizeof(STRTOL_NAN_ERROR));
        return 1;
    }

    long nanoseconds = 0;
    char *suffix = endptr;

    if (dot) {
        errno = 0;
        char *frac_end;
        long value = strtol(frac_part, &frac_end, 10);
        if (errno != 0) {
            write(2, STRTOL_NAN_ERROR, sizeof(STRTOL_NAN_ERROR));
            return 1;
        }
        int num_digits = (int)(frac_end - frac_part);
        long scale = 1;
        for (int i = 0; i < 9 - num_digits; i++) scale *= 10;
        nanoseconds = value * scale;
        suffix = frac_end;
    }

    long multiplier;
    switch (suffix[0]) {
        case '\0':
        case 's': multiplier = 1;    break;
        case 'm': multiplier = 60;   break;
        case 'h': multiplier = 3600; break;
        case 'd': multiplier = 86400; break;
        default:
            fputs("sleep: invalid time unit\n", stderr);
            return 1;
    }

    seconds *= multiplier;
    nanoseconds *= multiplier;
    seconds += nanoseconds / NSEC_PER_SEC;
    nanoseconds %= NSEC_PER_SEC;

    struct timespec time = {
      .tv_sec = seconds,
      .tv_nsec = nanoseconds
    };

    clock_nanosleep(CLOCK_REALTIME, 0, &time, NULL);

    return 0;
}
