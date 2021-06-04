#ifndef PATHPARSER_H
#define PATHPARSER_H

// 0:/path/test.txt -> path_root:/path_part/path_part
struct path_root
{
  int drive_no;
  struct path_part *first;
};

struct path_part
{
  const char *part;
  struct path_part *next;
};
struct path_root *pathparser_parse(const char *path, const char *current_directory_path);
void pathparser_free(struct path_root *root);

#endif