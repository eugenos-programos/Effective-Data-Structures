#include "tree.c"

typedef struct string
{
    splay_tree * tree;
    int * nodes_count;
} splay_string;

bool bigger_predicate(void * first_element, void * second_element)
{
    return *(int *)(first_element) > *(int *)(second_element);
}

splay_string * create_string(char * char_string)
{
    splay_string * string = malloc(sizeof(*string));
    string->tree = new_tree();
    for(int i = 0; i < sizeof(char_string); ++i)
    {
        void * string_element = &char_string[i];
        insert(string->tree, string_element, bigger_predicate);
        ++string->nodes_count;
    }
    return string;
}

int * find_substring(splay_string * string, splay_string * substring)
{
    
}

int main(){
    char * string = "Hello!";
    splay_string * string_ = create_string(string);
    return 0;
}