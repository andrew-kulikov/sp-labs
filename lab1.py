import os


def main():
    extension = input()
    outfile = input()
    files = []
    for dirpath, dnames, fnames in os.walk(os.path.abspath(os.sep)):
        for file in fnames:
            if file.endswith(extension):
                files.append(os.path.join(dirpath, file))

    with open(outfile, 'a+', encoding='utf-8') as f:
        f.write(' '.join(files) + ' ')


if __name__ == '__main__':
    main()
