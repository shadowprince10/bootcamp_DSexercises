#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_ELEMENT = 10;

struct node
{
    char name[255];
    node *next; // buat Friends kalau di project Study Network
    // node *up; // buat post kalau di project Study Network
}*head[MAX_ELEMENT], *tail[MAX_ELEMENT];


// hash angka -- simplenya angka modulo MAX_ELEMENT kalau misalkan angka cukup random
// kalau angka mirip dan kurang random, buat random terlebih dahulu dengan memperlebar range-nya.
// 20 * 20 % MAX_ELEMENT;
// 20 -> '2' + '0' = ASCII 2 + ASCII 0 + ASCII X % MAX_ELEMENT;
// di mana X ini adalah rand() -> random value kelipatan 13
// ATAU
// di mana X ini adalah rand() -> random value kelipatan Y
// di mana Y adalah random prime number dari 0 sampai 100. Ini akan semakin memperbesar kemungkinan range.
// random sama pas dicek run meski random banyak
// ini yang dinamakan dengan Prime Hashing
// Cari saja Fibonacci Hashing
node *create_node(const char *string)
{
    node *temp = (node*)malloc(sizeof(node));
    strcpy(temp -> name, string);
    temp -> next = NULL;
    return temp;
}

void push_friends()
{
    // pakai next
}

void push_post()
{
    // pakai up
}

unsigned long djb2(const char *string) // hashing function algorithm untuk menghasilkan angka dari sebuah string
{
    unsigned long hash = 5381;
    int c;

    while ((c = *string++))
    {
        hash = ((hash << 5) + hash) + c;
    }
}

// tergantung soal -- biasa diberitahu nama hash function apa
// biasa keluar di BINUS hash function -- ASCII sum sesuai nama ditambhakn di karakter

void insert(const char *string)
{
    // 0 -> .. -> ..
    // .. 1 -> ..
    // 
    int index = djb2(string);

    if (head[index] == NULL) // jika head kosong
    {
        head[index] = tail[index];
    }

    else // jika head telah terisi
    {
        node *new_node = create_node(string);
        tail[index] -> next = new_node;
        tail[index] = new_node;
    }
}

void traverse_linked_list (int i)
{
    if (head[i])
    {
        node *current = head[i];
        while (current)
        {
            printf("%s -> ", current -> name);
            current = current -> next;
        }
    }
}

void view()
{

    for (int i = 0; i < MAX_ELEMENT; i++)
    {
        if (head[i]) // kalau ada head, dia akan taruh head di current
        {
            // node *current = head[i];
            // kalau kalian mau ada versi yang lebih modular-nya
            traverse_linked_list(i);
            puts("");
        }

        else
        {
            puts("NULL");
        }
        
    }
}
