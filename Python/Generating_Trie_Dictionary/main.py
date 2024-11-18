# import pandas lib as pd
import pandas as pd
import re

WORDS_COLUMN = 1

def remove_parentheses(text):
    return re.sub(r"\s*\(.*?\)", "", text)  # removes ' ( ... )' including space before

def remove_markers(text):
    return re.sub(r"\s*\*\s*", "", text) # removes ' * ' and eventual spaces around

def is_composed(text):
    return (re.search(r"[-\s]+", text) != None)

def is_contracted(text):
    return (re.search(r"\'+", text) != None)

def is_a_number(text):
    return (re.search(r"\d+", text) != None)

def have_special_characters(text):
    return (re.search(r"[/~&.]+", text) != None) # Not '.' as some must be treated separately: ' or -

def is_single_letter(text):
    return (re.search(r"^[a-zA-Z0-9]$", text) != None)

def preprocessing_dictionarries(
        file_name,
        check_parenthesis = False,
        check_markers = False,
        check_single_letter=False,
        check_composed = False,
        check_contractions = False,
        check_numbers = False,
        check_special_characters = False
):
    dictionary_xlsx = pd.read_excel(file_name)
    dictionary_list = dictionary_xlsx.iloc[:, WORDS_COLUMN]
    lines_to_remove = []

    for index, word in enumerate(dictionary_list):
        word = str(word) # Essential to prevent calling re.search on a int
        if check_parenthesis:
            dictionary_xlsx.iloc[index, WORDS_COLUMN] = remove_parentheses(word)

        if check_markers:
            dictionary_xlsx.iloc[index, WORDS_COLUMN] = remove_markers(word)

        if check_single_letter:
            if is_single_letter(word):
                lines_to_remove.append(index)
                continue  # There is no need to check other criteria to remove this line

        if check_composed:
            if is_composed(word):
                lines_to_remove.append(index)
                continue

        if check_contractions:
            if is_contracted(word):
                lines_to_remove.append(index)
                continue

        if check_numbers:
            if is_a_number(word):
                lines_to_remove.append(index)
                continue

        if check_special_characters:
            if have_special_characters(word):
                lines_to_remove.append(index)
                continue

    if not(not lines_to_remove):
        dictionary_xlsx = dictionary_xlsx.drop(lines_to_remove)
    dictionary_xlsx.to_excel(file_name, index=False)

def write_word_list(word_list, override=True):
    # Determine the mode: 'w' for overwrite, 'a' for append
    mode = 'w' if override else 'a'

    # Open the file with the specified mode
    with open("../../ressources/trie_word_list.txt", mode) as file:
        # Write each word on a new line
        for word in word_list:
            file.write(word + "\n")


preprocessing_dictionarries('simple_words.xlsx',
                            check_parenthesis = True,
                            check_markers = True,
                            check_composed = True,
                            check_contractions = True,
                            check_numbers = True,
                            check_special_characters = True
                            )

preprocessing_dictionarries('contractions.xlsx',
                            check_parenthesis = True,
                            )

preprocessing_dictionarries('custom_words.xlsx',
                            check_parenthesis = True,
                            )

simple_words_list = pd.read_excel('simple_words.xlsx').iloc[:, WORDS_COLUMN]
contracted_words_list = pd.read_excel('contractions.xlsx').iloc[:, WORDS_COLUMN]
custom_words_list = pd.read_excel('custom_words.xlsx').iloc[:, WORDS_COLUMN]
write_word_list(contracted_words_list, override=True)
write_word_list(simple_words_list, override=False)
write_word_list(custom_words_list, override=False)
