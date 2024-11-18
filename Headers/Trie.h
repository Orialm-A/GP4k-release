/* Trie.h */

#ifndef TRIE_H
#define TRIE_H

#include "Headers/GP4k_TilesMapping.h"
#include <QString>
#include <QMap>
#include <QStringList>

#define MAX_SUGGESTIONS 3

/**
 * @brief The TrieNode class is a class used by the Trie to represent a direction/letter.
 */
class TrieNode {
public:
    /**
     * @brief Holds all the children nodes of the current one.
     */
    QMap<QChar, TrieNode*> _Children;

    /**
     * @brief Indicates rather the node is the end of word or not.
     */
    bool _IsEndOfWord;

    /**
     * @brief Constructor for the TrieNode class.
     */
    TrieNode();

    /**
     * @brief Destructor for the TrieNode class.
     */
    ~TrieNode();
};

/**
 * @brief A trie is a tool used to organize words in a tree, in which the branch (called nodes) represents the different
 * possible letters from the previous one.
 */
class Trie {
public:
    /**
     * @brief Constructor for the Trie class.
     */
    Trie();

    /**
     * @brief Destructor for the Trie class.
     */
    ~Trie();

    /**
     * @brief Insert a word in the Trie.
     * @param Word the word to insert.
     */
    void Insert(const QString &Word);

    /**
     * @brief Search a word in the Trie.
     * @param Word the word to search.
     * @return true if the word is in the Trie, false else.
     */
    bool Search(const QString &Word) const;

    /**
     * @brief The method used to get word suggestions.
     * @param Prefix The beggining of the word to suggest completions.
     * @param SkipLastChar The letters forbidden as last letters.
     * @return The suggested words.
     *
     * SkipLastChar is used to prevent suggesting words:
     *      - miss an unique letter to be complete.
     *   && - this letter is available on the current tile group.
     * It prevents using a suggestion slot for a word requiring the same effort to reach the letter.
     * or the suggestion tile.
     */
    QVector<QString> Suggest(const QString &Prefix, const CharGroup_t SkipLastChar) const;

    /**
     * @brief Search a word and insert it in the node if not already present.
     * @param Word the word to search.
     * @return true if the word has been inserted, false else.
     */
    bool SearchAndInsert(const QString &Word);

private: // Attributes
    /**
     * @brief _Root The root node of the Trie
     */
    TrieNode *_Root;

private: // Methods
    /**
     * @brief A function used by the method `Suggest` to isolate its recursive part.
     * @param Node The current position in the Trie. A position IS a Node.
     * @param Prefix The part of the word already read at this position.
     * @param Suggestions The suggestions to complete.
     * @param Buffer The initial full buffer received at the beginning of the search
     * @param SkipLastChar The letters that can't be used to end the word
     */
    void SuggestHelper(TrieNode *Node, const QString &Prefix, QVector<QString> &Suggestions, QString Buffer, const CharGroup_t &SkipLastChar) const;
};

#endif // TRIE_H
