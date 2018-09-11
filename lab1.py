import os


def main():
    extension = input()
    outfile = input()
    files = [f for f in os.listdir('.') if os.path.isfile(f) and os.path.splitext(f)[1] == extension]
    with open(outfile, 'a+', encoding='utf-8') as f:
        f.write(' '.join(files))


if __name__ == '__main__':
    main()
