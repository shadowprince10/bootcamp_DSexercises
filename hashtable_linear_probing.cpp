// HASH TABLE LINEAR PROBING

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_ELEMENT = 6;
const int MAX_LENGTH = 255;
char hashtables[MAX_ELEMENT][255];

void view_hashtable()
{
    for (int i = 0; i < MAX_ELEMENT; i++)
    {
        printf("%d -> %s\n", i, hashtables[i]);
    }
}

// untuk mereturn indeks di hash table
int hash_function(const char *string)
{
    // ini untuk return karakter pertama dikurang string ASCII 'a'
    // lalu dimodulo max element

    return (string[0] - 'a') % MAX_ELEMENT;
}

// CONTOH VISUALISASI
// 0          1        2       3        4        5
// Abdul             Cecep    Dodi    Elvan    Fajar
int linear_probing(int index) // indeks ini sudah terisi, maka kita loop dari indeks + 1.
{
    // harus loop 2 hingga 5
    // dilanjutkan dengan loop 0 hingga 1
    // anggap indeks sekarang 2

    // intinya kita mau loop hingga max element. Ketika dia sudah sampai ke max element, diulang kembali prosesnya dari indeks awal.
    /*
    for (int i = index; i != index; i++)
    {
        if (hashtables[i][0] == '\0')
        {
            return i;
        }
    }

    for (int i = 0; i < index - 1; i++)
    {
        if (hashtables[i][0] != '\0')
        {
            return i;
        }
    }
    //return -1;
    // ngapain kita cek di indeks kalau indeks full.
    // jadi indeks + 1
    */

    for (int i = index + 1; i != index; i = (i + 1) % MAX_ELEMENT)
    {
        if (hashtables[i][0] != '\0')
        {
            return i;
        }
    }

    return -1; // menandakan bahwa loop sudah selesai, namun
    // belum masuk apa-apa, maka akan return -1
}

void insert(const char *string)
{
    int index = hash_function(string); // untuk mendapatkan indeks melalui hash function.

    // dari 0 hingga 9 isinya '\0' semua.
    if (hashtables[index][0] == '\0') // jika indeks masih kosong
    {
        strcpy(hashtables[index], string); // memasukkan string di hashtable
    }

    else // jika indeks telah terisi
    {
        index = linear_probing(index); // untuk mencari indeks baru
        if (index == -1)
        {
            puts("Sudah penuh");
            return;
        }
        strcpy(hashtables[index], string); // untuk memasukkan string di indeks baru
    }
}

int main()
{
    insert("Ben Alark");
    insert("Rosella Meadow");
    insert("Nicky Varensky");
    insert("Princella Sephora");
    insert("Vincent Oscario");
    view_hashtable();
}

