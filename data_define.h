#ifndef DATA_DEFINE_H_
#define DATA_DEFINE_H_

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;

template <typename T>
void print(const T &t)
{
    std::cout << t << std::endl;
}

template <typename T>
void print(const vector<T> &t)
{
    for (auto it = t.begin(); it != t.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void print(const vector<vector<T> > &t)
{
    for (auto it = t.begin(); it != t.end(); ++it) {
        print(*it);
    }
}

template <typename T>
std::string getString(const T &t)
{
    return std::to_string(t);
}

std::string getString(char t)
{
    return std::string(1, t);
}

std::string getString(bool t)
{
    return t ? "true" : "false";
}

std::string getString(const std::string &t)
{
    return t;
}

std::string getString(const char *t)
{
    return std::string(t);
}

template <typename T>
std::string getString(const vector<T> &t)
{
    std::string strRet;
    strRet.append("[");
    for (auto it = t.begin(); it != t.end(); ++it) {
        strRet.append(getString(*it));
        strRet.append(", ");
    }
    if (strRet.size() > 1) {
        strRet.pop_back();
        strRet.pop_back();
    }
    strRet.append("]");
    return strRet;
}

template <typename T>
std::string getString(const vector<vector<T> > &t)
{
    std::string strRet;
    strRet.append("[\n");
    for (auto it = t.begin(); it != t.end(); ++it) {
        if (it != t.begin()) {
            strRet.append(",\n");
        }
        strRet.append(getString(*it));
    }
    strRet.append("\n]");
    return strRet;
}

template <typename... Ts>
std::string getString(std::tuple<Ts...> &&ts, int index = 0)
{
    index = std::tuple_size<std::tuple<Ts...> >::value;
    return std::apply(
        [&](auto &&...ts) -> std::string {
            return ((std::to_string(--index) + ": " + getString(ts) + "\n") + ...);
        },
        ts);
}

template <typename... Ts>
std::string getString(const std::tuple<Ts...> &ts, int index = 0)
{
    index = std::tuple_size<std::tuple<Ts...> >::value;
    return std::apply(
        [&](auto &&...ts) -> std::string {
            return ((std::to_string(--index) + ": " + getString(ts) + "\n") + ...);
        },
        ts);
}

template <typename T>
bool isEqualWithoutOrder(const vector<T> &t1, const vector<T> &t2)
{
    if (t1.size() != t2.size())
        return false;
    unordered_set<T> setTmp;
    for (int i = 0; i < (int)t1.size(); ++i) {
        setTmp.insert(t1.at(i));
    }
    bool bRet = true;
    for (int i = 0; i < (int)t2.size(); ++i) {
        if (setTmp.find(t2.at(i)) == setTmp.end()) {
            bRet = false;
            break;
        }
    }
    return bRet;
}

// 第一维不要求顺序，第二维要求
template <typename T>
bool isEqualWithoutOrder(const vector<vector<T> > &t1, const vector<vector<T> > &t2)
{
    if (t1.size() != t2.size())
        return false;
    bool bRet = true;
    for (int i = 0; i < (int)t2.size() && bRet; ++i) {
        if (find(t1.begin(), t1.end(), t2.at(i)) == t1.end()) {
            bRet = false;
        }
    }
    for (int i = 0; i < (int)t1.size() && bRet; ++i) {
        if (find(t2.begin(), t2.end(), t1.at(i)) == t2.end()) {
            bRet = false;
        }
    }
    return bRet;
}

// 第一维和第二维都不要求顺序
template <typename T>
bool isEqualWithoutOrder_2(const vector<vector<T> > &t1, const vector<vector<T> > &t2)
{
    if (t1.size() != t2.size())
        return false;
    bool bRet = true;
    for (int i = 0; i < (int)t1.size() && bRet; ++i) {
        bRet = false;
        for (int j = 0; j < (int)t2.size(); ++j) {
            if (isEqualWithoutOrder(t1.at(i), t2.at(j))) {
                bRet = true;
                break;
            }
        }
    }
    for (int i = 0; i < (int)t2.size() && bRet; ++i) {
        bRet = false;
        for (int j = 0; j < (int)t1.size(); ++j) {
            if (isEqualWithoutOrder(t2.at(i), t1.at(j))) {
                bRet = true;
                break;
            }
        }
    }
    return bRet;
}

template <typename T>
inline std::string ToString(T t_arg)
{
    std::string strvalue;
    std::string strRet;
    std::stringstream ss;
    ss << t_arg;
    return ss.str();
}

template <typename T>
void stringHelper(std::string &str_fmt, int &n_start, T t_arg)
{
    std::string::size_type position;
    position = str_fmt.find("%", n_start);
    if (position != str_fmt.npos) {
        if (str_fmt.at(position + 1) == '%') {
            str_fmt.erase(position, 1);
            n_start = position + 1;
            stringHelper(str_fmt, n_start, t_arg);
        } else if (str_fmt.at(position + 1) == 'v') {
            std::string strArg = ToString(t_arg);
            str_fmt.replace(position, 2, ToString(t_arg));
            n_start = position + strArg.size();
        }
    } else {
        n_start = str_fmt.size();
    }
}

template <typename T0, typename... T1>
void stringHelper(std::string &str_fmt, int &n_start, T0 t0, T1... args)
{
    stringHelper(str_fmt, n_start, t0);
    if (n_start < (int)str_fmt.size()) {
        stringHelper(str_fmt, n_start, args...);
    }
}

template <typename... T>
std::string fmtString(const std::string &str_fmt, T... args)
{
    std::string strRet = str_fmt;
    int nStart = 0;
    stringHelper(strRet, nStart, args...);
    return strRet;
}

inline void TrimLeftTrailingSpaces(string &input)
{
    input.erase(input.begin(),
                find_if(input.begin(), input.end(), [](int ch) { return !isspace(ch); }));
}

inline void TrimRightTrailingSpaces(string &input)
{
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) { return !isspace(ch); }).base(),
                input.end());
}

inline void TrimTrailingSpaces(string &input)
{
    input.erase(input.begin(),
                find_if(input.begin(), input.end(), [](int ch) { return !isspace(ch); }));
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) { return !isspace(ch); }).base(),
                input.end());
}

inline std::vector<int> String2VertorInt(std::string input)
{
    vector<int> output;
    TrimLeftTrailingSpaces(input);
    TrimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

inline std::vector<vector<int> > String2VertorInt2(std::string input)
{
    vector<vector<int> > output;
    TrimLeftTrailingSpaces(input);
    TrimRightTrailingSpaces(input);
    std::string str_tmp;
    int tmp_strat = 0;
    for (size_t i = 1; i < input.size() - 1; i++) {
        if (input[i] == '[') {
            str_tmp.clear();
            tmp_strat = i;
        } else if (input[i] == ']') {
            str_tmp = input.substr(tmp_strat, i - tmp_strat + 1);
            output.push_back(String2VertorInt(str_tmp));
        }
    }

    return output;
}

inline std::vector<std::string> String2VertorString(std::string input)
{
    vector<string> output;
    TrimLeftTrailingSpaces(input);
    TrimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        TrimTrailingSpaces(item);
        output.push_back(item);
    }
    return output;
}

// -------------------------- 链表相关 --------------------------
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(NULL) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *initListNode(std::vector<int> &&vec)
{
    ListNode *root = NULL;
    ListNode *preNode = NULL;
    ListNode *tmp = NULL;
    for (int i = 0; i < (int)vec.size(); ++i) {
        tmp = new ListNode(vec[i]);
        if (preNode != NULL) {
            preNode->next = tmp;
        } else {
            root = tmp;
        }
        preNode = tmp;
    }
    return root;
}

bool isEqualListNode(ListNode *l1, ListNode *l2)
{
    ListNode *tmp1 = l1;
    ListNode *tmp2 = l2;
    bool bRet = true;
    while (tmp1 != NULL && tmp2 != NULL) {
        if (tmp1->val != tmp2->val) {
            bRet = false;
            break;
        }
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
    if (bRet && tmp1 != tmp2) {
        bRet = false;
    }
    return bRet;
}

std::string getString(ListNode *root)
{
    ListNode *tmp = root;
    std::string strRet = "[";
    while (tmp != NULL) {
        strRet.append(std::to_string(tmp->val));
        strRet.append(" ");
        tmp = tmp->next;
    }
    strRet.append("]");
    return strRet;
}

void print(ListNode *root)
{
    ListNode *tmp = root;
    std::cout << "[";
    while (tmp != NULL) {
        std::cout << tmp->val << " ";
        tmp = tmp->next;
    }
    std::cout << "]" << std::endl;
}

// -------------------------- 二叉树相关 --------------------------
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

static TreeNode *CreatTree_heap(const std::vector<std::string> vec_data)
{
    if (vec_data.empty()) {
        return nullptr;
    }
    TreeNode *pRoot = new (std::nothrow) TreeNode(std::stoi(vec_data[0]));

    std::queue<std::pair<TreeNode *, int> > queueNode;
    queueNode.push(std::make_pair(pRoot, 0));
    while (!queueNode.empty()) {
        std::pair<TreeNode *, int> &pairData = queueNode.front();
        size_t idxLeft = pairData.second * 2 + 1;
        size_t idxRight = pairData.second * 2 + 2;
        if (idxLeft < vec_data.size() && vec_data[idxLeft] != "null") {
            pairData.first->left = new (std::nothrow) TreeNode(std::stoi(vec_data[idxLeft]));
            queueNode.push(std::make_pair(pairData.first->left, idxLeft));
        }
        if (idxRight < vec_data.size() && vec_data[idxRight] != "null") {
            pairData.first->right = new (std::nothrow) TreeNode(std::stoi(vec_data[idxRight]));
            queueNode.push(std::make_pair(pairData.first->right, idxRight));
        }
        queueNode.pop();
    }
    return pRoot;
}

static TreeNode *CreatTree(const std::vector<std::string> vec_data)
{
    if (vec_data.empty()) {
        return nullptr;
    }
    int index = 0;
    TreeNode *pRoot = new (std::nothrow) TreeNode(std::stoi(vec_data[index++]));
    std::queue<TreeNode *> queueNode;
    queueNode.push(pRoot);
    while (!queueNode.empty() && index < vec_data.size()) {
        TreeNode *node = queueNode.front();
        queueNode.pop();
        if (vec_data[index] != "null") {
            node->left = new (std::nothrow) TreeNode(std::stoi(vec_data[index]));
            queueNode.push(node->left);
        }
        index++;
        if (index >= vec_data.size()) {
            break;
        }
        if (vec_data[index] != "null") {
            node->right = new (std::nothrow) TreeNode(std::stoi(vec_data[index]));
            queueNode.push(node->right);
        }
        index++;
    }
    return pRoot;
}

static TreeNode *TreeCopy(TreeNode *root)
{
    if (root == nullptr) {
        return nullptr;
    }
    TreeNode *rootNew = new (std::nothrow) TreeNode(root->val);
    if (rootNew == nullptr) {
        return nullptr;
    }
    if (root->left != nullptr) {
        rootNew->left = TreeCopy(root->left);
    }
    if (root->right != nullptr) {
        rootNew->right = TreeCopy(root->right);
    }
    return rootNew;
}

static bool TreeIsEqual(const TreeNode *tree1, const TreeNode *tree2)
{
    if (tree1 == nullptr && tree2 == nullptr) {
        return true;
    }
    if (tree1 == nullptr || tree2 == nullptr) {
        return false;
    }
    if (tree1->val != tree2->val) {
        return false;
    }
    if (!TreeIsEqual(tree1->left, tree2->left)) {
        return false;
    }
    if (!TreeIsEqual(tree1->right, tree2->right)) {
        return false;
    }
    return true;
}

static void TreePreorder(TreeNode *tree, std::vector<int> &vec_out, bool b_print)
{
    if (tree == nullptr) {
        return;
    }
    TreePreorder(tree->left, vec_out, b_print);
    vec_out.push_back(tree->val);
    if (b_print) {
        std::cout << tree->val << " ";
    }
    TreePreorder(tree->right, vec_out, b_print);
}

static std::vector<int> TreePreorder(TreeNode *tree, bool b_print)
{
    std::vector<int> result;
    TreePreorder(tree, result, b_print);
    if (b_print) {
        std::cout << "\n";
    }
    return result;
}

static void TreeInorder(TreeNode *tree, std::vector<int> &vec_out, bool b_print)
{
    if (tree == nullptr) {
        return;
    }
    vec_out.push_back(tree->val);
    if (b_print) {
        std::cout << tree->val << " ";
    }
    TreeInorder(tree->left, vec_out, b_print);
    TreeInorder(tree->right, vec_out, b_print);
}

static std::vector<int> TreeInorder(TreeNode *tree, bool b_print)
{
    std::vector<int> result;
    TreeInorder(tree, result, b_print);
    if (b_print) {
        std::cout << "\n";
    }
    return result;
}

static void TreePostorder(TreeNode *tree, std::vector<int> &vec_out, bool b_print)
{
    if (tree == nullptr) {
        return;
    }
    TreePreorder(tree->left, vec_out, b_print);
    TreePreorder(tree->right, vec_out, b_print);
    vec_out.push_back(tree->val);
    if (b_print) {
        std::cout << tree->val << " ";
    }
}

static std::vector<int> TreePostorder(TreeNode *tree, bool b_print)
{
    std::vector<int> result;
    TreePostorder(tree, result, b_print);
    if (b_print) {
        std::cout << "\n";
    }
    return result;
}

static void TreeLevelorder(TreeNode *tree, std::vector<int> &vec_out, bool b_print)
{
    if (tree == nullptr) {
        return;
    }
    std::queue<TreeNode *> queueNode;
    queueNode.push(tree);
    while (!queueNode.empty()) {
        TreeNode *pNode = queueNode.front();
        queueNode.pop();
        vec_out.push_back(pNode->val);
        if (b_print) {
            std::cout << pNode->val << " ";
        }
        if (pNode->left != nullptr) {
            queueNode.push(pNode->left);
        }
        if (pNode->right != nullptr) {
            queueNode.push(pNode->right);
        }
    }
}

static std::vector<int> TreeLevelorder(TreeNode *tree, bool b_print)
{
    if (tree == nullptr) {
        return {};
    }
    std::vector<int> result;
    TreeLevelorder(tree, result, b_print);
    if (b_print) {
        std::cout << "\n";
    }
    return result;
}

static void TreePrint(TreeNode *node, size_t n_deepth, std::vector<bool> &vec_flag,
                      std::string *p_strprint = nullptr)
{
    if (n_deepth > 0) {
        for (size_t i = 0; i < n_deepth - 1; i++) {
            if (p_strprint == nullptr) {
                printf(vec_flag[i] ? "│   " : "    ");
            } else {
                p_strprint->append(vec_flag[i] ? "│   " : "    ");
            }
        }
        if (p_strprint == nullptr) {
            printf(vec_flag[n_deepth - 1] ? "├── " : "└── ");
        } else {
            p_strprint->append(vec_flag[n_deepth - 1] ? "├── " : "└── ");
        }
    }
    if (node == nullptr) {
        if (p_strprint == nullptr) {
            printf("(null)\n");
        } else {
            p_strprint->append("(null)\n");
        }
        return;
    } else {
        if (p_strprint == nullptr) {
            std::cout << node->val << std::endl;
        } else {
            p_strprint->append(fmtString("%v\n", node->val));
        }
    }

    if (node->left == nullptr && node->right == nullptr) {
        return;
    }
    if (vec_flag.size() <= n_deepth) {
        vec_flag.push_back(true);
    } else {
        vec_flag[n_deepth] = true;
    }
    TreePrint(node->right, n_deepth + 1, vec_flag, p_strprint);
    vec_flag[n_deepth] = false;
    TreePrint(node->left, n_deepth + 1, vec_flag, p_strprint);
}

static void TreePrint(TreeNode *tree)
{
    std::vector<bool> vecFlag;
    TreePrint(tree, 0, vecFlag);
}

static std::string GetTreePrint(TreeNode *tree)
{
    std::string strResult;
    std::vector<bool> vecFlag;
    TreePrint(tree, 0, vecFlag, &strResult);
    return strResult;
}

static std::string getString(TreeNode *root)
{
    return GetTreePrint(root);
}

#endif // DATA_DEFINE_H_
