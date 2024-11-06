#include <bits/stdc++.h>
using namespace std;

struct Node
{
    char data;
    int freq;
    Node *left, *right;
    Node(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

struct Compare
{
    bool operator()(Node *a, Node *b){return a->freq > b->freq;}
};

void generateCodes(Node *root, string code, unordered_map<char, string> &huffCodes)
{
    if (!root)
        return;
    if (!root->left && !root->right)
        huffCodes[root->data] = code;
    generateCodes(root->left, code + "0", huffCodes);
    generateCodes(root->right, code + "1", huffCodes);
}

void huffmanEncoding(const string &text)
{
    unordered_map<char, int> freq;
    for (char ch : text)
        freq[ch]++;

    // MIN HEAP
    priority_queue<Node *, vector<Node *>, Compare> pq;
    for (auto &f : freq)
        pq.push(new Node(f.first, f.second));

    while (pq.size() > 1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();
        // NULL node
        Node *parent = new Node('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    unordered_map<char, string> huffCodes;
    generateCodes(pq.top(), "", huffCodes);

    cout << "Huffman Codes:\n";
    for (auto &p : huffCodes)
        cout << p.first << ": " << p.second << endl;

    cout << "\nEncoded string: ";
    for (char ch : text)
        cout << huffCodes[ch];
    cout << endl;
}

int main()
{
    string text;
    cout << "Enter text to encode: ";
    getline(cin, text);
    huffmanEncoding(text);
    return 0;
}

/*
// freq, priority queue
Time Complexity: 𝑂(𝑛+𝑚log 𝑚)
Space Complexity: O(m)
*/