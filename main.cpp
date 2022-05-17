#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
#define ll long long
#define name "a"
#define sz size()
#define ff first
#define ss second
#include "RBTree.h"
typedef pair <int, int> ii;
const ll maxn = 2e5 + 7, mod = 1e9 + 7, base = 311, oo = 1e18;

int main()
{
//    ios_base::sync_with_stdio(0);
//    cin.tie(0);cout.tie(0);
//    freopen(name".inp", "r", stdin);
    //freopen(name".out", "w", stdout);
    RBTree a;
    cout << "Here are action you can take in Red - Black Tree:\n";
    cout << "1. Insert node into tree\n";
    cout << "2. Delete node in tree\n";
    cout << "3. Search any node in tree\n";
    cout << "4. Display tree\n";
    cout << "5. Exit\n";
    while(1)
    {
        cout << "-----------------------------------\n";
        cout << "The action you want to take: ";
        int sel; cin >> sel;
        if (sel == 1)
        {
            int x;
            cout << "Enter value of node you want to insert: ";
            cin >> x;
            a.InsertNode(x);
        }
        else if (sel == 2)
        {
            int x;
            cout << "Enter value of node you want to delete: ";
            cin >> x;
            a.findX(x);
        }
        else if (sel == 3)
        {
            int x;
            cout << "Enter value of node you want to search: ";
            cin >> x;
            a.SearchNode(x);
        }
        else if (sel == 4)
        {
            cout << "The tree have " << a.getNumberNode() << " node(s).\n";
            a.disp();
        }
        else
        {
            cout << "Thanks for using my demo of RBTree\n";
            return 0;
        }
    }
    return 0;
}
