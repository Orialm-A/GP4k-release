/* Autocomplete.h */

#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include "Headers/Trie.h"

/**
 * @brief Represents the possible performed on the Autocomplete buffer.
 */
enum actions_t {
    CLEARED_BUFFER,
    SOUGHT_SUGGESTIONS,
    NOTHING
};

/**
 * @brief The Autocomplete class is the interface between the controller and a trie
 * It's meant to simplify reading of the controller class source file.
 */
class Autocomplete{
public: // Methods
    /**
     * @brief Constructor of the Autocomplete.
     */
    Autocomplete();

    /**
     * @brief Change a character in the buffer at the position described by the the buffer info.
     * @param Character to implement. An empty character is a backspace.
     * @return CLEARED_BUFFER if backspace on last character, SOUGHT_SUGGESTIONS else.
     * @see _BufferInfo
     */
    actions_t ChangeCharacter(const QString Character = "");

    /**
     * @brief Moves the cursor within the buffer.
     * @param The move direction.
     */
    actions_t MoveBufferCursor(const Qt::Key Direction);

    /**
     * @brief Clear the buffer.
     */
    void ClearBuffer(void);

    /**
     * @brief Getter for suggestions.
     * @return The suggestions.
     */
    QVector<QString> GetSuggestions(void) const;

    /**
     * @brief Getter for the index of the buffer's cursor.
     * @return The position of the buffer's cursor.
     */
    uint8_t GetBufferIndex(void) const;

    /**
     * @brief Setter for the SkipLastChars.
     * @param the index of the char group in InnerTilesChars.
     */
    void SetSkipLastChars(const uint8_t CharGroupIndex);

private: // Methods
    /**
     * @brief Seek for new Suggestions.
     */
    void SeekSuggestions(void);

private: // Attributes
    /**
     * @brief The Trie of autocomplete feature.
     */
    Trie* _Trie;

    /**
     * @def _BufferInfo
     * @brief Holds the capacity and cursor index of the buffer.
     */
    struct BufferInfo_t{
        uint8_t Index;
        uint8_t Capacity;
    } _BufferInfo;

    /**
     * @brief Holds the suggestions of the autocompleter.
     */
    QVector<QString> _Suggestions;

    /**
     * @brief The buffer used by the controller to ask suggestions.
     */
    QString _Buffer;

    /**
     * @brief The chars to avoid as a last character.
     */
    CharGroup_t _SkipLastChars;
};

#endif // AUTOCOMPLETE_H
