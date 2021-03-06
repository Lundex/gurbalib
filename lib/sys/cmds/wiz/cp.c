inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: cp [-h] [file1] [file2]" });
   lines += ({ " " });
   lines += ({ "Copy [file1] to [file2]." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tcp " + DOMAINS_DIR + "/newbie/rooms/workroom.c workroom.c" });
   lines += ({ "See also:" });
   lines += ({ "\tbrowse, cat, cd, diff, edit, indent, ls, more, mkdir, pwd, " +
      "rm, tail" });

   this_player()->more(lines);
}

static void main(string str) {
   string file, dest, where, file_name, in;
   string *parts;

   if (empty_str(str) || (sscanf(str, "%s %s", str, where) != 2)) {
      write("Please specify a source and a destination.");
      usage();
      return;
   }

   file = normalize_path(str, this_player()->query_env("cwd"));

   if (!file || (file == "") || !valid_read(file)) {
      write(file + ": Permission denied.");
      return;
   }

   if (file_exists(file) == -1) {
      write(file + ": Unable to copy directories.");
      return;
   }

   if (!file_exists(file)) {
      write(file + ": File doesn't exist.");
      return;
   }

   parts = explode(file, "/");
   file_name = parts[sizeof(parts) - 1];

   dest = normalize_path(where, this_player()->query_env("cwd"));
   if (!dest || (dest == "") || !valid_write(dest)) {
      write(dest + ": Permission denied.");
      return;
   }

   if (file_exists(dest) == -1) {
      if (dest[strlen(dest) - 1] != '/') {
	 dest += "/";
      }

      dest += file_name;
   }

   if (file_exists(dest) == -1) {
      write(dest + ": Unable to create destination.");
      return;
   }

   copy(file, dest);
}
