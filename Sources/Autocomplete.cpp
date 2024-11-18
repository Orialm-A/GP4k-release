#include <QChar>

#include "Headers/Autocomplete.h"
#include "Headers/GP4k_Typedefs.h"

Autocomplete::Autocomplete()
{
    _Trie = new Trie();
    _Buffer = "";
    _BufferInfo.Index = 0;
    _BufferInfo.Capacity = 0;
    _Suggestions = {};
}

actions_t Autocomplete::ChangeCharacter(const QString Character){
    // Empty character "" indicates a backspace
    if(Character == "" && _BufferInfo.Capacity <= 1){
        ClearBuffer();
        return CLEARED_BUFFER;
    }else{
        if(Character == ""){
            _Buffer.remove(_BufferInfo.Index-1, 1);
            _BufferInfo.Index -= 1;
            _BufferInfo.Capacity -= 1;
        }else{
            _Buffer.insert(_BufferInfo.Index, Character.toLower());
            /* Lowering the case to ensure a match is possible in
             * the Trie as it contains only lowercase words */
            _BufferInfo.Index += 1;
            _BufferInfo.Capacity += 1;
        }

        SeekSuggestions();
        return SOUGHT_SUGGESTIONS;
    }
}

void Autocomplete::ClearBuffer(void){
    _Buffer = "";
    _BufferInfo.Index = 0;
    _BufferInfo.Capacity = 0;
    _Suggestions = {};
}

void Autocomplete::SeekSuggestions(void){
    const CharGroup_t SkipLastChars = _SkipLastChars;
    if(_Buffer != ""){
        _Suggestions = _Trie->Suggest(_Buffer, SkipLastChars);
    }
}

actions_t Autocomplete::MoveBufferCursor(const Qt::Key Direction){
    const uint8_t Capacity = _BufferInfo.Capacity;

    if(Capacity != 0){
        if(
           (Direction == Qt::Key_Left && _BufferInfo.Index == 0)
         ||(Direction == Qt::Key_Right && _BufferInfo.Index == Capacity)
        ){
            ClearBuffer();
            return CLEARED_BUFFER;
        }
        else{
            _BufferInfo.Index += (Direction == Qt::Key_Left) ? -1 : 1;
            return NOTHING;
        }
    }
    return NOTHING;
}

QVector<QString> Autocomplete::GetSuggestions(void) const{
    return _Suggestions;
}

uint8_t Autocomplete::GetBufferIndex(void) const{
    return _BufferInfo.Index;
}

void Autocomplete::SetSkipLastChars(uint8_t CharGroupIndex){
    _SkipLastChars = InnerTilesChars[NOT_SHIFTED][CharGroupIndex];
    SeekSuggestions();
}
