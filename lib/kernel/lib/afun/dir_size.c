/* get the size of all files in a directory */
int dir_size(string file) {
   mixed **info;
   int *sizes, size, i, sz;

   argcheck(file, 1, "string");

   info = get_dir(file + "/*");
   sizes = info[1];
   size = 1;			/* 1K for directory itself */
   i = sizeof(sizes);
   while (--i >= 0) {
      sz = sizes[i];
      size += (sz > 0) ?
	 (sz + 1023) >> 10 : (sz == 0) ? 1 : dir_size(file + "/" + info[0][i]);
   }

   return size;
}
