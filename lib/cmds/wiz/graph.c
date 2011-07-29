void usage() {
  write("Usage: graph [-h] DIR\n");
  write("prints dot compatible output of a graph of the directory you " +
    "specify.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  int i;

  if( !str || str == "" ) {
    usage();
    return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  str = normalize_path( str, this_player()->query_env( "cwd" ) );

  if( !str || str == "" ) {
    write( "Access denied.\n" );
    return;
  }

 if( strlen(str) > 1 && str[strlen(str)-1] == '/' ) {
    str = str[..strlen(str)-2];
  }
    
  if( file_exists( str ) != -1 ) {
    write( "Dir not found.\n" );
    return;
  }

  /* Look at ls it does this and then does str + "/*"
     I don't think we need both... it's odd... */
  files = get_dir( str );
  if( !files ) {
    write( "Dir:" + str + " is empty.\n");
    return;
  }

  /* do the work here... */
  /* XXX */ 
  i = sizeof(files);
  while(i>0) {
     i--;
     write("Looking at : " + str + "/" + files[i] + "\n");
  }
}

