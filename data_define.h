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
#include <format>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;

template <typename T>
std::string GetString(const T &t)
{
    return std::to_string(t);
}

static inline std::string GetString(char t)
{
    return std::string(1, t);
}

static inline std::string GetString(bool t)
{
    return t ? "true" : "false";
}

static inline std::string GetString(const std::string &t)
{
    return t;
}

static inline std::string GetString(const char *t)
{
    return std::string(t);
}

template <typename T>
std::string GetString(const vector<T> &t)
{
    std::string strRet;
    strRet.append("[");
    for (auto it = t.begin(); it != t.end(); ++it) {
        strRet.append(GetString(*it));
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
std::string GetString(const vector<vector<T> > &t)
{
    std::string strRet;
    strRet.append("[\n");
    for (auto it = t.begin(); it != t.end(); ++it) {
        if (it != t.begin()) {
            strRet.append(",\n");
        }
        strRet.append(GetString(*it));
    }
    strRet.append("\n]");
    return strRet;
}

template <typename... Ts>
std::string GetString(const std::tuple<Ts...> &ts)
{
    int i = 0;
    std::string result;
    auto f_getString = [&](auto &&v) { result += std::format("{}: {}\n", i++, GetString(v)); };
    [&]<size_t... I>(std::index_sequence<I...>) {
        ((f_getString(std::get<I>(ts))), ...);
    }(std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<std::tuple<Ts...> > > >{});
    return result;
}

template <typename T>
bool IsEqual(const T &t1, const T &t2)
{
    return t1 == t2;
}

template <typename T>
bool IsEqualWithoutOrder(const vector<T> &t1, const vector<T> &t2)
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
bool IsEqualWithoutOrder(const vector<vector<T> > &t1, const vector<vector<T> > &t2)
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
bool IsEqualWithoutOrder_2(const vector<vector<T> > &t1, const vector<vector<T> > &t2)
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

static inline void TrimLeftTrailingSpaces(string &input)
{
    input.erase(input.begin(),
                find_if(input.begin(), input.end(), [](int ch) { return !isspace(ch); }));
}

static inline void TrimRightTrailingSpaces(string &input)
{
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) { return !isspace(ch); }).base(),
                input.end());
}

static inline void TrimTrailingSpaces(string &input)
{
    input.erase(input.begin(),
                find_if(input.begin(), input.end(), [](int ch) { return !isspace(ch); }));
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) { return !isspace(ch); }).base(),
                input.end());
}

static inline std::vector<int> String2VertorInt(std::string input)
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

static inline std::vector<vector<int> > String2VertorInt2(std::string input)
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

static inline std::vector<std::string> String2VertorString(std::string input)
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
    ListNode()
        : val(0)
        , next(nullptr)
    {
    }
    ListNode(int x)
        : val(x)
        , next(NULL)
    {
    }
    ListNode(int x, ListNode *next)
        : val(x)
        , next(next)
    {
    }
};

static inline ListNode *InitListNode(std::vector<int> &&vec)
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

static inline bool IsEqualListNode(ListNode *l1, ListNode *l2)
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

static inline std::string GetString(ListNode *root)
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

static inline void PrintListNode(ListNode *root)
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
    TreeNode()
        : val(0)
        , left(nullptr)
        , right(nullptr)
    {
    }
    TreeNode(int x)
        : val(x)
        , left(nullptr)
        , right(nullptr)
    {
    }
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x)
        , left(left)
        , right(right)
    {
    }
};

static inline TreeNode *CreatTree_heap(const std::vector<std::string> vec_data)
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

static inline TreeNode *CreatTree(const std::vector<std::string> vec_data)
{
    if (vec_data.empty()) {
        return nullptr;
    }
    size_t index = 0;
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

static inline TreeNode *TreeCopy(TreeNode *root)
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

static inline bool IsEqualTree(const TreeNode *tree1, const TreeNode *tree2)
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
    if (!IsEqualTree(tree1->left, tree2->left)) {
        return false;
    }
    if (!IsEqualTree(tree1->right, tree2->right)) {
        return false;
    }
    return true;
}

static inline void TreePreorder(TreeNode *tree, std::vector<int> &vec_out, bool b_print)
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

static inline std::vector<int> TreePreorder(TreeNode *tree, bool b_print)
{
    std::vector<int> result;
    TreePreorder(tree, result, b_print);
    if (b_print) {
        std::cout << "\n";
    }
    return result;
}

static inline void TreeInorder(TreeNode *tree, std::vector<int> &vec_out, bool b_print)
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

static inline std::vector<int> TreeInorder(TreeNode *tree, bool b_print)
{
    std::vector<int> result;
    TreeInorder(tree, result, b_print);
    if (b_print) {
        std::cout << "\n";
    }
    return result;
}

static inline void TreePostorder(TreeNode *tree, std::vector<int> &vec_out, bool b_print)
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

static inline std::vector<int> TreePostorder(TreeNode *tree, bool b_print)
{
    std::vector<int> result;
    TreePostorder(tree, result, b_print);
    if (b_print) {
        std::cout << "\n";
    }
    return result;
}

static inline void TreeLevelorder(TreeNode *tree, std::vector<int> &vec_out, bool b_print)
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

static inline std::vector<int> TreeLevelorder(TreeNode *tree, bool b_print)
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

static inline void PrintTree(TreeNode *node, size_t n_deepth, std::vector<bool> &vec_flag,
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
            p_strprint->append(std::format("{}\n", node->val));
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
    PrintTree(node->right, n_deepth + 1, vec_flag, p_strprint);
    vec_flag[n_deepth] = false;
    PrintTree(node->left, n_deepth + 1, vec_flag, p_strprint);
}

static inline void PrintTree(TreeNode *tree)
{
    std::vector<bool> vecFlag;
    PrintTree(tree, 0, vecFlag);
}

static inline std::string GetStringTreePrint(TreeNode *tree)
{
    std::string strResult;
    std::vector<bool> vecFlag;
    PrintTree(tree, 0, vecFlag, &strResult);
    return strResult;
}

static inline std::string GetString(TreeNode *root)
{
    return GetStringTreePrint(root);
}

#endif // DATA_DEFINE_H_
