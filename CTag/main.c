/**
 * @file main.c
 * @author Antonin Nepras
 * @brief Tag test file
 * @version 0.1
 * @date 2022-08-17
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "src/tag.h"


void
tag_tree_print(Tag* tag, int indent);


int
main(int argc, const char** argv)
{
  // create html tag
  Tag* html = tag_new("html");

  // add ancestors
  Tag* head = tag_new("head");
  tag_add_child(html, head);

  Tag* title = tag_new("title");
  tag_set_text(title, "TEST");
  tag_add_child(head, title);

  Tag* body = tag_new("body");
  tag_add_child(html, body);

  Tag* paragraph = tag_new("p");
  tag_set_text(paragraph, "Hello there");
  tag_add_attr_new(paragraph,
                   "style",
                   "color:red;"
                   "background-color:black;"
                   "padding:20;"
                   "font-size:25");
  tag_add_child(body, paragraph);

  tag_tree_print(html, 0);

  // export and delete html tag
  tag_export(html, "test.html");
  tag_del(html);
}


void
tag_tree_print(Tag* tag, int indent)
{
  for (int i = 0; i < indent; ++i) {
    putchar('\t');
  }

  printf("%s\n",tag->name);
  for (int i = 0; i < tag->childs->size; ++i) {
    tag_tree_print(list_get(tag->childs, i), indent + 1);
  }
}
