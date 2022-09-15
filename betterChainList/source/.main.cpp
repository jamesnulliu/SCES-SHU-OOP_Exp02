#include "../header/ChainList.h"
#include <conio.h>

using namespace std;

int main()
{
    cout << "Create an empty chain list." << endl;
    ChainList<int> list;
    cout << "Test output:" << endl;
    try {
        cout << list << endl;
    } catch (EmptyChain e) {
        e.show();
    }
    cout << "[SYSTEM] Press any key to continue:" << endl << endl;
    int a = _getch();

    cout << "Insert 3 and 1 after headnode." << endl;
    list.insert(3); list.insert(1);
    cout << "Test output:" << endl;
    cout << list << endl;
    cout << "[SYSTEM] Press any key to continue:" << endl << endl;
    a = _getch();

    cout << "Insert 5 making it to be list[0]." << endl;
    list.insert(0, 5);
    cout << "Test output:" << endl;
    cout << list << endl;
    cout << "[SYSTEM] Press any key to continue:" << endl << endl;
    a = _getch();

    cout << "Sort." << endl;
    list.binSort(5);
    cout << "Test output:" << endl;
    cout << list << endl;
    cout << "[SYSTEM] Press any key to continue:" << endl << endl;
    a = _getch();

    cout << "Erase [2] 5." << endl;
    list.erase(2);
    cout << "Test output:" << endl;
    cout << list << endl;
    cout << "[SYSTEM] Press any key to continue:" << endl << endl;
    a = _getch();

    cout << "Delete the chain list." << endl;
    list.~ChainList();
    cout << "Test output:" << endl;
    try {
        cout << list << endl;
    } catch (EmptyChain e) {
        e.show();
    }

    cout << "\nPress enter to exit.";
    std::cin.get();
}