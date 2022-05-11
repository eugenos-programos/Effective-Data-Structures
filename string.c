#include "tree.c"
#include <string.h>

typedef struct splay_string
{
    splay_tree * tree;
    const unsigned int nodes_count;
} splay_string;

typedef struct string_element
{
    unsigned int index;
    char element;
} string_element;

bool bigger_predicate(void * first_element, void * second_element)
{
    return ((string_element *)(first_element))->index > ((string_element *)(second_element))->index;
}

bool equal_predicate(void * first_element, void * second_element)
{
    return ((string_element *)(first_element))->index == ((string_element *)(second_element))->index;
}

string_element * new_string_element(unsigned int index, char element)
{
    string_element * str_element = malloc(sizeof(*str_element));
    str_element->element = element;
    str_element->index = index;
    return str_element;
}

unsigned int strlength(char * string)
{
    unsigned int length = 0;
    char el = string[length];
    while (el != '\0')
    {
        ++length;
        el = string[length];
    }
    return length;
}

splay_string * new_string(char * char_string)
{
    splay_string * string = malloc(sizeof(*string));
    *(unsigned int *)&string->nodes_count = strlength(char_string);
    string->tree = new_tree();
    for (unsigned int i = 0; i < string->nodes_count; ++i)
    {
        string_element * element = new_string_element(i, char_string[i]);
        insert(string->tree, element, bigger_predicate);
    }
    return string;
}

void set_indices(unsigned int * start_index, unsigned int * last_index, splay_string * string)
{
    *start_index = 0;
    *last_index = string->nodes_count;
}

char get_char_element(splay_string * string, unsigned int index)
{
    char empty_char;
    string_element * str_el = new_string_element(index, empty_char);
    splay_node * node = _search(string->tree, (void *)(str_el), bigger_predicate, equal_predicate);
    if (node == NULL)
    {
        printf("No element with index = %d", index);
        exit(1);
    }
    string_element * str_char_el = (string_element *)(node->data);
    return str_char_el->element;
}

unsigned int find_substring(splay_string * string, splay_string * substring)
{
   unsigned int start_index, end_index;
   set_indices(&start_index, &end_index, string); 
   unsigned int substring_length = substring->nodes_count;
   for (unsigned int i = 0; i < end_index - substring_length + 1; ++i)
   {
       unsigned int j = 0;
       while (j < substring_length)
       {
           char empty_char;
           string_element * str_element = new_string_element(i + j, get_char_element(string, i + j));
           splay_node * str_node = _search(string->tree, (void *)(str_element), bigger_predicate, equal_predicate);
           string_element * substr_element = new_string_element(j, get_char_element(string, j));
           splay_node * substr_node = _search(substring->tree, (void *)(substr_element), bigger_predicate, equal_predicate);
           char char_str_el = ((string_element *)(str_node->data))->element;
           char char_substr_el = ((string_element *)(substr_node->data))->element;
           if (char_str_el != char_substr_el)
           {
               break;
           }
           ++j;
       }
       if (j == substring_length)
       {
           return i;
       }
   }
   unsigned int not_found_code = -1;     
   return not_found_code;
}

bool equal_strings(splay_string * first_string, splay_string * second_string)
{
    return find_substring(first_string, second_string) == 0 && find_substring(second_string, first_string) == 0;
}

void delete_substring(splay_string * string, splay_string * substring)
{
    unsigned int start_index = find_substring(string, substring);
    unsigned int substring_length = substring->nodes_count;
    char * new_string = "";

    for (unsigned int index = start_index; index < start_index + substring_length; ++index)
    {
        char char_element = get_char_element(string, index);
        string_element * str_el = new_string_element(index, char_element);
        erase(string->tree, (void *)(str_el), bigger_predicate, equal_predicate);
    }
    *(unsigned int *)&string->nodes_count -= substring->nodes_count;
}

unsigned int main(){
    char * string = "Hello!";
    char * substring = "lo!";
    splay_string * string_ = new_string(string);
    splay_string * substring_ = new_string(substring);
    delete_substring(string_, substring_);
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!%d", find_substring(string_, substring_));
    return 0;
}
