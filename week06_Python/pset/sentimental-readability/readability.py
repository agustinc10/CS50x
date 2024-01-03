# TODO


def main():
    text = input('Text: ')
    letters = 0
    sentences = 0
    for i in text:
        if i.isalpha():
            letters += 1
        if i == '.' or i == '!' or i == '?':
            sentences += 1
    words_list = text.split()
    words = len(words_list)

    L = letters * 100 / words
    S = sentences * 100 / words
    index = round(0.0588 * L - 0.296 * S - 15.8)

    if index > 15:
        print('Grade 16+')
    elif index < 1:
        print('Before Grade 1')
    else:
        print(f'Grade: {index}')

main()
