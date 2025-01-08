#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <map>

using namespace std;

// Struktur node pohon Huffman
struct Node {
    char ch;
    int freq;
    Node *left;
    Node *right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Comparator untuk priority queue
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Membangun pohon Huffman
Node* buildHuffmanTree(map<char, int>& freq) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    return pq.top();
}

// Membuat kode Huffman
void buildHuffmanCode(Node* root, string code, map<char, string>& huffmanCode) {
    if (root == nullptr) return;

    if (root->ch != '\0') {
        huffmanCode[root->ch] = code;
    }

    buildHuffmanCode(root->left, code + "0", huffmanCode);
    buildHuffmanCode(root->right, code + "1", huffmanCode);
}

// Mengenkode string
string encode(string text, map<char, string>& huffmanCode) {
    string encodedText = "";
    for (char c : text) {
        encodedText += huffmanCode[c];
    }
    return encodedText;
}

// Mendekode string (membutuhkan pohon Huffman yang sama)
string decode(string encodedText, Node* root) {
    string decodedText = "";
    Node* current = root;
    for (char bit : encodedText) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if (current->left == nullptr && current->right == nullptr) {
            decodedText += current->ch;
            current = root;
        }
    }
    return decodedText;
}

int main() {
	
	cout << "Nama  : Muhammad Raihan" << endl;
	cout << "NIM   : 231011401201 " << endl;
	cout << "Kelas : 03TPLP029" << endl << endl;
	
    string text;
    cout << "Masukkan teks: ";
    getline(cin, text);

    // Menghitung frekuensi karakter
    map<char, int> freq;
    for (char c : text) {
        freq[c]++;
    }

    // Membangun pohon Huffman
    Node* root = buildHuffmanTree(freq);

    // Membuat kode Huffman
    map<char, string> huffmanCode;
    buildHuffmanCode(root, "", huffmanCode);

    // Menampilkan kode Huffman
    cout << "Kode Huffman:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << " : " << pair.second << endl;
    }

    // Mengenkode teks
    string encodedText = encode(text, huffmanCode);
    cout << "Teks terenkode: " << encodedText << endl;

    // Mendekode teks
    string decodedText = decode(encodedText, root);
    cout << "Teks terdekode: " << decodedText << endl;

    return 0;
}
