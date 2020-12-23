#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ke bawah adalah next, ke atas adalah prev.
8 -> top
3
5
2
1
*/
struct node
{
    int value;
    node *next, *prev;
}*top;

node *create_node (int value)
{
    node *temp = (node*)malloc(sizeof(node));
    temp -> value = value;
    temp -> next = temp -> prev = NULL;
    return temp;
}

void push(int value)
{
    node *temp = create_node(value);

    if (!top) // kasus 0 node
    {
        top = temp;
    }

    else
    {
        top -> prev = temp;
        temp -> next = top;
        top = temp;
    }
}

void remove() // tetap harus pasang kasus 1 node saja, kalau tidak segmentation fault
{
    if (!top) // kasus 0 node
    {
        return;
    }

    /*
    STACK
    8 (top)
    */
    else if (top && top -> next == NULL) // kasus 1 node
    {
        free(top);
        top = NULL;
    }

    else // kasus >1 node
    {
        // kita bisa langsung pop ke next
        /*  
        8 -> top
        ||
        3 (temp)
        */
       node *temp = top -> next;
       top -> next = temp -> prev = NULL; // antara top dengan temp, kita putuskan hubungannya
       free(top);
       top = temp;
    }
    
}

int peek()
{
    return (top) ? top -> value;
}

void print_stack()
{
    if (!top)
    {
        puts("Empty");
        return;
    }

    else
    {
        node *current = top;

        puts("Stack:");
        while (current)
        {
            printf("%d", current -> value);
            current = current -> next;
        }
        puts("");     
    }
}

void max_value()
{
    node *current = top;
    int max = current -> value;

    while (current && current -> value)
    {
        if (current -> value > max)
        {
            max = current -> value;
        }
        max = current -> value;
        current = current -> next;
    }
}

void min_value()
{
    
}

int main()
{
    push(8);
    /*
    push(4);
    remove();
    push(10);
    push(12);
    remove();
    remove();
    remove();
    */
    print_stack();
    push(4);
    print_stack();
    remove();
    print_stack();
    push(10);
    push(12);
    print_stack();
    remove();
    remove();
    remove();

    int top_value = peek(); // return nilai tertinggi
    
    if (top_value == 1)
    {
        puts("No node");
    }

    else
    {
        printf("%d\n", top_value); // dengan anggapan tidak ada angka -1 di dalam stack kalian
    }
    
    return 0;
}
