#include "tree.c"

typedef struct splay_string
{
    splay_tree * tree;
    int nodes_count;
} splay_string;

typedef struct string_element
{
    int index;
    char * element;
} string_element;

bool bigger_predicate(void * first_element, void * second_element)
{
    return *(int *)(first_element) > *(int *)(second_element);
}

string_element * new_string_element(int index, char * element)
{
    string_element * str_element = malloc(sizeof(*str_element));
    str_element->element = element;
    str_element->index = index;
    return str_element;
}

splay_string * new_string(char * char_string)
{
    splay_string * string = malloc(sizeof(*string));
    string->tree = new_tree();
    string->nodes_count = 0;
    for(int i = 0; i < sizeof(char_string); ++i)
    {
        string_element * element = new_string_element(i, &char_string[i]);
        insert(string->tree, element, bigger_predicate);
        ++string->nodes_count;
    }
    return string;
}

void set_indices(int * start_index, int * last_index, splay_string * string)
{
    *start_index = 0;
    *last_index = string->nodes_count;
}

int * find_substring(splay_string * string, splay_string * substring, int start_index, int end_index)
{
   set_indices(&start_index, &end_index, string); // end_index = len(string) //
   printf("%d, %d", start_index, end_index);
   return &start_index;
}

int main(){
    char * string = "Hello!";
    char * substring = "Hel";
    printf("%d\n", sizeof(string));
    splay_string * string_ = new_string(string);
    splay_string * substring_ = new_string(substring);
    int start, end;
    find_substring(string_, substring_, start, end);
    return 0;
}