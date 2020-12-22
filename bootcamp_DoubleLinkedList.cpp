// Double Linked List
// push Mid
// pop Mid
// max, min, range, mean

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NULL <- 3 -> <- 5 -> 7 -> <- NULL
struct node
{
    char name[255];
    node *next, *prev;
}*head, *tail;

node *create_node(const char *name)
{
    node *temp = (node*)malloc(sizeof(node));
    strcpy(temp -> name, name);
    temp -> next = temp -> prev = NULL;
    return temp;
}

void push_head(const char *name)
{
    node *temp = create_node(name);
    if (!head) // linked list kosong
    {
        head = tail = temp;
    }

    else
    {
        temp -> next = head;
        head -> prev = temp;
        head = temp;
    }
}

void push_tail(const char *name)
{
    node *temp = create_node(name);
    if (!head) // linked list kosong
    {
        head = tail = temp;
    }

    else // >= 1 node
    {
        temp -> prev = tail;
        tail -> next = temp;
        tail = temp;
    }
}

void pop_head(const char *name)
{
    if (!head)
    {
        return;
    }

    else if (head == tail)
    {
        head = tail = NULL;
        free(head);
    }

    else
    {
        // harus tahu siapa kandidat baru
        node *temp = head -> next;
        head -> next = temp -> prev = NULL;
        head = NULL;
        free(head);
        head = temp;
    }
}

void pop_tail(const char *name)
{
    if (!head)
    {
        return;
    }

    else if (head == tail)
    {
        head = tail = NULL;
        free(head);
    }

    else
    {
        node *temp = tail -> prev;
        tail -> prev = temp -> next = NULL;

        // Dangling Pointer
        tail = NULL;
        free(tail);
        tail = temp;
    }
    
}

void push_mid(const char *name)
{
    node *temp = create_node(name);

    if (strcmp(name, head -> name) < 0)
    {
        push_head(name);
    }

    else if (strcmp(name, tail -> name) > 0)
    {
        push_tail(name);
    }

    node *current = head;

    while (strcmp(name, current -> name) > 0) // traverse sampai kondisi tidak terpenuhi
    // bukan "break" pakai break statement sih
    // lebih tepatnya pasti berhenti sebelum tail
    // dan ya keluar dari loop, bukan "break" dengan break statement (break;)
    {
        current = current -> next;
    }

    // current -> prev = temp; Tidak bisa pakai ini karena tidak dapat mengakses node Elvan.
    temp -> prev = current -> prev; // current itu adalah satu-satunya node yang diakses temp ini
    temp -> next = current;
    // temp -> prev = current -> prev -> prev;
    temp -> prev -> next = temp; // ATAU current -> prev -> next = temp;
    // temp -> prev -> next = temp;
    current -> prev = temp;
}

// Pop Mid sama seperti konsep Push Mid, tapi bedanya kalau di Push Mid kita assign, kalau di Pop Mid kita NULL-kan
void pop_mid(const char *name)
{
    if (!head)
    {
        return;
    }

    else if (strcmp(name, head -> name) == 0)
    {
        pop_head(name);
    }

    else if (strcmp(name, tail -> name) == 0)
    {
        pop_tail(name);
    }

    else
    {
        node *current = head;

        // current -> next != NULL (artinya kita sudah di tail)
        // current != NULL (artinya kita satu node setelah tail)

        while (current && strcmp(name, current -> name) != 0) // tambahkan kondisi setelah strcmp untuk mengantisipasi kalau nama tidak ada di linked list
        // bukan while (strcmp(name, current -> name) != 0 && current). Jadi, cek terlebih dahulu node-nya ada atau tidak karena kalau tidak ada node, ngapain harus cek kondisi sebelahnya lagi
        {
            current = current -> next;
        }
        // kondisi while itu cek dari kiri ke kanan

        current -> prev -> next = current -> next;
        current -> next -> prev = current -> prev;
        current -> next = current -> prev = NULL;
        current = NULL;

    }
    
}

void printLinkedList()
{
    node *current = head;

    while (current)
    {
        printf("%s -> ");
    }
}

int main()
{
    return 0;
}

// SEGMENTATION -- mengakses memori yang gagal