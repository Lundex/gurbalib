inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: loglevel [-h] [LOG #]" });
   lines += ({ " " });
   lines += ({ "Change the loglevel of LOG to #.  For now log levels are " +
      "between: 0 and 5" });
   lines += ({ "Level 0 is no logging, and as you work your way down you " +
      "get more and more logs." });
   lines += ({ "If no LOG is given display the current log levels." });
   lines += ({ "If a log is not listed it uses the \"default\" log level." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tloglevel" });
   lines += ({ "\tloglevel default 1" });
   lines += ({ "\tloglevel imud_d 5" });
   lines += ({ "See also:" });

   lines += ({ "\t" });

   this_player()->more(lines);
}

static void main(string msg) {
   string log, *lines;
   mixed x;

   if (empty_str(msg)) {
      lines = LOG_D->show_log_levels();
      this_player()->more(lines);
      return;
   } else if (sscanf(msg, "-%s", msg)) {
      usage();
      return;
   } else {
      if (sscanf(msg, "%s default", log) == 1) {
         x = "default";
/* XXX Do some checks against log to see if user has perms... */
         if (!LOG_D->set_log_level(log,x)) {
            write("Unable to set loglevel: " + log + ": " + x  + "\n");
         }
      } else if (sscanf(msg, "%s %d", log, x) == 2) {
         if (!LOG_D->set_log_level(log,x)) {
            write("Unable to set loglevel: " + log + ": " + x  + "\n");
         }
      } else {
         write("Error in syntax, expecting LOG #, not: " + msg + "\n");
      }
   }
}
