#include <iostream>
#include <string>
#include <map>
#include <bitset>
#include <queue>
#include <algorithm>
#include <iomanip>



using namespace std;
struct code{
    char character;
    string bitcode;
    int numBits;
};


bool compareCodes(const code& a, const code& b) {
    if (a.numBits == b.numBits) {
        return a.character < b.character;
    } else {
        return a.numBits < b.numBits;
    }
}

struct Node{
    char ch;
    int freq;
    int tiebreak;
    Node* left;
    Node* right;
    Node(char c, int f, int t) : ch(c), freq(f), tiebreak(t), left(nullptr), right(nullptr){}
};
struct NodeComparator {
    bool operator()(Node* left, Node* right) {
        if (left->freq == right->freq) {
            return left->tiebreak > right->tiebreak;
        }
        return left->freq > right->freq;
    }
};

void buildMap(Node* node, string str, map<char, string>& huffman) {
    if (node == nullptr) return;
    if (node->left == nullptr && node->right == nullptr) huffman[node->ch] = str;
    buildMap(node->left, str + "0", huffman);
    buildMap(node->right, str + "1", huffman);
}

int main(){
    string passage = "Once there were brook trouts in the streams in the mountains. "
    "You could see them standing in the amber current where the white edges of their fins wimpled softly in the flow. "
    "They smelled of moss in your hand. Polished and muscular and torsional. On their backs were vermiculate patterns that were maps of the world in its becoming. "
    "Maps and mazes. Of a thing which could not be put back. Not be made right again. In the deep glens where they lived all things were older than man and they hummed of mystery.";
    
    //Use a std::map<char,int> to accumulate your character frequencies.  
    //Iterate the collection in order to populate the priority queue when building the tree.
    map<char, int> freq;
    for (char ch : passage) freq[ch]++;
    priority_queue<Node*, vector<Node*>, NodeComparator> pq;
    int tiebreakerCounter = 0;

    for (auto const& [ch, count] : freq) {
        pq.push(new Node(ch, count, tiebreakerCounter++));
    }
    
    while(pq.size() != 1){
        //When dequeuing nodes from your priority queue, always use the first node dequeued as the left child, and the second node dequeued as the right child.
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        //empty char
        Node *parent = new Node('\0', left->freq + right->freq, tiebreakerCounter++);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }
    map<char, string> huffmanMap;
    buildMap(pq.top(), "", huffmanMap);
    vector<code> encodings;
    for (auto const& [ch, bitstr] : huffmanMap) {
        encodings.push_back({ch, bitstr, (int)bitstr.length()});
    }
    sort(encodings.begin(), encodings.end(), compareCodes);

    cout << left << setw(10) << "Symbol" << "Code" << endl;
    cout << "----------------------" << endl;
    for (const auto& e : encodings) {
        string label = (e.character == ' ') ? "SPACE" : string(1, e.character);
        cout << left << setw(10) << label << e.bitcode << endl;
    }

    string encoded = "";
    for (char ch : passage) encoded += huffmanCodeMap[ch];

    cout << "\nFirst 8 bytes (binary):" << endl;
    for(int i=0; i<8; i++) cout << encoded.substr(i*8, 8) << " ";
    
    double compSize = encoded.length();
    double uncompSize = passage.length() * 8;
    
    cout << "\n\nSize: " << compSize << " bits (" << compSize/8 << " bytes)" << endl;
    cout << "Compression Ratio: " << compSize / uncompSize << endl;

    return 0;
}

