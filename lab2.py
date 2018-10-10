import os


def main():
    max_size = 0
    file_name = ""
    for dirpath, dnames, fnames in os.walk(os.path.abspath(os.sep)):
        for file in fnames:
            full_name = os.path.join(dirpath, file)
            file_size = os.stat(full_name).st_size
            if file_size > max_size:
                max_size = file_size
                file_name = full_name

    print(file_name, max_size)


if __name__ == '__main__':
    main()
