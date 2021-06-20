#include "classes.h"

using namespace std;

//RedBlack tree class
template <class T>
class RedBlackTree
{
    //Structure of node
    struct RedBlackTreeNode
    {
        T value_;
        bool colour_;
        RedBlackTreeNode* parent_;
        RedBlackTreeNode* left_;
        RedBlackTreeNode* right_;
        int size_;

        //Constructors
        RedBlackTreeNode(const T& el) : value_(el), colour_(1), parent_(nullptr), left_(nullptr), right_(nullptr), size_(1) {};

        RedBlackTreeNode(const RedBlackTreeNode* node) : value_(node->value_), colour_(node->colour_),
            parent_(node->parent_), left_(node->left_), right_(node->right_), size_(node->size_) {}

        //Output in console
        void Print(ostream& os)
        {
            if (colour_)
                os << red;
            os << "Value: " << value_;// << "; Parent: ";
        //    if (parent_)
        //        os << parent_->value_;
        //    else os << "NULL";
        //    os << "; Left: ";
        //    if (left_)
        //        os << left_->value_;
        //    else os << "NULL";
        //    os << "; Right: ";
        //    if (right_)
        //        os << right_->value_;
        //    else os << "NULL";
            os << "; Size: " << size_;
            os << blue;
        }
    };

    //Overloaded operator = 
    RedBlackTreeNode* operator=(const RedBlackTreeNode* node)
    {
        return RedBlackTreeNode(node);
    }

    RedBlackTreeNode* root_;

    //Left rotate function
    void LeftRotate(RedBlackTreeNode* x)
    {
        RedBlackTreeNode* y(x->right_);
        y->size_ = x->size_;
        x->right_ = y->left_;
        if (y->left_)
            y->left_->parent_ = x;
        y->parent_ = x->parent_;
        if (!x->parent_)
            root_ = y;
        else if (x == x->parent_->left_)
            x->parent_->left_ = y;
        else x->parent_->right_ = y;
        y->left_ = x;
        x->parent_ = y;
        x->size_ = 1;
        if (x->left_)
            x->size_ += x->left_->size_;
        if (x->right_)
            x->size_ += x->right_->size_;
    }

    //Right rotate funtion
    void RightRotate(RedBlackTreeNode* x)
    {
        RedBlackTreeNode* y(x->left_);
        y->size_ = x->size_;
        x->left_ = y->right_;
        if (y->right_)
            y->right_->parent_ = x;
        y->parent_ = x->parent_;
        if (!x->parent_)
            root_ = y;
        else if (x == x->parent_->right_)
            x->parent_->right_ = y;
        else x->parent_->left_ = y;
        y->right_ = x;
        x->parent_ = y;
        x->size_ = 1;
        if (x->left_)
            x->size_ += x->left_->size_;
        if (x->right_)
            x->size_ += x->right_->size_;
    }

    //Function that repair red black tree properties after insertion
    void InsertFixup(RedBlackTreeNode* node)
    {
        RedBlackTreeNode* u;
        if (root_ == node)
        {
            node->colour_ = 0;
            return;
        }
        while (node->parent_ && node->parent_->colour_)
        {
            RedBlackTreeNode* g = node->parent_->parent_;
            if (node->parent_ == node->parent_->parent_->left_)
            {
                if (g->right_)
                {
                    u = g->right_;
                    //node->parent_->colour_ = 0;
                    if (u->colour_)
                    {
                        node->parent_->colour_ = 0;
                        u->colour_ = 0;
                        g->colour_ = 1;
                        node = g;
                    }
                }
                else
                {
                    if (node->parent_->right_ == node)
                    {
                        node = node->parent_;
                        LeftRotate(node);
                    }
                    node->parent_->colour_ = 0;
                    g->colour_ = 1;
                    RightRotate(g);
                }
            }
            else
            {
                if (g->left_)
                {
                    u = g->left_;
                    //node->parent_->colour_ = 0;
                    if (u->colour_)
                    {
                        node->parent_->colour_ = 0;
                        u->colour_ = 0;
                        g->colour_ = 1;
                        node = g;
                    }
                }
                else
                {
                    if (node->parent_->left_ == node)
                    {
                        node = node->parent_;
                        RightRotate(node);
                    }
                    node->parent_->colour_ = 0;
                    g->colour_ = 1;
                    LeftRotate(g);
                }
            }
            root_->colour_ = 0;
        }
    }

    //Function that repair red black tree properties after extraction
    void DelFixup(RedBlackTreeNode* p)
    {
        RedBlackTreeNode* s;
        while (p != root_ && !p->colour_)
        {
            if (p->parent_->left_ == p)
            {
                s = p->parent_->right_;
                if (s->colour_)
                {
                    s->colour_ = 0;
                    p->parent_->colour_ = 1;
                    LeftRotate(p->parent_);
                    s = p->parent_->right_;
                }
                if (!s->right_->colour_ && s->left_->colour_)
                {
                    s->colour_ = 1;
                    p = p->parent_;
                }
                else
                {
                    if (!s->right_->colour_)
                    {
                        s->left_->colour_ = 0;
                        s->colour_ = 1;
                        RightRotate(s);
                        s = p->parent_->right_;
                    }
                    s->colour_ = p->parent_->colour_;
                    p->parent_->colour_ = 0;
                    s->right_->colour_ = 0;
                    LeftRotate(p->parent_);
                    p = root_;
                }
            }
            else
            {
                s = p->parent_->left_;
                if (s->colour_)
                {
                    s->colour = 0;
                    p->parent_->colour_ = 1;
                    RightRotate(p->parent_);
                    s = p->parent_->left_;
                }
                if (!s->left_->colour_ && !s->right_->colour_)
                {
                    s->colour_ = 1;
                    p = p->parent_;
                }
                else
                {
                    if (!s->left_->colour_)
                    {
                        s->right_->colour_ = 0;
                        s->colour_ = 1;
                        LeftRotate(s);
                        s = p->parent_->left_;
                    }
                    s->colour_ = p->parent_->colour_;
                    p->parent_->colour_ = 0;
                    s->left_->colour_ = 0;
                    RightRotate(p->parent_);
                    p = root_;
                }
            }
            p->colour_ = 0;
            root_->colour_ = 0;
        }
    }

    //Finding max element
    RedBlackTreeNode* Successor(RedBlackTreeNode* p)
    {
        RedBlackTreeNode* y = nullptr;
        if (p->left_)
        {
            y = p->left_;
            while (y->right_)
                y = y->right_;
        }
        else
        {
            y = p->right_;
            while (y->left_)
                y = y->left_;
        }
        return y;
    }
public:
    //Constructor
    RedBlackTree() : root_(nullptr) {};

    //Insert new element
    void Insert(const T& el)
    {
        int i = 0;
        RedBlackTreeNode* new_node = new RedBlackTreeNode(el);
        RedBlackTreeNode* p = root_;
        RedBlackTreeNode* q = nullptr;
        if (!root_)
            root_ = new_node;
        else
        {
            while (p)
            {
                p->size_++;
                q = p;
                if (p->value_ < el)
                    p = p->right_;
                else
                    p = p->left_;
            }
            new_node->parent_ = q;
            if (q->value_ < new_node->value_)
                q->right_ = new_node;
            else
                q->left_ = new_node;
        }
        InsertFixup(new_node);
    }

    //Removing element
    void Del(const T& key)
    {
        if (!root_)
        {
            cout << "Empty Tree." << endl;
            return;
        }
        RedBlackTreeNode* p = root_;
        RedBlackTreeNode* y = nullptr;
        RedBlackTreeNode* q = nullptr;
        bool found = 0;
        while (!p && !found)
        {
            if (p->value_ == key)
                found = 1;
            if (!found)
            {
                if (p->value_ < key)
                    p = p->right_;
                else
                    p = p->left_;
            }
        }
        if (!found)
        {
            cout << "Element Not Found." << endl;
            return;
        }
        else
        {
            cout << "Deleted Element: ";
            p->Print(cout);
            cout << endl;
            if (!p->left_ || !p->right)
                y = p;
            else
                y = Successor(p);
            if (y->left_)
                q = y->left_;
            else
            {
                if (y->right_)
                    q = y->right_;
                else
                    q = nullptr;
            }
            if (q)
                q->parent_ = y->parent_;
            if (!y->parent_)
                root_ = q;
            else
            {
                if (y == y->parent_->left_)
                    y->parent_->left_ = q;
                else
                    y->parent_->right_ = q;
            }
            if (y != p)
            {
                p->colour_ = y->colour_;
                p->value_ = y->value_;
            }
            if (!y->colour_)
                DelFixup(q);
        }
    }

    //Finding element
    void Search(const T& value)
    {
        if (!root_)
        {
            cout << "Empty Tree\n";
            return;
        }
        RedBlackTreeNode* p = root_;
        bool found = 0;
        while (p && !found)
        {
            if (p->value_ == value)
                found = 1;
            if (found == 0)
            {
                if (p->value_ < value)
                    p = p->right_;
                else
                    p = p->left_;
            }
        }
        if (found == 0)
            cout << "\nElement Not Found.";
        else
        {
            cout << "FOUND NODE: ";
            p->Print(cout);
            cout << endl;
        }
    }

    //Interactive output
    void Print()
    {
        auto p = ChooseNode(root_);
    }
};

int main()
{
    RedBlackTree<Group> A;
    int  n;
    cout << blue << "Enter number groups" << endl;
    cin >> n;
    cin.ignore();
    cout << endl;
    string name;
    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << "-th group name:" << endl;
        getline(cin, name);
        cout << i + 1 << "-th group students:" << endl;
        string models;
        getline(cin, models);
        A.Insert(Group(name, Parse(models)));
    }
    A.Print();
    return 0;
}