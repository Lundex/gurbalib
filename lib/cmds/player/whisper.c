inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: whisper [-h] WHO MSG" });
   lines += ({ "" });
   lines += ({ "Whisper a message MSG to WHO" });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\twhisper sirdude you are cool." });
   lines += ({ "\twhisper guest Hi how are you?" });
   lines += ({ "See also:" });
   if (query_wizard(this_player())) {
      lines += ({ "\tbug, chan, echo, echoto, emote, rsay, shout, " +
         "ssay, say, sysmsg, tell, translate, wizcall" });
   } else {
      lines += ({ "\tbug, chan, emote, rsay, say, shout, tell, wizcall" });
   }

   if (query_admin(this_player())) {
      lines += ({ "\twall" });
   }

   this_player()->more(lines);
}

static void main(string who) {
   object *usr;
   int i, flag;
   string what;

   if (empty_str(who)) {
      usage();
      return;
   }
   if (sscanf(who, "-%s", who)) {
      usage();
      return;
   }

   sscanf(who, "%s %s", who, what);

   if (what && (what != "")) {
      what = capitalize(what);
   }

   usr = USER_D->query_players();
   flag = 0;
   for (i = 0; i < sizeof(usr); i++) {
      if ((usr[i]->query_environment() == this_environment()) &&
         (usr[i]->query_name() == who)) {
         usr[i]->message(this_player()->query_Name() +
            " whispers to you: " + what + "\n");
         write("You whisper to " + capitalize(who) + ": " + what + "\n");
         this_player()->query_environment()->tell_room(this_player(),
            this_player()->query_Name() +
            " whispers something to " + capitalize(who) + ".\n", usr[i]);
         flag = 1;
      }
   }

   if (!flag) {
      write("Who did you want to whisper to?\n");
   }
}

