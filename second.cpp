#include <bits/stdc++.h>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;      
    }
};

struct compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq; 
    }
};

void printHuffmanTree(Node* root, string code) {
    if(!root) {
        return;
    }

    if(!root->left && !root->right) {
        if(code == "") code = "0";
        cout<<root->ch<<" : "<<code<<endl;
    }

    printHuffmanTree(root->left, code + "0");
    printHuffmanTree(root->right, code + "1");
}

void buildHuffmanTree(string text) {
    unordered_map<char,int> freq;
    for(char c : text) {
        freq[c]++;
    }

    priority_queue<Node*, vector<Node*>, compare> pq;

    for(auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    while(pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* sum = new Node('$', left->freq + right->freq);
        sum->left = left;
        sum->right = right;

        pq.push(sum);
    }

    Node* root = pq.top();
    cout<<"Huffman Code : "<<endl;
    printHuffmanTree(root, "");
}

int main() {
    string text;
    cout<<"Enter text: ";
    getline(cin, text);

    buildHuffmanTree(text);
    return 0;
}