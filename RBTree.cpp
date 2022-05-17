#include "RBTree.h"
RBTree::RBTree()
{
    //ctor
    root = NULL;
    numberOfNode = 0;
//    root->color = 'b';
}

RBTree::~RBTree()
{
    //dtor
}

void RBTree::LeftRotate(node *x)
{
    if (x->right == NULL)
        return;
    node *y = x->right;

    if (x->parent == NULL)
    {
        root = y;
        y->parent = NULL;
    }
    else
    {
        y->parent = x->parent;
        if (x->parent->left == x)
            x->parent->left = y;
        else x->parent->right = y;
    }

    if (y->left != NULL)
    {
        x->right = y->left;
        y->left->parent = x;
    }
    else x->right = NULL;

    y->left = x;
    x->parent = y;
}

void RBTree::RightRotate(node *x)
{
    if (x->left == NULL)
        return;
    node *y = x->left;

    if (x->parent == NULL)
    {
        root = y;
        y->parent = NULL;
    }
    else
    {
        y->parent = x->parent;
        if (x->parent->left == x)
            x->parent->left = y;
        else x->parent->right = y;
    }

    if (y->right != NULL)
    {
        x->left = y->right;
        y->right->parent = x;
    }
    else x->left = NULL;

    y->right = x;
    x->parent = y;
}

void RBTree::InsertNode(int val)
{
    node *new_node = new node;
    new_node->val = val;
    new_node->color = 'r';
    new_node->left = NULL;
    new_node->right = NULL;

    ++numberOfNode;

    if (root == NULL)
    {
        root = new_node;
        new_node->parent = NULL;
    }
    else
    {
        node *cur = root;
        node *pa;
        while (cur != NULL)
        {
            pa = cur;
            if (val > cur->val)
                cur = cur->right;
            else cur = cur->left;
        }
        new_node->parent = pa;
        if (new_node->val > pa->val)
            pa->right = new_node;
        else pa->left = new_node;
    }
    InsertFix(new_node);
    root->color = 'b';
    cout << "Inserted " << val << " into tree!\n";
}

void RBTree::InsertFix(node *x)
{
    // if x is root, just change its color is black
    if (x == root)
    {
        x->color = 'b';
        return;
    }
    root->color = 'b';

    // now, we will check the color of parent of x
    node *p = x->parent;
    if (p->color == 'b')
        return;
    else // the color of parent of x is red -> conflict
    {
        // now we will check the color of node uncle
        node *u;
        if (p == p->parent->left)
            u = p->parent->right;
        else u = p->parent->left;
        if (u != NULL && u->color == 'r')
        {
            u->color = 'b';
            p->color = 'b';
            p->parent->color = 'r';
            InsertFix(p->parent);
        }

        else // the color of node uncle is black, so we will have 4 case
        {
            node *g = p->parent;
            // Left case
            if (p == g->left)
            {
                // left right case
                if (x == p->right)
                {
                    LeftRotate(p);
                    p = p->parent;
                }
                p->color = 'b';
                g->color = 'r';
                RightRotate(g);
            }
            else // right case
            {
                // right left case
                if (x == p->left)
                {
                    RightRotate(p);
                    p = p->parent;
                }
                p->color = 'b';
                g->color = 'r';
                LeftRotate(g);
            }
        }
    }
    root->color = 'b';
}

node* RBTree::successor(node *x)
{
    // this function will find node have value max in left child or min value in right child
    if (x->left == NULL && x->right == NULL)
        return NULL;
    if (x->left != NULL)
    {
        x = x->left;
        while (x->right != NULL)
            x = x->right;
    }
    else
    {
        x = x->right;
        while (x->left != NULL)
            x = x->left;
    }
    return x;
}

node *RBTree::sibling(node *x)
{
    if (x->parent->left == x)
        return x->parent->right;
    return x->parent->left;
}

node* RBTree::BSTreplace(node *x)
{
    // x have two child
    if (x->left != NULL && x->right != NULL)
        return successor(x);
    // x is the leaf
    if (x->left == NULL && x->right == NULL)
        return NULL;
    // x have a child
    if (x->left != NULL)
        return x->left;
    return x->right;
}

void RBTree::findX(int x)
{
    node *cur = root;
    while (cur != NULL)
    {
        if (x == cur->val)
        {
            --numberOfNode;
            cout << "Deleted " << x << " in tree!\n";
            return DeleteNode(cur);
        }
        if (x > cur->val)
            cur = cur->right;
        else cur = cur->left;

    }
    cout << "Not found " << x << " in tree" << '\n';
}

void RBTree::DeleteNode(node *need_to_delete)
{
    node *child = BSTreplace(need_to_delete);

    bool uvBlack = ((child == NULL || child->color == 'b') && (need_to_delete->color == 'b'));
    node *parent = need_to_delete->parent;
    if (child == NULL) // need_to_delete is leaf
    {
        if (need_to_delete == root)
            root = NULL;
        else
        {
            if (uvBlack) // node need to delete and node its child have color black
                fixDoubleBlack(need_to_delete);// node need to delete become double black
            else // node need to delete or its child have color red
            {
                if (sibling(need_to_delete) != NULL) // if sibling not null, make it red
                    sibling(need_to_delete)->color = 'r';
            }

            // delete node from tree
            if (need_to_delete == need_to_delete->parent->left)
                parent->left = NULL;
            else parent->right = NULL;
      }
      delete need_to_delete;
      return;
    }

    if (need_to_delete->left == NULL || need_to_delete->right == NULL) // node need to delete have 1 child
    {
        if (need_to_delete == root) // if the node is root, just assign val of child to root, then delete child
        {
            need_to_delete->val = child->val;
            need_to_delete->left = need_to_delete->right = NULL;
            delete child;
        }
        else
        {
            if (need_to_delete == need_to_delete->parent->left)
                parent->left = child;
            else parent->right = child;
            delete need_to_delete;

            child->parent = parent;

            if (uvBlack)
                fixDoubleBlack(child);
            else child->color = 'b';// one of them have red color -> change color of child become to black
        }
        return;
    }
    // node need to delete have 2 child
    swap(child->val, need_to_delete->val);
    DeleteNode(child);
}

void RBTree::fixDoubleBlack(node *x)
{
    if (x == root)
      return;

    node *s = sibling(x);
    node *parent = x->parent;
    if (s == NULL)
        fixDoubleBlack(parent);
    else
    {
        if (s->color == 'r') // sibling is red
        {
            parent->color = 'r';
            s->color = 'b';
            if (s == s->parent->left)
                RightRotate(parent); // left case
            else LeftRotate(parent); // right case
            fixDoubleBlack(x);
        }
        else // sibling is black
        {
            if ((s->left != NULL && s->left->color == 'r') || (s->right != NULL && s->right->color == 'r')) // have red child
            {
                if (s->left != NULL && s->left->color == 'r')
                {
                    if (s == s->parent->left) // left left case
                    {
                        s->left->color = s->color;
                        s->color = parent->color;
                        RightRotate(parent);
                    }
                    else // right left case
                    {
                        s->left->color = parent->color;
                        RightRotate(s);
                        LeftRotate(parent);
                    }
                }
                else
                {
                    if (s == s->parent->left) // left right
                    {
                        s->right->color = parent->color;
                        LeftRotate(s);
                        RightRotate(parent);
                    }
                    else // right right
                    {
                        s->right->color = s->color;
                        s->color = parent->color;
                        LeftRotate(parent);
                    }
                }
                parent->color = 'b';
            }
            else // have 2 black child
            {
                s->color = 'r';
                if (parent->color == 'b')
                    fixDoubleBlack(parent);
                else parent->color = 'b';
            }
        }
    }
}

int global_length;

int _get_height(node *sr)
{
    if (!sr)
        return -1;
    return 1 + max(_get_height(sr->left), _get_height(sr->right));
}

void set_color(int b)
{
    int code = (0 << 4) | b;
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color , code);
}

void _display_subtree(node *q, char **output, int left, int top, int width, int **make_color)
{
    string str = to_string(q->val);

    int left_begin_shift = 1 - (str.length()-1)/2;
    for (int i = 0; i < str.length() && left + width/2 + i < global_length; i++)
    {
        if (q->color == 'r')
            make_color[top][left + width/2 + left_begin_shift + i] = 4;

        else if (q->color == 'b')
            make_color[top][left + width/2 + left_begin_shift + i] = 2;
        else make_color[top][left + width/2 + left_begin_shift + i] = 7;
            output[top][left + width/2 + left_begin_shift + i] = str[i];
    }

    int branch_off_set = (width+3)/pow(2, 3);
    int mid = left + width/2;
    int left_mid = left + (width/2 - 1)/2;
    int right_mid = left + width/2 + 2 + (width/2 - 1)/2;

    if (q->left)
    {
        int branch_position = mid - branch_off_set + 1;
        for (int pos = mid + left_begin_shift - 2; pos > branch_position; pos--)
        {
            output[top][pos] = '_';
            make_color[top][pos] = 7;
        }
        output[top+1][branch_position] = '/';
        make_color[top+1][branch_position] = 7;

        for (int pos = branch_position-1; pos > left_mid + 2; pos--)
        {
            output[top+1][pos] = '_';
            make_color[top+1][pos] = 7;
        }
        _display_subtree(q->left, output, left, top+2, width/2 - 1, make_color);
    }

    if (q->right)
    {
        int branch_position = mid + branch_off_set + 1;
        for (int pos = mid + left_begin_shift + str.length() + 1; pos < branch_position; pos++)
        {
            output[top][pos] = '_';
            make_color[top][pos] = 7;
        }
        output[top+1][branch_position] = '\\';
        make_color[top+1][branch_position] = 7;
        for (int pos = branch_position+1; pos < right_mid; pos++)
        {
            output[top+1][pos] = '_';
            make_color[top+1][pos] = 7;
        }
        _display_subtree(q->right, output, left + width/2 + 2, top+2, width/2 - 1, make_color);
    }
}


void RBTree::_display_tree(node *root)
{
    if (!root)
        return;

    int height = _get_height(root);
    int width_display = 4*pow(2, height) - 3;
    int height_display = 2 * height + 1;

    global_length = width_display + 4;
    char **output = new char *[height_display];
    int **make_color = new int *[height_display];
    for (int i = 0; i < height_display; i++)
    {
        output[i] = new char [width_display + 4];
        make_color[i] = new int [width_display + 4];
        for (int j = 0; j <  width_display + 4; j++)
        {
            if (j == width_display + 3)
            {
                output[i][j] = '\0';
                make_color[i][j] = 7;
            }
            else
            {
                output[i][j] = ' ';
                make_color[i][j] = 7;
            }
        }
    }
    _display_subtree(root, output, 0, 0, width_display, make_color);

    for (int row = 0; row < height_display; row++)
    {
        for (int i = 0; i < width_display + 4; ++i)
        {
            set_color(make_color[row][i]);
            cout << output[row][i];
        }
        cout << '\n';
        set_color(7);
        //cout << output[row] << endl;
    }
}

void RBTree::disp()
{
    _display_tree(root);
}

void RBTree::SearchNode(int x)
{
    node *cur = root;
    while (cur != NULL)
    {
        if (cur->val == x)
        {
            cout << "FOUND " << x << '\n';
            cout << "Key: " << x << '\n';
            cout << "Color: ";
            if (cur->color == 'b')
            {
                set_color(2);
                cout << "BLACK\n";
            }
            else
            {
                set_color(4);
                cout << "RED\n";
            }
            set_color(7);
            if (cur->left == NULL)
                cout << "Don't have left child\n";
            else cout << "Left child: " << cur->left->val << '\n';
            if (cur->right == NULL)
                cout << "Don't have right child\n";
            else cout << "Right child: " << cur->right->val << '\n';
            return;
        }
        else
        {
            if (x > cur->val)
                cur = cur->right;
            else cur = cur->left;
        }
    }
    cout << "Don't found node have value " << x << endl;
    return;
}

int RBTree::getNumberNode()
{
    return numberOfNode;
}
