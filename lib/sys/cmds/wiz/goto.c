/*Made by Aphex on Fri 21 Nov 97*/
/* Fixed to handle goto'ing of room files by Fudge. */
/* Fixed to properly setup rooms that get loaded by this command */

inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: goto [-h] PLAYER|ROOM" });
   lines += ({ " " });
   lines += ({ "Find PLAYER, and then transport you to them." });
   lines += ({ "or goto the specified ROOM." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples" });
   lines += ({ "\tgoto sirdude" });
   lines += ({ "\tgoto " + DOMAINS_DIR + "/required/rooms/start.c" });
   lines += ({ "See also:" });
   lines += ({ "\thome, summon, where" });

   this_player()->more(lines);
}

static void main(string str) {
   object usr;

   if (empty_str(str)) {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   usr = USER_D->find_player(str);
   if (usr) {
      if (this_player()->query_environment() != usr->query_environment()) {
	 this_player()->query_environment()->tell_room(this_player(),
	    this_player()->query_Name() + " disappears.\n");

	 this_player()->move(usr->query_environment()->base_name());

	 this_player()->query_environment()->tell_room(this_player(),
	    this_player()->query_Name() + " appears from nowhere.\n");
	 this_player()->do_look(0);
      } else {
	 out("Going somewhere?\n");
      }
   } else {
      string file;
      object ob;

      file = normalize_path(str, this_player()->query_env("cwd"));
      if (file_exists(file + ".c")) {
	 file = file + ".c";
      }
      if (file_exists(file)) {
	 if (!(ob = find_object(file))) {
	    catch {
	       ob = compile_object(file);
	       ob->setup();
	       ob->setup_mudlib();
	    } : {
	       write("Could not load " + str);
	    }
	 }
	 if (ob == this_environment()) {
	    write("You are already there.\n");
	    return;
	 }

	 this_environment()->tell_room(this_player(),
	    this_player()->query_Name() + " disappears.\n");
	 if (!ob || !this_player()->move(ob)) {
	    write("\nConstruction blocks your path.\n");
	 } else {
	    this_player()->do_look(0);
	 }
	 this_environment()->tell_room(this_player(),
	    this_player()->query_Name() + " appears.\n");
      } else {
	 write("Unable to find " + str + ".\n");
      }
   }
}
