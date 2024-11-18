#include <QFile>
#include <QTextStream>
#include "Headers/Trie.h"
#include "Headers/GP4k_TilesMapping.h"
#include "qdebug.h"

TrieNode::TrieNode() : _IsEndOfWord(false) {}

TrieNode::~TrieNode() {
    qDeleteAll(_Children);
}

Trie::Trie() {
    _Root = new TrieNode();
    QFile WordListFile(":/Resources/trie_word_list.txt");
    qDebug() << "Opening Trie words list...";
    Q_ASSERT(WordListFile.open(QIODevice::ReadOnly | QIODevice::Text));
    QTextStream WordListStream(&WordListFile);
    QString Word;
    while (!WordListStream.atEnd()){
        Word = WordListStream.readLine();
        SearchAndInsert(Word);
    }
}

Trie::~Trie() {
    delete _Root;
}

void Trie::Insert(const QString &Word) {
    TrieNode *CurrentNode = _Root;
    for (const QChar &Letter : Word) {
        if (!(CurrentNode->_Children.contains(Letter))) {
            CurrentNode->_Children[Letter] = new TrieNode();
        }
        CurrentNode = CurrentNode->_Children[Letter];
    }
    CurrentNode->_IsEndOfWord = true;
}

bool Trie::Search(const QString &Word) const {
    TrieNode *CurrentNode = _Root;
    for (const QChar &Letter : Word) {
        if (!CurrentNode->_Children.contains(Letter)) {
            return false;
        }
        CurrentNode = CurrentNode->_Children[Letter];
    }
    return CurrentNode->_IsEndOfWord;
}

QVector<QString> Trie::Suggest(const QString &Prefix, const CharGroup_t SkipLastChar) const {
    QVector<QString> Suggestions;
    TrieNode *CurrentNode = _Root;
    const QString Buffer = Prefix;

    for (const QChar &Letter : Prefix) {
        if (!CurrentNode->_Children.contains(Letter)) { // No words with this prefix
            return Suggestions;
        }
        CurrentNode = CurrentNode->_Children[Letter];
    }
    SuggestHelper(CurrentNode, Prefix, Suggestions, Buffer, SkipLastChar);
    return Suggestions;
}

void Trie::SuggestHelper(TrieNode *Node, const QString &Prefix, QVector<QString> &Suggestions, QString Buffer, const CharGroup_t &SkipLastChar) const {
    if (Suggestions.size() >= MAX_SUGGESTIONS) { // Stop early if we have enough results
        return;
    }

    QChar LastLetter = Prefix[Prefix.length()-1];
    if (Node->_IsEndOfWord // To suggest a complete word
     && Prefix != Buffer // To prevent suggesting exactly what's already typed
     && !(SkipLastChar.contains(LastLetter) && Prefix.length() == Buffer.length()+1) // To prevent suggesting a word that is on char away in the same group
     ){
        Suggestions.append(Prefix);
    }

    for (auto NodeIterator = Node->_Children.begin(); NodeIterator != Node->_Children.end(); ++NodeIterator) {
        SuggestHelper(NodeIterator.value(), Prefix + NodeIterator.key(), Suggestions, Buffer, SkipLastChar);
        if (Suggestions.size() >= MAX_SUGGESTIONS) { // Stop early if we have enough results
            return;
        }
    }
}

bool Trie::SearchAndInsert(const QString &Word) {
    TrieNode *CurrentNode = _Root;

    for (const QChar &Letter : Word) {
        if (!CurrentNode->_Children.contains(Letter)) { // Word not found, insert it
            Insert(Word);
            return true; // Return true to indicate the has been inserted
        }
        CurrentNode = CurrentNode->_Children[Letter];
    }

    if (!CurrentNode->_IsEndOfWord) {
        // Word is partially in the Trie but not marked as a complete word, so insert it
        Insert(Word);
        return true;
    }

    return false; // Word already exists
}
