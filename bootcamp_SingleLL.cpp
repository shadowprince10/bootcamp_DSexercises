// BOOTCAMP (SINGLE) LINKED LIST I CODING
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Buat terlebih dahulu struct-nya
/*
struct Node
{
    char name[255];
    int score;
};
*/

// kalau kita ingin menjadikan Linked List, kita tinggal menambahkan satu baris di Struct, yaitu pointer. Selain itu, kita juga tambahkan head dan tail.

struct Node
{
    char name[255];
    int score;
    Node *next; // pointer ke node selanjutnya
} *head, *tail; // head: note pertama, tail: node terakhir

// 3
// kalau hanya 1 data, data tersebut adalah head dan tail.
// 3 -> 4
// Beda kasusnya kalau 2 data, maka data pertama adalah head dan data kedua adalah tail.

Node *create_node(const char *name, int score)
{
    Node *new_node = (Node*) malloc(sizeof(Node)); // kita tulis Node* supaya typecast karena malloc return pointer.
    strcpy(new_node -> name, name);
    new_node -> score = score;
    new_node -> next = NULL; // awalnya tidak memiliki node selanjutnya
    return new_node;
}

// head                tail
// A5   ->   B7    ->   C9
// FUNGSI INSERT DATA
void push_tail(const char *name, int score) // push dari depan ke belakang
{
    // kita buat terlebih dahulu node-nya
    Node *temp = create_node(name, score); // memmbuat node baru
    if (!head) // kasus linked list kosong (0 node)
    {
        head = tail = temp; // current akan menjadi head dan tail
    }

    else // >= 1 node
    {
        tail -> next = temp; // tail lama -> next adalah node baru
        tail = temp; // current akan menjadi tail (node terakhir)
    }
}

void push_head(const char* name, int score)
{
    /*
    VISUALISASI:
    // kita ingin push head A1 di linked list berikut:
    // A2 (head) -> B3 -> C4 (tail) -> NULL
    // A1 (temp) -> NULL || Node *temp = create_new_node(name, score)
    // 
    // A1 -> A2 (head) -> B3 -> C4 -> D10 (tail) -> NULL || head = temp;

    */
    Node *temp = create_node(name, score);
    
    if (head == NULL)
    {
        head = tail = temp;
    }

    else
    {
        temp -> next = head;
        head = temp;
    }
}

void pop_head()
{
    if(!head) // jika tidak ada node
    {
        return; // return (tidak melakukan apa-apa)
    }

    else
    {
        // INITIAL: 98 (head) -> 100 -> 95 -> 97 (tail)
        Node *temp = head; // 98 (head, temp) -> 100 -> 95 -> 97 (tail)
        head = temp -> next; // 98 (temp) -> 100 (head) -> 95 -> 97 (tail)
        temp -> next = NULL; // 98 (temp) -> NULL || 100 (head) -> 95 -> 97 (tail)
        free(temp); // 100 (head) -> 95 -> 97 (tail)

    }  
}

void pop_tail()
{
    if(!head) // jika tidak ada node
    {
        return; // return (tidak melakukan apa-apa)
    }

    else if (head == tail) // kasus 1 node
    {
        free(head); // free node tersebut
        // atau free(tail);
    }

    else
    {
        // INITIAL: 98 (head) -> 100 -> 95 -> 97 (tail)
        Node *temp = head; // 98 (head, temp) -> 100 -> 95 -> 97 (tail)

        while (temp -> next != tail)
        {
            temp = temp -> next;
        }

        temp -> next = NULL; // 98 (temp) -> NULL || 100 (head) -> 95 -> 97 (tail)
        free(temp); // 100 (head) -> 95 -> 97 (tail)
        tail = temp;

    }  
}

void print_LinkedList()
{
    Node *current = head;

    while (current) // selama current bukan NULL
    {
        printf("%s %d", current -> name, current -> score);
        current = current -> next; // current akan berjalan ke code selanjutnya
    }
    puts("NULL");
}

int main()
{

    /*
    push_head("Ben Alark", 100); // 100 (head, tail) -> NULL 
    push_tail("Vincent Oscario", 50); // 100 (head) -> 50 (tail) -> NULL
    push_head("Rosella Meadow", 95); // 95 (head) -> 100 -> 50 (tail) -> NULL
    push_head("Nicky Varensky", 88); // 88 (head) -> 95 -> 100 -> 50 (tail) -> NULL
    push_tail("Princella Sephora", 98); // 88 (head) -> 95 -> 100 -> 50 -> 98 (tail) -> NULL
    push_tail("Sverra Note", 92); // 88 (head) -> 95 -> 100 -> 50 -> 98 -> 92 (tail) -> NULL
    */

    push_head("Ben Alark", 100); // 100 (head, tail) -> NULL 
    push_tail("Vincent Oscario", 50); // 100 (head) -> 50 (tail) -> NULL
    push_head("Rosella Meadow", 95); // 95 (head) -> 100 -> 50 (tail) -> NULL
    push_head("Nicky Varensky", 88); // 88 (head) -> 95 -> 100 -> 50 (tail) -> NULL
    pop_head(); // 95 (head) -> 100 -> 50 (tail) -> NULL
    pop_tail(); // 95 (head) -> 100 (tail) -> NULL
    pop_tail(); // 95 (head, tail) -> NULL
    pop_head(); // NULL

    print_LinkedList();
    

    return 0;
}



