#include <iostream>
#include <set>
#include <Windows.h>

const short SHIFT = 192;
const short LENOFLETTERS = 32;

using namespace std;

#pragma region list

struct ST {
    unsigned char letter;
    ST* next;
    ST(unsigned char l, ST* n) : letter(l), next(n) {}
    ~ST() { delete next; }
};

ST* ToList(unsigned char* set) {
    ST* x = nullptr;
    for (size_t i = 0; set[i]; ++i) {
        x = new ST(set[i], x);
    }
    return x;
}

bool isInSet(unsigned char item, ST* set) {
    ST* x = set;
    while (x) {
        if (x->letter == item) {
            return true;
        }
        x = x->next;
    }

    return false;
}

ST* DeleteItem(unsigned char item, ST* set) {
    ST* x = set;
    if (x->letter == item) {
        set = x->next;
        x->next = nullptr;
        delete x;
    }
    else {
        ST* tmp = x;
        x = x->next;
        while (x) {
            if (x->letter == item) {
                tmp->next = x->next;
                x->next = nullptr;
                delete x;
            }
            x = x->next;
            tmp = tmp->next;
        }
    }
    return set;
}

ST* AddItem(unsigned char item, ST* set) {
    set = new ST(item, set);
    return set;
}

ST* UnionSets(ST* source, ST* destination) {
    ST* s = source, * d = destination;
    while (s) {
        if (!isInSet(s->letter, d)) {
            d = AddItem(s->letter, d);
        }
        s = s->next;
    }
    return d;
}

ST* ExclusionSets(ST* source, ST* destination) {
    ST* s = source, * d = destination;
    while (s) {
        if (isInSet(s->letter, d)) {
            d = DeleteItem(s->letter, d);
        }
        s = s->next;
    }
    return d;
}

void PrintSet(ST* set) {
    while (set) {
        cout << set->letter;
        set = set->next;
    }
}

#pragma endregion all what needed for list

#pragma region set

void ToBool(unsigned char* set, bool* universum) {
    for (size_t i = 0; set[i]; ++i) {
        universum[set[i] - SHIFT] = true;
    }
}

void UnionSets(bool* source, bool* destination) {
    for (size_t i = 0; i < LENOFLETTERS; ++i) {
        if (source[i] != destination[i]) {
            destination[i] = true;
        }
    }
}

void ExclusionSets(bool* source, bool* destination) {
    for (size_t i = 0; i < LENOFLETTERS; ++i) {
        if (source[i] == destination[i]) {
            destination[i] = false;
        }
    }
}

void PrintSet(bool* set) {
    for (size_t i = 0; i < LENOFLETTERS; ++i) {
        if (set[i]) {
            cout << (unsigned char)(i + SHIFT);
        }
    }
}

#pragma endregion all what neded for set

#pragma region bool

bool isInSet(unsigned char item, unsigned char* set) {
    for (size_t i = 0; set[i]; ++i) {
        if (set[i] == item) {
            return true;
        }
    }

    return false;
}

void DeleteItem(int index, unsigned char* set) {
    for (size_t i = index; set[i]; ++i) {
        set[i] = set[i + 1];
    }
}

void AddItem(unsigned char item, unsigned char* set) {
    size_t i;
    for (i = 0; set[i]; ++i);
    set[i] = item;
    set[i + 1] = 0;
}

void UnionSets(unsigned char* source, unsigned char* destination) {
    for (size_t i = 0; source[i]; ++i) {
        if (!isInSet(source[i], destination)) {
            AddItem(source[i], destination);
        }
    }
}

void ExclusionSets(unsigned char* source, unsigned char* destination) {
    for (size_t i = 0; source[i]; ++i) {
        if (isInSet(source[i], destination)) {
            DeleteItem(i, destination);
        }
    }
}

void PrintSet(unsigned char* set) {
    for (size_t i = 0; set[i]; ++i) {
        cout << set[i];
    }
}

#pragma endregion all what neded for bool

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    unsigned char A[LENOFLETTERS + 1];
    unsigned char B[LENOFLETTERS + 1];
    unsigned char C[LENOFLETTERS + 1];
    unsigned char D[LENOFLETTERS + 1];
    unsigned char E[LENOFLETTERS + 1] = {'\0'};

    ST* A_List = nullptr;
    ST* B_List = nullptr;
    ST* C_List = nullptr;
    ST* D_List = nullptr;
    ST* E_List = nullptr;

    bool A_Bool[LENOFLETTERS] = { false };
    bool B_Bool[LENOFLETTERS] = { false };
    bool C_Bool[LENOFLETTERS] = { false };
    bool D_Bool[LENOFLETTERS] = { false };
    bool E_Bool[LENOFLETTERS] = { false };

    cout << "Enter set A: ";
    cin >> A;
    cout << "Enter set B: ";
    cin >> B;
    cout << "Enter set C: ";
    cin >> C;
    cout << "Enter set D: ";
    cin >> D;

    ToBool(A, A_Bool);
    ToBool(B, B_Bool);
    ToBool(C, C_Bool);
    ToBool(D, D_Bool);

    UnionSets(A_Bool, E_Bool);
    ExclusionSets(B_Bool, E_Bool);
    ExclusionSets(C_Bool, E_Bool);
    ExclusionSets(D_Bool, E_Bool);

    cout << "Resulted set E: ";
    PrintSet(E_Bool);

    return 0;
}
