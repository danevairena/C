"""Your program should count the number of letters, words, and sentences in the text.
Your program should print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula, rounded
to the nearest integer.If the resulting index number is 16 or higher (equivalent to or greater than a senior
undergraduate reading level), your program should output "Grade 16+" instead of giving the exact index number.
If the index number is less than 1, your program should output "Before Grade 1"."""


def main():
    text = input("Enter your text here: ")
    num_letters = count_letters(text)
    num_words = count_words(text)
    num_sentences = count_sentences(text)
    calc_grade(num_letters, num_words, num_sentences)


def count_letters(txt):
    # check every character in the string is for letters
    letters = 0
    for char in txt:
        if char.isalpha():
            letters += 1
    return letters


def count_words(txt):
    # any sequence of characters separated by spaces should count as a word
    words = 0
    for char in txt:
        if char == " ":
            words += 1
    # check if the last word of the string is not ending with space
    if not txt[:-1].endswith(" "):
        words = words + 1
    return words


def count_sentences(txt):
    # any occurrence of a period, exclamation point, or question mark indicates the end of a sentence
    sentences = 0
    for char in txt:
        if char == "." or char == "!" or char == "?":
            sentences += 1
    # checking last character for possible ending without punctuation
    if txt[:-1].endswith(".") or txt[:-1].endswith("!") or txt[:-1].endswith("?"):
        sentences += 1
    return sentences


def calc_grade(letters, words, sentences):
    # calculating average values
    # where ll is the average number of letters per 100 words in the text,
    # and s is the average number of sentences per 100 words in the text.
    ll = (letters / words) * 100
    s = (sentences / words) * 100

    # calculating index using the formula index = 0.0588 * L - 0.296 * S - 15.8
    index = 0.0588 * ll - 0.296 * s - 15.8
    # round the resulting index number to the nearest int
    grade = round(index)

    # print grade result
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


main()
