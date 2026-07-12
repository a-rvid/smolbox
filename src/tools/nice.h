/* int niceness(int argc, char **argv, bool offset) { */
/*   errno = 0; */
/*   int niceness = getpriority(PRIO_PROCESS, 0); */
/*   if (errno != 0) { */
/*     perror("getpriority"); */
/*     return 1; */
/*   } */

/*   static struct option long_options[] = { */
/*     {"adjustment", required_argument, NULL, 'n'}, */
/*     {NULL, 0, NULL, 0} */
/*   }; */

/*   int outnice = niceness; */
/*   int opt; */

/*   char *fake_argv[3] = {NULL}; */
/*   fake_argv[0] = argv[0]; */
/*   fake_argv[1] = argv[1+offset]; */
/*   // Segmentation Fault here!!! */
/*   if ((opt = getopt_long(2, fake_argv, "n:", long_options, NULL)) == 'n') {
 */
/*     outnice += atoi(optarg); */
/*   } else { */
/*     outnice += 10; */
/*   } */

/*   if (argc <= 1 + offset) { */
/*     char sniceness[4]; */
/*     Itoa(niceness, sniceness, 10); */
/*     puts(sniceness); */
/*     return 0; */
/*   } */

/*   if(setpriority(PRIO_PROCESS, 0, outnice) == -1) { */
/*     perror("nice"); */
/*     return 1; */
/*   } else { */
/*     if(execvp(argv[1 + offset], &argv[1 + offset]) == -1) { */
/*       perror(argv[1 + offset]); */
/*     }; */
/*   } */

/*   return 0; */
/* } */
