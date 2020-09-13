#include <iostream>
#include <set>
#include <Windows.h>

const short SHIFT = 192;
const short LENOFLETTERS = 32;
const int ONE = 1;

using namespace std;

#pragma region set

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

#pragma endregion all what neded for set

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

#pragma region bool

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

#pragma endregion all what neded for bool

#pragma region word

int ToMachineWord(unsigned char* set) {
    int mword = 0;
    for (size_t i = 0; set[i]; ++i) {
        mword = mword | ONE << (int)(set[i] - SHIFT);
    }
    return mword;
}

bool isInSet(int index, int mword) {
    return mword & ONE << index;
}

int DeleteItem(int index, int mword) {
    mword = mword & ~(ONE << index);
    return mword;
}

int AddItem(int index, int mword) {
    mword = mword | ONE << index;
    return mword;
}

void UnionSets(int source, int& destination) {
    for (size_t i = 0; i < LENOFLETTERS; ++i) {
        if (isInSet(i, source)) {
            destination = AddItem(i, destination);
        }
    }
}

void ExclusionSets(int source, int& destination) {
    for (size_t i = 0; i < LENOFLETTERS; ++i) {
        if (isInSet(i, source)) {
            destination = DeleteItem(i , destination);
        }
    }
}

void PrintSet(int mword) {
    int one = 1;
    for (size_t i = 0; i < LENOFLETTERS; ++i) {
        if (mword & one << i) {
            cout << (unsigned char)(i + SHIFT);
        }
    }
}

#pragma endregion all what neded for word

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    unsigned char choose;

    unsigned char A[LENOFLETTERS + 1];
    unsigned char B[LENOFLETTERS + 1];
    unsigned char C[LENOFLETTERS + 1];
    unsigned char D[LENOFLETTERS + 1];
    unsigned char E[LENOFLETTERS + 1] = {'\0'};

    cout << "Choose type of memory: " << endl << "1. Array of values" << endl;
    cout  << "2. List of values" << endl << "3. Boolean array " << endl;
    cout << "4. Machine word" << endl;

    do {
        cin >> choose;
        if (choose < '1' && choose > '4') {
            cout << "Incorrect enter, try again" << endl;
        }
    } while (choose < '1' && choose > '4');

    cout << "Enter set A: ";
    cin >> A;
    cout << "Enter set B: ";
    cin >> B;
    cout << "Enter set C: ";
    cin >> C;
    cout << "Enter set D: ";
    cin >> D;

    switch (choose) {
    case '1':
        UnionSets(A, E);

        ExclusionSets(B, E);
        ExclusionSets(C, E);
        ExclusionSets(D, E);

        cout << "Resulted set E: ";
        PrintSet(E);
        break;
    case '2':
        ST * A_List = nullptr;
        ST* B_List = nullptr;
        ST* C_List = nullptr;
        ST* D_List = nullptr;
        ST* E_List = nullptr;

        A_List = ToList(A);
        B_List = ToList(B);
        C_List = ToList(C);
        D_List = ToList(D);

        E_List = UnionSets(A_List, E_List);

        E_List = ExclusionSets(B_List, E_List);
        E_List = ExclusionSets(C_List, E_List);
        E_List = ExclusionSets(D_List, E_List);

        cout << "Resulted set E: ";
        PrintSet(E_List);
        break;
    case '3':
        bool A_Bool[LENOFLETTERS] = { false };
        bool B_Bool[LENOFLETTERS] = { false };
        bool C_Bool[LENOFLETTERS] = { false };
        bool D_Bool[LENOFLETTERS] = { false };
        bool E_Bool[LENOFLETTERS] = { false };


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
        break;
    case '4':
        int A_Mword = 0;
        int B_Mword = 0;
        int C_Mword = 0;
        int D_Mword = 0;
        int E_Mword = 0;

        A_Mword = ToMachineWord(A);
        B_Mword = ToMachineWord(B);
        C_Mword = ToMachineWord(C);
        D_Mword = ToMachineWord(D);

        UnionSets(A_Mword, E_Mword);

        ExclusionSets(B_Mword, E_Mword);
        ExclusionSets(C_Mword, E_Mword);
        ExclusionSets(D_Mword, E_Mword);

        cout << "Resulted set E: ";
        PrintSet(E_Mword);
        break;
    }

    return 0;
}
