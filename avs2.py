import threading


def worker():
    for i in range(30):
        print("i from thread", threading.current_thread(), " =", i)


def main():
    threads = []
    for i in range(3):
        t = threading.Thread(target=worker)
        threads.append(t)
        t.start()


if __name__ == "__main__":
    main()
